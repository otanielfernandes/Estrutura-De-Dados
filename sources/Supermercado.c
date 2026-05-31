#include "../includes/Supermercado.h"
#include "../includes/Ficheiro.h"

extern int Aleatorio(int min, int max);
static void OferecerProduto(Cliente *C);

// CRIAR SUPERMERCADO
Supermercado *CriarSupermercado(char *nome)
{
    Supermercado *S = (Supermercado *)malloc(sizeof(Supermercado));

    if (S == NULL)
        return NULL;

    S->NOME = (char *)malloc(strlen(nome) + 1);

    if (S->NOME != NULL)
        strcpy(S->NOME, nome);

    S->Rolex = CriarRelogio(10);

    S->max_espera = 0;
    S->n_caixas = 0;
    S->tempo_atendimento_produto = 0;
    S->max_preco = 0;
    S->max_fila = 0;
    S->min_fila = 0;

    S->CadenciaEntradaClientes = 30;

    S->LProdutos = NULL;
    S->LClientes = NULL;
    S->LFuncionarios = NULL;
    S->HCaixas = NULL;

    S->simulacao_ativa = 1;
    S->totalClientesGerados = 0;
    S->maxClientesSimulacao = 160;
    S->terminarPrograma = 0;
    return S;
}

// INICIALIZAR SUPERMERCADO
int InicializarSupermercado(Supermercado *S, char *config)
{
    if (S == NULL)
        return 0;

    FILE *f = fopen(config, "r");

    if (f == NULL)
    {
        printf("Erro ao abrir ficheiro %s\n", config);
        return 0;
    }

    char tag[50];
    int valor;

    while (fscanf(f, "%s %d", tag, &valor) != EOF)
    {
        if (strcmp(tag, "MAX_ESPERA") == 0)
            S->max_espera = valor;

        else if (strcmp(tag, "N_CAIXAS") == 0)
            S->n_caixas = valor;

        else if (strcmp(tag, "TEMPO_ATENDIMENTO_PRODUTO") == 0)
            S->tempo_atendimento_produto = valor;

        else if (strcmp(tag, "MAX_PRECO") == 0)
            S->max_preco = valor;

        else if (strcmp(tag, "MAX_FILA") == 0)
            S->max_fila = valor;

        else if (strcmp(tag, "MIN_FILA") == 0)
            S->min_fila = valor;
    }

    fclose(f);

    printf("\n===== CONFIGURACOES =====\n");

    printf("MAX_ESPERA: %d\n", S->max_espera);
    printf("N_CAIXAS: %d\n", S->n_caixas);
    printf("TEMPO_ATENDIMENTO_PRODUTO: %d\n", S->tempo_atendimento_produto);
    printf("MAX_PRECO: %d\n", S->max_preco);
    printf("MAX_FILA: %d\n", S->max_fila);
    printf("MIN_FILA: %d\n", S->min_fila);

    /* LISTAS */

    S->LProdutos = CriarListaProdutos();
    S->LClientes = CriarListaClientes();
    S->LFuncionarios = CriarListaFuncionarios();

    /* FICHEIROS */

    LerProdutos(S->LProdutos, "dados/Produtos.txt");
    LerClientes(S->LClientes, "dados/Clientes.txt");
    LerFuncionarios(S->LFuncionarios, "dados/Funcionarios.txt");

    /* MatrizSupermercado */

    S->HCaixas = CriarMatrizSupermercado(S->n_caixas);

    if (S->HCaixas != NULL)
    {
        if (S->n_caixas >= 1)
            ObterCaixa(S->HCaixas, 1)->aberta = 1;

        if (S->n_caixas >= 2)
            ObterCaixa(S->HCaixas, 2)->aberta = 1;
    }

    return 1;
}

// CLIENTE JA ESTA NA FILA
static int ClienteJaNaFila(Supermercado *S, Cliente *C)
{
    if (S == NULL || C == NULL)
        return 0;

    for (int i = 0; i < S->HCaixas->tamanho; i++)
    {
        Caixa *CX = &S->HCaixas->Tabela[i];

        if (CX->fila == NULL)
            continue;

        NoCliente *Aux = CX->fila->Inicio;

        while (Aux != NULL)
        {
            if (Aux->Cli != NULL)
            {
                if (Aux->Cli->id == C->id)
                    return 1;
            }

            Aux = Aux->Prox;
        }
    }

    return 0;
}

// ABRIR NOVA CAIXA
Caixa *AbrirNovaCaixa(Supermercado *S)
{
    if (S == NULL || S->HCaixas == NULL)
        return NULL;

    for (int i = 0; i < S->HCaixas->tamanho; i++)
    {
        Caixa *C = &S->HCaixas->Tabela[i];

        if (!C->aberta)
        {
            C->aberta = 1;

            printf("\nCaixa %d aberta.\n", C->id);

            return C;
        }
    }

    return NULL;
}

// ESCOLHER MELHOR CAIXA
Caixa *EscolherCaixa(Supermercado *S)
{
    if (S == NULL || S->HCaixas == NULL)
        return NULL;

    Caixa *Melhor = NULL;

    float menorTempo = 999999;

    for (int i = 0; i < S->HCaixas->tamanho; i++)
    {
        Caixa *C = &S->HCaixas->Tabela[i];

        if (!C->aberta)
            continue;

        float tempo = CalcularTempoCaixa(C);

        if (tempo < menorTempo)
        {
            menorTempo = tempo;
            Melhor = C;
        }
    }

    return Melhor;
}

// GERAR CARRINHO
void GerarCarrinhoCliente(Supermercado *S, Cliente *C,
                          int quantidade)
{
    if (S == NULL || C == NULL)
        return;

    for (int i = 0; i < quantidade; i++)
    {
        Produto *P = ObterProdutoAleatorio(S->LProdutos);

        if (P != NULL)
        {
            Produto *Novo = CriarProduto(
                P->codigo,
                P->nome,
                P->preco,
                P->tempoCompra,
                P->tempoCaixa);

            InserirProduto(C->carrinho, Novo);
        }
    }
}

// ENTRADA CLIENTE
void EntradaPessoaSupermercado(Supermercado *S)
{
    if (S == NULL)
        return;

    int X = Aleatorio(0, 100);

    if (X >= S->CadenciaEntradaClientes)
        return;

    Cliente *C = NULL;
    int tentativas = 0;

    while (tentativas < 20)
    {
        C = ObterClienteAleatorio(S->LClientes);

        if (C != NULL)
        {
            if (!ClienteJaNaFila(S, C))
                break;
        }

        tentativas++;
    }

    if (C == NULL)
        return;
    C->mudouCaixa = 0;
    C->tempoEspera = 0;
    if (ClienteJaNaFila(S, C))
        return;

    if (C->carrinho != NULL)
        DestruirListaProdutos(C->carrinho);

    C->carrinho = CriarListaProdutos();

    int nProdutos = Aleatorio(1, 20);

    GerarCarrinhoCliente(S, C, nProdutos);

    C->tempoTotalCaixa = CalcularTempoCliente(C);
    C->tempoInicialCaixa = C->tempoTotalCaixa;
    C->mudouCaixa = 0;
    C->tempoEspera = 0;
    Caixa *CX = EscolherCaixa(S);

    if (CX == NULL)
    {
        printf("\nNao existe caixa aberta.\n");
        return;
    }

    float tempoCliente = CalcularTempoCliente(C);

    float tempoCaixa = CalcularTempoCaixa(CX);

    /* ULTRAPASSOU O MAX_ESPERA */
    if ((tempoCaixa + tempoCliente) > S->max_espera)
    {
        /* oferecer produto */
        OferecerProduto(C);

        /* tentar abrir nova caixa */
        Caixa *Nova = AbrirNovaCaixa(S);

        if (Nova != NULL)
            CX = Nova;
    }

    InserirClienteCaixa(CX, C);

    printf("\nCliente %s entrou na Caixa %d\n",
           C->nome,
           CX->id);
}

/*Numero de Caixas Abertas */
static int NumeroCaixasAbertas(Supermercado *S)
{
    if (S == NULL || S->HCaixas == NULL)
        return 0;

    int count = 0;
    for (int i = 0; i < S->HCaixas->tamanho; i++)
    {
        if (S->HCaixas->Tabela[i].aberta)
            count++;
    }
    return count;
}

/*Caixa Menor Fila*/
static Caixa *CaixaMenorFila(Supermercado *S)
{
    Caixa *melhor = NULL;

    int menor = 99999;

    for (int i = 0; i < S->HCaixas->tamanho; i++)
    {
        Caixa *C = &S->HCaixas->Tabela[i];

        if (!C->aberta)
            continue;

        if (C->fila->NEL < menor)
        {
            menor = C->fila->NEL;
            melhor = C;
        }
    }

    return melhor;
}

static Caixa *CaixaMaiorFila(Supermercado *S)
{
    Caixa *maior = NULL;

    int clientes = -1;

    for (int i = 0; i < S->HCaixas->tamanho; i++)
    {
        Caixa *C = &S->HCaixas->Tabela[i];

        if (!C->aberta)
            continue;

        if (C->fila->NEL > clientes)
        {
            clientes = C->fila->NEL;
            maior = C;
        }
    }

    return maior;
}

/*Abertura Automática de Caixa*/
static void VerificarAberturaCaixas(Supermercado *S)
{
    int abertas = NumeroCaixasAbertas(S);

    if (abertas == 0)
        return;

    int soma = 0;

    for (int i = 0; i < S->HCaixas->tamanho; i++)
    {
        Caixa *C = &S->HCaixas->Tabela[i];

        if (C->aberta)
            soma += C->fila->NEL;
    }

    float media = (float)soma / abertas;

    if (media > S->max_fila)
    {
        Caixa *Nova = AbrirNovaCaixa(S);

        if (Nova != NULL)
        {
            printf("\nNova caixa aberta automaticamente.\n");
        }
    }
}

/*Equilibrar Filas */
static void EquilibrarFilas(Supermercado *S)
{
    Caixa *Maior = CaixaMaiorFila(S);
    Caixa *Menor = CaixaMenorFila(S);

    if (Maior == NULL || Menor == NULL)
        return;

    while ((Maior->fila->NEL - Menor->fila->NEL) >= 3)
    {
        Cliente *C = RetirarClienteFim(Maior->fila);

        if (C == NULL)
            return;

        InserirCliente(Menor->fila, C);

        printf("\nCliente mudou da Caixa %d para Caixa %d\n",
               Maior->id,
               Menor->id);

        Maior = CaixaMaiorFila(S);
        Menor = CaixaMenorFila(S);

        if (Maior == NULL || Menor == NULL)
            return;
    }
}

/*Fecho Automático de Caixa*/
static void VerificarFechoCaixas(Supermercado *S)
{
    int abertas = NumeroCaixasAbertas(S);

    if (abertas <= 2)
        return;

    int soma = 0;

    for (int i = 0; i < S->HCaixas->tamanho; i++)
    {
        Caixa *C = &S->HCaixas->Tabela[i];

        if (C->aberta)
            soma += C->fila->NEL;
    }

    float media = (float)soma / abertas;

    if (media >= S->min_fila)
        return;

    for (int i = S->HCaixas->tamanho - 1; i >= 0; i--)
    {
        Caixa *C = &S->HCaixas->Tabela[i];

        if (!C->aberta)
            continue;

        if (C->fila->NEL != 0)
            continue;

        C->aberta = 0;

        printf("\nCaixa %d fechada.\n",
               C->id);

        return;
    }
}

/*Mudança de Fila */
static void VerificarMudancasFila(Supermercado *S)
{
    for (int i = 0; i < S->HCaixas->tamanho; i++)
    {
        Caixa *Origem = &S->HCaixas->Tabela[i];

        if (!Origem->aberta)
            continue;

        if (Origem->fila->NEL < 4)
            continue;

        Caixa *Destino = CaixaMenorFila(S);

        if (Destino == NULL)
            continue;

        if (Destino == Origem)
            continue;

        if ((Origem->fila->NEL - Destino->fila->NEL) < 3)
            continue;

        NoCliente *Aux = Origem->fila->Inicio;

        if (Aux == NULL)
            continue;

        Aux = Aux->Prox;

        if (Aux == NULL)
            continue;
        Cliente *C = RetirarClientePosicao(Origem->fila, 1);

        if (C == NULL)
            continue;

        if (C->mudouCaixa)
        {
            InserirCliente(Origem->fila, C);
            continue;
        }

        int podeMudar = 0;

        if ((Origem->fila->NEL - Destino->fila->NEL) >= 3)
        {
            podeMudar = 1;
        }

        float tempoDestino = CalcularTempoCaixa(Destino);

        if (C->tempoEspera >= (S->max_espera * 0.75) &&
            tempoDestino < C->tempoEspera)
        {
            podeMudar = 1;
        }

        if (podeMudar)
        {
            C->mudouCaixa = 1;

            InserirCliente(Destino->fila, C);

            printf("\nCliente %s mudou da Caixa %d para Caixa %d\n",
                   C->nome,
                   Origem->id,
                   Destino->id);
        }
        else
        {
            InserirCliente(Origem->fila, C);
        }
    }
}

// EXECUTAR SIMULACAO
int ExecutarSimulacao(Supermercado *S)
{
    if (S == NULL)
        return 0;

    EntradaPessoaSupermercado(S);

    VerificarAberturaCaixas(S);

    VerificarMudancasFila(S);

    EquilibrarFilas(S);

    ProcessarCaixas(S->HCaixas);

    VerificarFechoCaixas(S);

    return 1;
}

// Produtos oferecidos
static void OferecerProduto(Cliente *C)
{
    if (C == NULL)
        return;

    if (C->carrinho == NULL)
        return;

    if (C->carrinho->NEL <= 0)
        return;

    NoProduto *Aux = C->carrinho->Inicio;

    while (Aux->Prox != NULL)
    {
        Aux = Aux->Prox;
    }

    if (Aux->Info != NULL)
    {
        Aux->Info->oferecido = 1;

        printf("\nProduto OFERECIDO ao cliente %s: %s\n",
               C->nome,
               Aux->Info->nome);
    }
}

// MEMORIA
size_t MemoriaUtilizada(Supermercado *S)
{
    if (S == NULL)
        return 0;

    size_t mem = sizeof(Supermercado);

    if (S->NOME != NULL)
        mem += strlen(S->NOME) + 1;

    if (S->HCaixas != NULL)
    {
        mem += sizeof(MatrizSupermercado);
        mem += sizeof(Caixa) * S->HCaixas->tamanho;
    }

    return mem;
}

// TERMINAR SIMULACAO
int Supermercado_E_Para_Fechar(Supermercado *S)
{
    if (S == NULL)
        return 1;

    return 0;
}

// DESTRUIR
void DestruirSupermercado(Supermercado *S)
{
    if (S == NULL)
        return;

    if (S->NOME != NULL)
        free(S->NOME);

    if (S->Rolex != NULL)
        free(S->Rolex);

    if (S->LClientes != NULL)
        DestruirListaClientes(S->LClientes);

    if (S->LFuncionarios != NULL)
        DestruirListaFuncionarios(S->LFuncionarios);

    if (S->LProdutos != NULL)
        DestruirListaProdutos(S->LProdutos);

    if (S->HCaixas != NULL)
        DestruirMatrizSupermercado(S->HCaixas);

    free(S);
}
//"Versão 17.10" do projecto supermercad:
#include "../includes/Supermercado.h"
#include "../includes/Ficheiro.h"

extern int Aleatorio(int min, int max);

//---------------------------------------------

Supermercado *CriarSupermercado(char *nome)
{
    Supermercado *S = (Supermercado *)malloc(sizeof(Supermercado));
    //... fazer
    S->Rolex = CriarRelogio(10);
    return S;
}

int InicializarSupermercado(Supermercado *S, char *config)
{
    FILE *f = fopen(config, "r");
    if (f == NULL)
    {
        printf("Erro fatal: Nao foi possivel abrir o ficheiro %s\n", config);
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

    // --- BLOCO DE IMPRESSÃO PARA VERIFICAÇÃO ---
    printf("\n========================================\n");
    printf("   CONFIGURACOES CARREGADAS DO FICHEIRO \n");
    printf("========================================\n");
    printf("MAX_ESPERA: %d\n", S->max_espera);
    printf("N_CAIXAS: %d\n", S->n_caixas);
    printf("TEMPO_ATENDIMENTO: %d\n", S->tempo_atendimento_produto);
    printf("MAX_PRECO: %d\n", S->max_preco);
    printf("MAX_FILA: %d\n", S->max_fila);
    printf("MIN_FILA: %d\n", S->min_fila);
    printf("========================================\n\n");

    S->LProdutos = CriarListaProdutos();
    LerProdutos(S->LProdutos, "dados/Produtos.txt");
    printf("\nPRODUTOS CARREGADOS:\n");
    MostrarListaProdutos(S->LProdutos);

    S->LClientes = CriarListaClientes();
    LerClientes(S->LClientes, "dados/Clientes.txt");
    printf("\nCLIENTES CARREGADOS:\n");
    MostrarListaClientes(S->LClientes);

    S->LFuncionarios = CriarListaFuncionarios();
    LerFuncionarios(S->LFuncionarios, "dados/Funcionarios.txt");
    printf("\nFUNCIONARIOS CARREGADOS:\n");
    MostrarListaFuncionarios(S->LFuncionarios);

    S->CadenciaEntradaClientes = 30;

    // Criando o Hash:
    S->HCaixas = CriarHashing(S->n_caixas);

    // Abrir caixas iniciais:
    ObterCaixa(S->HCaixas, 1)->aberta = 1;
    ObterCaixa(S->HCaixas, 2)->aberta = 1;

    // Ilustrar o estado das caixas:
    printf("\nCAIXAS INICIAIS ABERTAS:\n");
    MostrarHashing(S->HCaixas);

    return 1;
}

int ExecutarSimulacao(Supermercado *S)
{
    printf("Estou a trabalhar...\n");
    EntradaPessoaSupermercado(S);

    EstadoPagamentoIrCaixa(S);

    ProcessarCaixas(S->HCaixas);

    return 1;
}
/*
int IrCaixa(Pessoa *P, Supermercado *S)
{
    //time_t T = GetTempo(S->Rolex);
    //Se (T >=  gfdglkfdglkfdg)
    //    return 1;
    return 0;
}
*/

// Função para abrir uma nova caixa:
Caixa *AbrirNovaCaixa(Supermercado *S)
{
    if (S == NULL)
        return NULL;

    for (int i = 0; i < S->HCaixas->tamanho; i++)
    {
        Caixa *C = &S->HCaixas->Tabela[i];

        if (!C->aberta)
        {
            C->aberta = 1;

            printf("\nCAIXA %d FOI ABERTA!\n", C->id);

            return C;
        }
    }

    return NULL;
}

// Função que compara os tempos de cada caixa e escolhe a caixa com menor tempo:
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

void EstadoPagamentoIrCaixa(Supermercado *S)
{
    // Para todas as Pessoas P da S->LClientes
    //     Se (IrCaixa(P, S))
    {
        // Escolher Caixa e Retirar essa pessoa de S->Clientes
        // e ir para o Hashing das Caixas
    }
}

// Função criada por Otaniel:
// Agora cada cliente poderá ter: 2 produtos, 5 produtos ou 20 produtos aleatórios
void GerarCarrinhoCliente(Supermercado *S, Cliente *C, int quantidade)
{
    if (S == NULL || C == NULL)
        return;

    for (int i = 0; i < quantidade; i++)
    {
        Produto *P = ObterProdutoAleatorio(S->LProdutos);

        if (P != NULL)
        {
            Produto *Novo =
                CriarProduto(
                    P->codigo,
                    P->nome,
                    P->preco,
                    P->tempoCompra,
                    P->tempoCaixa);

            InserirProduto(C->carrinho, Novo);
        }
    }
}

void EntradaPessoaSupermercado(Supermercado *S)
{
    int X = Aleatorio(0, 100);
    // printf("X = %d\n", X);
    if (X < S->CadenciaEntradaClientes)
    {
        Cliente *C = ObterClienteAleatorio(S->LClientes);

        if (C != NULL)
        {
            int nProdutos = Aleatorio(1, 20);

            GerarCarrinhoCliente(S, C, nProdutos);

            float tempoCliente = CalcularTempoCliente(C);

            Caixa *CX = EscolherCaixa(S);

            if (CX != NULL)
            {
                float tempoCaixa = CalcularTempoCaixa(CX);

                if ((tempoCaixa + tempoCliente) > S->max_espera)
                {
                    Caixa *Nova = AbrirNovaCaixa(S);

                    if (Nova != NULL)
                    {
                        CX = Nova;
                    }
                }

                if ((CalcularTempoCaixa(CX) + tempoCliente) <= S->max_espera)
                {
                    InserirClienteCaixa(CX, C);

                    printf("\nCliente %s entrou na Caixa %d\n", C->nome, CX->id);

                    printf("Tempo Cliente: %.2f\n", tempoCliente);

                    printf("Tempo Caixa: %.2f\n", CalcularTempoCaixa(CX));
                }

                // A cada 5 ciclos o sistema mostra o estado atualizado das caixas.
                static int contador = 0;
                contador++;
                if (contador % 5 == 0)
                {
                    MostrarHashing(S->HCaixas);
                }

                else
                {
                    printf("\nTODAS AS CAIXAS ESTAO CHEIAS!\n");
                }
            }
        }
    }
    //---------------------
}

size_t MemoriaUtilizada(Supermercado *S)
{
    if (S == NULL)
        return 0;

    size_t mem = 0;

    /* Estrutura principal */
    mem += sizeof(Supermercado);

    /* Nome do supermercado */
    if (S->NOME != NULL)
        mem += strlen(S->NOME) + 1;

    /* Relógio */
    if (S->Rolex != NULL)
        mem += sizeof(Relogio);

    /* =========================
       LISTA DE CLIENTES
       ========================= */
    if (S->LClientes != NULL)
    {
        mem += sizeof(ListaClientes);

        NoCliente *aux = S->LClientes->Inicio;

        while (aux != NULL)
        {
            mem += sizeof(NoCliente);

            if (aux->Cli != NULL)
            {
                mem += sizeof(Cliente);

                if (aux->Cli->nome != NULL)
                    mem += strlen(aux->Cli->nome) + 1;

                /* Carrinho do cliente */
                if (aux->Cli->carrinho != NULL)
                {
                    mem += sizeof(ListaProdutos);

                    NoProduto *p = aux->Cli->carrinho->Inicio;

                    while (p != NULL)
                    {
                        mem += sizeof(NoProduto);

                        if (p->Info != NULL)
                        {
                            mem += sizeof(Produto);

                            if (p->Info->nome != NULL)
                                mem += strlen(p->Info->nome) + 1;
                        }

                        p = p->Prox;
                    }
                }
            }

            aux = aux->Prox;
        }
    }

    /* =========================
       LISTA DE FUNCIONÁRIOS
       ========================= */
    if (S->LFuncionarios != NULL)
    {
        mem += sizeof(ListaFuncionarios);

        NoFuncionario *aux = S->LFuncionarios->Inicio;

        while (aux != NULL)
        {
            mem += sizeof(NoFuncionario);

            if (aux->Func != NULL)
            {
                mem += sizeof(Funcionario);

                if (aux->Func->nome != NULL)
                    mem += strlen(aux->Func->nome) + 1;
            }

            aux = aux->Prox;
        }
    }

    /* =========================
       LISTA DE PRODUTOS
       ========================= */
    if (S->LProdutos != NULL)
    {
        mem += sizeof(ListaProdutos);

        NoProduto *aux = S->LProdutos->Inicio;

        while (aux != NULL)
        {
            mem += sizeof(NoProduto);

            if (aux->Info != NULL)
            {
                mem += sizeof(Produto);

                if (aux->Info->nome != NULL)
                    mem += strlen(aux->Info->nome) + 1;
            }

            aux = aux->Prox;
        }
    }

    /* =========================
       HASHING DAS CAIXAS
       ========================= */
    if (S->HCaixas != NULL)
    {
        mem += sizeof(Hashing);

        if (S->HCaixas->Tabela != NULL)
        {
            mem += S->HCaixas->tamanho * sizeof(Caixa);

            for (int i = 0; i < S->HCaixas->tamanho; i++)
            {
                Caixa *C = &S->HCaixas->Tabela[i];

                /* Filas das caixas */
                if (C->fila != NULL)
                {
                    mem += sizeof(ListaClientes);

                    NoCliente *aux = C->fila->Inicio;

                    while (aux != NULL)
                    {
                        /*
                           IMPORTANTE:
                           Só contamos o nó da fila.
                           NÃO contamos Cliente novamente
                           porque ele já foi contado
                           na ListaClientes principal.
                        */
                        mem += sizeof(NoCliente);

                        aux = aux->Prox;
                    }
                }
            }
        }
    }

    return mem;
}

int Supermercado_E_Para_Fechar(Supermercado *S)
{
    //... fazer
    return 0;
}

void DestruirSupermercado(Supermercado *S)
{
    free(S->Rolex);
    free(S);
}

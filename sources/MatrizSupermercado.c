#include "../includes/MatrizSupermercado.h"
#include "../includes/Cliente.h"

extern float CalcularTempoCliente(Cliente *C);

MatrizSupermercado *CriarMatrizSupermercado(int tamanho)
{
    MatrizSupermercado *H = (MatrizSupermercado *)malloc(sizeof(MatrizSupermercado));
    if (H == NULL)
        return NULL;

    H->tamanho = tamanho;
    H->Tabela = (Caixa *)malloc(sizeof(Caixa) * tamanho);
    if (H->Tabela == NULL)
    {
        free(H);
        return NULL;
    }

    for (int i = 0; i < tamanho; i++)
    {
        H->Tabela[i].id = i + 1;
        H->Tabela[i].aberta = 0;
        H->Tabela[i].fila = CriarListaClientes();
        H->Tabela[i].totalPessoasAtendidas = 0;
        H->Tabela[i].totalProdutosVendidos = 0;
        H->Tabela[i].maxClientesFila = 0;
        H->Tabela[i].tempoTotalAtendimento = 0;
    }
    return H;
}

// Calcula o tempo total de atendimento de uma caixa somando o tempo de cada cliente na fila
float CalcularTempoCaixa(Caixa *C)
{
    if (C == NULL || C->fila == NULL)
        return 0;

    float total = 0;
    NoCliente *Aux = C->fila->Inicio;
    while (Aux != NULL)
    {
        /* Usa tempoTotalCaixa se já foi inicializado, senão calcula */
        if (Aux->Cli->tempoTotalCaixa > 0)
            total += Aux->Cli->tempoTotalCaixa;
        else
            total += CalcularTempoCliente(Aux->Cli);
        Aux = Aux->Prox;
    }
    return total;
}

int FuncaoHash(MatrizSupermercado *H, int idCaixa)
{
    return (idCaixa - 1) % H->tamanho;
}

int InserirClienteCaixa(Caixa *C, Cliente *Cli)
{
    if (C == NULL || Cli == NULL)
        return 0;

    InserirCliente(C->fila, Cli);

    /* atualizar máximo da fila */

    if (C->fila->NEL > C->maxClientesFila)
        C->maxClientesFila = C->fila->NEL;

    return 1;
}

/* A cada ciclo desconta TICK de tempo ao cliente na frente de cada caixa */
void ProcessarCaixas(MatrizSupermercado *H)
{
    
    if (H == NULL)
        return;

    //A diferença entre TICk = 5 e TICK é que o TICK 1 faz com que o cliente demore mais tempoa para sair da fila/caixa:
    const int TICK = 1;

    for (int i = 0; i < H->tamanho; i++)
    {
        Caixa *C = &H->Tabela[i];

        if (!C->aberta)
            continue;

        if (C->fila == NULL)
            continue;

        if (C->fila->Inicio == NULL)
            continue;

        /* Atualizar tempo de espera de todos */
        NoCliente *Aux = C->fila->Inicio->Prox;

        while (Aux != NULL)
        {
            Aux->Cli->tempoEspera += TICK;
            Aux = Aux->Prox;
        }

        /* Cliente que está a ser atendido */
        Cliente *Cli = C->fila->Inicio->Cli;

        if (Cli == NULL)
            continue;

        Cli->tempoTotalCaixa -= TICK;

        if (Cli->tempoTotalCaixa <= 0)
        {
            /* Estatísticas da caixa */
            C->tempoTotalAtendimento += Cli->tempoInicialCaixa;

          
                
            
            if ((Cli->carrinho != NULL) && (Cli->carrinho->NEL > 0) &&
            (Cli->tempoEspera > 120))
            {
                NoProduto *Aux = Cli->carrinho->Inicio;

                while (Aux != NULL && Aux->Prox != NULL)
                    Aux = Aux->Prox;

                if (Aux != NULL && Aux->Info != NULL)
                {
                    Aux->Info->oferecido = 1;

                    printf("\n[OFERTA] - Cliente: %s\n", Cli->nome);

                    printf("            Produto: %s\n", Aux->Info->nome);
                }
            }


            if (Cli->carrinho != NULL)
            {
                int vendidos = 0;

                NoProduto *P = Cli->carrinho->Inicio;

                while (P != NULL)
                {
                    if (!P->Info->oferecido)
                        vendidos++;

                    P = P->Prox;
                }

                C->totalProdutosVendidos += vendidos;
            }

            printf("\nCliente %s terminou atendimento na Caixa %d\n",
                   Cli->nome,
                   C->id);

            /* Libertar carrinho utilizado */
            if (Cli->carrinho != NULL)
            {
                DestruirListaProdutos(Cli->carrinho);
                Cli->carrinho = NULL;
            }

            /* Reiniciar dados do cliente */
            Cli->tempoTotalCaixa = 0;
            Cli->tempoInicialCaixa = 0;
            Cli->tempoEspera = 0;
            Cli->mudouCaixa = 0;

            /* Remover da fila */
            RemoverClienteInicio(C->fila);

            C->totalPessoasAtendidas++;
        }
    }
}

/*Numero de Clientes na Fila*/
int NumeroClientesFila(Caixa *C)
{
    if (C == NULL || C->fila == NULL)
        return 0;

    return C->fila->NEL;
}

/*Obter Caixa por ID*/
Caixa *ObterCaixa(MatrizSupermercado *H, int idCaixa)
{
    int indice = FuncaoHash(H, idCaixa);
    return &H->Tabela[indice];
}

void MostrarMatrizSupermercado(MatrizSupermercado *H)
{
    if (H == NULL)
        return;

    printf("\n╔════════════════════════════════════════════════╗\n");
    printf("║            ESTADO DAS CAIXAS                   ║\n");
    printf("╚════════════════════════════════════════════════╝\n");

    for (int i = 0; i < H->tamanho; i++)
    {
        Caixa *C = &H->Tabela[i];

        printf("\n[CAIXA %d]\n", C->id);
        printf("Estado      : %s\n", C->aberta ? "ABERTA" : "FECHADA");
        printf("Fila        : %d clientes\n", C->fila ? C->fila->NEL : 0);
        printf("Atendidos   : %d\n", C->totalPessoasAtendidas);
        printf("Vendidos    : %d produtos\n", C->totalProdutosVendidos);
        printf("Máx fila    : %d\n", C->maxClientesFila);
    }

    printf("\n╚════════════════════════════════════════════════╝\n");
}

void DestruirMatrizSupermercado(MatrizSupermercado *H)
{
    if (H == NULL)
        return;
    for (int i = 0; i < H->tamanho; i++)
        DestruirListaClientesSemClientes(H->Tabela[i].fila);
    free(H->Tabela);
    free(H);
}

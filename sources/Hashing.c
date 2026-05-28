#include "../includes/Hashing.h"
#include "../includes/Cliente.h"

extern float CalcularTempoCliente(Cliente *C);

Hashing *CriarHashing(int tamanho)
{
    Hashing *H = (Hashing *)malloc(sizeof(Hashing));
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

int FuncaoHash(Hashing *H, int idCaixa)
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
void ProcessarCaixas(Hashing *H)
{
    if (H == NULL)
        return;

    const int TICK = 5;

    for (int i = 0; i < H->tamanho; i++)
    {
        Caixa *C = &H->Tabela[i];
        if (!C->aberta)
            continue;
        if (C->fila == NULL || C->fila->Inicio == NULL)
            continue;

        Cliente *Cli = C->fila->Inicio->Cli;
        if (Cli == NULL)
            continue;

        Cli->tempoTotalCaixa -= TICK;

        if (Cli->tempoTotalCaixa <= 0)
        {
            //Somar tempo total de atendimento:
            C->tempoTotalAtendimento += Cli->tempoInicialCaixa;
            /* Contar produtos vendidos */
            if (Cli->carrinho != NULL)
                C->totalProdutosVendidos += Cli->carrinho->NEL;

            printf("\nCliente %s terminou atendimento na Caixa %d\n",
                   Cli->nome, C->id);
            
            
            RemoverClienteInicio(C->fila);
            C->totalPessoasAtendidas++;
        }
    }
}

Caixa *ObterCaixa(Hashing *H, int idCaixa)
{
    int indice = FuncaoHash(H, idCaixa);
    return &H->Tabela[indice];
}

void MostrarHashing(Hashing *H)
{
    if (H == NULL)
        return;

    printf("\n========== ESTADO DAS CAIXAS ==========\n");
    for (int i = 0; i < H->tamanho; i++)
    {
        Caixa *C = &H->Tabela[i];
        printf("Caixa %d | %s | Fila: %d | Atendidos: %d | Produtos vendidos: %d\n",
               C->id,
               C->aberta ? "ABERTA " : "FECHADA",
               C->fila ? C->fila->NEL : 0,
               C->totalPessoasAtendidas,
               C->totalProdutosVendidos);
    }
    printf("========================================\n");
}

void DestruirHashing(Hashing *H)
{
    if (H == NULL)
        return;
    for (int i = 0; i < H->tamanho; i++)
        DestruirListaClientesSemClientes(H->Tabela[i].fila);
    free(H->Tabela);
    free(H);
}

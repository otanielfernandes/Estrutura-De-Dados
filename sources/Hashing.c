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
    }

    return H;
}

//Função para calcular o tempo total de cada caixa (Fila):
float CalcularTempoCaixa(Caixa *C)
{
    if (C == NULL || C->fila == NULL)
        return 0;

    float total = 0;

    NoCliente *Aux = C->fila->Inicio;

    while (Aux != NULL)
    {
        total += CalcularTempoCliente(Aux->Cli);

        Aux = Aux->Prox;
    }

    return total;
}




int FuncaoHash(Hashing *H, int idCaixa)
{
    return (idCaixa - 1) % H->tamanho;
}

//Função para inserir um cliente na Caixa(Fila):
int InserirClienteCaixa(Caixa *C, Cliente *Cli)
{
    if (C == NULL || Cli == NULL)
        return 0;

    return InserirCliente(C->fila, Cli);
}

//Função para atender clientes:
void ProcessarCaixas(Hashing *H)
{
    if (H == NULL)
        return;

    for (int i = 0; i < H->tamanho; i++)
    {
        Caixa *C = &H->Tabela[i];

        if (C->aberta)
        {
            if (C->fila != NULL)
            {
                if (C->fila->Inicio != NULL)
                {
                    Cliente *Cli = C->fila->Inicio->Cli;
                    if (Cli != NULL)
                    {
                        Cli->tempoTotalCaixa -= 5;

                        if (Cli->tempoTotalCaixa <= 0)
                        {
                            printf(
                                "\nCliente %s terminou atendimento na Caixa %d\n",
                                Cli->nome,
                                C->id
                            );

                            RemoverClienteInicio(C->fila);

                            C->totalPessoasAtendidas++;
                        }
                    }
                }
            }
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

    for (int i = 0; i < H->tamanho; i++)
    {
        Caixa *C = &H->Tabela[i];

        printf("\n===== CAIXA %d =====\n", C->id);

        if (C->aberta)
            printf("Estado: ABERTA\n");
        else
            printf("Estado: FECHADA\n");

        printf("Clientes na fila: %d\n", C->fila->NEL);
    }
}

void DestruirHashing(Hashing *H)
{
    if (H == NULL)
        return;

    for (int i = 0; i < H->tamanho; i++)
    {
        DestruirListaClientes(H->Tabela[i].fila);
    }

    free(H->Tabela);

    free(H);
}
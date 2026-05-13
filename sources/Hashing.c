#include "../includes/Hashing.h"

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

        H->Tabela[i].fila = CriarListaPessoas();

        H->Tabela[i].totalPessoasAtendidas = 0;

        H->Tabela[i].totalProdutosVendidos = 0;
    }

    return H;
}

int FuncaoHash(Hashing *H, int idCaixa)
{
    return idCaixa % H->tamanho;
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
        DestruirListaPessoas(H->Tabela[i].fila);
    }

    free(H->Tabela);

    free(H);
}
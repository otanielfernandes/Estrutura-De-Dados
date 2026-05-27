#include "../includes/Cliente.h"
#include "../includes/ListaProdutos.h"
#include <time.h>

Cliente *CriarCliente(int id, char *nome)
{
    Cliente *C = (Cliente *)malloc(sizeof(Cliente));

    if (C == NULL)
        return NULL;

    C->id = id;

    C->nome = (char *)malloc(strlen(nome) + 1);
    if (C->nome == NULL)
    {
        free(C);
        return NULL;
    }
    strcpy(C->nome, nome);

    C->carrinho = CriarListaProdutos();
    C->tempoTotalCaixa = 0;
    C->tempoEntrada = time(NULL);

    return C;
}

// Função para calcular o tempo total de caixa de cada cliente:
float CalcularTempoCliente(Cliente *C)
{
    if (C == NULL || C->carrinho == NULL)
        return 0;

    float total = 0;

    NoProduto *Aux = C->carrinho->Inicio;

    while (Aux != NULL)
    {
        Produto *P = Aux->Info;

        total += 2 + (P->preco * (4.0 / 40.0));

        Aux = Aux->Prox;
    }

    return total;
}

void MostrarCliente(Cliente *C)
{
    if (C == NULL)
        return;

    printf("Cliente: %d | %s\n", C->id, C->nome);
}

void DestruirCliente(Cliente *C)
{
    if (C == NULL)
        return;

    free(C->nome);
    DestruirListaProdutos(C->carrinho);
    free(C);
}
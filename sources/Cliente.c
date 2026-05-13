#include "../includes/Cliente.h"

Cliente *CriarCliente(Pessoa *dados)
{
    Cliente *C = (Cliente *)malloc(sizeof(Cliente));

    if (C == NULL)
        return NULL;

    C->dados = dados;
    C->carrinho = CriarListaProdutos();
    C->tempoTotalCaixa = 0;
    C->tempoEntrada = time(NULL);

    return C;
}

void MostrarCliente(Cliente *C)
{
    if (C == NULL)
        return;

    printf("Cliente: %d | %s\n", C->dados->codigo, C->dados->nome);
}

void DestruirCliente(Cliente *C)
{
    if (C == NULL)
        return;

    DestruirPessoa(C->dados);
    DestruirListaProdutos(C->carrinho);
    free(C);
}
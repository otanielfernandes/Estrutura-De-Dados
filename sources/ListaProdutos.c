#include "../includes/ListaProdutos.h"

ListaProdutos *CriarListaProdutos()
{
    ListaProdutos *LProd =
        (ListaProdutos *)malloc(sizeof(ListaProdutos));

    if (LProd == NULL)
        return NULL;

    LProd->Inicio = NULL;

    LProd->NEL = 0;

    return LProd;
}

//Procedimento para inserir produto:
int InserirProduto(ListaProdutos *LProd, Produto *Prod)
{
    if (LProd == NULL || Prod == NULL)
        return INSUCESSO;

    NoProduto *novo =
        (NoProduto *)malloc(sizeof(NoProduto));

    if (novo == NULL)
        return INSUCESSO;

    novo->Info = Prod;
    novo->Prox = LProd->Inicio;
    LProd->Inicio = novo;
    LProd->NEL++;

    return SUCESSO;
}


void MostrarListaProdutos(ListaProdutos *LProd)
{
    if (LProd == NULL)
        return;

    NoProduto *aux = LProd->Inicio;

    while (aux != NULL)
    {
        MostrarProduto(aux->Info);
        aux = aux->Prox;
    }
}

void DestruirListaProdutos(ListaProdutos *LProd)
{
    if (LProd == NULL)
        return;

    NoProduto *aux = LProd->Inicio;

    while (aux != NULL)
    {
        NoProduto *temp = aux;
        aux = aux->Prox;
        DestruirProduto(temp->Info);
        free(temp);
    }

    free(LProd);
}


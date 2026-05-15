#include <stdio.h>
#include <stdlib.h>

#include "../includes/ListaProdutos.h"

ListaProdutos *CriarListaProdutos()
{
    ListaProdutos *LProd = (ListaProdutos *)malloc(sizeof(ListaProdutos));

    if (LProd == NULL)
        return NULL;

    LProd->Inicio = NULL;
    LProd->Fim = NULL;
    LProd->NEL = 0;

    return LProd;
}

int InserirProduto(ListaProdutos *LProd, Produto *Prod)
{
    if (LProd == NULL || Prod == NULL)
        return INSUCESSO;

    NoProduto *Novo =
        (NoProduto *)malloc(sizeof(NoProduto));

    if (Novo == NULL)
        return INSUCESSO;

    Novo->Info = Prod;

    Novo->Prox = LProd->Inicio;

    LProd->Inicio = Novo;

    if (LProd->Fim == NULL)
        LProd->Fim = Novo;

    LProd->NEL++;

    return SUCESSO;
}

void InverterListaProdutos(ListaProdutos *LProd)
{
    if (LProd == NULL)
        return;

    NoProduto *anterior = NULL;

    NoProduto *atual = LProd->Inicio;

    NoProduto *seguinte;

    LProd->Fim = LProd->Inicio;

    while (atual != NULL)
    {
        seguinte = atual->Prox;

        atual->Prox = anterior;

        anterior = atual;

        atual = seguinte;
    }

    LProd->Inicio = anterior;
}

void MostrarListaProdutos(ListaProdutos *LProd)
{
    if (LProd == NULL)
        return;

    NoProduto *Aux = LProd->Inicio;

    while (Aux != NULL)
    {
        MostrarProduto(Aux->Info);

        Aux = Aux->Prox;
    }
}

void DestruirListaProdutos(ListaProdutos *LProd)
{
    if (LProd == NULL)
        return;

    NoProduto *Aux = LProd->Inicio;

    while (Aux != NULL)
    {
        NoProduto *Temp = Aux;

        Aux = Aux->Prox;

        DestruirProduto(Temp->Info);

        free(Temp);
    }

    free(LProd);
}
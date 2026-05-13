#include <stdio.h>
#include <stdlib.h>

#include "../includes/ListaFuncionarios.h"

#define SUCESSO 1
#define INSUCESSO 0


ListaFuncionarios *CriarListaFuncionarios()
{
    ListaFuncionarios *LF =
     (ListaFuncionarios *)malloc(sizeof(ListaFuncionarios));

    if (LF == NULL)
        return NULL;

    LF->Inicio = NULL;
    LF->NEL = 0;

    return LF;
}


int InserirFuncionario(ListaFuncionarios *LF, Funcionario *F)
{
    if (LF == NULL || F == NULL)
        return INSUCESSO;

    NoFuncionario *novo = (NoFuncionario *)malloc(sizeof(NoFuncionario));

    if (novo == NULL)
        return INSUCESSO;

    novo->Func = F;
    novo->Prox = NULL;

    if (LF->Inicio == NULL)
    {
        LF->Inicio = novo;
    }

    else
    {
        NoFuncionario *aux = LF->Inicio;

        while (aux->Prox != NULL)
            aux = aux->Prox;

        aux->Prox = novo;
    }

    LF->NEL++;

    return SUCESSO;
}


void MostrarListaFuncionarios(ListaFuncionarios *LF)
{
    if (LF == NULL)
        return;

    NoFuncionario *aux = LF->Inicio;

    while (aux != NULL)
    {
        MostrarFuncionario(aux->Func);
        aux = aux->Prox;
    }
}


void DestruirListaFuncionarios(ListaFuncionarios *LF)
{
    if (LF == NULL)
        return;

    NoFuncionario *aux = LF->Inicio;

    while (aux != NULL)
    {
        NoFuncionario *temp = aux;
        aux = aux->Prox;

        DestruirFuncionario(temp->Func);
        free(temp);
    }

    free(LF);
}
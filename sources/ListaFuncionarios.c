#include <stdio.h>
#include <stdlib.h>

#include "../includes/ListaFuncionarios.h"

extern int Aleatorio(int min, int max);

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
        return 0;

    NoFuncionario *Novo = (NoFuncionario *)malloc(sizeof(NoFuncionario));

    if (Novo == NULL)
        return 0;

    Novo->Func = F;

    Novo->Prox = LF->Inicio;

    LF->Inicio = Novo;

    LF->NEL++;

    return 1;
}

void InverterListaFuncionarios(ListaFuncionarios *LF)
{
    if (LF == NULL)
        return;

    NoFuncionario *anterior = NULL;

    NoFuncionario *atual = LF->Inicio;

    NoFuncionario *seguinte;

    while (atual != NULL)
    {
        seguinte = atual->Prox;

        atual->Prox = anterior;

        anterior = atual;

        atual = seguinte;
    }

    LF->Inicio = anterior;
}



void MostrarListaFuncionarios(ListaFuncionarios *LF)
{
    if (LF == NULL)
        return;

    NoFuncionario *Aux = LF->Inicio;

    while (Aux != NULL)
    {
        MostrarFuncionario(Aux->Func);
        Aux = Aux->Prox;
    }
}

Funcionario *ObterFuncionarioAleatorio(ListaFuncionarios *LF)
{
    if (LF == NULL || LF->NEL == 0)
        return NULL;

    int indice = Aleatorio(0, LF->NEL - 1);

    NoFuncionario *Aux = LF->Inicio;

    for (int i = 0; i < indice; i++)
    {
        Aux = Aux->Prox;
    }

    return Aux->Func;
}

void DestruirListaFuncionarios(ListaFuncionarios *LF)
{
    if (LF == NULL)
        return;

    NoFuncionario *Aux = LF->Inicio;

    while (Aux != NULL)
    {
        NoFuncionario *Temp = Aux;

        Aux = Aux->Prox;

        DestruirFuncionario(Temp->Func);

        free(Temp);
    }

    free(LF);
}
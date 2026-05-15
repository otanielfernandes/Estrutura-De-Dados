#include <stdio.h>
#include <stdlib.h>

#include "../includes/ListaClientes.h"

ListaClientes *CriarListaClientes()
{
    ListaClientes *LC =  (ListaClientes *)malloc(sizeof(ListaClientes));

    if (LC == NULL)
        return NULL;

    LC->Inicio = NULL;
    LC->NEL = 0;

    return LC;
}

int InserirCliente(ListaClientes *LC, Cliente *C)
{
    if (LC == NULL || C == NULL)
        return 0;

    NoCliente *Novo = (NoCliente *)malloc(sizeof(NoCliente));

    if (Novo == NULL)
        return 0;

    Novo->Cli = C;

    Novo->Prox = LC->Inicio;

    LC->Inicio = Novo;

    LC->NEL++;

    return 1;
}

void InverterListaClientes(ListaClientes *LC)
{
    if (LC == NULL)
        return;

    NoCliente *anterior = NULL;

    NoCliente *atual = LC->Inicio;

    NoCliente *seguinte;

    while (atual != NULL)
    {
        seguinte = atual->Prox;

        atual->Prox = anterior;

        anterior = atual;

        atual = seguinte;
    }

    LC->Inicio = anterior;
}

void MostrarListaClientes(ListaClientes *LC)
{
    if (LC == NULL)
        return;

    NoCliente *Aux = LC->Inicio;

    while (Aux != NULL)
    {
        MostrarCliente(Aux->Cli);

        Aux = Aux->Prox;
    }
}

void DestruirListaClientes(ListaClientes *LC)
{
    if (LC == NULL)
        return;

    NoCliente *Aux = LC->Inicio;

    while (Aux != NULL)
    {
        NoCliente *Temp = Aux;

        Aux = Aux->Prox;

        DestruirCliente(Temp->Cli);

        free(Temp);
    }

    free(LC);
}
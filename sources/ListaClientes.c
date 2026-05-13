#include <stdio.h>
#include <stdlib.h>

#include "../includes/ListaClientes.h"

#define SUCESSO 1
#define INSUCESSO 0


ListaClientes *CriarListaClientes()
{
    ListaClientes *LC =(ListaClientes *)malloc(sizeof(ListaClientes));

    if (LC == NULL)
        return NULL;

    LC->Inicio = NULL;
    LC->NEL = 0;

    return LC;
}


int InserirCliente(ListaClientes *LC, Cliente *C
)
{
    if (LC == NULL || C == NULL)
        return INSUCESSO;

    NoCliente *novo = (NoCliente *)malloc(sizeof(NoCliente));

    if (novo == NULL)
        return INSUCESSO;

    novo->Cli = C;
    novo->Prox = NULL;

    if (LC->Inicio == NULL)
    {
        LC->Inicio = novo;
    }
    else
    {
        NoCliente *aux = LC->Inicio;

        while (aux->Prox != NULL)
            aux = aux->Prox;
        aux->Prox = novo;
    }
    LC->NEL++;

    return SUCESSO;
}

void MostrarListaClientes(ListaClientes *LC)
{
    if (LC == NULL)
        return;

    NoCliente *aux = LC->Inicio;

    while (aux != NULL)
    {
        MostrarCliente(aux->Cli);
        aux = aux->Prox;
    }
}

void DestruirListaClientes(ListaClientes *LC)
{
    if (LC == NULL)
        return;

    NoCliente *aux = LC->Inicio;

    while (aux != NULL)
    {
        NoCliente *temp = aux;

        aux = aux->Prox;

        DestruirCliente(temp->Cli);
        free(temp);
    }

    free(LC);
}
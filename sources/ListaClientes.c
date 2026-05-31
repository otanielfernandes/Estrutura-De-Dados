#include <stdio.h>
#include <stdlib.h>

#include "../includes/ListaClientes.h"

extern int Aleatorio(int min, int max);

ListaClientes *CriarListaClientes()
{
    ListaClientes *LC = (ListaClientes *)malloc(sizeof(ListaClientes));

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

/*Esta função escolhe um indice aleatório, percorre a lista e devolve um cliente aleatório*/
Cliente *ObterClienteAleatorio(ListaClientes *LC)
{
    if (LC == NULL || LC->NEL == 0)
        return NULL;

    int indice = Aleatorio(0, LC->NEL - 1);

    NoCliente *Aux = LC->Inicio;

    for (int i = 0; i < indice; i++)
    {
        Aux = Aux->Prox;
    }

    return Aux->Cli;
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

int RemoverClienteInicio(ListaClientes *LC)
{
    if (LC == NULL || LC->Inicio == NULL)
        return 0;

    NoCliente *Aux = LC->Inicio;

    LC->Inicio = Aux->Prox;

    // DestruirCliente(Aux->Cli);
    free(Aux);

    LC->NEL--;

    return 1;
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
Cliente *RetirarClienteFim(ListaClientes *LC)
{
    if (LC == NULL || LC->Inicio == NULL)
        return NULL;

    NoCliente *Atual = LC->Inicio;
    NoCliente *Anterior = NULL;

    while (Atual->Prox != NULL)
    {
        Anterior = Atual;
        Atual = Atual->Prox;
    }

    Cliente *C = Atual->Cli;

    if (Anterior == NULL)
    {
        LC->Inicio = NULL;
    }
    else
    {
        Anterior->Prox = NULL;
    }

    free(Atual);

    LC->NEL--;

    return C;
}

Cliente *RetirarClientePosicao(ListaClientes *LC, int posicao)
{
    if (LC == NULL)
        return NULL;

    if (LC->Inicio == NULL)
        return NULL;

    if (posicao < 0)
        return NULL;

    if (posicao >= LC->NEL)
        return NULL;

    NoCliente *Atual = LC->Inicio;
    NoCliente *Anterior = NULL;

    for (int i = 0; i < posicao; i++)
    {
        Anterior = Atual;
        Atual = Atual->Prox;
    }

    Cliente *C = Atual->Cli;

    if (Anterior == NULL)
    {
        LC->Inicio = Atual->Prox;
    }
    else
    {
        Anterior->Prox = Atual->Prox;
    }

    free(Atual);

    LC->NEL--;

    return C;
}

void DestruirListaClientesSemClientes(ListaClientes *LC)
{
    if (LC == NULL)
        return;

    NoCliente *Aux = LC->Inicio;

    while (Aux != NULL)
    {
        NoCliente *Temp = Aux;
        Aux = Aux->Prox;

        free(Temp);
    }

    free(LC);
}
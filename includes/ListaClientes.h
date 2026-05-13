#ifndef LISTACLIENTES_H
#define LISTACLIENTES_H

#include "Cliente.h"

typedef struct NoCliente
{
    Cliente *Cli;
    struct NoCliente *Prox;
} NoCliente;


typedef struct
{
    NoCliente *Inicio;
    int NEL;
} ListaClientes;


ListaClientes *CriarListaClientes();
int InserirCliente(ListaClientes *LC, Cliente *C);
void MostrarListaClientes(ListaClientes *LC);
void DestruirListaClientes(ListaClientes *LC);

#endif
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
    /* NOVO CAMPO possivel para a estrutura da lista de clientes:
        NoCliente *Fim; // Para facilitar inserções no final da fila
    */
    int NEL;
} ListaClientes;

ListaClientes *CriarListaClientes();
int InserirCliente(ListaClientes *LC, Cliente *C);
void InverterListaClientes(ListaClientes *LC);
Cliente *ObterClienteAleatorio(ListaClientes *LC);
void MostrarListaClientes(ListaClientes *LC);
int RemoverClienteInicio(ListaClientes *LC);
void DestruirListaClientes(ListaClientes *LC);
void DestruirListaClientesSemClientes(ListaClientes *LC);
Cliente *RetirarClienteFim(ListaClientes *LC);
Cliente *RetirarClientePosicao(ListaClientes *LC, int posicao);

#endif
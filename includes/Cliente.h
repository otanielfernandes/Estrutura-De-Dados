#ifndef CLIENTE_H
#define CLIENTE_H

#include <time.h>
#include "ListaProdutos.h"

typedef struct
{
    int id;
    char *nome;
    ListaProdutos *carrinho;
    int tempoTotalCaixa;
    time_t tempoEntrada;

} Cliente;

Cliente *CriarCliente(int id, char *nome);
void MostrarCliente(Cliente *C);
void DestruirCliente(Cliente *C);

#endif
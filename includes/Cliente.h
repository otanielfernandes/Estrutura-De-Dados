#ifndef CLIENTE_H
#define CLIENTE_H

#include <time.h>
#include "Pessoa.h"
#include "ListaProdutos.h"

typedef struct
{
    Pessoa *dados;
    ListaProdutos *carrinho;
    float tempoTotalCaixa;
    time_t tempoEntrada;

}Cliente;

Cliente *CriarCliente(Pessoa *dados);
void MostrarCliente(Cliente *C);
void DestruirCliente(Cliente *C);

#endif
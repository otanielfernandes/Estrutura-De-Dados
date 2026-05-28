#ifndef CLIENTE_H
#define CLIENTE_H

#include <time.h>
#include "ListaProdutos.h"

typedef struct
{
    int id;
    char *nome;
    ListaProdutos *carrinho;
    //Alterei o tipo de dado do campo abaixo, era int, passou a ser float:
    float tempoTotalCaixa;
    float tempoInicialCaixa;
    time_t tempoEntrada;

} Cliente;

Cliente *CriarCliente(int id, char *nome);
float CalcularTempoCliente(Cliente *C);
void MostrarCliente(Cliente *C);
void DestruirCliente(Cliente *C);

#endif
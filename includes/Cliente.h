#ifndef CLIENTE_H
#define CLIENTE_H

#include <time.h>
#include "ListaProdutos.h"

typedef struct
{
    int id;
    char *nome;
    ListaProdutos *carrinho;
    float tempoTotalCaixa;   // Tempo total que o cliente passará na caixa (soma dos tempos dos produtos)
    float tempoInicialCaixa; // Tempo inicial calculado para a caixa (sem descontos)
    time_t tempoEntrada;

} Cliente;

Cliente *CriarCliente(int id, char *nome);
float CalcularTempoCliente(Cliente *C);
void MostrarCliente(Cliente *C);
void DestruirCliente(Cliente *C);

#endif
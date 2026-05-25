#ifndef ESTATISTICAS_H
#define ESTATISTICAS_H

#include <stdio.h>
#include "Menu.h"

typedef struct
{
    int idCaixaMaisPessoas;
    int idCaixaMenosPessoas;
    int produtosOferecidos;
    float custoOferecidos;
    int idCaixaMaisProdutos;
    int operadorMenosPessoas;
    int operadorMaisProdutos;
    float tempoMedioEsperaCaixas;
    int numeroTotalClientesAtendidos;
    int maxProdutosVendidos;
    int numeroProdutosOferecidos;
    size_t memoriaUtilizada;

} Estatisticas;

// Funcoes para calcular estatisticas

void MenuEstatisticas(Supermercado *S);

void ObterCaixaMaisProdutos(Supermercado *S, Estatisticas *E);

Estatisticas CalcularEstatisticas(Supermercado *S);

void MostrarEstatisticasSupermercado(Supermercado *S);

void ObterCaixaMaisPessoas(Supermercado *S, Estatisticas *E);

void ObterNumeroProdutosOferecidos(Supermercado *S, Estatisticas *E);

void maxProdutosVendidos(Supermercado *S, Estatisticas *E);

void OperadorMenosPessoas(Supermercado *S, Estatisticas *E);

void NumeroProdutosOferecidos(Supermercado *S, Estatisticas *E);

void ValorTotalProdutosOferecidos(Supermercado *S, Estatisticas *E);

void TempoMedioEsperaCaixas(Supermercado *S, Estatisticas *E);

void NumeroTotalClientesAtendidos(Supermercado *S, Estatisticas *E);

void MemoriaUtilizada(Supermercado *S, Estatisticas *E);

void ObterCaixaMenosPessoas(Supermercado *S, Estatisticas *E);

void ObterOperadorMaisProdutos(Supermercado *S, Estatisticas *E);

#endif // ESTATISTICAS_H
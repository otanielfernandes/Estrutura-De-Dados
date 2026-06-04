#ifndef ESTATISTICAS_H
#define ESTATISTICAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "MatrizSupermercado.h"
#include "ListaClientes.h"
#include "ListaFuncionarios.h"
#include "ListaProdutos.h"

/* =========================
        ESTRUTURA
========================= */

typedef struct
{
        /* CAIXAS */
        int idCaixaMaisPessoas;
        int maxPessoasAtendidas;

        int idCaixaMenosPessoas;
        int minPessoasAtendidas;

        int idCaixaMaisProdutos;
        int maxProdutosVendidos;

        /* OPERADORES */
        int operadorMaisPessoas;
        int operadorMenosPessoas;

        int operadorMaisProdutos;
        int operadorMenosProdutos;

        /* PRODUTOS */
        float custoOferecidos;
        int numeroProdutosOferecidos;

        int numeroTotalProdutosVendidos;

        /* CLIENTES */
        int numeroTotalClientesAtendidos;

        /* TEMPOS */
        float tempoMedioEsperaCaixas;
        float tempoTotalAtendimento;

        /* FILAS */
        int maiorFila;

        /* CAIXAS */
        int numeroCaixasAbertas;
        int numeroCaixasFechadas;

        /* EXTRA */
        int numeroMudancasFila;

} Estatisticas;

/* BASE */
void DestruirEstatisticas(Estatisticas *E);

/* CÁLCULOS */
float CalcularTempoMedioEspera(MatrizSupermercado *H);

/* VISUALIZAÇÃO */
void MostrarEstatisticas(Estatisticas *E);

void MostrarResumoCaixas(MatrizSupermercado *H);

void MostrarResumoFuncionarios(ListaFuncionarios *LF);

void MostrarResumoProdutos(ListaProdutos *LP);

void MostrarResumoClientes(ListaClientes *LC);

/* ESTATÍSTICAS */
void ObterCaixaMaisProdutos(MatrizSupermercado *H, Estatisticas *E);

void ObterNumeroProdutosOferecidos(MatrizSupermercado *H, Estatisticas *E);

void ValorTotalProdutosOferecidos(MatrizSupermercado *H, Estatisticas *E);

void TempoMedioEsperaCaixas(MatrizSupermercado *H, Estatisticas *E);

void NumeroTotalClientesAtendidos(MatrizSupermercado *H, Estatisticas *E);

void OperadorMenosPessoas(MatrizSupermercado *H, Estatisticas *E);

void ObterOperadorMaisProdutos(MatrizSupermercado *H, Estatisticas *E);

void ObterCaixaMenosPessoas(MatrizSupermercado *H, Estatisticas *E);

void ObterCaixaMaisPessoas(MatrizSupermercado *H, Estatisticas *E);

void MostrarEstatisticasSupermercado(MatrizSupermercado *H);

void ObterNumeroProdutosVendidos(MatrizSupermercado *H, Estatisticas *E);

void ObterNumeroCaixasAbertas(MatrizSupermercado *H, Estatisticas *E);

void ObterNumeroCaixasFechadas(MatrizSupermercado *H, Estatisticas *E);

void ObterMaiorFila(MatrizSupermercado *H, Estatisticas *E);

void ObterTempoTotalAtendimento(MatrizSupermercado *H, Estatisticas *E);

/* MENUS */
void MenuEstatisticas(MatrizSupermercado *H);

void MenuCaixas(MatrizSupermercado *H);

void MenuProdutos(ListaProdutos *LP);

void MenuFuncionarios(ListaFuncionarios *LF);

#endif
#ifndef ESTATISTICAS_H
#define ESTATISTICAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Hashing.h"
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
        int produtosOferecidos;

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
Estatisticas *CriarEstatisticas();

void ResetEstatisticas(Estatisticas *E);

void DestruirEstatisticas(Estatisticas *E);

/* ATUALIZAÇÃO */
void AtualizarEstatisticasCaixas(Estatisticas *E, Hashing *H);

void AtualizarEstatisticasFuncionarios(Estatisticas *E, ListaFuncionarios *LF,
                                       Hashing *H);

void AtualizarEstatisticasProdutos(Estatisticas *E,
                                   ListaProdutos *LP);

void AtualizarEstatisticasClientes(Estatisticas *E,
                                   ListaClientes *LC);

/* CÁLCULOS */
float CalcularTempoMedioEspera(Hashing *H);

/* VISUALIZAÇÃO */
void MostrarEstatisticas(Estatisticas *E);

void MostrarResumoCaixas(Hashing *H);

void MostrarResumoFuncionarios(ListaFuncionarios *LF);

void MostrarResumoProdutos(ListaProdutos *LP);

void MostrarResumoClientes(ListaClientes *LC);

/* ESTATÍSTICAS */
void ObterCaixaMaisProdutos(Hashing *H, Estatisticas *E);

void ObterNumeroProdutosOferecidos(ListaProdutos *LP, Estatisticas *E);

void ValorTotalProdutosOferecidos(ListaProdutos *LP, Estatisticas *E);

void TempoMedioEsperaCaixas(Hashing *H, Estatisticas *E);

void NumeroTotalClientesAtendidos(Hashing *H, Estatisticas *E);

void OperadorMenosPessoas(Hashing *H, Estatisticas *E);

void ObterOperadorMaisProdutos(Hashing *H, Estatisticas *E);

void ObterCaixaMenosPessoas(Hashing *H, Estatisticas *E);

void ObterCaixaMaisPessoas(Hashing *H, Estatisticas *E);

void MostrarEstatisticasSupermercado(Hashing *H, ListaProdutos *LP);

void ObterNumeroProdutosVendidos(Hashing *H, Estatisticas *E);

void ObterNumeroCaixasAbertas(Hashing *H, Estatisticas *E);

void ObterNumeroCaixasFechadas(Hashing *H, Estatisticas *E);

void ObterMaiorFila(Hashing *H, Estatisticas *E);

void ObterTempoTotalAtendimento(Hashing *H, Estatisticas *E);

/* MENUS */
void MenuEstatisticas(Hashing *H, ListaProdutos *LP);

void MenuCaixas(Hashing *H);

void MenuClientes(ListaClientes *LC);

void MenuProdutos(ListaProdutos *LP);

void MenuFuncionarios(ListaFuncionarios *LF);

#endif
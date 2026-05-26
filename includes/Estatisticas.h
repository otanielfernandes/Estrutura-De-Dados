#ifndef ESTATISTICAS_H
#define ESTATISTICAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Hashing.h"
#include "ListaClientes.h"
#include "ListaFuncionarios.h"
#include "ListaProdutos.h"

/* IMPORTANTE: evita erro "unknown type name Supermercado" */

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

} Estatisticas;

/* =========================
        BASE
========================= */

Estatisticas *CriarEstatisticas();
void ResetEstatisticas(Estatisticas *E);
void DestruirEstatisticas(Estatisticas *E);

/* =========================
        ATUALIZAÇÃO
========================= */

void AtualizarEstatisticasCaixas(Estatisticas *E, Hashing *H);

void AtualizarEstatisticasFuncionarios(Estatisticas *E,
                                       ListaFuncionarios *LF,
                                       Hashing *H);

void AtualizarEstatisticasProdutos(Estatisticas *E,
                                   ListaProdutos *LP);

void AtualizarEstatisticasClientes(Estatisticas *E,
                                   ListaClientes *LC);

/* =========================
        CÁLCULOS
========================= */

float CalcularTempoMedioEspera(Hashing *H);

/* =========================
        VISUALIZAÇÃO
========================= */

void MostrarEstatisticas(Estatisticas *E);

void MostrarResumoCaixas(Hashing *H);

void MostrarResumoFuncionarios(ListaFuncionarios *LF);

void MostrarResumoProdutos(ListaProdutos *LP);

void MostrarResumoClientes(ListaClientes *LC);

/* =========================
        ESTATÍSTICAS
========================= */

void ObterCaixaMaisProdutos(Hashing *H, Estatisticas *E);

void ObterNumeroProdutosOferecidos(ListaProdutos *LP,
                                   Estatisticas *E);

void ValorTotalProdutosOferecidos(ListaProdutos *LP,
                                  Estatisticas *E);

void TempoMedioEsperaCaixas(Hashing *H,
                            Estatisticas *E);

void NumeroTotalClientesAtendidos(Hashing *H,
                                  Estatisticas *E);

void OperadorMenosPessoas(Hashing *H,
                          Estatisticas *E);

void ObterOperadorMaisProdutos(Hashing *H,
                               Estatisticas *E);

void ObterCaixaMenosPessoas(Hashing *H,
                            Estatisticas *E);

void ObterCaixaMaisPessoas(Hashing *H,
                           Estatisticas *E);

void MostrarEstatisticasSupermercado(Hashing *H,
                                     ListaProdutos *LP);

/* =========================
        MENUS
========================= */

void MenuEstatisticas(Hashing *H, ListaProdutos *LP);

void MenuCaixas();
void MenuClientes();
void MenuProdutos();
void MenuFuncionarios();

#endif
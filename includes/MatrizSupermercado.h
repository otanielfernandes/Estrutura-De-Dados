#ifndef MATRIZSUPERMERCADO_H
#define MATRIZSUPERMERCADO_H

#include "Cliente.h"
#include "ListaClientes.h"
#include "Funcionario.h"
#include "ListaFuncionarios.h"

typedef struct Caixa
{
    int id;
    int aberta;

    ListaClientes *fila;

    int totalPessoasAtendidas;
    int totalProdutosVendidos;

    /* NOVOS */
    float tempoTotalAtendimento;
    float tempoMedioFila;
    int maxClientesFila;

    /*outros campos possiveis para a estrutura caixa:
        Funcionario *operador;
        struct Caixa *CaixaSeguinte;
    */

} Caixa;

typedef struct MatrizSupermercado
{
    // Será um vector dinâmico para caixas:
    Caixa *Tabela;
    int tamanho;

    // Campos usados para obter o total de produtos oferecidos:
    int max_espera;
    int totalProdutosOferecidos;
    float valorProdutosOferecidos;
} MatrizSupermercado;

MatrizSupermercado *CriarMatrizSupermercado(int tamanho);

float CalcularTempoCaixa(Caixa *C);

int FuncaoEspalharCaixa(MatrizSupermercado *H, int idCaixa);

int InserirClienteCaixa(Caixa *C, Cliente *Cli);

void ProcessarCaixas(MatrizSupermercado *H);

Caixa *ObterCaixa(MatrizSupermercado *H, int idCaixa);

void MostrarMatrizSupermercado(MatrizSupermercado *H);

void DestruirMatrizSupermercado(MatrizSupermercado *H);

int NumeroClientesFila(Caixa *C);
#endif
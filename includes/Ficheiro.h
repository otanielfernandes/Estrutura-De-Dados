#ifndef FICHEIRO_H
#define FICHEIRO_H

#include "ListaProdutos.h"
#include "ListaClientes.h"
#include "ListaFuncionarios.h"
#include "MatrizSupermercado.h"

int LerProdutos(ListaProdutos *LP, char *ficheiro);

int LerClientes(ListaClientes *LC, char *ficheiro);

int LerFuncionarios(ListaFuncionarios *LF, char *ficheiro);

int ExportarProdutosCSV(ListaProdutos *LP, char *ficheiro);
int ExportarClientesCSV(ListaClientes *LC, char *ficheiro);
int ExportarFuncionariosCSV(ListaFuncionarios *LF, char *ficheiro);
int ExportarCaixasCSV(MatrizSupermercado *H, char *ficheiro);
int ExportarEstatisticasCSV(MatrizSupermercado *H, char *ficheiro);

int CriarHistoricoCSV(char *ficheiro);
int RegistrarHistoricoCSV(const char *evento,
                          Cliente *cliente,
                          int caixaOrigem,
                          int caixaDestino,
                          const char *produto,
                          float valor);

void MenuFicheiros(ListaProdutos *LP, ListaClientes *LC, ListaFuncionarios *LF, MatrizSupermercado *H);

#endif

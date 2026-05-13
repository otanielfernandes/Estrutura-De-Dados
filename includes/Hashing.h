#ifndef HASHING_H
#define HASHING_H

#include "Cliente.h"
#include "ListaClientes.h"
#include "Funcionario.h"
#include "ListaFuncionarios.h"

typedef struct
{
    int id;
    int aberta;

    ListaClientes *fila;

    int totalPessoasAtendidas;
    int totalProdutosVendidos;

} Caixa;

typedef struct
{   
    //Será um vector dinâmico para caixas:
    Caixa *Tabela;
    int tamanho;
} Hashing;

Hashing *CriarHashing(int tamanho);

int FuncaoHash(Hashing *H, int idCaixa);

Caixa *ObterCaixa(Hashing *H, int idCaixa);

void MostrarHashing(Hashing *H);

void DestruirHashing(Hashing *H);

#endif
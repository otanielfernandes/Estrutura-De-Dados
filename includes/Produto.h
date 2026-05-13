#ifndef PRODUTO_H
#define PRODUTO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int codigo;
    char *nome;
    float preco;
    float tempoCompra;
    float tempoCaixa;
} Produto;

Produto *CriarProduto(int _codigo, char *_nome, float _preco, float _tempoCompra,
    float _tempoCaixa);
void MostrarProduto(Produto *P);
void DestruirProduto(Produto *P);

#endif
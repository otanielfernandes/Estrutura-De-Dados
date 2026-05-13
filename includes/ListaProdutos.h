#ifndef LISTAPRODUTOS_H
#define LISTAPRODUTOS_H
#include "Produto.h"

#define SUCESSO 1
#define INSUCESSO 0

typedef struct _noProduto
{
    Produto *Info;
    struct _noProduto *Prox;
} NoProduto;

typedef struct
{
    NoProduto *Inicio;
    NoProduto *Fim;
    int NEL;

} ListaProdutos;

ListaProdutos *CriarListaProdutos();
int InserirProduto(ListaProdutos *LProd, Produto *Prod);
void MostrarListaProdutos(ListaProdutos *LProd);
void DestruirListaProdutos(ListaProdutos *LProd);

#endif
#ifndef HUSHING_H
#define HUSHING_H

#include "MatrizSupermercado.h"

typedef struct HashNode
{
  int idCliente;

  Cliente *cliente;

  Caixa *caixa;

  struct HashNode *prox;

} HashNode;

typedef struct
{
  HashNode **tabela;

  int tamanho;

} HashTable;

HashTable *CriarHashTable(int tamanho);
int FuncaoHash(int idCliente, int tamanho);
int InserirHashTable(HashTable *H, int idCliente, Cliente *cliente, Caixa *caixa);
HashNode *BuscarHashTable(HashTable *H, int idCliente);
void DestruirHashTable(HashTable *H);
#endif
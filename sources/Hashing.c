#include "../includes/Hashing.h"

/*Cria uma nova tabela hash dos Elementos do Supermercado*/
HashTable *CriarHashTable(int tamanho)
{
  HashTable *H = (HashTable *)malloc(sizeof(HashTable));
  if (H == NULL)
    return NULL;

  H->tamanho = tamanho;
  H->tabela = (HashNode **)malloc(sizeof(HashNode *) * tamanho);
  if (H->tabela == NULL)
  {
    free(H);
    return NULL;
  }

  for (int i = 0; i < tamanho; i++)
    H->tabela[i] = NULL;

  return H;
}

/*Função de Hashing para calcular o índice da tabela a partir do ID do cliente*/
int FuncaoHash(int idCliente, int tamanho)
{
  return idCliente % tamanho;
}

/*Função para inserir um novo elemento na tabela hash*/
int InserirHashTable(HashTable *H, int idCliente, Cliente *cliente, Caixa *caixa)
{
  if (H == NULL || cliente == NULL || caixa == NULL)
    return 0;

  int indice = FuncaoHash(idCliente, H->tamanho);

  HashNode *Novo = (HashNode *)malloc(sizeof(HashNode));
  if (Novo == NULL)
    return 0;

  Novo->idCliente = idCliente;
  Novo->cliente = cliente;
  Novo->caixa = caixa;
  Novo->prox = H->tabela[indice];

  H->tabela[indice] = Novo;

  return 1;
}

/*Função para buscar um elemento na tabela hash pelo ID do cliente*/
HashNode *BuscarHashTable(HashTable *H, int idCliente)
{
  if (H == NULL)
    return NULL;

  int indice = FuncaoHash(idCliente, H->tamanho);

  HashNode *Atual = H->tabela[indice];

  while (Atual != NULL)
  {
    if (Atual->idCliente == idCliente)
      return Atual;

    Atual = Atual->prox;
  }

  return NULL;
}

/*Função para destruir a tabela hash*/
void DestruirHashTable(HashTable *H)
{
  if (H == NULL)
    return;

  for (int i = 0; i < H->tamanho; i++)
  {
    HashNode *Atual = H->tabela[i];

    while (Atual != NULL)
    {
      HashNode *Temp = Atual;
      Atual = Atual->prox;
      free(Temp);
    }
  }

  free(H->tabela);
  free(H);
}
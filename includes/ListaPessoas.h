#ifndef LISTAPESSOAS_H
#define LISTAPESSOAS_H

#include "Pessoa.h"
#include "Cliente.h"

#define SUCESSO 1
#define INSUCESSO 0

//Criando uma estrutura nó para a estrutura Pessoa:
typedef struct _noPessoa
{   
    //Quem entra na Fila são apenas os clientes, não os funcionários:
    Cliente *Info;
    struct _noPessoa *Prox;
} NoPessoa;

typedef struct
{
    NoPessoa *Inicio;
    NoPessoa *Fim;
    int NEL;
} ListaPessoas;

// Funções
ListaPessoas *CriarListaPessoas();
int InserirPessoa(ListaPessoas *LP, Cliente *P);
int InserirPessoa_Fim(ListaPessoas *LP, Cliente *P);
Cliente *RemoverPessoa_Inicio(ListaPessoas *LP);
void MostrarListaPessoas(ListaPessoas *LP);
void DestruirListaPessoas(ListaPessoas *LP);

#endif
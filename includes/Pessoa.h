#ifndef PESSOA_H_INCLUDED
#define PESSOA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int codigo;
    char *nome;
}Pessoa;

Pessoa *CriarPessoa(int _codigo, char *_nome);
void MostrarPessoa(Pessoa *P);
void DestruirPessoa(Pessoa *P);

#endif
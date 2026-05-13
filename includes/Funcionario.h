#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

#include "Pessoa.h"

typedef struct
{
    Pessoa *dados;
    int caixaID;
}Funcionario;

Funcionario *CriarFuncionario(int codigo, char *nome);
void MostrarFuncionario(Funcionario *F);
void DestruirFuncionario(Funcionario *F);

#endif
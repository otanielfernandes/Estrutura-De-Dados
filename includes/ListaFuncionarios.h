#ifndef LISTAFUNCIONARIOS_H
#define LISTAFUNCIONARIOS_H

#include "Funcionario.h"

typedef struct NoFuncionario
{
    Funcionario *Func;
    struct NoFuncionario *Prox;

} NoFuncionario;


typedef struct
{
    NoFuncionario *Inicio;
    int NEL;

} ListaFuncionarios;


ListaFuncionarios *CriarListaFuncionarios();

int InserirFuncionario(ListaFuncionarios *LF, Funcionario *F);
void MostrarListaFuncionarios(ListaFuncionarios *LF);
void DestruirListaFuncionarios(ListaFuncionarios *LF);

#endif
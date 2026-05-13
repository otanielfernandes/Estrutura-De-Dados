#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

typedef struct
{
    int id;
    char *nome;
    int caixaID;
} Funcionario;

Funcionario *CriarFuncionario(int id, char *nome, int caixaID);
void MostrarFuncionario(Funcionario *F);
void DestruirFuncionario(Funcionario *F);

#endif
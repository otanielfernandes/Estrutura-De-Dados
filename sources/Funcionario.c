#include "../includes/Funcionario.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../includes/Funcionario.h"

Funcionario *CriarFuncionario(int id, char *nome, int caixaID)
{
    Funcionario *F =
        (Funcionario *)malloc(sizeof(Funcionario));

    if (F == NULL)
        return NULL;

    F->id = id;

    F->nome = (char *)malloc(strlen(nome) + 1);
    if (F->nome == NULL)
    {
        free(F);
        return NULL;
    }
    strcpy(F->nome, nome);

    F->caixaID = caixaID;

    return F;
}


void MostrarFuncionario(Funcionario *F)
{
    if (F == NULL)
        return;

    printf("Funcionario: %d | %s | Caixa: %d\n", F->id, F->nome, F->caixaID);
}

void DestruirFuncionario(Funcionario *F)
{
    if (F == NULL)
        return;

    free(F->nome);
    free(F);
}
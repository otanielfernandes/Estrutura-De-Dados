#include "../includes/Funcionario.h"

Funcionario *CriarFuncionario(int codigo, char *nome)
{
    Funcionario *F = (Funcionario *)malloc(sizeof(Funcionario));

    if (F == NULL)
        return NULL;

    F->dados = CriarPessoa(codigo, nome);
    F->caixaID = -1;

    return F;
}

void MostrarFuncionario(Funcionario *F)
{
    if (F == NULL)
        return;

    printf("Funcionario: %d | %s\n", F->dados->codigo, F->dados->nome);
}

void DestruirFuncionario(Funcionario *F)
{
    if (F == NULL)
        return;

    DestruirPessoa(F->dados);
    free(F);
}
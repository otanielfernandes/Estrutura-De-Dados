#include "../includes/Pessoa.h"

Pessoa *CriarPessoa(int _codigo, char *_nome)
{
    Pessoa *P =
        (Pessoa *)malloc(sizeof(Pessoa));

    if (P == NULL)
        return NULL;

    P->codigo = _codigo;

    P->nome =
        (char *)malloc(strlen(_nome) + 1);

    if (P->nome == NULL)
    {
        free(P);

        return NULL;
    }

    strcpy(P->nome, _nome);

    return P;
}

void MostrarPessoa(Pessoa *P)
{
    if (P == NULL)
        return;

    printf("%d | %s\n", P->codigo, P->nome);
}

void DestruirPessoa(Pessoa *P)
{
    if (P == NULL)
        return;

    free(P->nome);
    free(P);
}
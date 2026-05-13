#include "../includes/ListaPessoas.h"

ListaPessoas *CriarListaPessoas()
{
    ListaPessoas *LP =
        (ListaPessoas *)malloc(sizeof(ListaPessoas));

    if (LP == NULL)
        return NULL;

    LP->Inicio = NULL;
    LP->Fim = NULL;
    LP->NEL = 0;

    return LP;
}


// Inserir no fim da fila (FIFO)
int InserirPessoa_Fim(ListaPessoas *LP, Cliente *P)
{
    if (LP == NULL || P == NULL)
        return INSUCESSO;

    NoPessoa *novo =
        (NoPessoa *)malloc(sizeof(NoPessoa));

    if (novo == NULL)
        return INSUCESSO;

    novo->Info = P;

    novo->Prox = NULL;

    if (LP->Fim == NULL)
    {
        LP->Inicio = novo;

        LP->Fim = novo;
    }
    else
    {
        LP->Fim->Prox = novo;

        LP->Fim = novo;
    }

    LP->NEL++;

    return SUCESSO;
}


void MostrarListaPessoas(ListaPessoas *LP)
{
    if (LP == NULL)
        return;

    NoPessoa *aux = LP->Inicio;

    while (aux != NULL)
    {
        MostrarCliente(aux->Info);

        aux = aux->Prox;
    }
}


void DestruirListaPessoas(ListaPessoas *LP)
{
    if (LP == NULL)
        return;

    NoPessoa *temp;

    NoPessoa *aux = LP->Inicio;

    while (aux != NULL)
    {
        temp = aux;

        aux = aux->Prox;

        DestruirCliente(temp->Info);

        free(temp);
    }

    free(LP);
}


// Remover do início da fila
Cliente *RemoverPessoa_Inicio(ListaPessoas *LP)
{
    if (LP == NULL || LP->Inicio == NULL)
        return NULL;

    NoPessoa *aux = LP->Inicio;

    Cliente *P = aux->Info;

    LP->Inicio = aux->Prox;

    if (LP->Inicio == NULL)
        LP->Fim = NULL;

    free(aux);

    LP->NEL--;

    return P;
}
#include "../includes/Produto.h"

Produto *CriarProduto(int codigo, char *nome, float preco, float tempoCompra, float tempoCaixa)
{
    Produto *Prod =(Produto *)malloc(sizeof(Produto));

    if (Prod == NULL)
        return NULL;

    Prod->codigo = codigo;
    Prod->nome =(char *)malloc(strlen(nome) + 1);
    if (Prod->nome == NULL)
    {
        free(Prod);

        return NULL;
    }
    strcpy(Prod->nome, nome);

    Prod->preco = preco;
    Prod->tempoCompra = tempoCompra;
    Prod->tempoCaixa = tempoCaixa;

    return Prod;
}

void MostrarProduto(Produto *Prod)
{
    if (Prod == NULL)
        return;

    printf(
        "%d | %s | %.2f€ | TempoCompra: %.1f | TempoCaixa: %.1f\n",
        Prod->codigo,
        Prod->nome,
        Prod->preco,
        Prod->tempoCompra,
        Prod->tempoCaixa
    );
}

void DestruirProduto(Produto *Prod)
{
    if (Prod != NULL){
        free(Prod->nome);
        free(Prod);
    }
        
}
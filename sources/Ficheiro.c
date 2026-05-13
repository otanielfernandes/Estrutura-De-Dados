#include "../includes/Ficheiro.h"

int LerProdutos(ListaProdutos *LProd, char *ficheiro)
{
    FILE *f = fopen(ficheiro, "r");
    if (f == NULL)
    {
        printf("Erro ao abrir %s\n", ficheiro);
        return 0;
    }

    int codigo;
    char nome[100];
    float preco;
    float tempoCompra;
    float tempoCaixa;
    while 
    (
        fscanf(f,"%d %s %f %f %f", &codigo, nome, &preco, &tempoCompra, &tempoCaixa) != EOF
    )
    {
        Produto *Prod =
            CriarProduto(codigo, nome, preco, tempoCompra, tempoCaixa);
        InserirProduto(LProd, Prod);
    }

    fclose(f);

    return 1;
}
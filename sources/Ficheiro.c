#include "../includes/Ficheiro.h"


int LerProdutos(ListaProdutos *LProd, char *ficheiro)
{
    FILE *f = fopen(ficheiro, "r");
    if (f == NULL)
    {
        printf("Erro ao abrir %s\n", ficheiro);
        return 0;
    }

    char linha[512];

    while (fgets(linha, sizeof(linha), f))
    {
        int codigo;
        char nome[300];
        float preco;
        float tempoCompra;
        float tempoCaixa;

        int lidos = sscanf(
            linha, 
            "%d %[^\t]\t%f\t%f\t%f",
            &codigo,
            nome,
            &preco,
            &tempoCompra,
            &tempoCaixa
        );

        if (lidos == 5)
        {
            Produto *Prod = CriarProduto(
                    codigo,
                    nome,
                    preco,
                    tempoCompra,
                    tempoCaixa
                );

            InserirProduto(LProd, Prod);
        }
    }

    fclose(f);

    return 1;
}
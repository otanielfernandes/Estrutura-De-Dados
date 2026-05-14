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


#include "../includes/Ficheiro.h"

//Mexer depois:
int LerClientes(ListaClientes *LC, char *ficheiro)
{
    FILE *f = fopen(ficheiro, "r");

    if (f == NULL)
    {
        printf("\nErro ao abrir ficheiro de clientes!\n");
        return 0;
    }

    int id;
    char nome[200];

    while (fscanf(f, "%d\t%[^\n]\n", &id, nome) == 2)
    {
        Cliente *C = CriarCliente(id, nome);
        InserirCliente(LC, C);
    }

    fclose(f);

    return 1;
}

int LerFuncionarios(ListaFuncionarios *LF, char *ficheiro)
{
    FILE *f = fopen(ficheiro, "r");

    if (f == NULL)
    {
        printf("Erro ao abrir Funcionarios.txt\n");
        return 0;
    }

    int id;
    char nome[200];

    while (fscanf(f, "%d\t%[^\n]\n", &id, nome) == 2)
    {
        Funcionario *F = CriarFuncionario(id, nome, 0);
        InserirFuncionario(LF, F);
    }

    fclose(f);

    return 1;
}
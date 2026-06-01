#include "../includes/Ficheiro.h"

int LerProdutos(ListaProdutos *LProd, char *ficheiro)
{
    FILE *f = fopen(ficheiro, "r");

    if (f == NULL)
    {
        printf("[ERRO] Não foi possível abrir: %s\n", ficheiro);
        return 0;
    }

    char linha[512];
    int contador = 0;
    const int MAX_PRODUTOS = 600;

    while (fgets(linha, sizeof(linha), f) && contador < MAX_PRODUTOS)
    {
        int codigo;
        char nome[300];
        float preco, tempoCompra, tempoCaixa;

        int lidos = sscanf(linha,
                           "%d %[^\t]\t%f\t%f\t%f",
                           &codigo,
                           nome,
                           &preco,
                           &tempoCompra,
                           &tempoCaixa);

        if (lidos == 5)
        {
            Produto *Prod = CriarProduto(codigo, nome, preco, tempoCompra, tempoCaixa);
            InserirProduto(LProd, Prod);
            contador++;
        }
    }

    InverterListaProdutos(LProd);

    fclose(f);

    printf("[INFO] Produtos carregados: %d\n", contador);
    return 1;
}

// Mexer depois:
int LerClientes(ListaClientes *LC, char *ficheiro)
{
    FILE *f = fopen(ficheiro, "r");

    if (f == NULL)
    {
        printf("[ERRO] Ficheiro de clientes não encontrado!\n");
        return 0;
    }

    int id;
    char nome[200];
    int contador = 0;
    const int MAX_CLIENTES = 120;

    while (fscanf(f, "%d\t%[^\n]\n", &id, nome) == 2 && contador < MAX_CLIENTES)
    {
        Cliente *C = CriarCliente(id, nome);
        InserirCliente(LC, C);
        contador++;
    }

    InverterListaClientes(LC);

    fclose(f);

    printf("[INFO] Clientes carregados: %d\n", contador);
    return 1;
}

int LerFuncionarios(ListaFuncionarios *LF, char *ficheiro)
{
    FILE *f = fopen(ficheiro, "r");

    if (f == NULL)
    {
        printf("[ERRO] Não foi possível abrir Funcionarios.txt\n");
        return 0;
    }

    int id;
    char nome[200];
    int contador = 0;
    const int MAX_FUNCIONARIOS = 6;

    while (fscanf(f, "%d\t%[^\n]\n", &id, nome) == 2 && contador < MAX_FUNCIONARIOS)
    {
        Funcionario *F = CriarFuncionario(id, nome, 0);
        InserirFuncionario(LF, F);
        contador++;
    }

    InverterListaFuncionarios(LF);

    fclose(f);

    printf("[INFO] Funcionários carregados: %d\n", contador);
    return 1;
}
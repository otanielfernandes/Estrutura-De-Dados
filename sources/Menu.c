#include "../includes/Menu.h"
#include "../includes/Estatisticas.h"
#include "../includes/Hashing.h"
#include <stdio.h>
#include <string.h>

static void Pausar(void)
{
    printf("\nPrima ENTER para continuar...");
    getchar();
}

static void LimparTela(void)
{
    system("cls || clear");
}

// Menu principal
void MenuPrincipal(Supermercado *S)
{
    int op;

    do
    {
        LimparTela();
        printf("\n===================================\n");
        printf("        MENU  PRINCIPAL\n");
        printf("===================================\n\n");
        printf("1 - Caixas\n");
        printf("2 - Clientes\n");
        printf("3 - Estatisticas\n");
        printf("4 - Ficheiros\n");
        printf("0 - Sair\n");
        printf("\nOpcao: ");
        scanf("%d", &op);
        getchar();

        switch (op)
        {
        case 1:
            MenuCaixas(S);
            break;
        case 2:
            MenuClientes(S);
            break;
        case 3:
            MenuEstatisticas(S);
            break;
        case 4:
            MenuFicheiros(S);
            break;
        case 0:
            printf("\nAte logo!\n");
            break;
        default:
            printf("\nOpcao invalida.\n");
            Pausar();
        }

    } while (op != 0);
}

// Menu caixas

static void ListarCaixas(Supermercado *S)
{
    printf("\n===== LISTA DE CAIXAS =====\n");

    if (S->HCaixas == NULL || S->HCaixas->Tabela == NULL)
    {
        printf("Nenhuma caixa registada.\n");
        return;
    }

    for (int i = 0; i < S->HCaixas->tamanho; i++)
    {
        Caixa *C = &S->HCaixas->Tabela[i];
        printf("Caixa %d | Estado: %s | Pessoas atendidas: %d | Produtos vendidos: %d | Fila: %d cliente(s)\n",
               C->id,
               C->aberta ? "Aberta" : "Fechada",
               C->totalPessoasAtendidas,
               C->totalProdutosVendidos,
               C->fila ? C->fila->NEL : 0);
    }
}

static void AbrirCaixa(Supermercado *S)
{
    int id;
    printf("\nID da caixa a abrir: ");
    scanf("%d", &id);
    getchar();

    Caixa *C = ObterCaixa(S->HCaixas, id);
    if (C == NULL)
    {
        printf("Caixa %d nao encontrada.\n", id);
        return;
    }
    if (C->aberta)
    {
        printf("A caixa %d ja esta aberta.\n", id);
        return;
    }
    C->aberta = 1;
    printf("Caixa %d aberta com sucesso.\n", id);
}

static void FecharCaixa(Supermercado *S)
{
    int id;
    printf("\nID da caixa a fechar: ");
    scanf("%d", &id);
    getchar();

    Caixa *C = ObterCaixa(S->HCaixas, id);
    if (C == NULL)
    {
        printf("Caixa %d nao encontrada.\n", id);
        return;
    }
    if (!C->aberta)
    {
        printf("A caixa %d ja esta fechada.\n", id);
        return;
    }
    if (C->fila && C->fila->NEL > 0)
    {
        printf("Aviso: a caixa %d ainda tem %d cliente(s) na fila.\n",
               id, C->fila->NEL);
    }
    C->aberta = 0;
    printf("Caixa %d fechada.\n", id);
}

void MenuCaixas(Supermercado *S)
{
    int op;

    do
    {
        LimparTela();
        printf("\n===================================\n");
        printf("          MENU  CAIXAS\n");
        printf("===================================\n\n");
        printf("1 - Listar caixas\n");
        printf("2 - Abrir caixa\n");
        printf("3 - Fechar caixa\n");
        printf("0 - Voltar\n");
        printf("\nOpcao: ");
        scanf("%d", &op);
        getchar();

        LimparTela();

        switch (op)
        {
        case 1:
            ListarCaixas(S);
            Pausar();
            break;
        case 2:
            AbrirCaixa(S);
            Pausar();
            break;
        case 3:
            FecharCaixa(S);
            Pausar();
            break;
        case 0:
            break;
        default:
            printf("\nOpcao invalida.\n");
            Pausar();
        }

    } while (op != 0);
}

// Menu clientes

static void ListarClientes(Supermercado *S)
{
    printf("\n===== LISTA DE CLIENTES =====\n");

    if (S->LClientes == NULL || S->LClientes->NEL == 0)
    {
        printf("Nenhum cliente registado.\n");
        return;
    }

    NoCliente *no = S->LClientes->Inicio;
    int idx = 1;
    while (no != NULL)
    {
        Cliente *C = no->Cli;
        if (C != NULL)
        {
            printf("%d. [ID %d] %s | Produtos no carrinho: %d\n",
                   idx++, C->id, C->nome,
                   C->carrinho ? C->carrinho->NEL : 0);
        }
        no = no->Prox;
    }
}

static void PesquisarCliente(Supermercado *S)
{
    char nome[100];
    printf("\nNome do cliente: ");
    scanf("%99s", nome);
    getchar();

    if (S->LClientes == NULL)
    {
        printf("Lista de clientes vazia.\n");
        return;
    }

    int encontrado = 0;
    NoCliente *no = S->LClientes->Inicio;
    while (no != NULL)
    {
        Cliente *C = no->Cli;
        if (C != NULL && strcmp(C->nome, nome) == 0)
        {
            printf("\nCliente encontrado:\n");
            MostrarCliente(C);
            encontrado = 1;
        }
        no = no->Prox;
    }

    if (!encontrado)
        printf("\nNenhum cliente com o nome \"%s\" encontrado.\n", nome);
}

static void MoverCliente(Supermercado *S)
{
    int idOrigem, idDestino;

    printf("\nID da caixa de origem : ");
    scanf("%d", &idOrigem);
    getchar();
    printf("ID da caixa de destino: ");
    scanf("%d", &idDestino);
    getchar();

    Caixa *origem = ObterCaixa(S->HCaixas, idOrigem);
    Caixa *destino = ObterCaixa(S->HCaixas, idDestino);

    if (origem == NULL)
    {
        printf("Caixa de origem %d nao encontrada.\n", idOrigem);
        return;
    }
    if (destino == NULL)
    {
        printf("Caixa de destino %d nao encontrada.\n", idDestino);
        return;
    }
    if (!destino->aberta)
    {
        printf("A caixa de destino %d esta fechada.\n", idDestino);
        return;
    }

    if (origem->fila == NULL || origem->fila->NEL == 0)
    {
        printf("A caixa %d nao tem clientes para mover.\n", idOrigem);
        return;
    }

    /* Move o primeiro cliente da fila de origem para o fim da fila de destino. */
    NoCliente *noC = origem->fila->Inicio;
    Cliente *cli = noC->Cli;

    RemoverClienteInicio(origem->fila);
    InserirCliente(destino->fila, cli);

    printf("Cliente \"%s\" movido da caixa %d para a caixa %d.\n",
           cli->nome, idOrigem, idDestino);
}

void MenuClientes(Supermercado *S)
{
    int op;

    do
    {
        LimparTela();
        printf("\n===================================\n");
        printf("        MENU  CLIENTES\n");
        printf("===================================\n\n");
        printf("1 - Listar clientes\n");
        printf("2 - Pesquisar cliente\n");
        printf("3 - Mover cliente entre caixas\n");
        printf("0 - Voltar\n");
        printf("\nOpcao: ");
        scanf("%d", &op);
        getchar();

        LimparTela();

        switch (op)
        {
        case 1:
            ListarClientes(S);
            Pausar();
            break;
        case 2:
            PesquisarCliente(S);
            Pausar();
            break;
        case 3:
            MoverCliente(S);
            Pausar();
            break;
        case 0:
            break;
        default:
            printf("\nOpcao invalida.\n");
            Pausar();
        }

    } while (op != 0);
}

// Menu ficheiros

void MenuFicheiros(Supermercado *S)
{
    int op;

    do
    {
        LimparTela();
        printf("\n===================================\n");
        printf("        MENU  FICHEIROS\n");
        printf("===================================\n\n");
        printf("1 - Guardar relatorio CSV\n");
        printf("2 - Carregar produtos\n");
        printf("3 - Carregar clientes\n");
        printf("4 - Carregar funcionarios\n");
        printf("0 - Voltar\n");
        printf("\nOpcao: ");
        scanf("%d", &op);
        getchar();

        LimparTela();

        switch (op)
        {
        case 1:
            printf("Guardar relatorio CSV ainda nao implementado.\n");
            Pausar();
            break;

        case 2:
        {
            char ficheiro[256];
            printf("Caminho do ficheiro de produtos: ");
            scanf("%255s", ficheiro);
            getchar();
            if (LerProdutos(S->LProdutos, ficheiro))
                printf("Produtos carregados com sucesso.\n");
            else
                printf("Erro ao carregar produtos.\n");
            Pausar();
            break;
        }

        case 3:
        {
            char ficheiro[256];
            printf("Caminho do ficheiro de clientes: ");
            scanf("%255s", ficheiro);
            getchar();
            if (LerClientes(S->LClientes, ficheiro))
                printf("Clientes carregados com sucesso.\n");
            else
                printf("Erro ao carregar clientes.\n");
            Pausar();
            break;
        }

        case 4:
        {
            char ficheiro[256];
            printf("Caminho do ficheiro de funcionarios: ");
            scanf("%255s", ficheiro);
            getchar();
            if (LerFuncionarios(S->LFuncionarios, ficheiro))
                printf("Funcionarios carregados com sucesso.\n");
            else
                printf("Erro ao carregar funcionarios.\n");
            Pausar();
            break;
        }

        case 0:
            break;

        default:
            printf("\nOpcao invalida.\n");
            Pausar();
        }

    } while (op != 0);
}
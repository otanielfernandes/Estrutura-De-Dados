#include "../includes/Estatisticas.h"
#include "../includes/Supermercado.h"
#include "../includes/Ficheiro.h"
#include "../includes/ListaClientes.h"
#include "../includes/MatrizSupermercado.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static void Pausar(void)
{
    printf("\nPrima ENTER para continuar...");
    getchar();
}

static void LimparTela(void)
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/* MENU PRINCIPAL */

void MenuPrincipal(Supermercado *S)
{
    int op;

    if (S == NULL)
        return;

    do
    {
        // LimparTela();

        printf("\n===================================\n");
        printf("        MENU PRINCIPAL\n");
        printf("===================================\n\n");

        printf("1 - Caixas\n");
        printf("2 - Clientes\n");
        printf("3 - Estatisticas\n");
        printf("4 - Ficheiros\n");
        printf("5 - Produtos\n");
        printf("0 - Sair\n");

        printf("\nOpcao: ");

        scanf("%d", &op);
        getchar();

        switch (op)
        {
        case 1:
            MenuCaixas(S->HCaixas);
            break;

        case 2:
            MenuClientes(S->LClientes);
            break;

        case 3:
            MenuEstatisticas(S->HCaixas);
            break;

        case 4:
            MenuFicheiros(S->LProdutos, S->LClientes, S->LFuncionarios);
            break;

        case 5:
            MenuProdutos(S->LProdutos);
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

/* CAIXAS */

static void ListarCaixas(MatrizSupermercado *H)
{
    if (H == NULL || H->Tabela == NULL)
    {
        printf("\nNenhuma caixa registada.\n");
        return;
    }

    printf("\n===== LISTA DE CAIXAS =====\n");

    for (int i = 0; i < H->tamanho; i++)
    {
        Caixa *C = &H->Tabela[i];

        printf("Caixa %d | %s | Pessoas: %d | Produtos: %d | Fila: %d\n",
               C->id,
               C->aberta ? "Aberta" : "Fechada",
               C->totalPessoasAtendidas,
               C->totalProdutosVendidos,
               (C->fila ? C->fila->NEL : 0));
    }
}

static void AbrirCaixa(MatrizSupermercado *H)
{
    int id;

    if (H == NULL)
        return;

    printf("\nID da caixa: ");
    scanf("%d", &id);
    getchar();

    Caixa *C = ObterCaixa(H, id);

    if (C == NULL)
    {
        printf("\nCaixa nao encontrada.\n");
        return;
    }

    C->aberta = 1;

    printf("\nCaixa aberta com sucesso.\n");
}

static void FecharCaixa(MatrizSupermercado *H)
{
    int id;

    if (H == NULL)
        return;

    printf("\nID da caixa: ");
    scanf("%d", &id);
    getchar();

    Caixa *C = ObterCaixa(H, id);

    if (C == NULL)
    {
        printf("\nCaixa nao encontrada.\n");
        return;
    }

    if (C->fila != NULL && C->fila->NEL > 0)
    {
        printf("\nNao pode fechar caixa com clientes.\n");
        return;
    }

    C->aberta = 0;

    printf("\nCaixa fechada com sucesso.\n");
}

void MenuCaixas(MatrizSupermercado *H)
{
    int op;

    if (H == NULL)
        return;

    do
    {
        // LimparTela();

        printf("\n===== MENU CAIXAS =====\n");

        printf("1 - Listar caixas\n");
        printf("2 - Abrir caixa\n");
        printf("3 - Fechar caixa\n");
        printf("0 - Voltar\n");

        printf("Opcao: ");

        scanf("%d", &op);
        getchar();

        LimparTela();

        switch (op)
        {
        case 1:
            ListarCaixas(H);
            Pausar();
            break;

        case 2:
            AbrirCaixa(H);
            Pausar();
            break;

        case 3:
            FecharCaixa(H);
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

/* CLIENTES */

static void ListarClientesMenu(ListaClientes *LC)
{
    if (LC == NULL || LC->Inicio == NULL)
    {
        printf("\nNenhum cliente registado.\n");
        return;
    }

    printf("\n===== LISTA DE CLIENTES =====\n");

    NoCliente *aux = LC->Inicio;

    while (aux != NULL)
    {
        printf("Nome: %s\n", aux->Cli->nome);

        aux = aux->Prox;
    }
}

void MenuClientes(ListaClientes *LC)
{
    int op;

    if (LC == NULL)
        return;

    do
    {
        // LimparTela();

        printf("\n===== MENU CLIENTES =====\n");

        printf("1 - Listar clientes\n");
        printf("0 - Voltar\n");

        printf("Opcao: ");

        scanf("%d", &op);
        getchar();

        LimparTela();

        switch (op)
        {
        case 1:
            ListarClientesMenu(LC);
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

/* FICHEIROS */

void MenuFicheiros(ListaProdutos *LP, ListaClientes *LC, ListaFuncionarios *LF)
{
    int op;

    char ficheiro[100];

    do
    {
        // LimparTela();

        printf("\n===== MENU FICHEIROS =====\n");

        printf("1 - Carregar produtos\n");
        printf("2 - Carregar clientes\n");
        printf("3 - Carregar funcionarios\n");
        printf("0 - Voltar\n");

        printf("\nOpcao: ");

        scanf("%d", &op);
        getchar();

        // LimparTela();

        switch (op)
        {
        case 1:

            printf("Nome do ficheiro: ");

            fgets(ficheiro, sizeof(ficheiro), stdin);

            ficheiro[strcspn(ficheiro, "\n")] = '\0';

            LerProdutos(LP, ficheiro);

            printf("\nProdutos carregados com sucesso.\n");

            Pausar();

            break;

        case 2:

            printf("Nome do ficheiro: ");

            fgets(ficheiro, sizeof(ficheiro), stdin);

            ficheiro[strcspn(ficheiro, "\n")] = '\0';

            LerClientes(LC, ficheiro);

            printf("\nClientes carregados com sucesso.\n");

            Pausar();

            break;

        case 3:

            printf("Nome do ficheiro: ");

            fgets(ficheiro, sizeof(ficheiro), stdin);

            ficheiro[strcspn(ficheiro, "\n")] = '\0';

            LerFuncionarios(LF, ficheiro);

            printf("\nFuncionarios carregados com sucesso.\n");

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

void MenuProdutos(ListaProdutos *LP)
{
    int op;

    if (LP == NULL)
        return;

    do
    {
        // LimparTela();

        printf("\n===== MENU PRODUTOS =====\n");
        printf("1 - Listar produtos\n");
        printf("0 - Voltar\n");
        printf("Opcao: ");

        scanf("%d", &op);
        getchar();

        switch (op)
        {
        case 1:
            MostrarListaProdutos(LP);
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
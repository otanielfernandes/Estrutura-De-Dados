#include "../includes/Estatisticas.h"
#include "../includes/Supermercado.h"
#include "../includes/Ficheiro.h"
#include "../includes/ListaClientes.h"
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
    system("cls || clear");
}

/* =========================
   MENU PRINCIPAL
   ========================= */

void MenuPrincipal(Supermercado *S)
{
    int op;

    if (S == NULL)
        return;

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
            // MenuCaixas(S);
            printf("Ainda nao implementado.\n");
            break;

        case 2:
            // MenuClientes(S);
            break;

        case 3:
            MenuEstatisticas(S->HCaixas, S->LProdutos);

            break;

        case 4:
            // MenuFicheiros(S);
            printf("Ainda nao implementado.\n");
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

/* =========================
   CAIXAS
   ========================= */

/*static void ListarCaixas(Supermercado *S)
{
    if (!S || !S->HCaixas || !S->HCaixas->Tabela)
    {
        printf("Nenhuma caixa registada.\n");
        return;
    }

    printf("\n===== LISTA DE CAIXAS =====\n");

    for (int i = 0; i < S->HCaixas->tamanho; i++)
    {
        Caixa *C = &S->HCaixas->Tabela[i];

        printf("Caixa %d | %s | Pessoas: %d | Produtos: %d | Fila: %d\n",
               C->id,
               C->aberta ? "Aberta" : "Fechada",
               C->totalPessoasAtendidas,
               C->totalProdutosVendidos,
               (C->fila ? C->fila->NEL : 0));
    }
}

static void AbrirCaixa(Supermercado *S)
{
    int id;
    printf("\nID da caixa: ");
    scanf("%d", &id);
    getchar();

    Caixa *C = ObterCaixa(S->HCaixas, id);

    if (!C)
    {
        printf("Caixa nao encontrada.\n");
        return;
    }

    C->aberta = 1;
    printf("Caixa aberta.\n");
}

static void FecharCaixa(Supermercado *S)
{
    int id;
    printf("\nID da caixa: ");
    scanf("%d", &id);
    getchar();

    Caixa *C = ObterCaixa(S->HCaixas, id);

    if (!C)
    {
        printf("Caixa nao encontrada.\n");
        return;
    }

    C->aberta = 0;
    printf("Caixa fechada.\n");
}

void MenuCaixas(Supermercado *S)
{
    int op;

    do
    {
        LimparTela();

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
        }

    } while (op != 0);
}

/* =========================
   CLIENTES
   ========================= */

/*void MenuClientes(Supermercado *S)
{
    int op;

    do
    {
        LimparTela();

        printf("\n===== MENU CLIENTES =====\n");
        printf("1 - Listar clientes\n");
        printf("0 - Voltar\n");
        printf("Opcao: ");

        scanf("%d", &op);
        getchar();

        /*if (op == 1)
        {
            ListarClientes(S);
            Pausar();
        }

    } while (op != 0);
}

/* =========================
   FICHEIROS
   ========================= */

/*void MenuFicheiros(Supermercado *S)
{
    int op;

    do
    {
        LimparTela();

        printf("\n===== MENU FICHEIROS =====\n");
        printf("1 - Carregar produtos\n");
        printf("2 - Carregar clientes\n");
        printf("3 - Carregar funcionarios\n");
        printf("0 - Voltar\n");
        printf("Opcao: ");

        scanf("%d", &op);
        getchar();

        switch (op)
        {
        case 1:
            printf("Ainda nao implementado.\n");
            break;

        case 2:
            printf("Ainda nao implementado.\n");
            break;

        case 3:
            printf("Ainda nao implementado.\n");
            break;
        }

    } while (op != 0);
}*/
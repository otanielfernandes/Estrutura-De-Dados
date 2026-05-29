#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../includes/Supermercado.h"
#include "../includes/Uteis.h"

/* =========================================
   MENU
========================================= */

int Menu()
{
    printf("\n====================================\n");
    printf("         MENU PRINCIPAL\n");
    printf("====================================\n");

    printf("1 - Menu Principal\n");
    printf("2 - Estatisticas\n");
    printf("3 - Estado das Caixas\n");
    printf("4 - Memoria Utilizada\n");
    printf("5 - Parar Simulacao\n");
    printf("6 - Continuar Simulacao\n");
    printf("0 - Sair\n");

    printf("\nOpcao: ");

    return LerInteiro("");
}

/* =========================================
   EXECUTAR OPCOES
========================================= */

void ExecutaAccoesMenu(Supermercado *S, int *simulacaoAtiva,
                       int *programaAtivo)
{
    int op = Menu();

    switch (op)
    {
    case 1:

        MenuPrincipal(S);

        break;

    case 2:

        MenuEstatisticas(S->HCaixas);

        break;

    case 3:

        MostrarMatrizSupermercado(S->HCaixas);

        break;

    case 4:

        printf("\nMemoria Utilizada: %lu bytes\n",
               (unsigned long)MemoriaUtilizada(S));

        break;

    case 5:

        *simulacaoAtiva = 0;

        printf("\nSimulacao parada.\n");

        break;

    case 6:

        *simulacaoAtiva = 1;

        printf("\nSimulacao retomada.\n");

        break;

    case 0:

        *programaAtivo = 0;

        printf("\nA sair do programa...\n");

        break;

    default:

        printf("\nOpcao invalida.\n");
    }

    printf("\nPrima ENTER para continuar...");
    getchar();
}

/* =========================================
   MAIN
========================================= */

int main()
{
#ifdef _WIN32
    system("chcp 65001 > nul");
#endif

    srand((unsigned)time(NULL));

    printf("========================================\n");
    printf("   PROJETO ED - SUPERMERCADO\n");
    printf("========================================\n");

    Supermercado *S = CriarSupermercado("Lidl");

    if (S == NULL)
    {
        printf("Erro ao criar supermercado.\n");

        return 1;
    }

    if (!InicializarSupermercado(S, "dados/Configuracao.txt"))
    {
        printf("Erro ao inicializar supermercado.\n");

        DestruirSupermercado(S);

        return 1;
    }

    printf("\nProdutos carregados: %d\n", S->LProdutos->NEL);

    printf("Clientes carregados: %d\n", S->LClientes->NEL);

    printf("\n========================================\n");
    printf(" SIMULACAO INICIADA\n");
    printf(" Prima qualquer tecla para abrir menu\n");
    printf("========================================\n");

    int programaAtivo = 1;

    int simulacaoAtiva = 1;

    while (programaAtivo)
    {
        /* EXECUTA SIMULACAO */

        if (simulacaoAtiva)
        {
            ExecutarSimulacao(S);
        }

        /* MENU APENAS SE CLICAR TECLA */

        if (TeclaPressionada())
        {
            ExecutaAccoesMenu(S, &simulacaoAtiva, &programaAtivo);

            printf("\nSimulacao retomada...\n");
        }

        wait_segundos(1);
    }

    printf("\n========================================\n");
    printf("        ESTATISTICAS FINAIS\n");
    printf("========================================\n");

    MenuEstatisticas(S->HCaixas);

    DestruirSupermercado(S);

    return 0;
}
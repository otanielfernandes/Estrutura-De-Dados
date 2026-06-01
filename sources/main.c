#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../includes/Supermercado.h"
#include "../includes/Uteis.h"
#include "../includes/UI.h"

int Menu()
{
    int op;

    printf("\n╔════════════════════════════════════╗\n");
    printf("║     SUPERMERCADO SIMULADOR        ║\n");
    printf("╠════════════════════════════════════╣\n");
    printf("║ 1  - Menu Principal               ║\n");
    printf("║ 2  - Estatísticas                 ║\n");
    printf("║ 3  - Estado das Caixas           ║\n");
    printf("║ 4  - Memória Utilizada           ║\n");
    printf("║ 5  - Parar Simulação             ║\n");
    printf("║ 6  - Continuar Simulação         ║\n");
    printf("║ 0  - Sair                        ║\n");
    printf("╚════════════════════════════════════╝\n");

    printf("Opção: ");
    scanf("%d", &op);
    getchar();

    return op;
}

void ExecutaAccoesMenu(Supermercado *S, int *simulacaoAtiva, int *programaAtivo)
{
    int op = Menu();

    limparTela();

    switch (op)
    {
    case 1:
        cor(9);
        printf("\n[MENU PRINCIPAL]\n");
        resetCor();
        MenuPrincipal(S);
        break;

    case 2:
        cor(10);
        printf("\n[ESTATÍSTICAS]\n");
        resetCor();
        MenuEstatisticas(S->HCaixas);
        break;

    case 3:
        cor(11);
        printf("\n[CAIXAS]\n");
        resetCor();
        MostrarMatrizSupermercado(S->HCaixas);
        break;

    case 4:
        cor(14);
        printf("\n[MEMÓRIA]\n");
        resetCor();
        printf("Utilizada: %lu bytes\n",
               (unsigned long)MemoriaUtilizada(S));
        break;

    case 5:
        *simulacaoAtiva = 0;
        cor(12);
        printf("\nSimulação parada.\n");
        resetCor();
        break;

    case 6:
        *simulacaoAtiva = 1;
        cor(10);
        printf("\nSimulação retomada.\n");
        resetCor();
        break;

    case 0:
        *programaAtivo = 0;
        cor(12);
        printf("\nA sair...\n");
        resetCor();
        break;
    }

    printf("\nENTER para continuar...");
    getchar();
}

int main()
{
#ifdef _WIN32
    system("chcp 65001 > nul");
#endif

    srand((unsigned)time(NULL));
    limparTela();

    cor(11);
    printf("====================================\n");
    printf("   PROJETO SUPERMERCADO SIMULADOR  \n");
    printf("====================================\n");
    resetCor();

    Supermercado *S = CriarSupermercado("Lidl");

    if (!S || !InicializarSupermercado(S, "dados/Configuracao.txt"))
    {
        cor(12);
        printf("Erro ao iniciar sistema.\n");
        resetCor();
        return 1;
    }

    printf("\nProdutos: %d | Clientes: %d\n",
           S->LProdutos->NEL,
           S->LClientes->NEL);

    int programaAtivo = 1;
    int simulacaoAtiva = 1;

    while (programaAtivo)
    {
        if (simulacaoAtiva)
            ExecutarSimulacao(S);

        if (TeclaPressionada())
            ExecutaAccoesMenu(S, &simulacaoAtiva, &programaAtivo);

        wait_segundos(1);
    }

    limparTela();

    cor(10);
    printf("\n=== ESTATÍSTICAS FINAIS ===\n");
    resetCor();

    MenuEstatisticas(S->HCaixas);

    DestruirSupermercado(S);
    return 0;
}
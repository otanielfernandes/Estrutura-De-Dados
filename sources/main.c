#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../includes/Supermercado.h"
#include "../includes/Uteis.h"

/* =========================
   MENU SIMPLES DE TESTE
   ========================= */

int Menu()
{
    printf("\n===== MENU SIMULACAO =====\n");
    printf("1 - Executar Menu Principal\n");
    printf("2 - Mostrar Estatisticas\n");
    printf("0 - Sair\n");

    return LerInteiro("Opcao: ");
}

/* =========================
   EXECUÇÃO MENU
   ========================= */

void ExecutaAccoesMenu(Supermercado *S)
{
    int op = Menu();

    switch (op)
    {
    case 1:
        MenuPrincipal(S);
        break;

    case 2:
        MenuEstatisticas(S->HCaixas, S->LProdutos);
        break;

    case 0:
        printf("A sair...\n");
        break;

    default:
        printf("Opcao invalida.\n");
        break;
    }
}

/* =========================
   MAIN
   ========================= */

int main()
{
    system("chcp 65001");
    printf("Projeto ED - Supermercado\n");

    srand((unsigned)time(NULL));

    Supermercado *S = CriarSupermercado("Lidl");

    if (S == NULL)
    {
        printf("Erro ao criar supermercado.\n");
        return 1;
    }

    InicializarSupermercado(S, "dados/Configuracao.txt");

    int terminar = 0;

    while (!terminar)
    {
        if (TeclaPressionada())
        {
            ExecutaAccoesMenu(S);
        }

        ExecutarSimulacao(S);

        wait_segundos(1);

        terminar = Supermercado_E_Para_Fechar(S);
    }

    printf("\nSimulacao terminada.\n");

    // Debug opcional
    // MostrarHashing(S->HCaixas);

    DestruirSupermercado(S);

    return 0;
}
#include "../includes/Estatisticas.h"
#include "../includes/Hashing.h"
#include "../includes/ListaProdutos.h"
#include <stdio.h>
#include <stdlib.h>

/* =========================
   FUNÇÕES AUXILIARES
   ========================= */

static void LimparTela(void)
{
    system("cls || clear");
}

static void Pausar(void)
{
    printf("\nPrima ENTER para continuar...");
    getchar();
}

/* =========================
   MENU
   ========================= */

static void MostrarMenuEstatisticas(void)
{
    printf("===================================\n");
    printf("       MENU  ESTATISTICAS\n");
    printf("===================================\n\n");

    printf(" 2  - Caixa com mais produtos\n");
    printf(" 3  - Numero de produtos oferecidos\n");
    printf(" 4  - Custo produtos oferecidos\n");
    printf(" 5  - Tempo medio espera caixas\n");
    printf(" 6  - Total clientes atendidos\n");
    printf(" 7  - Operador com menos pessoas\n");
    printf(" 8  - Operador com mais produtos\n");
    printf(" 9  - Caixa com menos pessoas\n");
    printf("10  - Caixa com mais pessoas\n");
    printf("11  - Estatisticas globais\n");
    printf(" 0  - Voltar\n");
}

/* =========================
   MENU PRINCIPAL
   ========================= */

void MenuEstatisticas(Hashing *H, ListaProdutos *LP)
{
    Estatisticas E;
    int opcao;

    do
    {
        LimparTela();
        MostrarMenuEstatisticas();

        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        LimparTela();

        switch (opcao)
        {
        case 2:
            ObterCaixaMaisProdutos(H, &E);
            printf("CAIXA COM MAIS PRODUTOS\n\n");
            printf("Caixa: %d (%d produtos)\n",
                   E.idCaixaMaisProdutos, E.maxProdutosVendidos);
            Pausar();
            break;

        case 3:
            ObterNumeroProdutosOferecidos(LP, &E);
            printf("PRODUTOS OFERECIDOS\n\n");
            printf("Total: %d\n", E.numeroProdutosOferecidos);
            Pausar();
            break;

        case 4:
            ValorTotalProdutosOferecidos(LP, &E);
            printf("CUSTO PRODUTOS OFERECIDOS\n\n");
            printf("Custo total: %.2f EUR\n", E.custoOferecidos);
            Pausar();
            break;

        case 5:
            TempoMedioEsperaCaixas(H, &E);
            printf("TEMPO MEDIO DE ESPERA\n\n");
            printf("Tempo: %.2f s\n", E.tempoMedioEsperaCaixas);
            Pausar();
            break;

        case 6:
            NumeroTotalClientesAtendidos(H, &E);
            printf("TOTAL CLIENTES ATENDIDOS\n\n");
            printf("Total: %d\n", E.numeroTotalClientesAtendidos);
            Pausar();
            break;

        case 7:
            OperadorMenosPessoas(H, &E);
            printf("OPERADOR COM MENOS PESSOAS\n\n");
            printf("Caixa: %d\n", E.operadorMenosPessoas);
            Pausar();
            break;

        case 8:
            ObterOperadorMaisProdutos(H, &E);
            printf("OPERADOR COM MAIS PRODUTOS\n\n");
            printf("Caixa: %d\n", E.operadorMaisProdutos);
            Pausar();
            break;

        case 9:
            ObterCaixaMenosPessoas(H, &E);
            printf("CAIXA COM MENOS PESSOAS\n\n");
            printf("Caixa: %d\n", E.idCaixaMenosPessoas);
            Pausar();
            break;

        case 10:
            ObterCaixaMaisPessoas(H, &E);
            printf("CAIXA COM MAIS PESSOAS\n\n");
            printf("Caixa: %d\n", E.idCaixaMaisPessoas);
            Pausar();
            break;

        case 11:
            printf("ESTATISTICAS GLOBAIS\n\n");
            MostrarEstatisticasSupermercado(H, LP);
            Pausar();
            break;

        case 0:
            printf("A sair...\n");
            break;

        default:
            printf("Opcao invalida!\n");
            Pausar();
            break;
        }

    } while (opcao != 0);
}
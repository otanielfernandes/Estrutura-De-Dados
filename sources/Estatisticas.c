#include "../includes/Estatisticas.h"
#include "../includes/Hashing.h"
#include "../includes/ListaProdutos.h"
#include <stdio.h>
#include <stdlib.h>

/* =========================
   FUNÇÕES AUXILIARES
   ========================= */

/*static void LimparTela(void)
{
    system("cls || clear");
}*/

static void Pausar(void)
{
    printf("\nPrima ENTER para continuar...");
    getchar();
}

// =====================================================
// MENU ESTATISTICAS
// =====================================================

static void MostrarMenuEstatisticas(void)
{
    printf("=========================================\n");
    printf("         MENU ESTATISTICAS\n");
    printf("=========================================\n\n");

    printf(" 1  - Caixa com mais produtos\n");
    printf(" 2  - Caixa com mais clientes\n");
    printf(" 3  - Caixa com menos clientes\n");
    printf(" 4  - Numero produtos oferecidos\n");
    printf(" 5  - Valor produtos oferecidos\n");
    printf(" 6  - Numero produtos vendidos\n");
    printf(" 7  - Tempo medio espera\n");
    printf(" 8  - Tempo total atendimento\n");
    printf(" 9  - Total clientes atendidos\n");
    printf("10  - Numero caixas abertas\n");
    printf("11  - Numero caixas fechadas\n");
    printf("12  - Maior fila\n");
    printf("13  - Operador menos clientes\n");
    printf("14  - Operador mais produtos\n");
    printf("15  - Estatisticas globais\n");

    printf("\n 0  - Voltar\n");
}

// =====================================================
// MENU PRINCIPAL ESTATISTICAS
// =====================================================

void MenuEstatisticas(Hashing *H,
                      ListaProdutos *LP)
{
    Estatisticas E;
    int opcao;

    do
    {
        MostrarMenuEstatisticas();

        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        // LimparTela();

        switch (opcao)
        {
        case 1:

            ObterCaixaMaisProdutos(H, &E);

            printf("CAIXA COM MAIS PRODUTOS\n\n");

            printf("Caixa: %d\n",
                   E.idCaixaMaisProdutos);

            printf("Produtos vendidos: %d\n",
                   E.maxProdutosVendidos);

            break;

        case 2:

            ObterCaixaMaisPessoas(H, &E);

            printf("CAIXA COM MAIS CLIENTES\n\n");

            printf("Caixa: %d\n",
                   E.idCaixaMaisPessoas);

            printf("Clientes atendidos: %d\n",
                   E.maxPessoasAtendidas);

            break;

        case 3:

            ObterCaixaMenosPessoas(H, &E);

            printf("CAIXA COM MENOS CLIENTES\n\n");

            printf("Caixa: %d\n",
                   E.idCaixaMenosPessoas);

            printf("Clientes atendidos: %d\n",
                   E.minPessoasAtendidas);

            break;

        case 4:

            ObterNumeroProdutosOferecidos(LP, &E);

            printf("NUMERO PRODUTOS OFERECIDOS\n\n");

            printf("Total: %d\n",
                   E.numeroProdutosOferecidos);

            break;

        case 5:

            ValorTotalProdutosOferecidos(LP, &E);

            printf("VALOR PRODUTOS OFERECIDOS\n\n");

            printf("Valor: %.2f EUR\n",
                   E.custoOferecidos);

            break;

        case 6:

            ObterNumeroProdutosVendidos(H, &E);

            printf("NUMERO PRODUTOS VENDIDOS\n\n");

            printf("Produtos vendidos: %d\n",
                   E.numeroTotalProdutosVendidos);

            break;

        case 7:

            TempoMedioEsperaCaixas(H, &E);

            printf("TEMPO MEDIO ESPERA\n\n");

            printf("Tempo medio: %.2f segundos\n",
                   E.tempoMedioEsperaCaixas);

            break;

        case 8:

            ObterTempoTotalAtendimento(H, &E);

            printf("TEMPO TOTAL ATENDIMENTO\n\n");

            printf("Tempo total: %.2f segundos\n",
                   E.tempoTotalAtendimento);

            break;

        case 9:

            NumeroTotalClientesAtendidos(H, &E);

            printf("TOTAL CLIENTES ATENDIDOS\n\n");

            printf("Clientes: %d\n",
                   E.numeroTotalClientesAtendidos);

            break;

        case 10:

            ObterNumeroCaixasAbertas(H, &E);

            printf("CAIXAS ABERTAS\n\n");

            printf("Total: %d\n",
                   E.numeroCaixasAbertas);

            break;

        case 11:

            ObterNumeroCaixasFechadas(H, &E);

            printf("CAIXAS FECHADAS\n\n");

            printf("Total: %d\n",
                   E.numeroCaixasFechadas);

            break;

        case 12:

            ObterMaiorFila(H, &E);

            printf("MAIOR FILA\n\n");

            printf("Maior fila registada: %d clientes\n",
                   E.maiorFila);

            break;

        case 13:

            OperadorMenosPessoas(H, &E);

            printf("OPERADOR MENOS CLIENTES\n\n");

            printf("Caixa: %d\n",
                   E.operadorMenosPessoas);

            break;

        case 14:

            ObterOperadorMaisProdutos(H, &E);

            printf("OPERADOR MAIS PRODUTOS\n\n");

            printf("Caixa: %d\n",
                   E.operadorMaisProdutos);

            break;

        case 15:

            MostrarEstatisticasSupermercado(H, LP);

            break;

        case 0:

            printf("A sair...\n");

            break;

        default:

            printf("Opcao invalida!\n");

            break;
        }

        if (opcao != 0)
        {
            Pausar();
        }

        // LimparTela();

    } while (opcao != 0);
}
#include "../includes/Estatisticas.h"
#include "../includes/MatrizSupermercado.h"
#include "../includes/ListaProdutos.h"
#include <stdio.h>
#include <stdlib.h>

/*FUNÇÕES AUXILIARES */
/*static void LimparTela(void)
{
    system("cls || clear");
}*/

/*static void Pausar(void)
{
    printf("\nPrima ENTER para continuar...");
    getchar();
}*/

// MENU ESTATISTICA
static void MostrarMenuEstatisticas(void)
{
    printf("\n╔════════════════════════════════════╗\n");
    printf("║     PAINEL DE ESTATISTICAS         ║\n");
    printf("╚════════════════════════════════════╝\n");

    printf("  1  | Caixa com mais produtos\n");
    printf("  2  | Caixa com mais clientes\n");
    printf("  3  | Caixa com menos clientes\n");
    printf("  4  | Numero de produtos oferecidos\n");
    printf("  5  | Valor total de produtos oferecidos\n");
    printf("  6  | Numero de produtos vendidos\n");
    printf("  7  | Tempo medio de espera\n");
    printf("  8  | Tempo total de atendimento\n");
    printf("  9  | Total de clientes atendidos\n");
    printf(" 10  | Numero de caixas abertas\n");
    printf(" 11  | Numero de caixas fechadas\n");
    printf(" 12  | Maior fila registada\n");
    printf(" 13  | Operador com menos clientes\n");
    printf(" 14  | Operador com mais produtos\n");
    printf(" 15  | Resumo global do supermercado\n");

    printf("\n  0  | Voltar\n");
    printf("╚════════════════════════════════════╝\n");
}

// MENU PRINCIPAL ESTATISTICAS
void MenuEstatisticas(MatrizSupermercado *H)
{
    Estatisticas E = {0};
    int opcao = -1;

    do
    {
        MostrarMenuEstatisticas();

        printf("\nEscolha uma opcao: ");

        if (scanf("%d", &opcao) != 1)
        {
            while (getchar() != '\n')
                ; // limpa buffer
            opcao = -1;
            continue;
        }

        getchar(); // limpar ENTER

        switch (opcao)
        {
        case 1:
            ObterCaixaMaisProdutos(H, &E);
            printf("\nCaixa: %d | Produtos: %d\n",
                   E.idCaixaMaisProdutos,
                   E.maxProdutosVendidos);
            break;

        case 2:
            ObterCaixaMaisPessoas(H, &E);
            printf("\nCaixa: %d | Clientes: %d\n",
                   E.idCaixaMaisPessoas,
                   E.maxPessoasAtendidas);
            break;

        case 3:
            ObterCaixaMenosPessoas(H, &E);
            printf("\nCaixa: %d | Clientes: %d\n",
                   E.idCaixaMenosPessoas,
                   E.minPessoasAtendidas);
            break;

        case 4:
            ObterNumeroProdutosOferecidos(H, &E);
            printf("\nProdutos oferecidos: %d\n",
                   E.numeroProdutosOferecidos);
            break;

        case 5:
            ValorTotalProdutosOferecidos(H, &E);
            printf("\nValor total: %.2f EUR\n",
                   E.custoOferecidos);
            break;

        case 6:
            ObterNumeroProdutosVendidos(H, &E);
            printf("\nProdutos vendidos: %d\n",
                   E.numeroTotalProdutosVendidos);
            break;

        case 7:
            TempoMedioEsperaCaixas(H, &E);
            printf("\nTempo medio: %.2f s\n",
                   E.tempoMedioEsperaCaixas);
            break;

        case 8:
            ObterTempoTotalAtendimento(H, &E);
            printf("\nTempo total: %.2f s\n",
                   E.tempoTotalAtendimento);
            break;

        case 9:
            NumeroTotalClientesAtendidos(H, &E);
            printf("\nClientes: %d\n",
                   E.numeroTotalClientesAtendidos);
            break;

        case 10:
            ObterNumeroCaixasAbertas(H, &E);
            printf("\nCaixas abertas: %d\n",
                   E.numeroCaixasAbertas);
            break;

        case 11:
            ObterNumeroCaixasFechadas(H, &E);
            printf("\nCaixas fechadas: %d\n",
                   E.numeroCaixasFechadas);
            break;

        case 12:
            ObterMaiorFila(H, &E);
            printf("\nMaior fila: %d\n",
                   E.maiorFila);
            break;

        case 13:
            OperadorMenosPessoas(H, &E);
            printf("\nCaixa: %d\n",
                   E.operadorMenosPessoas);
            break;

        case 14:
            ObterOperadorMaisProdutos(H, &E);
            printf("\nCaixa: %d\n",
                   E.operadorMaisProdutos);
            break;

        case 15:
            MostrarEstatisticasSupermercado(H);
            break;

        case 0:
            printf("\nA sair...\n");
            break;

        default:
            printf("\nOpcao invalida!\n");
            break;
        }

        if (opcao != 0)
        {
            printf("\nPrima ENTER para continuar...");
            getchar();
        }

    } while (opcao != 0);
}
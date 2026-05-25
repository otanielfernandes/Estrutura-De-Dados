#include "../includes/Estatisticas.h"

static void LimparTela(void)
{
    system("cls || clear");
}

static void Pausar(void)
{
    printf("\nPrima ENTER para continuar...");
    getchar();
}

static void MostrarMenuEstatisticas(void)
{
    printf("===================================\n");
    printf("       MENU  ESTATISTICAS\n");
    printf("===================================\n\n");
    printf(" 1  - Memoria utilizada\n");
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

// Menu de Estatísticas

void MenuEstatisticas(Supermercado *S)
{
    Estatisticas E;
    int opcao;

    do
    {
        LimparTela();
        MostrarMenuEstatisticas();
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); /* consumir '\n' */
        LimparTela();

        switch (opcao)
        {
        /* 1  Memória*/
        case 1:
            MemoriaUtilizada(S, &E);
            printf("MEMORIA UTILIZADA\n\n");
            printf("Total: %.2f bytes\n", E.memoriaUtilizada);
            Pausar();
            break;

        /* 2 Caixa com mais produtos  */
        case 2:
            ObterCaixaMaisProdutos(S, &E);
            printf("CAIXA COM MAIS PRODUTOS\n\n");
            if (E.idCaixaMaisProdutos != -1)
            {
                printf("Caixa           : %d\n", E.idCaixaMaisProdutos);
                printf("Produtos vendidos: %d\n", E.maxProdutosVendidos);
            }
            else
                printf("Nenhuma caixa encontrada.\n");
            Pausar();
            break;

        /* 3  Produtos oferecidos */
        case 3:
            ObterNumeroProdutosOferecidos(S, &E);
            printf("PRODUTOS OFERECIDOS\n\n");
            printf("Total: %d\n", E.numeroProdutosOferecidos);
            Pausar();
            break;

        /* 4  Custo produtos oferecidos */
        case 4:
            ValorTotalProdutosOferecidos(S, &E);
            printf("CUSTO PRODUTOS OFERECIDOS\n\n");
            printf("Custo total: %.2f EUR\n", E.custoOferecidos);
            Pausar();
            break;

        /* 5  Tempo médio de espera */
        case 5:
            TempoMedioEsperaCaixas(S, &E);
            printf("TEMPO MEDIO DE ESPERA NAS CAIXAS\n\n");
            printf("Tempo medio: %.2f s\n", E.tempoMedioEsperaCaixas);
            Pausar();
            break;

        /* 6  Total clientes atendidos */
        case 6:
            NumeroTotalClientesAtendidos(S, &E);
            printf("TOTAL CLIENTES ATENDIDOS\n\n");
            printf("Total: %d\n", E.numeroTotalClientesAtendidos);
            Pausar();
            break;

        /* 7  Operador com menos pessoas */
        case 7:
            OperadorMenosPessoas(S, &E);
            printf("OPERADOR COM MENOS PESSOAS\n\n");
            if (E.operadorMenosPessoas != -1)
                printf("Caixa do operador: %d\n", E.operadorMenosPessoas);
            else
                printf("Nenhum operador ativo encontrado.\n");
            Pausar();
            break;

        /* 8  Operador com mais produtos */
        case 8:
            ObterOperadorMaisProdutos(S, &E);
            printf("OPERADOR COM MAIS PRODUTOS\n\n");
            if (E.operadorMaisProdutos != -1)
                printf("Caixa do operador: %d\n", E.operadorMaisProdutos);
            else
                printf("Nenhum operador ativo encontrado.\n");
            Pausar();
            break;

        /* 9  Caixa com menos pessoas */
        case 9:
            ObterCaixaMenosPessoas(S, &E);
            printf("CAIXA COM MENOS PESSOAS\n\n");
            if (E.idCaixaMenosPessoas != -1)
                printf("Caixa: %d\n", E.idCaixaMenosPessoas);
            else
                printf("Nenhuma caixa encontrada.\n");
            Pausar();
            break;

        /* 10  Caixa com mais pessoas */
        case 10:
            ObterCaixaMaisPessoas(S, &E);
            printf("CAIXA COM MAIS PESSOAS\n\n");
            if (E.idCaixaMaisPessoas != -1)
                printf("Caixa: %d\n", E.idCaixaMaisPessoas);
            else
                printf("Nenhuma caixa encontrada.\n");
            Pausar();
            break;

        /* 11  Estatísticas globais */
        case 11:
            printf("ESTATISTICAS GLOBAIS\n\n");
            MostrarEstatisticasSupermercado(S);
            Pausar();
            break;

        /* 0  Voltar */
        case 0:
            printf("A voltar ao menu principal...\n");
            break;

        default:
            printf("Opcao invalida! Escolha entre 0 e 11.\n");
            Pausar();
        }

    } while (opcao != 0);
}

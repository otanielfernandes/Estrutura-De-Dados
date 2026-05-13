/*#include "../includes/Estatisticas.h"
#include "../includes/Supermercado.h"
#include <stdio.h>

void MenuEstatisticas(Supermercado *S)
{

    int op;

    do
    {

        system("cls || clear");

        printf("\n===== MENU ESTATISTICAS =====\n");
        printf("1 - Estatisticas globais\n");
        printf("2 - Memoria utilizada\n");
        printf("3 - Melhor caixa\n");
        printf("4 - Produtos oferecidos\n");
        printf("0 - Voltar\n");

        printf("\nOpcao: ");
        scanf("%d", &op);

        switch (op)
        {

        case 1:

            system("cls || clear");

            MostrarEstatisticasSupermercado(S);

            printf("\nPrima ENTER para continuar...");
            getchar();
            getchar();

            break;

        case 2:
        {

            system("cls || clear");

            size_t memoria = sizeof(Supermercado);

            if (S->LPessoas != NULL)
            {
                memoria += sizeof(*(S->LPessoas));
            }

            printf("\n===== MEMORIA =====\n");
            printf("Memoria utilizada: %zu bytes\n", memoria);

            printf("\nPrima ENTER para continuar...");
            getchar();
            getchar();

            break;
        }

        case 3:
        {

            system("cls || clear");

            Estatisticas E = CalcularEstatisticas(S);

            printf("\n===== MELHOR CAIXA =====\n");

            if (E.idCaixaMaisPessoas >= 0)
            {
                printf("Caixa com mais atendimentos: %d\n",
                       E.idCaixaMaisPessoas);
            }
            else
            {
                printf("Nenhuma caixa encontrada.\n");
            }

            printf("\nPrima ENTER para continuar...");
            getchar();
            getchar();

            break;
        }

        case 4:
        {

            system("cls || clear");

            Estatisticas E = CalcularEstatisticas(S);

            printf("\n===== PRODUTOS OFERECIDOS =====\n");
            printf("Produtos oferecidos: %d\n",
                   E.produtosOferecidos);

            printf("Custo total: %.2f euros\n",
                   E.custoOferecidos);

            printf("\nPrima ENTER para continuar...");
            getchar();
            getchar();

            break;
        }

        case 0:
            break;

        default:

            printf("\nOpcao invalida.\n");

            printf("\nPrima ENTER para continuar...");
            getchar();
            getchar();
        }

    } while (op != 0);
}*/
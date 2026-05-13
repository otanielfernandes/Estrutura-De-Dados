/*#include "Menu.h"
#include "Estatisticas.h"
#include <stdio.h>
#include <string.h>

void pausar() {
    printf("\nPrima ENTER para continuar...");
    getchar();
    getchar();
}

// ================= MENU PRINCIPAL =================

void MenuPrincipal(Supermercado *S) {

    int op;

    do {

        system("cls || clear");

        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1 - Caixas\n");
        printf("2 - Clientes\n");
        printf("3 - Estatisticas\n");
        printf("4 - Ficheiros\n");
        printf("0 - Sair\n");

        printf("\nOpcao: ");
        scanf("%d", &op);

        switch(op) {

            case 1:
                MenuCaixas(S);
                break;

            case 2:
                MenuClientes(S);
                break;

            case 3:
                MenuEstatisticas(S);
                break;

            case 4:
                MenuFicheiros(S);
                break;

            case 0:
                printf("\nAte logo!\n");
                break;

            default:
                printf("\nOpcao invalida.\n");
                pausar();
        }

    } while(op != 0);
}

// ================= MENU CAIXAS =================

void listarCaixas(Supermercado *S) {

    printf("\n===== LISTA DE CAIXAS =====\n");

    if(S->HCaixas == NULL) {
        printf("Nenhuma caixa implementada.\n");
    }
}

void MenuCaixas(Supermercado *S) {

    int op;

    do {

        system("cls || clear");

        printf("\n===== MENU CAIXAS =====\n");
        printf("1 - Listar caixas\n");
        printf("2 - Abrir caixa\n");
        printf("3 - Fechar caixa\n");
        printf("0 - Voltar\n");

        printf("\nOpcao: ");
        scanf("%d", &op);

        switch(op) {

            case 1:
                listarCaixas(S);
                pausar();
                break;

            case 2:
                printf("\nAbrir caixa ainda nao implementado.\n");
                pausar();
                break;

            case 3:
                printf("\nFechar caixa ainda nao implementado.\n");
                pausar();
                break;

            case 0:
                break;

            default:
                printf("\nOpcao invalida.\n");
                pausar();
        }

    } while(op != 0);
}

// ================= MENU CLIENTES =================

void listarClientes(Supermercado *S) {

    printf("\n===== CLIENTES =====\n");

    if(S->LPessoas == NULL || S->LPessoas->NEL == 0) {
        printf("Nenhum cliente registado.\n");
        return;
    }

    NoPessoa *no = S->LPessoas->Inicio;

    while(no != NULL) {

        Pessoa *P = no->Info;

        if(P != NULL) {
            printf("Nome: %s\n", P->nome);
            printf("Produtos: %d\n\n", P->nProdutos);
        }

        no = no->Prox;
    }
}

void pesquisarCliente(Supermercado *S) {

    char nome[100];
    int encontrado = 0;

    printf("\nNome do cliente: ");
    scanf("%s", nome);

    if(S->LPessoas != NULL) {

        NoPessoa *no = S->LPessoas->Inicio;

        while(no != NULL) {

            Pessoa *P = no->Info;

            if(P != NULL && strcmp(P->nome, nome) == 0) {

                printf("\nCliente encontrado!\n");
                printf("Nome: %s\n", P->nome);
                printf("Produtos: %d\n", P->nProdutos);

                encontrado = 1;
                break;
            }

            no = no->Prox;
        }
    }

    if(!encontrado) {
        printf("\nCliente nao encontrado.\n");
    }
}

void MenuClientes(Supermercado *S) {

    int op;

    do {

        system("cls || clear");

        printf("\n===== MENU CLIENTES =====\n");
        printf("1 - Listar clientes\n");
        printf("2 - Pesquisar cliente\n");
        printf("3 - Mover cliente\n");
        printf("0 - Voltar\n");

        printf("\nOpcao: ");
        scanf("%d", &op);

        switch(op) {

            case 1:
                listarClientes(S);
                pausar();
                break;

            case 2:
                pesquisarCliente(S);
                pausar();
                break;

            case 3:
                printf("\nMover cliente ainda nao implementado.\n");
                pausar();
                break;

            case 0:
                break;

            default:
                printf("\nOpcao invalida.\n");
                pausar();
        }

    } while(op != 0);
}

// ================= MENU FICHEIROS =================

void MenuFicheiros(Supermercado *S) {

    int op;

    do {

        system("cls || clear");

        printf("\n===== MENU FICHEIROS =====\n");
        printf("1 - Guardar CSV\n");
        printf("2 - Guardar relatorio\n");
        printf("3 - Carregar dados\n");
        printf("0 - Voltar\n");

        printf("\nOpcao: ");
        scanf("%d", &op);

        switch(op) {

            case 1:
                printf("\nGuardar CSV ainda nao implementado.\n");
                pausar();
                break;

            case 2:
                printf("\nRelatorio final ainda nao implementado.\n");
                pausar();
                break;

            case 3:
                printf("\nCarregar dados ainda nao implementado.\n");
                pausar();
                break;

            case 0:
                break;

            default:
                printf("\nOpcao invalida.\n");
                pausar();
        }

    } while(op != 0);
}
    */
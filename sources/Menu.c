#include "../includes/Estatisticas.h"
#include "../includes/Supermercado.h"
#include "../includes/Ficheiro.h"
#include "../includes/ListaClientes.h"
#include "../includes/MatrizSupermercado.h"
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
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/* MENU PRINCIPAL */
void MenuPrincipal(Supermercado *S)
{
    int op;

    if (S == NULL)
        return;

    do
    {
        LimparTela();
        printf("\n");
        printf("╔════════════════════════════════════════════════════╗\n");
        printf("║              SUPERMERCADO %-24s ║\n", S->NOME);
        printf("╠════════════════════════════════════════════════════╣\n");
        printf("║ 1  - Gestao de Caixas                              ║\n");
        printf("║ 2  - Gestao de Clientes                            ║\n");
        printf("║ 3  - Estatisticas                                  ║\n");
        printf("║ 4  - Ficheiros                                     ║\n");
        printf("║ 5  - Produtos                                      ║\n");
        printf("║ 6  - Funcionarios                                  ║\n");
        printf("║ 0  - Sair                                          ║\n");
        printf("╚════════════════════════════════════════════════════╝\n");

        printf("\nOpcao: ");

        scanf("%d", &op);
        getchar();

        switch (op)
        {
        case 1:
            LimparTela();
            MenuCaixas(S->HCaixas);
            break;

        case 2:
            LimparTela();
            MenuClientes(S);
            break;

        case 3:
            LimparTela();
            MenuEstatisticas(S->HCaixas);
            break;

        case 4:
            LimparTela();
            MenuFicheiros(
                S->LProdutos,
                S->LClientes,
                S->LFuncionarios,
                S->HCaixas);
            break;

        case 5:
            LimparTela();
            MenuProdutos(S->LProdutos);
            break;

        case 6:
            LimparTela();
            MenuFuncionarios(S->LFuncionarios);
            break;

        case 0:
            LimparTela();
            printf("\nA Sair...\n");
            break;

        default:
            LimparTela();
            printf("\n[ERRO] Opcao invalida.\n");
            Pausar();
        }

    } while (op != 0);
}

/* FUNCIONARIOS */

static void ListarFuncionariosMenu(ListaFuncionarios *LF)
{
    if (LF == NULL || LF->Inicio == NULL)
    {
        printf("\nNenhum funcionario registado.\n");
        return;
    }

    printf("\n");
    printf("═══════════════════════════════════════════════════════\n");
    printf(" ID       NOME\n");
    printf("═══════════════════════════════════════════════════════\n");

    NoFuncionario *Aux = LF->Inicio;

    while (Aux != NULL)
    {
        printf(" %-8d %s\n",
               Aux->Func->id,
               Aux->Func->nome);

        Aux = Aux->Prox;
    }

    printf("═══════════════════════════════════════════════════════\n");
}

static void PesquisarFuncionario(ListaFuncionarios *LF)
{
    int id;

    printf("\nID do funcionario: ");
    scanf("%d", &id);
    getchar();

    NoFuncionario *Aux = LF->Inicio;

    while (Aux != NULL)
    {
        if (Aux->Func != NULL &&
            Aux->Func->id == id)
        {
            printf("\n");
            printf("╔══════════════════════════════════════╗\n");
            printf("║      DADOS DO FUNCIONARIO            ║\n");
            printf("╚══════════════════════════════════════╝\n");

            printf("ID   : %d\n",
                   Aux->Func->id);

            printf("Nome : %s\n",
                   Aux->Func->nome);

            return;
        }

        Aux = Aux->Prox;
    }

    printf("\nFuncionario nao encontrado.\n");
}

void MenuFuncionarios(ListaFuncionarios *LF)
{
    int op;

    if (LF == NULL)
        return;

    do
    {
        LimparTela();

        printf("\n");
        printf("╔══════════════════════════════╗\n");
        printf("║      MENU FUNCIONARIOS       ║\n");
        printf("╠══════════════════════════════╣\n");
        printf("║ 1 - Listar Funcionarios      ║\n");
        printf("║ 2 - Pesquisar por ID         ║\n");
        printf("║ 0 - Voltar                   ║\n");
        printf("╚══════════════════════════════╝\n");

        printf("\nOpcao: ");

        scanf("%d", &op);
        getchar();

        switch (op)
        {
        case 1:
            LimparTela();
            ListarFuncionariosMenu(LF);
            Pausar();
            break;

        case 2:
            LimparTela();
            PesquisarFuncionario(LF);
            Pausar();
            break;

        case 0:
            break;

        default:
            printf("\nOpcao invalida.\n");
            Pausar();
        }

    } while (op != 0);
}

/* CAIXAS */
static void ListarCaixas(MatrizSupermercado *H)
{
    if (H == NULL || H->Tabela == NULL)
    {
        printf("\nNenhuma caixa registada.\n");
        return;
    }

    printf("\n");
    printf("╔══════╦══════════╦══════╦════════════╦════════════╗\n");
    printf("║  ID  ║  ESTADO  ║ FILA ║  PESSOAS   ║ PRODUTOS   ║\n");
    printf("╠══════╬══════════╬══════╬════════════╬════════════╣\n");

    for (int i = 0; i < H->tamanho; i++)
    {
        Caixa *C = &H->Tabela[i];

        printf("║ %4d ║ %-8s ║ %4d ║ %10d ║ %10d ║\n",
               C->id,
               C->aberta ? "ABERTA" : "FECHADA",
               C->fila ? C->fila->NEL : 0,
               C->totalPessoasAtendidas,
               C->totalProdutosVendidos);
    }

    printf("╚══════╩══════════╩══════╩════════════╩════════════╝\n");
}

static void AbrirCaixa(MatrizSupermercado *H)
{
    int id;

    if (H == NULL)
        return;

    printf("\nID da caixa: ");
    scanf("%d", &id);
    getchar();

    Caixa *C = ObterCaixa(H, id);

    if (C == NULL)
    {
        printf("\n[CAIXA] - Caixa nao encontrada.\n");
        return;
    }

    C->aberta = 1;

    printf("\nCaixa aberta com sucesso.\n");
    RegistrarHistoricoCSV("ABERTURA_MANUAL_CAIXA", NULL, 0, C->id, NULL, 0);
}

static void FecharCaixa(MatrizSupermercado *H)
{
    int id;

    if (H == NULL)
        return;

    printf("\nID da caixa: ");
    scanf("%d", &id);
    getchar();

    Caixa *C = ObterCaixa(H, id);

    if (C == NULL)
    {
        printf("\nCaixa nao encontrada.\n");
        return;
    }

    if (C->fila != NULL && C->fila->NEL > 0)
    {
        printf("\nNao pode fechar caixa com clientes.\n");
        return;
    }

    C->aberta = 0;

    printf("\nCaixa fechada com sucesso.\n");
    RegistrarHistoricoCSV("FECHO_MANUAL_CAIXA", NULL, C->id, 0, NULL, 0);
}

void MenuCaixas(MatrizSupermercado *H)
{
    int op;

    if (H == NULL)
        return;

    do
    {
        LimparTela();
        printf("\n");
        printf("╔══════════════════════════════╗\n");
        printf("║         MENU CAIXAS          ║\n");
        printf("╠══════════════════════════════╣\n");
        printf("║ 1 - Listar Caixas            ║\n");
        printf("║ 2 - Abrir Caixa              ║\n");
        printf("║ 3 - Fechar Caixa             ║\n");
        printf("║ 0 - Voltar                   ║\n");
        printf("╚══════════════════════════════╝\n");

        printf("\nOpcao: ");

        scanf("%d", &op);
        getchar();

        switch (op)
        {
        case 1:
            LimparTela();
            ListarCaixas(H);
            Pausar();
            break;

        case 2:
            LimparTela();
            AbrirCaixa(H);
            Pausar();
            break;

        case 3:
            LimparTela();
            FecharCaixa(H);
            Pausar();
            break;

        case 0:
            LimparTela();
            break;

        default:
            printf("\nOpcao invalida.\n");
            Pausar();
        }

    } while (op != 0);
}

/* CLIENTES */
static void ListarClientesMenu(ListaClientes *LC)
{
    if (LC == NULL || LC->Inicio == NULL)
    {
        printf("\nNenhum cliente registado.\n");
        return;
    }

    printf("\n");
    printf("═══════════════════════════════════════\n");
    printf(" ID       NOME\n");
    printf("═══════════════════════════════════════\n");

    NoCliente *aux = LC->Inicio;

    while (aux != NULL)
    {
        printf(" %-8d %s\n",
               aux->Cli->id,
               aux->Cli->nome);

        aux = aux->Prox;
    }

    printf("═══════════════════════════════════════\n");
}

void MenuClientes(Supermercado *S)
{
    int op;

    if (S->LClientes == NULL)
        return;

    do
    {
        LimparTela();
        printf("\n");
        printf("╔══════════════════════════════╗\n");
        printf("║        MENU CLIENTES         ║\n");
        printf("╠══════════════════════════════╣\n");
        printf("║ 1 - Listar Clientes          ║\n");
        printf("║ 2 - Pesquisar por ID         ║\n");
        printf("║ 0 - Voltar                   ║\n");
        printf("╚══════════════════════════════╝\n");

        printf("\nOpcao: ");

        scanf("%d", &op);
        getchar();

        switch (op)
        {
        case 1:
            LimparTela();
            ListarClientesMenu(S->LClientes);
            Pausar();
            break;

        case 2:
        {
            int id;

            printf("\nID do cliente: ");
            scanf("%d", &id);
            getchar();

            if (id <= 0)
            {
                printf("\nID invalido.\n");
                Pausar();
                break;
            }

            HashNode *clienteNode = BuscarHashTable(S->HClientes, id);

            if (clienteNode == NULL)
            {
                printf("\nCliente nao encontrado.\n");
                Pausar();
                break;
            }

            LimparTela();
            Cliente *C = clienteNode->cliente;

            printf("\n");
            printf("╔══════════════════════════════════════════════╗\n");
            printf("║           DADOS DO CLIENTE                   ║\n");
            printf("╚══════════════════════════════════════════════╝\n");

            printf("Nome              : %s\n", C->nome);
            printf("ID                : %d\n", C->id);

            printf("Tempo Total Caixa : %.2f\n",
                   C->tempoTotalCaixa);

            printf("Tempo Espera      : %d\n",
                   C->tempoEspera);

            printf("Mudou Caixa       : %s\n",
                   C->mudouCaixa ? "SIM" : "NAO");

            printf("Em Atendimento    : %s\n",
                   C->emAtendimento ? "SIM" : "NAO");

            if (clienteNode->caixa != NULL)
            {
                printf("Caixa Atual       : %d\n",
                       clienteNode->caixa->id);
            }

            printf("\n");
            printf("═══════════════════════════════════════════════\n");
            printf("                 CARRINHO\n");
            printf("═══════════════════════════════════════════════\n");

            if (C->carrinho == NULL ||
                C->carrinho->Inicio == NULL)
            {
                printf("Carrinho vazio.\n");
            }
            else
            {
                NoProduto *P = C->carrinho->Inicio;

                float total = 0;
                int totalProdutos = 0;
                int produtosOferecidos = 0;

                while (P != NULL)
                {
                    Produto *Prod = P->Info;

                    if (Prod != NULL)
                    {
                        printf("\nProduto : %s\n",
                               Prod->nome);

                        printf("Codigo  : %d\n",
                               Prod->codigo);

                        printf("Preco   : %.2f €\n",
                               Prod->preco);

                        printf("Tempo Caixa : %.2f s\n",
                               Prod->tempoCaixa);

                        printf("Oferecido : %s\n",
                               Prod->oferecido ? "SIM" : "NAO");

                        total += Prod->preco;
                        totalProdutos++;

                        if (Prod->oferecido)
                            produtosOferecidos++;
                    }

                    P = P->Prox;
                }

                printf("\n");
                printf("═══════════════════════════════════════════════\n");
                printf("Total Produtos      : %d\n",
                       totalProdutos);

                printf("Produtos Oferecidos : %d\n",
                       produtosOferecidos);

                printf("Valor Total Compra  : %.2f €\n",
                       total);

                printf("═══════════════════════════════════════════════\n");
            }

            Pausar();
            break;
        }

        case 0:
            LimparTela();
            break;

        default:
            printf("\nOpcao invalida.\n");
            Pausar();
        }

    } while (op != 0);
}
/* FICHEIROS */

void MenuFicheiros(ListaProdutos *LP, ListaClientes *LC, ListaFuncionarios *LF, MatrizSupermercado *H)
{
    int op;
    char ficheiro[100];

    do
    {
        LimparTela();
        printf("\n");
        printf("╔══════════════════════════════════════════════╗\n");
        printf("║              MENU FICHEIROS                  ║\n");
        printf("╠══════════════════════════════════════════════╣\n");
        printf("║  1 - Carregar Produtos (TXT/CSV)             ║\n");
        printf("║  2 - Carregar Clientes (TXT/CSV)             ║\n");
        printf("║  3 - Carregar Funcionarios (TXT/CSV)         ║\n");
        printf("╠══════════════════════════════════════════════╣\n");
        printf("║  4 - Exportar Produtos CSV                   ║\n");
        printf("║  5 - Exportar Clientes CSV                   ║\n");
        printf("║  6 - Exportar Funcionarios CSV               ║\n");
        printf("║  7 - Exportar Caixas CSV                     ║\n");
        printf("║  8 - Exportar Estatisticas CSV               ║\n");
        printf("║  9 - Exportar Tudo CSV                       ║\n");
        printf("╠══════════════════════════════════════════════╣\n");
        printf("║ 10 - Reiniciar Historico CSV                 ║\n");
        printf("║  0 - Voltar                                  ║\n");
        printf("╚══════════════════════════════════════════════╝\n");

        printf("\nOpcao: ");
        scanf("%d", &op);
        getchar();

        LimparTela();

        switch (op)
        {
        case 1:
            printf("Nome do ficheiro: ");
            fgets(ficheiro, sizeof(ficheiro), stdin);
            ficheiro[strcspn(ficheiro, "\n")] = '\0';
            LerProdutos(LP, ficheiro);
            Pausar();
            break;

        case 2:
            printf("Nome do ficheiro: ");
            fgets(ficheiro, sizeof(ficheiro), stdin);
            ficheiro[strcspn(ficheiro, "\n")] = '\0';
            LerClientes(LC, ficheiro);
            Pausar();
            break;

        case 3:
            printf("Nome do ficheiro: ");
            fgets(ficheiro, sizeof(ficheiro), stdin);
            ficheiro[strcspn(ficheiro, "\n")] = '\0';
            LerFuncionarios(LF, ficheiro);
            Pausar();
            break;

        case 4:
            printf("Nome do ficheiro CSV: ");
            fgets(ficheiro, sizeof(ficheiro), stdin);
            ficheiro[strcspn(ficheiro, "\n")] = '\0';
            ExportarProdutosCSV(LP, ficheiro);
            Pausar();
            break;

        case 5:
            printf("Nome do ficheiro CSV: ");
            fgets(ficheiro, sizeof(ficheiro), stdin);
            ficheiro[strcspn(ficheiro, "\n")] = '\0';
            ExportarClientesCSV(LC, ficheiro);
            Pausar();
            break;

        case 6:
            printf("Nome do ficheiro CSV: ");
            fgets(ficheiro, sizeof(ficheiro), stdin);
            ficheiro[strcspn(ficheiro, "\n")] = '\0';
            ExportarFuncionariosCSV(LF, ficheiro);
            Pausar();
            break;

        case 7:
            printf("Nome do ficheiro CSV: ");
            fgets(ficheiro, sizeof(ficheiro), stdin);
            ficheiro[strcspn(ficheiro, "\n")] = '\0';
            ExportarCaixasCSV(H, ficheiro);
            Pausar();
            break;

        case 8:
            printf("Nome do ficheiro CSV: ");
            fgets(ficheiro, sizeof(ficheiro), stdin);
            ficheiro[strcspn(ficheiro, "\n")] = '\0';
            ExportarEstatisticasCSV(H, ficheiro);
            Pausar();
            break;

        case 9:
            ExportarProdutosCSV(LP, "dados/Produtos.csv");
            ExportarClientesCSV(LC, "dados/Clientes.csv");
            ExportarFuncionariosCSV(LF, "dados/Funcionarios.csv");
            ExportarCaixasCSV(H, "dados/Caixas.csv");
            ExportarEstatisticasCSV(H, "dados/Estatisticas.csv");
            printf("\n[CSV] - Exportacao completa concluida.\n");
            Pausar();
            break;

        case 10:
            CriarHistoricoCSV("dados/Historico.csv");
            Pausar();
            break;

        case 0:
            break;

        default:
            printf("\nOpcao invalida.\n");
            Pausar();
        }

    } while (op != 0);
}
// Produtos Menu
void MostrarProdutosVendidos(ListaProdutos *LP)
{
    if (LP == NULL || LP->Inicio == NULL)
    {
        printf("\nNenhum produto encontrado.\n");
        return;
    }

    NoProduto *Aux = LP->Inicio;
    int contador = 0;

    printf("\n");
    printf("╔════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║          PRODUTOS PARA VENDER                                              ║\n");
    printf("╠════╦═════════════════════════════════════════════╦═════════════════════════╣\n");
    printf("║ ID ║ NOME                                        ║ PREÇO (€)               ║\n");
    printf("╠════╬═════════════════════════════════════════════╬═════════════════════════╣\n");

    while (Aux != NULL)
    {
        if (Aux->Info != NULL && Aux->Info->oferecido == 0)
        {
            contador++;

            printf("║%-2d║ %-20s             %9.2f                  \n",
                   contador,
                   Aux->Info->nome,
                   Aux->Info->preco);
        }

        Aux = Aux->Prox;
    }

    printf("╚════╩══════════════════════════════════════════════╩═══════════════════════╝\n");
    printf("\nTotal de produtos vendidos: %d\n", contador);
}

void MostrarProdutosOferecidos(ListaProdutos *LP)
{
    if (LP == NULL || LP->Inicio == NULL)
    {
        printf("\nNenhum produto encontrado.\n");
        return;
    }

    NoProduto *Aux = LP->Inicio;
    int contador = 0;
    float valorTotal = 0;

    printf("\n");
    printf("╔══════════════════════════════════════════════════════════════════════════╗\n");
    printf("║         PRODUTOS OFERECIDOS                                              ║\n");
    printf("╠════╦═══════════════════════════════════════════╦═════════════════════════╣\n");
    printf("║ ID ║ NOME                                      ║ PREÇO (€)               ║\n");
    printf("╠════╬═══════════════════════════════════════════╬═════════════════════════╣\n");

    while (Aux != NULL)
    {
        if (Aux->Info != NULL && Aux->Info->oferecido == 1)
        {
            contador++;
            valorTotal += Aux->Info->preco;

            printf("║%-2d║ %-20s                           %9.2f                   \n",
                   contador,
                   Aux->Info->nome,
                   Aux->Info->preco);
        }

        Aux = Aux->Prox;
    }

    printf("╚════╩════════════════════════════════════════╩══════════════════════════╝\n");
    printf("\nTotal de produtos oferecidos: %d\n", contador);
    printf("Valor total oferecido: %.2f €\n", valorTotal);
}

void MenuProdutos(ListaProdutos *LP)
{
    int op;

    if (LP == NULL)
        return;

    do
    {
        LimparTela();
        printf("\n");
        printf("╔══════════════════════════════╗\n");
        printf("║        MENU PRODUTOS         ║\n");
        printf("╠══════════════════════════════╣\n");
        printf("║ 1 - Listar Produtos          ║\n");
        printf("║ 2 - Produtos Vendidos        ║\n");
        printf("║ 3 - Produtos Oferecidos      ║\n");
        printf("║ 0 - Voltar                   ║\n");
        printf("╚══════════════════════════════╝\n");

        printf("\nOpcao: ");

        scanf("%d", &op);
        getchar();
        LimparTela();
        switch (op)
        {
        case 1:
            MostrarListaProdutos(LP);
            Pausar();
            break;

        case 2:
            MostrarProdutosVendidos(LP);
            Pausar();
            break;

        case 3:
            MostrarProdutosOferecidos(LP);
            Pausar();
            break;
        case 0:
            break;

        default:
            printf("\nOpcao invalida.\n");
            Pausar();
        }

    } while (op != 0);
}

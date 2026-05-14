
#include "../includes/Supermercado.h"
#include "../includes/Ficheiro.h"

extern int Aleatorio(int min, int max);

//---------------------------------------------

Supermercado *CriarSupermercado(char *nome)
{
    Supermercado *S = (Supermercado *)malloc(sizeof(Supermercado));
    //... fazer
    S->Rolex = CriarRelogio(10);
    return S;
}


int InicializarSupermercado(Supermercado *S, char *config)
{
    FILE *f = fopen(config, "r");
    if (f == NULL) {
        printf("Erro fatal: Nao foi possivel abrir o ficheiro %s\n", config);
        return 0;
    }

    char tag[50];
    int valor;

    while (fscanf(f, "%s %d", tag, &valor) != EOF) {
        if (strcmp(tag, "MAX_ESPERA") == 0) S->max_espera = valor;
        else if (strcmp(tag, "N_CAIXAS") == 0) S->n_caixas = valor;
        else if (strcmp(tag, "TEMPO_ATENDIMENTO_PRODUTO") == 0) S->tempo_atendimento_produto = valor;
        else if (strcmp(tag, "MAX_PRECO") == 0) S->max_preco = valor;
        else if (strcmp(tag, "MAX_FILA") == 0) S->max_fila = valor;
        else if (strcmp(tag, "MIN_FILA") == 0) S->min_fila = valor;
    }

    fclose(f);

    // --- BLOCO DE IMPRESSÃO PARA VERIFICAÇÃO ---
    printf("\n========================================\n");
    printf("   CONFIGURACOES CARREGADAS DO FICHEIRO \n");
    printf("========================================\n");
    printf("MAX_ESPERA: %d\n", S->max_espera);
    printf("N_CAIXAS: %d\n", S->n_caixas);
    printf("TEMPO_ATENDIMENTO: %d\n", S->tempo_atendimento_produto);
    printf("MAX_PRECO: %d\n", S->max_preco);
    printf("MAX_FILA: %d\n", S->max_fila);
    printf("MIN_FILA: %d\n", S->min_fila);
    printf("========================================\n\n");

    //S->LPessoas = CriarListaPessoas();
    S->LProdutos = CriarListaProdutos();
    LerProdutos(S->LProdutos,"dados/Produtos.txt");
    printf("\nPRODUTOS CARREGADOS:\n");
    MostrarListaProdutos(S->LProdutos);

    S->LClientes = CriarListaClientes();
    LerClientes(S->LClientes, "dados/Clientes.txt");
    printf("\nCLIENTES CARREGADOS:\n");
    MostrarListaClientes(S->LClientes);


    S->LFuncionarios = CriarListaFuncionarios();
    LerFuncionarios(S->LFuncionarios, "dados/Funcionarios.txt");
    printf("\nFUNCIONARIOS CARREGADOS:\n");
    MostrarListaFuncionarios(S->LFuncionarios);

    S->CadenciaEntradaClientes = 30;
    /*
    Falta implemnetar devidamente:
    //Criando o Hash:
    S->HCaixas = CriarHashing(S->n_caixas);
    
    //Abrir caixas iniciais:
    ObterCaixa(S->HCaixas, 1)->aberta = 1;
    ObterCaixa(S->HCaixas, 2)->aberta = 1;
    */
    return 1;
}

int ExecutarSimulacao(Supermercado *S)
{
    printf("Estou a trabalhar...\n");
    EntradaPessoaSupermercado(S);

    EstadoPagamentoIrCaixa(S);

    return 1;
}
/*
int IrCaixa(Pessoa *P, Supermercado *S)
{
    //time_t T = GetTempo(S->Rolex);
    //Se (T >=  gfdglkfdglkfdg)
    //    return 1;
    return 0;
}
*/

void EstadoPagamentoIrCaixa(Supermercado *S)
{
    //Para todas as Pessoas P da S->LClientes
    //    Se (IrCaixa(P, S))
        {
            // Escolher Caixa e Retirar essa pessoa de S->Clientes
            // e ir para o Hashing das Caixas
        }
}
void EntradaPessoaSupermercado(Supermercado *S)
{
    int X = Aleatorio(0, 100);
    //printf("X = %d\n", X);
    if (X < S->CadenciaEntradaClientes)
    {
        //Pessoa *P = CriarPessoa();
        //AddLista(S->LCliente, P);
        printf("Mais um Cliente a Entrar!\n");
    }
    //---------------------
}

int Supermercado_E_Para_Fechar(Supermercado *S)
{
        //... fazer
    return 0;
}

void DestruirSupermercado(Supermercado *S)
{
    free(S->Rolex);
    free(S);
}

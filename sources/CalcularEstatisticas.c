#include "../includes/Estatisticas.h"

// FUNÇÃO AUXILIAR

// Tempo total de espera estimado numa caixa
/*static double TempoEsperaCaixa(Caixa *C)
{
    if (C == NULL || C->fila == NULL)
        return 0.0;

    double tempo = 0.0;
    NoCliente *noC = C->fila->Inicio;

    while (noC != NULL)
    {
        Cliente *cli = noC->Cli;

        if (cli != NULL && cli->carrinho != NULL)
        {
            NoProduto *noP = cli->carrinho->Inicio;

            while (noP != NULL)
            {
                if (noP->Info != NULL)
                    tempo += noP->Info->tempoCaixa;

                noP = noP->Prox;
            }
        }

        noC = noC->Prox;
    }

    return tempo;
}*/

// Tempo total de Atendimento
void ObterTempoTotalAtendimento(MatrizSupermercado *H, Estatisticas *E)
{
    E->tempoTotalAtendimento = 0;

    if (H == NULL)
        return;

    for (int i = 0; i < H->tamanho; i++)
    {
        E->tempoTotalAtendimento +=
            H->Tabela[i].tempoTotalAtendimento;
    }
}

// CAIXA MAIS PRODUTOS
void ObterCaixaMaisProdutos(MatrizSupermercado *H, Estatisticas *E)
{
    E->idCaixaMaisProdutos = -1;
    E->maxProdutosVendidos = 0;

    if (H == NULL || H->Tabela == NULL)
        return;

    int maxProdutos = -1;

    for (int i = 0; i < H->tamanho; i++)
    {
        Caixa *caixa = &H->Tabela[i];

        if (caixa->totalProdutosVendidos > maxProdutos)
        {
            maxProdutos = caixa->totalProdutosVendidos;
            E->idCaixaMaisProdutos = caixa->id;
            E->maxProdutosVendidos = maxProdutos;
        }
    }
}

// CAIXA MAIS PESSOAS
void ObterCaixaMaisPessoas(MatrizSupermercado *H, Estatisticas *E)
{
    E->idCaixaMaisPessoas = -1;
    E->maxPessoasAtendidas = 0;

    if (H == NULL || H->Tabela == NULL)
        return;

    for (int i = 0; i < H->tamanho; i++)
    {
        Caixa *caixa = &H->Tabela[i];

        if (caixa->totalPessoasAtendidas > E->maxPessoasAtendidas)
        {
            E->maxPessoasAtendidas = caixa->totalPessoasAtendidas;

            E->idCaixaMaisPessoas = caixa->id;
        }
    }
}

// CAIXA MENOS PESSOAS
void ObterCaixaMenosPessoas(MatrizSupermercado *H, Estatisticas *E)
{
    E->idCaixaMenosPessoas = -1;
    E->minPessoasAtendidas = 999999;

    if (H == NULL || H->Tabela == NULL)
        return;

    for (int i = 0; i < H->tamanho; i++)
    {
        Caixa *caixa = &H->Tabela[i];

        if (caixa->totalPessoasAtendidas < E->minPessoasAtendidas)
        {
            E->minPessoasAtendidas = caixa->totalPessoasAtendidas;

            E->idCaixaMenosPessoas = caixa->id;
        }
    }
}

// CAIXAS ABERTAS
void ObterNumeroCaixasAbertas(MatrizSupermercado *H, Estatisticas *E)
{
    E->numeroCaixasAbertas = 0;

    if (H == NULL)
        return;

    for (int i = 0; i < H->tamanho; i++)
    {
        if (H->Tabela[i].aberta)
            E->numeroCaixasAbertas++;
    }
}

// CAIXAS FECHADAS
void ObterNumeroCaixasFechadas(MatrizSupermercado *H, Estatisticas *E)
{
    E->numeroCaixasFechadas = 0;

    if (H == NULL)
        return;

    for (int i = 0; i < H->tamanho; i++)
    {
        if (!H->Tabela[i].aberta)
            E->numeroCaixasFechadas++;
    }
}
// MAIOR FILA
void ObterMaiorFila(MatrizSupermercado *H, Estatisticas *E)
{
    E->maiorFila = 0;

    if (H == NULL)
        return;

    for (int i = 0; i < H->tamanho; i++)
    {
        if (H->Tabela[i].maxClientesFila >
            E->maiorFila)
        {
            E->maiorFila = H->Tabela[i].maxClientesFila;
        }
    }
}

// PRODUTOS
void ObterNumeroProdutosOferecidos(MatrizSupermercado *H, Estatisticas *E)
{
    E->numeroProdutosOferecidos = 0;

    if (H == NULL)
        return;

    for (int i = 0; i < H->tamanho; i++)
    {
        Caixa *C = &H->Tabela[i];

        if (C->fila == NULL)
            continue;

        NoCliente *NC = C->fila->Inicio;

        while (NC != NULL)
        {
            if (NC->Cli != NULL &&
                NC->Cli->carrinho != NULL)
            {
                E->numeroProdutosOferecidos += NC->Cli->carrinho->NEL;
            }

            NC = NC->Prox;
        }
    }
}

void ValorTotalProdutosOferecidos(MatrizSupermercado *H, Estatisticas *E)
{
    E->custoOferecidos = 0;

    if (H == NULL)
        return;

    for (int i = 0; i < H->tamanho; i++)
    {
        Caixa *C = &H->Tabela[i];

        if (C->fila == NULL)
            continue;

        NoCliente *NC = C->fila->Inicio;

        while (NC != NULL)
        {
            if (NC->Cli != NULL &&
                NC->Cli->carrinho != NULL)
            {
                NoProduto *NP =
                    NC->Cli->carrinho->Inicio;

                while (NP != NULL)
                {
                    E->custoOferecidos +=
                        NP->Info->preco;

                    NP = NP->Prox;
                }
            }

            NC = NC->Prox;
        }
    }
}
void ObterNumeroProdutosVendidos(MatrizSupermercado *H, Estatisticas *E)
{
    if (H == NULL || E == NULL)
        return;

    E->numeroTotalProdutosVendidos = 0;

    for (int i = 0; i < H->tamanho; i++)
    {
        E->numeroTotalProdutosVendidos += H->Tabela[i].totalProdutosVendidos;
    }
}

// FUNCIONÁRIOS / OPERADORES
void OperadorMenosPessoas(MatrizSupermercado *H, Estatisticas *E)
{
    E->operadorMenosPessoas = -1;

    if (H == NULL || H->Tabela == NULL)
        return;

    int minPessoas = -1;

    for (int i = 0; i < H->tamanho; i++)
    {
        Caixa *caixa = &H->Tabela[i];

        if (!caixa->aberta)
            continue;

        if (minPessoas == -1 || caixa->totalPessoasAtendidas < minPessoas)
        {
            minPessoas = caixa->totalPessoasAtendidas;
            E->operadorMenosPessoas = caixa->id;
        }
    }
}

void ObterOperadorMaisProdutos(MatrizSupermercado *H, Estatisticas *E)
{
    E->operadorMaisProdutos = -1;

    if (H == NULL || H->Tabela == NULL)
        return;

    int maxProd = -1;

    for (int i = 0; i < H->tamanho; i++)
    {
        Caixa *caixa = &H->Tabela[i];

        if (!caixa->aberta)
            continue;

        if (caixa->totalProdutosVendidos > maxProd)
        {
            maxProd = caixa->totalProdutosVendidos;
            E->operadorMaisProdutos = caixa->id;
        }
    }
}

// TEMPO MÉDIO DE ESPERA
void TempoMedioEsperaCaixas(MatrizSupermercado *H, Estatisticas *E)
{
    E->tempoMedioEsperaCaixas = 0;

    if (H == NULL)
        return;

    float tempoTotal = 0;
    int totalClientes = 0;

    for (int i = 0; i < H->tamanho; i++)
    {
        tempoTotal += H->Tabela[i].tempoTotalAtendimento;

        totalClientes += H->Tabela[i].totalPessoasAtendidas;
    }

    if (totalClientes > 0)
    {
        E->tempoMedioEsperaCaixas = tempoTotal / totalClientes;
    }
}

// CLIENTES
void NumeroTotalClientesAtendidos(MatrizSupermercado *H, Estatisticas *E)
{
    E->numeroTotalClientesAtendidos = 0;

    if (H == NULL || H->Tabela == NULL)
        return;

    for (int i = 0; i < H->tamanho; i++)
        E->numeroTotalClientesAtendidos += H->Tabela[i].totalPessoasAtendidas;
}

// PRINCIPAL
Estatisticas CalcularEstatisticas(MatrizSupermercado *H)
{
    Estatisticas E = {0};

    // CAIXAS
    ObterCaixaMaisProdutos(H, &E);
    ObterCaixaMaisPessoas(H, &E);
    ObterCaixaMenosPessoas(H, &E);

    ObterNumeroCaixasAbertas(H, &E);
    ObterNumeroCaixasFechadas(H, &E);

    ObterMaiorFila(H, &E);

    // PRODUTOS
    ObterNumeroProdutosOferecidos(H, &E);
    ValorTotalProdutosOferecidos(H, &E);
    ObterNumeroProdutosVendidos(H, &E);

    // TEMPOS
    TempoMedioEsperaCaixas(H, &E);
    ObterTempoTotalAtendimento(H, &E);

    // CLIENTES
    NumeroTotalClientesAtendidos(H, &E);

    // OPERADORES
    OperadorMenosPessoas(H, &E);
    ObterOperadorMaisProdutos(H, &E);

    return E;
}

// OUTPUT
void MostrarEstatisticasSupermercado(MatrizSupermercado *H)
{
    Estatisticas E = CalcularEstatisticas(H);

    printf("\n=========================================\n");
    printf("     ESTATISTICAS DO SUPERMERCADO\n");
    printf("=========================================\n\n");

    // CLIENTES
    printf("TOTAL CLIENTES ATENDIDOS\n");
    printf("-----------------------------------------\n");
    printf("Clientes atendidos : %d\n\n",
           E.numeroTotalClientesAtendidos);

    // PRODUTOS
    printf("PRODUTOS\n");
    printf("-----------------------------------------\n");

    printf("Produtos oferecidos : %d\n",
           E.numeroProdutosOferecidos);

    printf("Valor produtos      : %.2f EUR\n",
           E.custoOferecidos);

    printf("Produtos vendidos   : %d\n\n",
           E.numeroTotalProdutosVendidos);

    // CAIXAS
    printf("CAIXAS\n");
    printf("-----------------------------------------\n");

    printf("Caixa mais produtos : %d (%d produtos)\n",
           E.idCaixaMaisProdutos,
           E.maxProdutosVendidos);

    printf("Caixa mais clientes : %d (%d clientes)\n",
           E.idCaixaMaisPessoas,
           E.maxPessoasAtendidas);

    printf("Caixa menos clientes: %d (%d clientes)\n",
           E.idCaixaMenosPessoas,
           E.minPessoasAtendidas);

    printf("Caixas abertas      : %d\n",
           E.numeroCaixasAbertas);

    printf("Caixas fechadas     : %d\n",
           E.numeroCaixasFechadas);

    printf("Maior fila registada: %d clientes\n\n",
           E.maiorFila);

    // TEMPOS
    printf("TEMPOS\n");
    printf("-----------------------------------------\n");

    printf("Tempo medio atendimento : %.2f segundos\n",
           E.tempoMedioEsperaCaixas);

    printf("Tempo total caixa   : %.2f segundos\n\n",
           E.tempoTotalAtendimento);

    // OPERADORES
    printf("OPERADORES\n");
    printf("-----------------------------------------\n");

    printf("Operador menos clientes : Caixa %d\n",
           E.operadorMenosPessoas);

    printf("Operador mais produtos  : Caixa %d\n",
           E.operadorMaisProdutos);

    printf("\n=========================================\n");
}
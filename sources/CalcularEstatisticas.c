#include "../includes/Estatisticas.h"

// ==========================
// FUNÇÃO AUXILIAR
// ==========================

// Tempo total de espera estimado numa caixa
static double TempoEsperaCaixa(Caixa *C)
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
}

// ==========================
// CAIXA MAIS PRODUTOS
// ==========================
void ObterCaixaMaisProdutos(Hashing *H, Estatisticas *E)
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

// ==========================
// CAIXA MAIS PESSOAS
// ==========================
void ObterCaixaMaisPessoas(Hashing *H, Estatisticas *E)
{
    E->idCaixaMaisPessoas = -1;

    if (H == NULL || H->Tabela == NULL)
        return;

    int maxPessoas = -1;

    for (int i = 0; i < H->tamanho; i++)
    {
        Caixa *caixa = &H->Tabela[i];

        if (caixa->totalPessoasAtendidas > maxPessoas)
        {
            maxPessoas = caixa->totalPessoasAtendidas;
            E->idCaixaMaisPessoas = caixa->id;
        }
    }
}

// ==========================
// CAIXA MENOS PESSOAS
// ==========================
void ObterCaixaMenosPessoas(Hashing *H, Estatisticas *E)
{
    E->idCaixaMenosPessoas = -1;

    if (H == NULL || H->Tabela == NULL)
        return;

    int minPessoas = -1;

    for (int i = 0; i < H->tamanho; i++)
    {
        Caixa *caixa = &H->Tabela[i];

        if (minPessoas == -1 || caixa->totalPessoasAtendidas < minPessoas)
        {
            minPessoas = caixa->totalPessoasAtendidas;
            E->idCaixaMenosPessoas = caixa->id;
        }
    }
}

// ==========================
// PRODUTOS
// ==========================
void ObterNumeroProdutosOferecidos(ListaProdutos *L, Estatisticas *E)
{
    E->numeroProdutosOferecidos = (L != NULL) ? L->NEL : 0;
}

void ValorTotalProdutosOferecidos(ListaProdutos *L, Estatisticas *E)
{
    E->custoOferecidos = 0.0;

    if (L == NULL)
        return;

    NoProduto *no = L->Inicio;

    while (no != NULL)
    {
        if (no->Info != NULL)
            E->custoOferecidos += no->Info->preco;

        no = no->Prox;
    }
}

// ==========================
// FUNCIONÁRIOS / OPERADORES
// ==========================
void OperadorMenosPessoas(Hashing *H, Estatisticas *E)
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

void ObterOperadorMaisProdutos(Hashing *H, Estatisticas *E)
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

// ==========================
// TEMPO MÉDIO
// ==========================
void TempoMedioEsperaCaixas(Hashing *H, Estatisticas *E)
{
    E->tempoMedioEsperaCaixas = 0.0;

    if (H == NULL || H->Tabela == NULL)
        return;

    double totalTempo = 0.0;
    int totalPessoas = 0;

    for (int i = 0; i < H->tamanho; i++)
    {
        Caixa *caixa = &H->Tabela[i];

        totalTempo += TempoEsperaCaixa(caixa);
        totalPessoas += caixa->totalPessoasAtendidas;
    }

    if (totalPessoas > 0)
        E->tempoMedioEsperaCaixas = totalTempo / totalPessoas;
}

// ==========================
// CLIENTES
// ==========================
void NumeroTotalClientesAtendidos(Hashing *H, Estatisticas *E)
{
    E->numeroTotalClientesAtendidos = 0;

    if (H == NULL || H->Tabela == NULL)
        return;

    for (int i = 0; i < H->tamanho; i++)
        E->numeroTotalClientesAtendidos += H->Tabela[i].totalPessoasAtendidas;
}

// ==========================
// PRINCIPAL
// ==========================
Estatisticas CalcularEstatisticas(Hashing *H, ListaProdutos *LP)
{
    Estatisticas E = {0};

    ObterCaixaMaisProdutos(H, &E);
    ObterCaixaMaisPessoas(H, &E);
    ObterCaixaMenosPessoas(H, &E);

    ObterNumeroProdutosOferecidos(LP, &E);
    ValorTotalProdutosOferecidos(LP, &E);

    TempoMedioEsperaCaixas(H, &E);
    NumeroTotalClientesAtendidos(H, &E);

    OperadorMenosPessoas(H, &E);
    ObterOperadorMaisProdutos(H, &E);

    return E;
}

// ==========================
// OUTPUT
// ==========================
void MostrarEstatisticasSupermercado(Hashing *H, ListaProdutos *LP)
{
    Estatisticas E = CalcularEstatisticas(H, LP);

    printf("\n===== ESTATISTICAS DO SUPERMERCADO =====\n\n");

    printf("Caixa com mais produtos vendidos : %d (%d)\n",
           E.idCaixaMaisProdutos, E.maxProdutosVendidos);

    printf("Caixa com mais pessoas atendidas : %d\n",
           E.idCaixaMaisPessoas);

    printf("Caixa com menos pessoas atendidas: %d\n",
           E.idCaixaMenosPessoas);

    printf("Produtos no catalogo             : %d\n",
           E.numeroProdutosOferecidos);

    printf("Custo total do catalogo          : %.2f EUR\n",
           E.custoOferecidos);

    printf("Tempo medio de espera            : %.2f s\n",
           E.tempoMedioEsperaCaixas);

    printf("Total clientes atendidos         : %d\n",
           E.numeroTotalClientesAtendidos);

    printf("Operador menos produtivo         : %d\n",
           E.operadorMenosPessoas);

    printf("Operador mais produtivo          : %d\n",
           E.operadorMaisProdutos);
}
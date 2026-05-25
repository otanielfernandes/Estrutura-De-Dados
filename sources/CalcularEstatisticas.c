#include "../includes/Estatisticas.h"

// Auxiliares para cálculo de estatísticas específicas
static float CustoCarrinho(ListaProdutos *LP)
{
    if (LP == NULL)
        return 0.0f;

    float total = 0.0f;
    NoProduto *no = LP->Inicio;
    while (no != NULL)
    {
        if (no->Info != NULL)
            total += no->Info->preco;
        no = no->Prox;
    }
    return total;
}

// Função para calcular o tempo total de espera estimado numa caixa,
// somando o tempoCaixa de cada produto de cada cliente na fila.
static float TempoEsperaCaixa(Caixa *C)
{
    if (C == NULL || C->fila == NULL)
        return 0.0f;

    float tempo = 0.0f;
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

// Funções de estatística individuais

void ObterCaixaMaisProdutos(Supermercado *S, Estatisticas *E)
{
    E->idCaixaMaisProdutos = -1;
    E->maxProdutosVendidos = 0;

    if (S == NULL || S->HCaixas == NULL || S->HCaixas->Tabela == NULL)
        return;

    int maxProdutos = -1;

    for (int i = 0; i < S->HCaixas->tamanho; i++)
    {
        Caixa *caixa = &S->HCaixas->Tabela[i];
        if (caixa->totalProdutosVendidos > maxProdutos)
        {
            maxProdutos = caixa->totalProdutosVendidos;
            E->idCaixaMaisProdutos = caixa->id;
            E->maxProdutosVendidos = maxProdutos;
        }
    }
}

void ObterCaixaMaisPessoas(Supermercado *S, Estatisticas *E)
{
    E->idCaixaMaisPessoas = -1;

    if (S == NULL || S->HCaixas == NULL || S->HCaixas->Tabela == NULL)
        return;

    int maxPessoas = -1;

    for (int i = 0; i < S->HCaixas->tamanho; i++)
    {
        Caixa *caixa = &S->HCaixas->Tabela[i];
        if (caixa->totalPessoasAtendidas > maxPessoas)
        {
            maxPessoas = caixa->totalPessoasAtendidas;
            E->idCaixaMaisPessoas = caixa->id;
        }
    }
}

void ObterCaixaMenosPessoas(Supermercado *S, Estatisticas *E)
{
    E->idCaixaMenosPessoas = -1;

    if (S == NULL || S->HCaixas == NULL || S->HCaixas->Tabela == NULL)
        return;

    int minPessoas = -1;

    for (int i = 0; i < S->HCaixas->tamanho; i++)
    {
        Caixa *caixa = &S->HCaixas->Tabela[i];
        if (minPessoas == -1 || caixa->totalPessoasAtendidas < minPessoas)
        {
            minPessoas = caixa->totalPessoasAtendidas;
            E->idCaixaMenosPessoas = caixa->id;
        }
    }
}

void ObterNumeroProdutosOferecidos(Supermercado *S, Estatisticas *E)
{
    E->numeroProdutosOferecidos = 0;

    if (S == NULL || S->LProdutos == NULL)
        return;
    E->numeroProdutosOferecidos = S->LProdutos->NEL;
}

void OperadorMenosPessoas(Supermercado *S, Estatisticas *E)
{
    E->operadorMenosPessoas = -1;

    if (S == NULL || S->HCaixas == NULL || S->HCaixas->Tabela == NULL)
        return;

    int minPessoas = -1;

    for (int i = 0; i < S->HCaixas->tamanho; i++)
    {
        Caixa *caixa = &S->HCaixas->Tabela[i];
        /* Só considera caixas abertas (com operador activo). */
        if (!caixa->aberta)
            continue;

        if (minPessoas == -1 || caixa->totalPessoasAtendidas < minPessoas)
        {
            minPessoas = caixa->totalPessoasAtendidas;
            E->operadorMenosPessoas = caixa->id;
        }
    }
}

void ObterOperadorMaisProdutos(Supermercado *S, Estatisticas *E)
{
    E->operadorMaisProdutos = -1;

    if (S == NULL || S->HCaixas == NULL || S->HCaixas->Tabela == NULL)
        return;

    int maxProd = -1;

    for (int i = 0; i < S->HCaixas->tamanho; i++)
    {
        Caixa *caixa = &S->HCaixas->Tabela[i];
        if (!caixa->aberta)
            continue;

        if (caixa->totalProdutosVendidos > maxProd)
        {
            maxProd = caixa->totalProdutosVendidos;
            E->operadorMaisProdutos = caixa->id;
        }
    }
}

void ValorTotalProdutosOferecidos(Supermercado *S, Estatisticas *E)
{
    E->custoOferecidos = 0.0f;

    if (S == NULL || S->LProdutos == NULL)
        return;

    NoProduto *no = S->LProdutos->Inicio;
    while (no != NULL)
    {
        if (no->Info != NULL)
            E->custoOferecidos += no->Info->preco;
        no = no->Prox;
    }
}

void TempoMedioEsperaCaixas(Supermercado *S, Estatisticas *E)
{
    E->tempoMedioEsperaCaixas = 0.0f;

    if (S == NULL || S->HCaixas == NULL || S->HCaixas->Tabela == NULL)
        return;

    float totalTempo = 0.0f;
    int totalPessoas = 0;

    for (int i = 0; i < S->HCaixas->tamanho; i++)
    {
        Caixa *caixa = &S->HCaixas->Tabela[i];
        totalTempo += TempoEsperaCaixa(caixa);
        totalPessoas += caixa->totalPessoasAtendidas;
    }

    if (totalPessoas > 0)
        E->tempoMedioEsperaCaixas = totalTempo / (float)totalPessoas;
}

void NumeroTotalClientesAtendidos(Supermercado *S, Estatisticas *E)
{
    E->numeroTotalClientesAtendidos = 0;

    if (S == NULL || S->HCaixas == NULL || S->HCaixas->Tabela == NULL)
        return;

    for (int i = 0; i < S->HCaixas->tamanho; i++)
        E->numeroTotalClientesAtendidos += S->HCaixas->Tabela[i].totalPessoasAtendidas;
}

void NumeroProdutosOferecidos(Supermercado *S, Estatisticas *E)
{
    ObterNumeroProdutosOferecidos(S, E);
}

void maxProdutosVendidos(Supermercado *S, Estatisticas *E)
{
    ObterCaixaMaisProdutos(S, E);
}

void MemoriaUtilizada(Supermercado *S, Estatisticas *E)
{
    if (S == NULL || E == NULL)
        return;

    size_t mem = 0;

    // Memória base do supermercado
    mem += sizeof(Supermercado);

    // Nome do supermercado
    if (S->NOME)
        mem += strlen(S->NOME) + 1;

    // Relógio
    if (S->Rolex)
        mem += sizeof(Relogio);

    // Clientes
    if (S->LClientes)
    {
        mem += sizeof(ListaClientes);

        NoCliente *aux = S->LClientes->Inicio;

        while (aux)
        {
            mem += sizeof(NoCliente);

            if (aux->Cli)
            {
                mem += sizeof(Cliente);

                if (aux->Cli->nome)
                    mem += strlen(aux->Cli->nome) + 1;
            }

            aux = aux->Prox;
        }
    }

    // Funcionários
    if (S->LFuncionarios)
    {
        mem += sizeof(ListaFuncionarios);

        NoFuncionario *aux = S->LFuncionarios->Inicio;

        while (aux)
        {
            mem += sizeof(NoFuncionario);

            if (aux->Func)
            {
                mem += sizeof(Funcionario);

                if (aux->Func->nome)
                    mem += strlen(aux->Func->nome) + 1;
            }

            aux = aux->Prox;
        }
    }

    // Produtos
    if (S->LProdutos)
    {
        mem += sizeof(ListaProdutos);

        NoProduto *aux = S->LProdutos->Inicio;

        while (aux)
        {
            mem += sizeof(NoProduto);

            if (aux->Info)
            {
                mem += sizeof(Produto);

                if (aux->Info->nome)
                    mem += strlen(aux->Info->nome) + 1;
            }

            aux = aux->Prox;
        }
    }

    // Caixas (hashing)
    if (S->HCaixas)
    {
        mem += sizeof(Hashing);
        mem += (size_t)S->HCaixas->tamanho * sizeof(Caixa);

        for (int i = 0; i < S->HCaixas->tamanho; i++)
        {
            Caixa *C = &S->HCaixas->Tabela[i];

            if (C->fila)
            {
                mem += sizeof(ListaClientes);

                NoCliente *aux = C->fila->Inicio;

                while (aux)
                {
                    mem += sizeof(NoCliente);

                    if (aux->Cli)
                    {
                        mem += sizeof(Cliente);

                        if (aux->Cli->nome)
                            mem += strlen(aux->Cli->nome) + 1;
                    }

                    aux = aux->Prox;
                }
            }
        }
    }

    // Resultado final
    E->memoriaUtilizada = mem;
}

/*
 * Cálculo global e apresentação
 *  */

Estatisticas CalcularEstatisticas(Supermercado *S)
{
    Estatisticas E = {0}; /* inicializa todos os campos a zero */

    ObterCaixaMaisProdutos(S, &E);
    ObterCaixaMaisPessoas(S, &E);
    ObterCaixaMenosPessoas(S, &E);
    ObterNumeroProdutosOferecidos(S, &E);
    ValorTotalProdutosOferecidos(S, &E);
    TempoMedioEsperaCaixas(S, &E);
    NumeroTotalClientesAtendidos(S, &E);
    OperadorMenosPessoas(S, &E);
    ObterOperadorMaisProdutos(S, &E);
    MemoriaUtilizada(S, &E);

    return E;
}

void MostrarEstatisticasSupermercado(Supermercado *S)
{
    Estatisticas E = CalcularEstatisticas(S);

    printf("\n===== ESTATÍSTICAS DO SUPERMERCADO =====\n");

    if (E.idCaixaMaisProdutos != -1)
        printf("Caixa com mais produtos vendidos : Caixa %d (%d produtos)\n",
               E.idCaixaMaisProdutos, E.maxProdutosVendidos);
    else
        printf("Caixa com mais produtos vendidos : N/D\n");

    if (E.idCaixaMaisPessoas != -1)
        printf("Caixa com mais pessoas atendidas : Caixa %d\n",
               E.idCaixaMaisPessoas);
    else
        printf("Caixa com mais pessoas atendidas : N/D\n");

    if (E.idCaixaMenosPessoas != -1)
        printf("Caixa com menos pessoas atendidas: Caixa %d\n",
               E.idCaixaMenosPessoas);
    else
        printf("Caixa com menos pessoas atendidas: N/D\n");

    printf("Produtos no catálogo             : %d\n",
           E.numeroProdutosOferecidos);
    printf("Custo total do catálogo          : %.2f EUR\n",
           E.custoOferecidos);
    printf("Tempo médio de espera nas caixas : %.2f s\n",
           E.tempoMedioEsperaCaixas);
    printf("Total de clientes atendidos      : %d\n",
           E.numeroTotalClientesAtendidos);

    if (E.operadorMenosPessoas != -1)
        printf("Operador com menos pessoas       : Caixa %d\n",
               E.operadorMenosPessoas);
    else
        printf("Operador com menos pessoas       : N/D\n");

    if (E.operadorMaisProdutos != -1)
        printf("Operador com mais produtos       : Caixa %d\n",
               E.operadorMaisProdutos);
    else
        printf("Operador com mais produtos       : N/D\n");

    printf("Memória utilizada                : %zu bytes\n",
           E.memoriaUtilizada);
}

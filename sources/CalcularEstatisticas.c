#include "../includes/Estatisticas.h"

// Auxiliares para cálculo de estatísticas específicas
static double CustoCarrinho(ListaProdutos *LP)
{
    if (LP == NULL)
        return 0.0;

    double total = 0.0;
    NoProduto *no = LP->Inicio;

    while (no != NULL)
    {
        if (no->Info != NULL)
            total += no->Info->preco;

        no = no->Prox;
    }

    return total;
}

// Função para calcular o tempo total de espera estimado numa caixa
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
// ESTATÍSTICAS POR CAIXA
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

void ObterNumeroProdutosOferecidos(ListaProdutos *L, Estatisticas *E)
{
    E->numeroProdutosOferecidos = 0;

    if (L == NULL)
        return;

    E->numeroProdutosOferecidos = L->NEL;
}

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

void NumeroTotalClientesAtendidos(Hashing *H, Estatisticas *E)
{
    E->numeroTotalClientesAtendidos = 0;

    if (H == NULL || H->Tabela == NULL)
        return;

    for (int i = 0; i < H->tamanho; i++)
        E->numeroTotalClientesAtendidos += H->Tabela[i].totalPessoasAtendidas;
}

void NumeroProdutosOferecidos(ListaProdutos *L, Estatisticas *E)
{
    ObterNumeroProdutosOferecidos(L, E);
}

void maxProdutosVendidos(Hashing *H, Estatisticas *E)
{
    ObterCaixaMaisProdutos(H, E);
}

// ==========================
// MEMÓRIA
// ==========================

/*void MemoriaUtilizada(Supermercado *S, Estatisticas *E)
{
    if (S == NULL || E == NULL)
        return;

    size_t mem = 0;

    mem += sizeof(Supermercado);

    if (S->NOME)
        mem += strlen(S->NOME) + 1;

    if (S->relogio)
        mem += sizeof(Relogio);

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

    E->memoriaUtilizada = mem;
}
*/

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

void MostrarEstatisticasSupermercado(Hashing *H, ListaProdutos *LP)
{
    Estatisticas E = CalcularEstatisticas(H, LP);

    printf("\n===== ESTATÍSTICAS DO SUPERMERCADO =====\n\n");

    printf("Caixa com mais produtos vendidos : %d (%d)\n",
           E.idCaixaMaisProdutos, E.maxProdutosVendidos);

    printf("Caixa com mais pessoas atendidas : %d\n",
           E.idCaixaMaisPessoas);

    printf("Caixa com menos pessoas atendidas: %d\n",
           E.idCaixaMenosPessoas);

    printf("Produtos no catálogo             : %d\n",
           E.numeroProdutosOferecidos);

    printf("Custo total do catálogo          : %.2f EUR\n",
           E.custoOferecidos);

    printf("Tempo médio de espera            : %.2f s\n",
           E.tempoMedioEsperaCaixas);

    printf("Total clientes atendidos         : %d\n",
           E.numeroTotalClientesAtendidos);

    printf("Operador menos produtivo         : %d\n",
           E.operadorMenosPessoas);

    printf("Operador mais produtivo          : %d\n",
           E.operadorMaisProdutos);
}
#include "../includes/Ficheiro.h"
#include "../includes/Estatisticas.h"
#include <ctype.h>
#include <time.h>

#define FICHEIRO_HISTORICO "dados/Historico.csv"

static void RemoverQuebraLinha(char *texto)
{
    if (texto == NULL)
        return;

    texto[strcspn(texto, "\r\n")] = '\0';
}

static char *Aparar(char *texto)
{
    char *fim;

    if (texto == NULL)
        return texto;

    while (isspace((unsigned char)*texto))
        texto++;

    if (*texto == '\0')
        return texto;

    fim = texto + strlen(texto) - 1;
    while (fim > texto && isspace((unsigned char)*fim))
    {
        *fim = '\0';
        fim--;
    }

    if (*texto == '"' || *texto == '\'')
    {
        char aspas = *texto;
        texto++;
        fim = texto + strlen(texto) - 1;

        if (fim >= texto && *fim == aspas)
            *fim = '\0';
    }

    return texto;
}

static int SepararCampos(char *linha, char *campos[], int maxCampos)
{
    int total = 0;
    char delimitador = '\t';
    char *p;

    if (strchr(linha, ';') != NULL)
        delimitador = ';';
    else if (strchr(linha, ',') != NULL)
        delimitador = ',';

    p = linha;

    while (p != NULL && total < maxCampos)
    {
        char *prox = strchr(p, delimitador);

        if (prox != NULL)
        {
            *prox = '\0';
            prox++;
        }

        campos[total++] = Aparar(p);
        p = prox;
    }

    return total;
}

static int TokenEhInteiro(const char *texto)
{
    if (texto == NULL || *texto == '\0')
        return 0;

    if (*texto == '-' || *texto == '+')
        texto++;

    if (*texto == '\0')
        return 0;

    while (*texto != '\0')
    {
        if (!isdigit((unsigned char)*texto))
            return 0;
        texto++;
    }

    return 1;
}

static float ConverterFloat(char *texto)
{
    char copia[64];
    int i = 0;

    if (texto == NULL)
        return 0;

    while (texto[i] != '\0' && i < (int)sizeof(copia) - 1)
    {
        copia[i] = (texto[i] == ',') ? '.' : texto[i];
        i++;
    }

    copia[i] = '\0';
    return (float)atof(copia);
}

static void EscreverCampoCSV(FILE *f, const char *texto)
{
    const char *p;

    fputc('"', f);

    if (texto != NULL)
    {
        for (p = texto; *p != '\0'; p++)
        {
            if (*p == '"')
                fputc('"', f);

            fputc(*p, f);
        }
    }

    fputc('"', f);
}

int LerProdutos(ListaProdutos *LProd, char *ficheiro)
{
    FILE *f = fopen(ficheiro, "r");
    char linha[512];
    int contador = 0;
    const int MAX_PRODUTOS = 600;

    if (f == NULL)
    {
        printf("[ERRO] - Nao foi possivel abrir: %s\n", ficheiro);
        return 0;
    }

    while (fgets(linha, sizeof(linha), f) != NULL && contador < MAX_PRODUTOS)
    {
        char *campos[5];
        int totalCampos;
        int codigo;
        char *nome;
        float preco, tempoCompra, tempoCaixa;

        RemoverQuebraLinha(linha);

        if (Aparar(linha)[0] == '\0')
            continue;

        totalCampos = SepararCampos(linha, campos, 5);

        if (totalCampos < 5 || !TokenEhInteiro(campos[0]))
            continue;

        codigo = atoi(campos[0]);
        nome = campos[1];
        preco = ConverterFloat(campos[2]);
        tempoCompra = ConverterFloat(campos[3]);
        tempoCaixa = ConverterFloat(campos[4]);

        InserirProduto(LProd, CriarProduto(codigo, nome, preco, tempoCompra, tempoCaixa));
        contador++;
    }

    InverterListaProdutos(LProd);
    fclose(f);

    printf("[INFO] - Produtos carregados: %d\n", contador);
    return 1;
}

int LerClientes(ListaClientes *LC, char *ficheiro)
{
    FILE *f = fopen(ficheiro, "r");
    char linha[512];
    int contador = 0;
    const int MAX_CLIENTES = 120;

    if (f == NULL)
    {
        printf("[ERRO] - Ficheiro de clientes nao encontrado: %s\n", ficheiro);
        return 0;
    }

    while (fgets(linha, sizeof(linha), f) != NULL && contador < MAX_CLIENTES)
    {
        char *campos[2];
        int totalCampos;

        RemoverQuebraLinha(linha);

        if (Aparar(linha)[0] == '\0')
            continue;

        totalCampos = SepararCampos(linha, campos, 2);

        if (totalCampos < 2 || !TokenEhInteiro(campos[0]))
            continue;

        InserirCliente(LC, CriarCliente(atoi(campos[0]), campos[1]));
        contador++;
    }

    InverterListaClientes(LC);
    fclose(f);

    printf("[INFO] - Clientes carregados: %d\n", contador);
    return 1;
}

int LerFuncionarios(ListaFuncionarios *LF, char *ficheiro)
{
    FILE *f = fopen(ficheiro, "r");
    char linha[512];
    int contador = 0;
    const int MAX_FUNCIONARIOS = 6;

    if (f == NULL)
    {
        printf("[ERRO] - Nao foi possivel abrir: %s\n", ficheiro);
        return 0;
    }

    while (fgets(linha, sizeof(linha), f) != NULL && contador < MAX_FUNCIONARIOS)
    {
        char *campos[2];
        int totalCampos;

        RemoverQuebraLinha(linha);

        if (Aparar(linha)[0] == '\0')
            continue;

        totalCampos = SepararCampos(linha, campos, 2);

        if (totalCampos < 2 || !TokenEhInteiro(campos[0]))
            continue;

        InserirFuncionario(LF, CriarFuncionario(atoi(campos[0]), campos[1], 0));
        contador++;
    }

    InverterListaFuncionarios(LF);
    fclose(f);

    printf("[INFO] - Funcionarios carregados: %d\n", contador);
    return 1;
}

int ExportarProdutosCSV(ListaProdutos *LP, char *ficheiro)
{
    FILE *f = fopen(ficheiro, "w");
    NoProduto *aux;
    int contador = 0;

    if (f == NULL)
    {
        printf("[ERRO] - Nao foi possivel criar: %s\n", ficheiro);
        return 0;
    }

    fprintf(f, "codigo;nome;preco;tempo_compra;tempo_caixa;oferecido\n");

    for (aux = LP ? LP->Inicio : NULL; aux != NULL; aux = aux->Prox)
    {
        Produto *P = aux->Info;

        if (P == NULL)
            continue;

        fprintf(f, "%d;", P->codigo);
        EscreverCampoCSV(f, P->nome);
        fprintf(f, ";%.2f;%.2f;%.2f;%d\n",
                P->preco,
                P->tempoCompra,
                P->tempoCaixa,
                P->oferecido);
        contador++;
    }

    fclose(f);
    printf("[CSV] - Produtos exportados: %d (%s)\n", contador, ficheiro);
    return 1;
}

int ExportarClientesCSV(ListaClientes *LC, char *ficheiro)
{
    FILE *f = fopen(ficheiro, "w");
    NoCliente *aux;
    int contador = 0;

    if (f == NULL)
    {
        printf("[ERRO] - Nao foi possivel criar: %s\n", ficheiro);
        return 0;
    }

    fprintf(f, "id;nome;tempo_total_caixa;tempo_espera;mudou_caixa;em_atendimento;produtos_carrinho\n");

    for (aux = LC ? LC->Inicio : NULL; aux != NULL; aux = aux->Prox)
    {
        Cliente *C = aux->Cli;

        if (C == NULL)
            continue;

        fprintf(f, "%d;", C->id);
        EscreverCampoCSV(f, C->nome);
        fprintf(f, ";%.2f;%d;%d;%d;%d\n",
                C->tempoTotalCaixa,
                C->tempoEspera,
                C->mudouCaixa,
                C->emAtendimento,
                C->carrinho ? C->carrinho->NEL : 0);
        contador++;
    }

    fclose(f);
    printf("[CSV] - Clientes exportados: %d (%s)\n", contador, ficheiro);
    return 1;
}

int ExportarFuncionariosCSV(ListaFuncionarios *LF, char *ficheiro)
{
    FILE *f = fopen(ficheiro, "w");
    NoFuncionario *aux;
    int contador = 0;

    if (f == NULL)
    {
        printf("[ERRO] - Nao foi possivel criar: %s\n", ficheiro);
        return 0;
    }

    fprintf(f, "id;nome\n");

    for (aux = LF ? LF->Inicio : NULL; aux != NULL; aux = aux->Prox)
    {
        Funcionario *F = aux->Func;

        if (F == NULL)
            continue;

        fprintf(f, "%d;", F->id);
        EscreverCampoCSV(f, F->nome);
        fprintf(f, "\n");
        contador++;
    }

    fclose(f);
    printf("[CSV] - Funcionarios exportados: %d (%s)\n", contador, ficheiro);
    return 1;
}

int ExportarCaixasCSV(MatrizSupermercado *H, char *ficheiro)
{
    FILE *f = fopen(ficheiro, "w");
    int i;

    if (f == NULL)
    {
        printf("[ERRO] - Nao foi possivel criar: %s\n", ficheiro);
        return 0;
    }

    fprintf(f, "caixa_id;estado;clientes_fila;clientes_atendidos;produtos_vendidos;tempo_total_atendimento;maior_fila\n");

    for (i = 0; H != NULL && i < H->tamanho; i++)
    {
        Caixa *C = &H->Tabela[i];

        fprintf(f, "%d;%s;%d;%d;%d;%.2f;%d\n",
                C->id,
                C->aberta ? "ABERTA" : "FECHADA",
                C->fila ? C->fila->NEL : 0,
                C->totalPessoasAtendidas,
                C->totalProdutosVendidos,
                C->tempoTotalAtendimento,
                C->maxClientesFila);
    }

    fclose(f);
    printf("[CSV] - Caixas exportadas: %s\n", ficheiro);
    return 1;
}

int ExportarEstatisticasCSV(MatrizSupermercado *H, char *ficheiro)
{
    FILE *f = fopen(ficheiro, "w");
    Estatisticas E = {0};

    if (f == NULL)
    {
        printf("[ERRO] - Nao foi possivel criar: %s\n", ficheiro);
        return 0;
    }

    ObterCaixaMaisProdutos(H, &E);
    ObterCaixaMaisPessoas(H, &E);
    ObterCaixaMenosPessoas(H, &E);
    ObterNumeroProdutosOferecidos(H, &E);
    ValorTotalProdutosOferecidos(H, &E);
    ObterNumeroProdutosVendidos(H, &E);
    TempoMedioEsperaCaixas(H, &E);
    ObterTempoTotalAtendimento(H, &E);
    NumeroTotalClientesAtendidos(H, &E);
    ObterNumeroCaixasAbertas(H, &E);
    ObterNumeroCaixasFechadas(H, &E);
    ObterMaiorFila(H, &E);
    OperadorMenosPessoas(H, &E);
    ObterOperadorMaisProdutos(H, &E);

    fprintf(f, "estatistica;valor\n");
    fprintf(f, "caixa_mais_produtos;%d\n", E.idCaixaMaisProdutos);
    fprintf(f, "max_produtos_vendidos;%d\n", E.maxProdutosVendidos);
    fprintf(f, "caixa_mais_clientes;%d\n", E.idCaixaMaisPessoas);
    fprintf(f, "max_clientes_atendidos;%d\n", E.maxPessoasAtendidas);
    fprintf(f, "caixa_menos_clientes;%d\n", E.idCaixaMenosPessoas);
    fprintf(f, "min_clientes_atendidos;%d\n", E.minPessoasAtendidas);
    fprintf(f, "produtos_oferecidos;%d\n", E.numeroProdutosOferecidos);
    fprintf(f, "valor_produtos_oferecidos;%.2f\n", E.custoOferecidos);
    fprintf(f, "produtos_vendidos;%d\n", E.numeroTotalProdutosVendidos);
    fprintf(f, "tempo_medio_atendimento;%.2f\n", E.tempoMedioEsperaCaixas);
    fprintf(f, "tempo_total_atendimento;%.2f\n", E.tempoTotalAtendimento);
    fprintf(f, "clientes_atendidos;%d\n", E.numeroTotalClientesAtendidos);
    fprintf(f, "caixas_abertas;%d\n", E.numeroCaixasAbertas);
    fprintf(f, "caixas_fechadas;%d\n", E.numeroCaixasFechadas);
    fprintf(f, "maior_fila;%d\n", E.maiorFila);
    fprintf(f, "operador_menos_clientes;%d\n", E.operadorMenosPessoas);
    fprintf(f, "operador_mais_produtos;%d\n", E.operadorMaisProdutos);

    fclose(f);
    printf("[CSV] - Estatisticas exportadas: %s\n", ficheiro);
    return 1;
}

int CriarHistoricoCSV(char *ficheiro)
{
    FILE *f = fopen(ficheiro, "w");

    if (f == NULL)
    {
        printf("[ERRO] - Nao foi possivel criar o historico: %s\n", ficheiro);
        return 0;
    }

    fprintf(f, "data_hora;evento;cliente_id;cliente_nome;caixa_origem;caixa_destino;produto;valor\n");
    fclose(f);

    printf("[CSV] - Historico iniciado: %s\n", ficheiro);
    return 1;
}

int RegistrarHistoricoCSV(const char *evento,
                          Cliente *cliente,
                          int caixaOrigem,
                          int caixaDestino,
                          const char *produto,
                          float valor)
{
    FILE *f = fopen(FICHEIRO_HISTORICO, "a");
    time_t agora;
    struct tm *infoTempo;
    char dataHora[32] = "";

    if (f == NULL)
        return 0;

    agora = time(NULL);
    infoTempo = localtime(&agora);

    if (infoTempo != NULL)
        strftime(dataHora, sizeof(dataHora), "%Y-%m-%d %H:%M:%S", infoTempo);

    EscreverCampoCSV(f, dataHora);
    fprintf(f, ";");
    EscreverCampoCSV(f, evento ? evento : "");
    fprintf(f, ";%d;", cliente ? cliente->id : 0);
    EscreverCampoCSV(f, cliente ? cliente->nome : "");
    fprintf(f, ";%d;%d;", caixaOrigem, caixaDestino);
    EscreverCampoCSV(f, produto ? produto : "");
    fprintf(f, ";%.2f\n", valor);

    fclose(f);
    return 1;
}

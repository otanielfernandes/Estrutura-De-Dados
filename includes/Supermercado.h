#ifndef SUPERMERCADO_H_INCLUDED
#define SUPERMERCADO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Definicoes.h"
#include "ListaClientes.h"
#include "ListaProdutos.h"
#include "ListaFuncionarios.h"
#include "Relogio.h"
#include "Hashing.h"
#include "Estatisticas.h"

// doxygen
// Apagar daqui por enquanto:
/*
//Estrurura para as caixas:
typedef struct {
    int id;                         // NÃºmero da caixa (1, 2, 3...)
    int aberta;                     // 1 para ativa, 0 para desativada [cite: 22, 45]
    ListaPessoas *fila;             // A fila de clientes nesta caixa
    int totalPessoasAtendidas;      // Para as estatÃ­sticas finais [cite: 72]
    int totalProdutosVendidos;      // Para as estatÃ­sticas finais [cite: 73]
    // Podes adicionar o nome do operador aqui para o requisito da pÃ¡g 2 [cite: 75]
} Caixa;
*/

typedef struct
{
    char *NOME;

    ListaClientes *LClientes;
    ListaFuncionarios *LFuncionarios;
    ListaProdutos *LProdutos;

    Hashing *HCaixas; // Tabela de Hash para as caixas (JÃ¡ tinhas)

    // HorÃ¡rios (JÃ¡ tinhas)
    int HoraInicio, HoraFim;

    // NOVOS CAMPOS (ConfiguraÃ§Ã£o):
    int max_espera;                // MAX_ESPERA
    int n_caixas;                  // N_CAIXAS
    int tempo_atendimento_produto; // TEMPO_ATENDIMENTO_PRODUTO
    int max_preco;                 // MAX_PRECO
    int max_fila;                  // MAX_FILA
    int min_fila;                  // MIN_FILA

    int CadenciaEntradaClientes;
    Relogio *Rolex;

    /* Controlo da duraÃ§Ã£o da simulaÃ§Ã£o */
    int duracao_simulacao; /* ciclos atÃ© fechar portas (lido do ficheiro) */
    int ciclo_atual;       /* ciclo em que estamos agora                  */
    int simulacao_ativa;   /* 1 = sem novas entradas, a aguardar filas    */

    int totalClientesGerados;
    int maxClientesSimulacao;
    int terminarPrograma;

} Supermercado;

Supermercado *CriarSupermercado(char *nome);
int InicializarSupermercado(Supermercado *S, char *config);
void GerarCarrinhoCliente(Supermercado *S, Cliente *C, int quantidade);
void EstadoPagamentoIrCaixa(Supermercado *S);
int ExecutarSimulacao(Supermercado *S);
void EntradaPessoaSupermercado(Supermercado *S);
Caixa *EscolherCaixa(Supermercado *S);
Caixa *AbrirNovaCaixa(Supermercado *S);
int Supermercado_E_Para_Fechar(Supermercado *S);
void DestruirSupermercado(Supermercado *S);
void MenuPrincipal(Supermercado *S);
size_t MemoriaUtilizada(Supermercado *S);

#endif // SUPERMERCADO_H_INCLUDED
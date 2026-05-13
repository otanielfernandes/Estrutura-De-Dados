#ifndef SUPERMERCADO_H_INCLUDED
#define SUPERMERCADO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Definicoes.h"
//#include "Pessoa.h"
//#include "ListaPessoas.h"
#include "ListaClientes.h"
#include "ListaFuncionarios.h"
#include "Relogio.h"
#include "Estatisticas.h"

//Apagar daqui por enquanto:
/*
//Estrurura para as caixas:
typedef struct {
    int id;                         // Número da caixa (1, 2, 3...)
    int aberta;                     // 1 para ativa, 0 para desativada [cite: 22, 45]
    ListaPessoas *fila;             // A fila de clientes nesta caixa 
    int totalPessoasAtendidas;      // Para as estatísticas finais [cite: 72]
    int totalProdutosVendidos;      // Para as estatísticas finais [cite: 73]
    // Podes adicionar o nome do operador aqui para o requisito da pág 2 [cite: 75]
} Caixa;
*/

typedef struct
{
    char *NOME;

    ListaClientes *LClientes;
    ListaFuncionarios *LFuncionarios;
    ListaProdutos *LProdutos;
    
    Hashing       *HCaixas;   // Tabela de Hash para as caixas (Já tinhas)
    
    // Horários (Já tinhas)
    int HoraInicio, HoraFim; 
    
    //NOVOS CAMPOS (Configuração):
    int max_espera;                 // MAX_ESPERA 
    int n_caixas;                   // N_CAIXAS 
    int tempo_atendimento_produto;  // TEMPO_ATENDIMENTO_PRODUTO 
    int max_preco;                  // MAX_PRECO 
    int max_fila;                   // MAX_FILA 
    int min_fila;                   // MIN_FILA 
    
    int CadenciaEntradaClientes;     
    Relogio *Rolex;                 
    
} Supermercado;

Supermercado *CriarSupermercado(char *nome);
int InicializarSupermercado(Supermercado *S, char *config);
void EstadoPagamentoIrCaixa(Supermercado *S);
int ExecutarSimulacao(Supermercado *S);
void EntradaPessoaSupermercado(Supermercado *S);
int Supermercado_E_Para_Fechar(Supermercado *S);
void DestruirSupermercado(Supermercado *S);


#endif // SUPERMERCADO_H_INCLUDED

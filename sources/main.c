#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../includes/Uteis.h"
#include "../includes/Supermercado.h"

extern void wait_segundos ( int seconds );
extern int LerInteiro(char *txt);

int Menu()
{
    printf("1 - Listar\n");
    //-------
    int OP = LerInteiro("Qual a Opcao ?");
    return OP;
}
void ExecutaAccoesMenu(Supermercado *S)
{
    int OP = Menu();
    switch(OP)
    {
        case 1: //ListarCliente(S->LCientes); break;
        case 0: break;
    }

}

int main()
{
    system("chcp 65001");
    printf("Projeto ED - 25-26!\n");
    srand(time(NULL));
    Supermercado *Lidl = CriarSupermercado("Lidal");
    InicializarSupermercado(Lidl, "dados/Configuracao.txt");
    int Terminar = 0;
    while (!Terminar)
    {
        if (TeclaPressionada())
        {
            ExecutaAccoesMenu(Lidl);
        }
        ExecutarSimulacao(Lidl);
        wait_segundos(1);
        Terminar = Supermercado_E_Para_Fechar(Lidl);
    }
    //Falat implementar o que está em baixo comentado:
    //MostrarHashing(Lidl->HCaixas);
    DestruirSupermercado(Lidl);
    return 0;
}



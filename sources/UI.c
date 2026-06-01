#include "../includes/UI.h"

void cor(int c)
{
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void resetCor()
{
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void limparTela()
{
  system("cls");
}

int lerTecla()
{
  int t = _getch();

  if (t == 224)
    return _getch();

  return t;
}

void esperarEnter()
{
  printf("\n");
  printf("Prima ENTER para continuar...");
  getchar();
}
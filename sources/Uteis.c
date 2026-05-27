#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#endif

int Aleatorio(int min, int max)
{
    return min + rand() % (max - min + 1);
}

int LerInteiro(char *txt)
{
    int X;

    printf("%s", txt);

    scanf("%d", &X);

    getchar(); // limpa ENTER

    return X;
}

char ToMaiscula(char x)
{
    if ((x >= 'a') && (x <= 'z'))
        return 'A' + x - 'a';

    return x;
}

/*ESPERA EM SEGUNDOS*/

void wait_segundos(int seconds)
{
#ifdef _WIN32

    Sleep(seconds * 1000);

#else

    sleep(seconds);

#endif
}

/* DETETAR TECLA */
int TeclaPressionada()
{
#ifdef _WIN32

    if (_kbhit())
    {
        _getch(); // limpa tecla do buffer
        return 1;
    }

    return 0;

#else

    struct termios oldt, newt;

    int ch;

    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);

    newt = oldt;

    newt.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);

    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF)
    {
        return 1;
    }

    return 0;

#endif
}
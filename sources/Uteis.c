#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#include <conio.h>
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
    printf("%s", txt);
    int X;
    scanf("%d", &X);
    return X;
}

char ToMaiscula(char x)
{
    if ((x >= 'a') && (x <= 'z'))
        return 'A' + x - 'a';
    return x;
}

void wait(int mlseconds)
{
    clock_t endwait;
    endwait = clock() + mlseconds;
    while (clock() < endwait)
        ;
}

void wait_segundos(int seconds)
{
    wait(seconds * CLOCKS_PER_SEC);
}

int TeclaPressionada()
{
#ifdef _WIN32
    return _kbhit();
#else
    struct termios oldt, newt;
    int ch, oldf;

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
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
#endif
}

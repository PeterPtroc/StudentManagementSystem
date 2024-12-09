#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "utils.h"
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// message为顶头展示的信息，time为进度条走完的时间
void fake_process(char* message, float time)
{
    clearScreen();
    float times = time * 4;
    float delta = 1.0 / times;
    float progress = 0.0;
    while (progress < 1.0) {
        int barWidth = 70;
        printf("%s\n", message);
        printf("[");
        int pos = barWidth * progress;
        for (int i = 0; i < barWidth; ++i) {
            if (i < pos) printf("=");
            else if (i == pos) printf(">");
            else printf(" ");
        }
        printf("] %d %%\n", (int)(progress * 100.0));
        fflush(stdout);
#ifdef _WIN32
            Sleep(250);
#else
            usleep(250000);
#endif
        progress += delta; // for demonstration only
        clearScreen();
    }
}



void clean_stdin(void)
{
    int c;
    do
    {
        c = getchar();
    } while (c != '\n' && c != EOF);
}
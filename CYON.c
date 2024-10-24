#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

struct termios og_termios;

void disableRawMode()
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &og_termios);
}

void enableRawMode()
{
    tcgetattr(STDIN_FILENO, &og_termios);

    atexit(disableRawMode);

    struct termios raw = og_termios;

    raw.c_lflag &= ~(ECHO | ICANON);

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main(void)
{
    enableRawMode();

    char c;
    while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q') 
    {
        if (iscntrl(c)){
            printf("%d\n",c);
        }
        else{
            printf("%d ('%c') \n", c, c);
        }
    }
    return 0;
}
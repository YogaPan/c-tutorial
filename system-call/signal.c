#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static int running = 1;

void intHandler(int sig)
{
        printf("Good Bye.\n");
        exit(EXIT_SUCCESS);
}

int main(void)
{
        signal(SIGINT, intHandler);
        while (running);
        return 0;
}

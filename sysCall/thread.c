#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

void *show_message(void *ptr)
{
    const char *message1;
    char *message2;
    message1 = (char *)ptr;

    for (int i = 0; i < 5; i++) {
        printf("%s\n", message1);
        sleep(1);
        usleep(1);
    }
    message2 = (char *)malloc(sizeof(char) * 10);
    strcpy(message2, "ass");
    pthread_exit((void *)message2);
}

int main(int argc, char **argv)
{
    pthread_t thread1, thread2;
    const char *message1 = "Thread 1";
    const char *message2 = "Thread 2";
    void *ret1, *ret2;

    pthread_create(&thread1, NULL, show_message, (void *)message1);
    pthread_create(&thread2, NULL, show_message, (void *)message2);
    printf("haha I work in same time.\n");
    pthread_join(thread1, &ret1);
    pthread_join(thread2, &ret2);
    printf("return value from thread1 = %s\n", (char *)ret1);
    printf("return value from thread2 = %s\n", (char *)ret2);
    free(ret1);
    free(ret2);

    return 0;
}

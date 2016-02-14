#include <stdio.h>

#define NRM  "\x1B[0m"
#define RED  "\x1B[31m"
#define GRN  "\x1B[32m"
#define YEL  "\x1B[33m"
#define BLU  "\x1B[34m"
#define MAG  "\x1B[35m"
#define CYN  "\x1B[36m"
#define WHT  "\x1B[37m"

int main(int argc, char **argv)
{
    printf("%sred\n", RED);
    printf("%sgreen\n", GRN);
    printf("%syellow\n", YEL);
    printf("%sblue\n", BLU);
    printf("%smagenta\n", MAG);
    printf("%scyan\n", CYN);
    printf("%swhite\n", WHT);
    printf("%snormal\n", NRM);
    return 0;
}

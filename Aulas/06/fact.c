#include <stdlib.h>
#include <stdio.h>

long long unsigned int fatorial_r(unsigned int n) {
    if(n <= 1) return 1;

    return (long long unsigned int) n * fatorial_r(n - 1);
}

long long unsigned int fatorial_i(unsigned int n) {
    if(n <= 1) return 1;

    long long unsigned int r = 1;
    for(long long unsigned int i = 2; i <= (long long unsigned int) n; i++) r *= i;

    return r;
}

int main(void) {
    for(unsigned int i = 1; i <= 20; i++) printf("%2u! = %llu\n", i, fatorial_r(i));

    putchar('\n');

    for(unsigned int i = 1; i <= 20; i++) printf("%2u! = %llu\n", i, fatorial_i(i));

    return 0;
}
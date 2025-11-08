#include <stdlib.h>
#include <stdio.h>

long long unsigned int fibonacci(unsigned int i) {
    if(i <= 1) return (long long unsigned int) i;

    return fibonacci(i - 1) + fibonacci(i - 2);
}

int main(void) {
    for(unsigned int i = 0; i <= 30; i++) printf("F%u%s: %llu\n", i, (i < 10 ? "  " : " "), fibonacci(i));

    return 0;
}
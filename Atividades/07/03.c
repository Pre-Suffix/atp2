// Exercicio 3 • Sequência de Ackermann: Uma função recursiva
// que cresce muito rapidamente. A função de Ackermann A(m,n)
// é definida para números inteiros não negativos m e n da
// seguinte forma:
//
// A(m,n) =
//   n + 1                  se m = 0
//   A(m-1, 1)              se m > 0 e n = 0
//   A(m-1, A(m, n-1))      se m > 0 e n > 0
#include <stdlib.h>
#include <stdio.h>

// Implementação recursiva da Sequência de Ackermann,
// descrita acima.
unsigned long long ackermann(unsigned long long m, unsigned long long n) {
    if(m == 0) return n + 1;
    else if(m > 0 && n == 0) return ackermann(m - 1, 1);

    return ackermann(m - 1, ackermann(m, n - 1));
}

int main(void) {
    unsigned long long m = 0, n = 0;
    printf("Insira valores de m e n: ");
    scanf("%llu %llu", &m, &n);

    printf("A(%llu, %llu) = %llu", m, n, ackermann(m, n));

    return 0;
}
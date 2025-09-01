#include "numeros.c"

int main(void) {
    Numbers *nums = nullptr;
    nums = numalloc();
    if(nums == nullptr) {
        fputs("Erro na alocação", stderr);
        return 1;
    }

    int elements = 0;
    scanf("%d", &elements);

    double val = 0;
    for(int i = 0; i < elements; i++) {
        scanf("%lf", &val);
        numshift(&nums, val);
    }

    Numbers *elem = nums;
    while(1) {
        printf("%12lf (0x%llX)\n", elem->value, (unsigned long long int) elem->next);
        if(elem->next == nullptr) break;

        elem = elem->next;
    }

    return 0;
}
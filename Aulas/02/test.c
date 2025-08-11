#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char **nomes = NULL;

void getString(char *strPointer) {
    int j = 0;
    if(strPointer == NULL) strPointer = calloc(2, sizeof(char));

    char c = fgetc(stdin);
    for(c = (c == '\n' ? fgetc(stdin) : c); c != '\n'; j++) {
        strPointer = realloc(strPointer, (j + 2) * sizeof(char));

        strPointer[j] = c;
        c = fgetc(stdin);
    }

    strPointer[j] = '\0';
}

int main(void) {
    unsigned int nameCount = 1;
    
    printf("Quantos nomes serao armazenados: ");
    scanf("%d", &nameCount);
    if(nameCount == 0) return 1;

    nomes = calloc(nameCount, sizeof(char*));
    if(nomes == NULL) return 1;

    

    for(unsigned int i = 0; i < nameCount; i++) printf("%s\n", nomes[i]);

    return 0;
}
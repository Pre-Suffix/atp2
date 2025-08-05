// Exercicio n • 
#include <stdlib.h>
#include <stdio.h>

typedef struct point {
    int x;
    int y;

} Point;

Point *newPoint(int x, int y) {
    Point *point = calloc(1, sizeof(Point));
    if(point == NULL) return NULL;

    point->x = x;
    point->y = y;

    return point;
}

void printPoint(Point *point, FILE *output) {
    if(point == NULL || output == NULL) return;

    fprintf(output, "x: %d, y: %d\n", point->x, point->y);
}

int main(void) {
    Point *point = newPoint(4, 2);
    printPoint(point, stdout);
    
    return 0;
}
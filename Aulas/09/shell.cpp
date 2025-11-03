#include <iostream>
#include <vector>
#include <random>

#define VEC_SIZE 1000

void printvec(int *vec, size_t max) {
    std::cout << "[ ";
    for(size_t i = 0; i < max; i++)
        std::cout << (int) vec[i] << ' ';
    
    std::cout << "]\n";
}

void shell(int *vec, int min, int max) {
    // Comece com uma distância entre trocas grande. Itere
    // múltiplas vezes até a distância entre elementos ordenados
    // ser igual a 0 (o vetor está ordenado).
    for(int dist = (max - min) / 2; dist > 0; dist /= 2) {
        // Para cada item da lista, faça uma ordenação de Insertion
        // Sort, só que cada par de itens analisados tem distância
        // "dist" ao invés de 1.
        for(int i = dist + min; i <= max; i++) {
            int atual = vec[i];
            int j = i;

            for(;j >= dist + min && vec[j - dist] > atual; j -= dist)
                vec[j] = vec[j - dist];
            
            vec[j] = atual;
        }
    }
}

int main(void) {
    std::mt19937 rng;
    std::uniform_int_distribution<int> _dist;

    rng.seed(time(NULL));

    int n; std::cin >> n;

    int *vec = new int[n];
    for(int i = 0; i < n; i++) std::cin >> vec[i];

    printvec(vec, n);

    shell(vec, 0, n - 1);

    printvec(vec, n);

    return 0;
}
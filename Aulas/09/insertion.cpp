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

void insertion(int vec[], int min, int max) {
    for(int i = min + 1; i <= max; i++) {
        int current = vec[i];
        int j = i - 1;

        while(j >= min && current < vec[j]) {
            vec[j + 1] = vec[j];
            j -= 1;
        }

        vec[j + 1] = current;
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

    insertion(vec, 0, n - 1);

    printvec(vec, n);

    for(int i = 1; i < n; i++) {
        if(vec[i] < vec[i - 1]) {
            std::cout << i << ' ' << vec[i - 1] << ' ' << vec[i] << '\n';
        }
    }

    return 0;
}
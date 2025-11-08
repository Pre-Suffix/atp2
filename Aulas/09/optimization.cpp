#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <random>
#include <chrono>

#define THRESHOLD_MAX 128
#define MAXTHREADS 6
#define VEC_SIZE 4098304

void insertion(int *vec, int min, int max) {
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

void shellsort(int *vec, int min, int max) {
    // Comece com uma distância entre trocas grande. Itere
    // múltiplas vezes até a distância entre elementos ordenados
    // ser igual a 0 (o vetor está ordenado).
    for(int dist = log2(max - min) - 1; dist > 0; dist /= 2) {
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

void quicksort(int *vec, int min, int max, int QS_THRESHOLD) {
    if(min >= max) return;

    if(max - min <= QS_THRESHOLD) {
        insertion(vec, min, max);
        return;
    }

    int pivo_i = min;
    int pivo = vec[pivo_i];

    int is = min - 1, ie = max + 1;
    while(true) {
        do { is++; } while (vec[is] < pivo);

        do { ie--; } while (vec[ie] > pivo);

        if(is >= ie) break;

        std::swap(vec[ie], vec[is]);
    }

    pivo_i = ie;

    quicksort(vec, min, pivo_i, QS_THRESHOLD);
    quicksort(vec, pivo_i + 1, max, QS_THRESHOLD);
}

void iteration(int_fast32_t seed, int iteration_id, int64_t **runtimes_list) {
    int64_t *runtimes = new int64_t[THRESHOLD_MAX];
    int *vec = new int[VEC_SIZE];

    std::mt19937 rng;
    std::uniform_int_distribution<int> dist;

    rng.seed(seed);

    for(int THRESHOLD = 1; THRESHOLD <= THRESHOLD_MAX; THRESHOLD++) {    
        for(int i = 0; i < VEC_SIZE; i++) vec[i] = dist(rng);

        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        quicksort(vec, 0, VEC_SIZE - 1, THRESHOLD);

        runtimes[THRESHOLD - 1] = (std::chrono::steady_clock::now() - begin).count();
    }

    delete[] vec;
    runtimes_list[iteration_id] = runtimes;
}

int main(void) {
    std::mt19937 rng;
    std::uniform_int_distribution<int_fast32_t> dist;

    rng.seed(time(NULL));

    int iterations = 24;
    int it_count = 0;
    std::cin >> iterations;

    int64_t *runtimes_list_min = new int64_t[THRESHOLD_MAX];
    int64_t *runtimes_list_max = new int64_t[THRESHOLD_MAX]();
    int64_t **runtimes_list = new int64_t*[iterations];

    for(int i = 0; i < THRESHOLD_MAX; i++) runtimes_list_min[i] = INT64_MAX;

    std::vector<std::thread> threads;

    for(int t = 0; t <= (iterations / MAXTHREADS); t++) {
        for(int it = 0; it < MAXTHREADS && it_count < iterations; it++) {
            threads.emplace_back(std::thread(iteration, dist(rng), it_count, runtimes_list));
            it_count++;
        }

        for(size_t i = MAXTHREADS * t; i < threads.size(); i++) {
            threads[i].join();

            for(int j = 0; j < THRESHOLD_MAX; j++) {
                runtimes_list_min[j] = std::min(runtimes_list_min[j], runtimes_list[i][j]);
                runtimes_list_max[j] = std::max(runtimes_list_max[j], runtimes_list[i][j]);
            }

            delete[] runtimes_list[i];
        }

        std::cout << "THREADS " << it_count - MAXTHREADS + 1 << '-' << it_count << " DONE.\n";
    }

    std::ofstream out("runtimes.txt");

    for(int i = 0; i < THRESHOLD_MAX; i++) {
        out << runtimes_list_min[i] << ';' << runtimes_list_max[i] << '\n';
    }

    delete[] runtimes_list_min;
    delete[] runtimes_list_max;
    delete[] runtimes_list;

    out.close();

    return 0;
}
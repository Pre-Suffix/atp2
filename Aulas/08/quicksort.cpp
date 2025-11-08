#include <algorithm>
#include <iostream>
#include <vector>
#include <random>
#include <chrono>

void quicksort(std::vector<unsigned int> &vec, size_t min, size_t max) {
    // Caso o subvetor analisado tenha tamanho 1 ou inválido, retorne.
    if(min >= max) return;

    // Obtém o valor do pivô para o subvetor analisado. Nesse caso, o
    // pivô é sempre o valor do meio do subvetor analisado.
    size_t pivo_i = (max - min) / 2 + min;
    unsigned int pivo = vec[pivo_i];

    // Instancia um segundo vetor onde a partição ocorrerá. Ele já é
    // instanciado com tamanho para melhorar a performance.
    std::vector<unsigned int> _vec(max - min + 1, 0);

    // Para cada valor do subvetor analisado, verifique se ele é maior
    // ou menor que o pivô, e coloque-o no fim ou começo do vetor
    // partição.
    size_t is = 0, ie = max - min;
    for(size_t i = min; i <= max; i++) {
        if(i == pivo_i) continue;

        if(vec[i] < pivo) {
            _vec[is] = vec[i];
            is++;
        } else {
            _vec[ie] = vec[i];
            ie--;
        }
    }

    // Insira o pivô no vetor partição.
    _vec[is] = pivo;

    // Troque o índice do pivô após a partição.
    pivo_i = is + min;

    // Copie o vetor partição ao vetor principal.
    for(size_t i = 0; i <= max - min; i++)
        vec[i + min] = _vec[i];


    // Ordene as duas metades divididas pelo pivô.
    if(pivo_i != 0) quicksort(vec, min, pivo_i - 1);
    quicksort(vec, pivo_i + 1, max);
}

void bubblesort(std::vector<unsigned int> &vec) {
    for(size_t i = 0; i < vec.size() - 1; i++) {
        bool swapped = false;
        for(size_t j = 0; j < vec.size() - i - 1; j++) {
            if(vec[j] > vec[j + 1])
                std::swap(vec[j], vec[j + 1]), swapped = true;
        }

        if(!swapped) return;
    }
}

int main(void) {
    std::mt19937 rng;
    std::uniform_int_distribution<unsigned int> _dist;

    rng.seed(time(NULL));

    std::vector<unsigned int> vec;

    size_t VEC_SIZE = 100000;
    std::cin >> VEC_SIZE;

    if(VEC_SIZE < 1) return -1;

    for(size_t i = 0; i < VEC_SIZE; i++) vec.push_back(_dist(rng));

    std::cout << "Random numbers inputed\n";

    std::chrono::steady_clock::time_point begin_q = std::chrono::steady_clock::now();
    quicksort(vec, 0, VEC_SIZE - 1);
    std::chrono::steady_clock::time_point end_q   = std::chrono::steady_clock::now();

    std::cout << "Quicksort done.\n";
    for(size_t i = 0; i < VEC_SIZE - 1; i++) if(vec[i] > vec[i + 1]) {
        std::cout << "vector wasn't sorted (?)\n";
        return -1;
    }

    for(size_t i = 0; i < VEC_SIZE; i++) vec[i] = _dist(rng);

    std::chrono::steady_clock::time_point begin_b = std::chrono::steady_clock::now();
    bubblesort(vec);
    std::chrono::steady_clock::time_point end_b   = std::chrono::steady_clock::now();

    for(size_t i = 0; i < VEC_SIZE - 1; i++) if(vec[i] > vec[i + 1]) {
        std::cout << "vector wasn't sorted (?)\n";
        return -1;
    }

    for(size_t i = 0; i < VEC_SIZE; i++) vec[i] = _dist(rng);

    std::chrono::steady_clock::time_point begin_a = std::chrono::steady_clock::now();
    std::sort(vec.begin(), vec.end());
    std::chrono::steady_clock::time_point end_a   = std::chrono::steady_clock::now();

    std::cout << "Quicksort  : " << std::chrono::duration_cast<std::chrono::microseconds>(end_q - begin_q).count() << "µs\n";
    std::cout << "Bubblesort : " << std::chrono::duration_cast<std::chrono::microseconds>(end_b - begin_b).count() << "µs\n";
    std::cout << "std::sort  : " << std::chrono::duration_cast<std::chrono::microseconds>(end_a - begin_a).count() << "µs" << std::endl;

    return 0;
}
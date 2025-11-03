#include <algorithm>
#include <iostream>
#include <iomanip>
#include <random>
#include <chrono>

void bubblesort(int *vec, int min, int max) {
    for(int lim = max; lim >= min + 1; lim--) {
        bool trocou = false;
        for(int i = 1; i <= lim; i++) {
            if(vec[i] > vec[i - 1]) continue;

            std::swap(vec[i], vec[i - 1]);
            trocou = true;
        }

        if(!trocou) return;
    }
}

void insertion(int *vec, int min, int max) {
    for(int i = min + 1; i <= max; i++) {
        int atual = vec[i];
        int j = i - 1;

        while(j >= min && atual < vec[j]) {
            vec[j + 1] = vec[j];
            j -= 1;
        }

        vec[j + 1] = atual;
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

void quicksort(int *vec, int min, int max, int qs_limiar) {
    // Caso o subvetor analisado tenha tamanho 1 ou inválido, retorne.
    if(min >= max) return;

    // Caso o tamanho do subvetor analisado seja menor que o limiar,
    // use Insertion Sort (que é mais rápido em vetores pequenos).
    if(max - min <= qs_limiar) {
        insertion(vec, min, max);
        return;
    }

    // Obtém o valor do pivô para o subvetor analisado. Nesse caso, o
    // pivô é sempre o valor do meio do subvetor analisado.
    int pivo_i = (max - min) / 2 + min;
    int pivo = vec[pivo_i];

    // Instancia um segundo vetor onde a partição ocorrerá. Ele já é
    // instanciado com tamanho para melhorar a performance.
    int *_vec = new int[max - min + 1];

    // Para cada valor do subvetor analisado, verifique se ele é maior
    // ou menor que o pivô, e coloque-o no fim ou começo do vetor
    // partição.
    int is = 0, ie = max - min;
    for(int i = min; i <= max; i++) {
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
    for(int i = 0; i <= max - min; i++)
        vec[i + min] = _vec[i];

    // Deleta o vetor instanciado
    delete[] _vec;

    // Ordene as duas metades divididas pelo pivô.
    if(pivo_i != 0) quicksort(vec, min, pivo_i - 1, qs_limiar);
    quicksort(vec, pivo_i + 1, max, qs_limiar);
}

// Retorna verdadeiro caso seja um modo de operação válido.
bool op_modovalido(char modo) {
    switch(modo) {
        case 'b':
        case 'i':
        case 's':
        case 'q':
        case 'm':
        case 't':
            return true;
        default:
            return false;
    }
}

void preencher_vetor(int *vec, int max, int_fast32_t seed) {
    std::mt19937 rng;
    std::uniform_int_distribution<int> dist;
    rng.seed(seed);

    for(int i = 0; i < max; i++) vec[i] = dist(rng);
}

int main(void) {
    // Configure o gerador de sementes
    std::mt19937 rng;
    std::uniform_int_distribution<int_fast32_t> dist;
    rng.seed(time(NULL));

    // Obtenha os parâmetros da comparação do usuário
    char modo = '\0';
    int tamanho_vetor = 0;

    while(!op_modovalido(modo)) {
        std::cout << "Modos de operacao:\n"
        << "b: Bubble Sort\n"
        << "q: Quicksort\n"
        << "i: Insertion Sort\n"
        << "s: Shell Sort\n"
        << "m: Misto (Quicksort + Insertion)\n"
        << "t: Todos\n";

        std::cin >> modo;
        if(modo >= 'A' && modo <= 'Z') modo += 32;
    }

    while(tamanho_vetor <= 0) {
        std::cout << "Tamanho do vetor teste: ";
        std::cin >> tamanho_vetor;
    }

    std::chrono::steady_clock::time_point comeco, fim;
    int *vec = new int[tamanho_vetor];

    std::cout << std::fixed << std::setprecision(5);

    if(modo == 'b' || modo == 't') {
        preencher_vetor(vec, tamanho_vetor, dist(rng));
        comeco = std::chrono::steady_clock::now();
        
        bubblesort(vec, 0, tamanho_vetor - 1);

        fim = std::chrono::steady_clock::now();

        std::cout << "Bubble Sort: " << (double) std::chrono::duration_cast<std::chrono::nanoseconds>(fim - comeco).count() / 1000000 << "ms\n";

        for(int i = 1; i < tamanho_vetor; i++) {
            if(vec[i] < vec[i - 1]) {
                std::cout << "nao deu certo...,\n";
                break;
            }
        }
    }

    if(modo == 'q' || modo == 't') {
        preencher_vetor(vec, tamanho_vetor, dist(rng));
        comeco = std::chrono::steady_clock::now();
        
        quicksort(vec, 0, tamanho_vetor - 1, 0);

        fim = std::chrono::steady_clock::now();

        std::cout << "Quicksort: " << (double) std::chrono::duration_cast<std::chrono::nanoseconds>(fim - comeco).count() / 1000000 << "ms\n"; 

        for(int i = 1; i < tamanho_vetor; i++) {
            if(vec[i] < vec[i - 1]) {
                std::cout << "nao deu certo...,\n";
                break;
            }
        }
    }

    if(modo == 'i' || modo == 't') {
        preencher_vetor(vec, tamanho_vetor, dist(rng));
        comeco = std::chrono::steady_clock::now();
        
        insertion(vec, 0, tamanho_vetor - 1);

        fim = std::chrono::steady_clock::now();

        std::cout << "Insertion Sort: " << (double) std::chrono::duration_cast<std::chrono::nanoseconds>(fim - comeco).count() / 1000000 << "ms\n"; 

        for(int i = 1; i < tamanho_vetor; i++) {
            if(vec[i] < vec[i - 1]) {
                std::cout << "nao deu certo...,\n";
                break;
            }
        }
    }

    if(modo == 's' || modo == 't') {
        preencher_vetor(vec, tamanho_vetor, dist(rng));
        comeco = std::chrono::steady_clock::now();
        
        shellsort(vec, 0, tamanho_vetor - 1);

        fim = std::chrono::steady_clock::now();

        std::cout << "Shellsort: " << (double) std::chrono::duration_cast<std::chrono::nanoseconds>(fim - comeco).count() / 1000000 << "ms\n"; 

        for(int i = 1; i < tamanho_vetor; i++) {
            if(vec[i] < vec[i - 1]) {
                std::cout << "nao deu certo...,\n";
                break;
            }
        }
    }
    
    if(modo == 'm' || modo == 't') {
        preencher_vetor(vec, tamanho_vetor, dist(rng));
        comeco = std::chrono::steady_clock::now();
        
        quicksort(vec, 0, tamanho_vetor - 1, 70);

        fim = std::chrono::steady_clock::now();

        std::cout << "Misto: " << (double) std::chrono::duration_cast<std::chrono::nanoseconds>(fim - comeco).count() / 1000000 << "ms\n"; 

        for(int i = 1; i < tamanho_vetor; i++) {
            if(vec[i] < vec[i - 1]) {
                std::cout << "nao deu certo...,\n";
                break;
            }
        }
    }

    return 0;
}
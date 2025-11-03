#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <random>
#include <chrono>

#define RUNS 1024
typedef std::chrono::_V2::steady_clock::rep timerep_t;

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

void iteracao(timerep_t **tempos, int i, int t_vec, int_fast32_t seed) {
    std::mt19937 rng;
    std::uniform_int_distribution<int_fast32_t> dist;
    rng.seed(seed);

    int *vec = new int[t_vec];
    
    tempos[i] = new timerep_t[6];
    for(int j = 0; j < 6; j++) tempos[i][j] = (timerep_t) 0;

    std::chrono::steady_clock::time_point comeco, fim;

    /**
     * BUBBLE SORT
     */
    for(int j = 0; j < RUNS; j++) {
        preencher_vetor(vec, t_vec, dist(rng));
        comeco = std::chrono::steady_clock::now();

        bubblesort(vec, 0, t_vec - 1);
        fim = std::chrono::steady_clock::now();
        tempos[i][0] += (fim - comeco).count();
    }

    /**
     * QUICKSORT
     */
    for(int j = 0; j < RUNS; j++) {
        preencher_vetor(vec, t_vec, dist(rng));
        comeco = std::chrono::steady_clock::now();

        quicksort(vec, 0, t_vec - 1, 0);
        fim = std::chrono::steady_clock::now();
        tempos[i][1] += (fim - comeco).count();
    }

    /**
     * INSERTION SORT
     */
    for(int j = 0; j < RUNS; j++) {
        preencher_vetor(vec, t_vec, dist(rng));
        comeco = std::chrono::steady_clock::now();

        insertion(vec, 0, t_vec - 1);
        fim = std::chrono::steady_clock::now();
        tempos[i][2] += (fim - comeco).count();
    }

    /**
     * SHELL SORT
     */
    for(int j = 0; j < RUNS; j++) {
        preencher_vetor(vec, t_vec, dist(rng));
        comeco = std::chrono::steady_clock::now();

        shellsort(vec, 0, t_vec - 1);
        fim = std::chrono::steady_clock::now();
        tempos[i][3] += (fim - comeco).count();
    }

    /**
     * QUICKSORT + ITERATION SORT
     */
    for(int j = 0; j < RUNS; j++) {
        preencher_vetor(vec, t_vec, dist(rng));
        comeco = std::chrono::steady_clock::now();

        quicksort(vec, 0, t_vec - 1, 70);
        fim = std::chrono::steady_clock::now();
        tempos[i][4] += (fim - comeco).count();
    }

    /**
     * std::sort
     */
    for(int j = 0; j < RUNS; j++) {
        preencher_vetor(vec, t_vec, dist(rng));
        comeco = std::chrono::steady_clock::now();

        std::sort(&vec[0], &vec[t_vec - 1]);
        fim = std::chrono::steady_clock::now();
        tempos[i][5] += (fim - comeco).count();
    }

    delete[] vec;
}

int main(void) {
    // Configure o gerador de sementes
    std::mt19937 rng;
    std::uniform_int_distribution<int_fast32_t> dist;
    rng.seed(time(NULL));

    // Obtenha os parâmetros da comparação do usuário
    int tamanho_vetor = 0, maxthreads = 0;

    while(tamanho_vetor <= 5) {
        std::cout << "Limite do tamanho vetorial (min 6): ";
        std::cin >> tamanho_vetor;
    }

    while(maxthreads <= 0) {
        std::cout << "Numero de threads: ";
        std::cin >> maxthreads;
    }

    timerep_t **tempos = new timerep_t*[tamanho_vetor];
    std::vector<std::thread> threads;
    int threadcount = 0;

    for(int t = 0; t <= (tamanho_vetor / maxthreads); t++) {
        for(int it = 0; it < maxthreads && threadcount < tamanho_vetor; it++) {
            threads.emplace_back(std::thread(iteracao, tempos, threadcount, threadcount + 1, dist(rng)));
            threadcount++;
        }

        for(size_t i = maxthreads * t; i < threads.size(); i++)
            threads[i].join();
    }

    std::cout << "Escrevendo resultados no arquivo.\n";

    std::string nome_arq = "comparacao-";
    nome_arq += std::to_string(tamanho_vetor);
    nome_arq += ".csv";

    std::ofstream out(nome_arq);

    out << "BubbleSort;QuickSort;InsertionSort;ShellSort;Misto;std::sort\n";

    for(int i = 0; i < tamanho_vetor; i++) {
        out << tempos[i][0] / RUNS << ';';
        out << tempos[i][1] / RUNS << ';';
        out << tempos[i][2] / RUNS << ';';
        out << tempos[i][3] / RUNS << ';';
        out << tempos[i][4] / RUNS << ';';
        out << tempos[i][5] / RUNS << '\n';

        delete[] tempos[i];
    }

    delete[] tempos;
    out.close();

    return 0;
}
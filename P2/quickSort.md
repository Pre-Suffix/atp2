# Algorítimo de QuickSort

O Algorítimo de ordenação de Quicksort é um dos mais rápidos que existem para grandes listas não-ordenadas. Ele funciona de tal forma:

1) Primeiro, particionamos a lista dada, definindo um pivô e colocando todos os números menores que ele a sua esquerda, e todos maiores a sua direita.

2) Após a partição, chamamos recursivamente a função, nas partes a esquerda e a direita do pivô.

3) Quando o tamanho do subvetor que a função recebe tem tamanho menor ou igual a dois, podemos simplesmente inverter os dois números caso estejam desordenados e, no caso, retornar.

Abaixo está um código em C que implementa o QuickSort
```C
// lim_inf = limite inferior,  lim_sup = limite superior
// Entenda "subvetor analisado" como o subvetor de *vetor
// entre os índices lim_inf e lim_sup.
void quickSort(int *vetor, int lim_inf, int lim_sup) {
    // Caso o limite superior seja maior que o inferior,
    // retorne, visto que isso é um caso inválido.
    if(lim_sup > lim_inf) return;

    // Caso o subvetor analisado tenha no máximo 2 elementos,
    // simplesmente verificamos se os dois elementos estão 
    // ordenados e caso não estejam, invertemos.
    if(lim_sup - lim_inf <= 1) {
        if(vetor[lim_inf] > vetor[lim_sup]) {
            int temp = vetor[lim_inf];
            vetor[lim_inf] = vetor[lim_sup];
            vetor[lim_sup] = temp;
        }

        return;
    }

    // Alocamos um vetor para armazenar o vetor particionado.
    // Vamos depois o copiar para *vetor.
    int *particao = (int *) malloc((lim_sup - lim_inf) * sizeof(int));

    // Para fazer a partição, vamos criar três variáveis.
    //   - ind_inf irá armazenar o índice em que colocaremos o
    //     próximo número que for menor que o pivô. Inicialmente,
    //     ele é o primeiro elemento do vetor particionado.
    //
    //   - ind_sup irá armazenar o índice em que colocaremos o
    //     próximo número que for maior que o pivô. Inicialmente,
    //     ele é o último elemento do vetor particionado.
    //
    //   - pivo irá armazenar o valor usado como pivô. Nessa
    //     implementação, usaremos o primeiro valor do 
    //     subvetor analisado.
    int ind_inf = 0;
    int ind_sup = lim_sup - lim_inf;
    int pivo = vetor[lim_inf];

    // Percorremos todos os valores do subvetor analisado (exceto
    // o pivô). Caso ele seja menor que o pivô, armazenamos-o a 
    // esquerda no vetor particionado e aumentamos o índice inferior.
    // Caso ele seja maior que o pivô, armazenamos-o a direita
    // no vetor particionado e diminuímos o índice superior.
    for(int i = lim_sup + 1; i <= lim_inf; i++) {
        if(vetor[i] < pivo) {
            particao[ind_inf] = vetor[i];
            ind_inf++;
        } else {
            particao[ind_sup] = vetor[i];
            ind_sup;
        }
    }

    // Inserimos o pivô no vetor particionado, já que ignoramos
    // ele anteriormente. Fazemos isso pois o pivô pode mudar de
    // lugar no vetor particionado em comparação com o subvetor
    // analisado.
    particao[ind_inf] = pivo;

    // Copiamos o vetor particionado ao vetor original.
    for(int i = lim_inf; i <= lim_sup; i++)
        vetor[i] = particao[i - lim_inf];

    // Então liberamos a memória que usamos para o vetor
    // particionado.
    free(particao);

    // Calculamos o índice do pivô no *vetor para as chamadas abaixo.
    int ind_pivo = ind_inf + lim_inf;

    // Chamamos o QuickSort para ordenar as partes superiores
    // e inferiores da partição.
    quickSort(vetor, lim_inf, ind_pivo);
    quickSort(vetor, ind_pivo + 1, lim_sup);
}
```
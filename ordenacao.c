#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include<time.h>

#define DEZ 10 //KKK
#define MIL 1000
#define CEMMIL 100000
#define DEZMILHOES 200

// troca os valores entre dois numeros inteiros
void trocarValor(int *x, int *y){
    int aux;
    aux = *x;
    *x = *y;
    *y = aux;
}

// >> ordenacao bubble
void bubbleSort(int* vetor, int tamanhoVetor){
	int i, j;
    for(i = tamanhoVetor-1; i >= 1; i--){
		for(j = 0; j < i; j++) { 
			if(vetor[j] > vetor[j+1]) { // se o valor posicao atual é maior que o valor da proxima posicao  
				trocarValor(&vetor[j], &vetor[j+1]); // realiza a troca entre os dois
			}
		}
	}
}
// << fim ordenacao bubble

// >> ordenacao insertion
void insertionSort(int *vetor, int tamanhoVetor){
	int i, j;
    int pivo;

	for(i = 1; i < tamanhoVetor; i++){
		pivo = vetor[i];
		for(j = i-1; (vetor[j] > pivo) && j >= 0; j--){ // enquanto o valor que esta sendo inserido é menor que o valor do vetor que esta sendo comparado no momento
			vetor[j+1] =  vetor[j]; // o elementos "avançam" de indice 
		}
		vetor[j+1] = pivo; // recebe o valor que esta sendo inserido quando encontra a posicao certa, o +1 é devido a decrementacao do for anterior
	}
}
// << fim ordenacao insertion

// >> inicio ordenacao mergesort
void merge(int vetor[], int tamanhoVetor){
    int i = 0, j, k = 0;
    int *tmp; //vetor temporario
    int meio;
    
    tmp = (int *) malloc(tamanhoVetor * sizeof(int));
    
    meio = tamanhoVetor/2;
    j = meio;

    while((i < meio) && (j < tamanhoVetor)){ 
        if(vetor[i] < vetor[j]){
            tmp[k] = vetor[i];
            i++;
        }
        else{
            tmp[k] = vetor[j];
            j++;
        }
        k++;
    }

    if(i == meio){
        while(j < tamanhoVetor){
            tmp[k] = vetor[j];
            j++;
            k++;
        }
    }
    else{
        while(i < meio){
            tmp[k] = vetor[i];
            i++;
            k++;
        }
    }

    for(i = 0; i < tamanhoVetor; ++i){
        vetor[i] = tmp[i];
    }
    free(tmp);
}
void mergeSort(int vetor[], int tamanhoVetor){
    int meio;
    if (tamanhoVetor > 1){ // divide o vetor consecutivas vezes ate sobrar só 1
        meio = tamanhoVetor/2;
        mergeSort(vetor, meio);
        mergeSort(vetor + meio, tamanhoVetor - meio);
        merge(vetor, tamanhoVetor); // de forma recursiva vai ordenar a "menor parte" de cada metade e "voltar unindo" as metades já ordenadas
  }
}
// << fim ordenacao mergesort

// >> ordenacao quicksort
void quickSort(int vetor[], int tamanhoVetor){
	int i = 1; 
    int j = (tamanhoVetor - 1); 
    int pivo = vetor[0];

    if(tamanhoVetor <= 1){ // parada de recursão e "volta pra uniao" do que foi ordenado
		return;
	}

	while(1){
		while((i < tamanhoVetor) && (vetor[i] <= pivo)){ // quantos elementos "anteriores" ao pivo
			i++;
		}
		while(vetor[j] > pivo){ // quantos elementos "posteriores" ao pivo 
			j--; 
		}
		if(i < j){ // realiza troca dos valores se i < j, pois depois do indice j esta ordenado
			trocarValor(&vetor[i],&vetor[j]);   
            i++;
			j--;
		}
		if(i >= j){ // depois do j ja esta ordenado
			break;
		}
	}
	vetor[0] = vetor[j];
	vetor[j] = pivo;

	quickSort(vetor, j);
	quickSort(&vetor[i], (tamanhoVetor-i));
}
// << fim ordenacao quicksort

// >> ordenacao heap
void peneira (int vetor[], int tamanhoHeap) { 
    int p = 1, f = 2, x = vetor[1];
    while (f <= tamanhoHeap) { // rearranja o vetor de modo para virar heap
        if (f < tamanhoHeap && vetor[f] < vetor[f+1]) 
            ++f;
        if (x >= vetor[f])
            break;
        vetor[p] = vetor[f];
        p = f, f = 2*p;
    }
    vetor[p] = x;
}

void construirHeap(int vetor[], int tamanhoHeap){ // heap ->  vetor[f/2] ≥ vetor[f], portanto é um vetor em que o valor de todo pai é maior ou igual ao valor de cada um de seus dois filhos 
    for(int k = 1; k < tamanhoHeap; ++k){            
        int f = k+1;
        while (f > 1 && vetor[f/2] < vetor[f]) {  
            trocarValor (&vetor[f/2], &vetor[f]);          
            f /= 2;                        
      }
   }
}

void heapsortTeste (int vetor[], int tamanhoVetor){
    construirHeap (vetor, tamanhoVetor);
    int tamanhoHeap;
    for(tamanhoHeap = tamanhoVetor; tamanhoHeap >= 2; --tamanhoHeap) {
        trocarValor (&vetor[1], &vetor[tamanhoHeap]);
        peneira (vetor, tamanhoHeap-1);
    }
}
// << fim ordenacao heap

void radixSort(int *vet, int n) {
	int i, exp = 1, m = 0, bucket[n], temp[n];

	for(i = 0; i < n; i++) {
		if(vet[i] > m) {
			m = vet[i];
		}
	}

	while((m/exp) > 0) {
		for (i = 0; i < n; i++) {
			bucket[i] = 0;
		}
		for(i = 0; i < n; i++) {
			bucket[(vet[i] / exp) % 10]++;
		}
		for(i = 1; i < n; i++) {
			bucket[i] += bucket[i-1];
		}
		for(i = (n - 1); i >= 0; i--) {
			temp[--bucket[(vet[i] / exp) % 10]] = vet[i];
		}
		for(i = 0; i < n; i++) {
			vet[i] = temp[i];
		}
		exp *= 10;
	}
}

void preencherVetor(int vetor[], int tamanhoVetor){
    int i;
    srand((unsigned) time(NULL));
    for(i = 0; i < tamanhoVetor; i++){
        vetor[i] = rand()%100;
    }
}

void copiarVetor(int vetor[], int vetorOriginal[], int tamanhoVetor){
    for (int i = 0; i < tamanhoVetor; i++){
        vetor[i] = vetorOriginal[0];
    }
}

void printarVetor(int vetor[], int tamanhoVetor){
    int i;
    printf("\n\tvetor(%i) = |", tamanhoVetor);
    // se for maior que 100, printa os 10 primeiros, os 10 do meio e os 10 ultimos
    if (tamanhoVetor > 100){
        for(i = 0; i < 10; i++){
            printf(" %i |", vetor[i]);
        }
        printf(" ... |");
        for(i = tamanhoVetor/2; i < (tamanhoVetor/2)+10; i++){
            printf(" %i |", vetor[i]);
        }   
        printf(" ... |");
        for(i = tamanhoVetor-10; i < tamanhoVetor; i++){
            printf(" %i |", vetor[i]);
        }   
    }

    else{
        for(i = 0; i < tamanhoVetor; i++){
        printf(" %i |", vetor[i]);
        }
    }
}

void copiarUmVetor(int vetor[], int vetorOriginal[], int tamanhoVetor){
    int i;
    for(i = 0; i < tamanhoVetor; i++){
        vetor[i] = vetorOriginal[i];
    }
}


int main() {
    int i, j;
    int tamanhoVetor[4] = {DEZ, MIL, CEMMIL, DEZMILHOES};
    // vetor original, valores gerados aleatorios de 0 a 99
    int *vetor;
    vetor = malloc(4 * sizeof(int));
    
    // vetores sao usados para armazar copias do vetor original, para que o tempo seja calculado de forma "justa" onde todos os vetores são iguais
    int *vetorBubble;
    vetorBubble = malloc(4 * sizeof(int));
    int *vetorInsertion;
    vetorInsertion = malloc(4 * sizeof(int));
    int *vetorMerge;
    vetorMerge = malloc(4 * sizeof(int));
    int *vetorQuick;
    vetorQuick = malloc(4 * sizeof(int));
    int *vetorHeap;
    vetorHeap = malloc(4 * sizeof(int));
    int *vetorRadix;
    vetorRadix = malloc(4 * sizeof(int));

    // variaveis para armazenar o tempo de cada funcao
    double tempoVetor[4] = {0.0, 0.0, 0.0, 0.0};
    double tempoBubble[4] = {0.0, 0.0, 0.0, 0.0};
    double tempoInsertion[4] = {0.0, 0.0, 0.0, 0.0};
    double tempoMerge[4] = {0.0, 0.0, 0.0, 0.0};
    double tempoQuick[4] = {0.0, 0.0, 0.0, 0.0};
    double tempoHeap[4] = {0.0, 0.0, 0.0, 0.0};
    double tempoRadix[4] = {0.0, 0.0, 0.0, 0.0};

    // preenchendo os vetores e armazeando o tempo que levou para gerar
    // vetor 0 = 10
    // vetor 1 = 1000
    // vetor 2 = 100000
    // vetor 3 = 10000000 
    for(i = 0; i < 4; i++){ // MUDAR PARA 4 DEPOIS
        vetor[i] = malloc(tamanhoVetor[i] * sizeof(int));
        clock_t begin = clock();
        preencherVetor(vetor[i], tamanhoVetor[i]);
        clock_t end = clock();
        tempoVetor[i] += (double)(end - begin) / CLOCKS_PER_SEC; 
        printf("\n\nVetor[%i] foi gerado! \nTamanho: %i \nTempo em segundos: %f", i, tamanhoVetor[i], tempoVetor[i]);
        printarVetor(vetor[i], tamanhoVetor[i]);
    }

    // fazendo copias do vetor original
    printf("\n\n>> Realizando copia do vetor");
    for(i = 0; i < 4; i++){
        vetorBubble[i] = malloc(tamanhoVetor[i] * sizeof(int));
        copiarUmVetor(vetorBubble[i], vetor[i], tamanhoVetor[i]);
    }
    printf("\nCopia de vetor bubble concluida");
    for(i = 0; i < 4; i++){
        vetorInsertion[i] = malloc(tamanhoVetor[i] * sizeof(int));
        copiarUmVetor(vetorInsertion[i], vetor[i], tamanhoVetor[i]);
    }
    printf("\nCopia de vetor insertion concluida");
    for(i = 0; i < 4; i++){
        vetorMerge[i] = malloc(tamanhoVetor[i] * sizeof(int));
        copiarUmVetor(vetorMerge[i], vetor[i], tamanhoVetor[i]);
    }
    printf("\nCopia de vetor merge concluida");
    for(i = 0; i < 4; i++){
        vetorQuick[i] = malloc(tamanhoVetor[i] * sizeof(int));
        copiarUmVetor(vetorQuick[i], vetor[i], tamanhoVetor[i]);
    }
    printf("\nCopia de vetor quick concluida");
    for(i = 0; i < 4; i++){
        vetorHeap[i] = malloc(tamanhoVetor[i] * sizeof(int));
        copiarUmVetor(vetorHeap[i], vetor[i], tamanhoVetor[i]);
    }
    printf("\nCopia de vetor heap concluida");
    for(i = 0; i < 4; i++){
        vetorRadix[i] = malloc(tamanhoVetor[i] * sizeof(int));
        copiarUmVetor(vetorRadix[i], vetor[i], tamanhoVetor[i]);
    }
    printf("\nCopia de vetor radix concluida\n");
    
    printf("\n------------------------------------------------------------------------\n");
    printf("\n>> ORDENACAO");
    printf("\n\tVETOR ORIGINAL:");
    for(i = 0; i < 4; i++){
        printarVetor(vetor[i], tamanhoVetor[i]);
    }
    printf("\n>> Ordenacao bubble");
    for(i = 0; i < 4; i++){
        clock_t begin = clock();
        bubbleSort(vetorBubble[i], tamanhoVetor[i]);
        clock_t end = clock();
        tempoBubble[i] += (double)(end - begin) / CLOCKS_PER_SEC; 
        printarVetor(vetorBubble[i], tamanhoVetor[i]);
        printf("\n\tTempo: %f\n", tempoBubble[i]);
    }
    printf("\n>> Ordenacao bubble");
    for(i = 0; i < 4; i++){
        clock_t begin = clock();
        bubbleSort(vetorBubble[i], tamanhoVetor[i]);
        clock_t end = clock();
        tempoBubble[i] += (double)(end - begin) / CLOCKS_PER_SEC; 
        printarVetor(vetorBubble[i], tamanhoVetor[i]);
        printf("\n\tTempo: %f\n", tempoBubble[i]);
    }
    printf("\n>> Ordenacao insertion");
    for(i = 0; i < 4; i++){
        clock_t begin = clock();
        insertionSort(vetorBubble[i], tamanhoVetor[i]);
        clock_t end = clock();
        tempoInsertion[i] += (double)(end - begin) / CLOCKS_PER_SEC; 
        printarVetor(vetorInsertion[i], tamanhoVetor[i]);
        printf("\n\tTempo: %f\n", tempoInsertion[i]);
    }
    printf("\n>> Ordenacao merge");
    for(i = 0; i < 4; i++){
        clock_t begin = clock();
        mergeSort(vetorMerge[i], tamanhoVetor[i]);
        clock_t end = clock();
        tempoMerge[i] += (double)(end - begin) / CLOCKS_PER_SEC; 
        printarVetor(vetorMerge[i], tamanhoVetor[i]);
        printf("\n\tTempo: %f\n", tempoMerge[i]);
    }
    printf("\n>> Ordenacao quick");
    for(i = 0; i < 4; i++){
        clock_t begin = clock();
        quickSort(vetorQuick[i], tamanhoVetor[i]);
        clock_t end = clock();
        tempoQuick[i] += (double)(end - begin) / CLOCKS_PER_SEC; 
        printarVetor(vetorQuick[i], tamanhoVetor[i]);
        printf("\n\tTempo: %f\n", tempoQuick[i]);
    }
    printf("\n>> Ordenacao heap");
    for(i = 0; i < 4; i++){
        clock_t begin = clock();
        heapsortTeste(vetorHeap[i], tamanhoVetor[i]);
        clock_t end = clock();
        tempoHeap[i] += (double)(end - begin) / CLOCKS_PER_SEC; 
        printarVetor(vetorHeap[i], tamanhoVetor[i]);
        printf("\n\tTempo: %f\n", tempoHeap[i]);
    }
    printf("\n>> Ordenacao radix");
    for(i = 0; i < 4; i++){
        clock_t begin = clock();
        radixSort(vetorRadix[i], tamanhoVetor[i]);
        clock_t end = clock();
        tempoRadix[i] += (double)(end - begin) / CLOCKS_PER_SEC; 
        printarVetor(vetorRadix[i], tamanhoVetor[i]);
        printf("\n\tTempo: %f\n", tempoRadix[i]);
    }

    printf("\n\n------------------------------------------------------------------------");
    printf("\n>> TEMPOS");
    printf("\n------------------------------------------------------------------------");
    printf("\n-Bubble-----------------------------------------------------------------");
    printf("\n------------------------------------------------------------------------");
    for(i = 0; i < 4; i ++){
        printf("\nTempo para %i: %f", tamanhoVetor[i], tempoBubble[i]);
    }
    printf("\n------------------------------------------------------------------------");
    printf("\n-Insertion--------------------------------------------------------------");
    printf("\n------------------------------------------------------------------------");
    for(i = 0; i < 4; i ++){
        printf("\nTempo para %i: %f", tamanhoVetor[i], tempoInsertion[i]);
    }
    printf("\n------------------------------------------------------------------------");
    printf("\n-Merge------------------------------------------------------------------");
    printf("\n------------------------------------------------------------------------");
    for(i = 0; i < 4; i ++){
        printf("\nTempo para %i: %f", tamanhoVetor[i], tempoMerge[i]);
    }
    
    printf("\n------------------------------------------------------------------------");
    printf("\n-Quick------------------------------------------------------------------");
    printf("\n------------------------------------------------------------------------");
    for(i = 0; i < 4; i ++){
        printf("\nTempo para %i: %f", tamanhoVetor[i], tempoQuick[i]);
    }
    printf("\n------------------------------------------------------------------------");
    printf("\n-Heap-------------------------------------------------------------------");
    printf("\n------------------------------------------------------------------------");
    for(i = 0; i < 4; i ++){
        printf("\nTempo para %i: %f", tamanhoVetor[i], tempoHeap[i]);
    }
    printf("\n------------------------------------------------------------------------");
    printf("\n-Radix------------------------------------------------------------------");
    printf("\n------------------------------------------------------------------------");
    for(i = 0; i < 4; i ++){
        printf("\nTempo para %i: %f", tamanhoVetor[i], tempoRadix[i]);
    }
    return(0);
}
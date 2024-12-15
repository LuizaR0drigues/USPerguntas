#include <stdlib.h>
#include <stdio.h>
#include <iostream>

int* noRepeatRandom(int range, int min, int max){

    int interval = max-min+1;

    if ((interval) < range){
        printf ("ERROR: Number of integers in the interval is lesser than the"
         "range of the interval.");
        return NULL;
    }

    int* numbers = (int*) malloc(sizeof(int) * (max-min+1));
    int* noRepeat = (int*) malloc(sizeof(int) * (range));

    if (numbers == NULL || noRepeat == NULL){
        printf ("ERROR: Unable to allocate space for integer vectors");
    };

    for (int i = 0; i < interval; i++) {
        numbers[i] = i + min;
    }

    int randN;

    for (int i = 0; i < range; i++) {

        if (interval == 1){
            noRepeat[i] = numbers[0];
            continue;
        }

        randN = rand() % interval;

        noRepeat[i] = numbers[randN];
        numbers[randN] = numbers[interval-1];
        interval--;
    }


free (numbers);
return noRepeat;
}

int main(){
    int* vetor = noRepeatRandom(20, 1, 20);

    for (int i = 0; i < 20 ; i++){
        std::cout << vetor[i] << std::endl;
    }

    free (vetor);
}
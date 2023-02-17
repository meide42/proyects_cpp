#include <iostream>
using namespace std;

// Array type
const int ARRAY_LENGTH = 10;
typedef int tArray[ARRAY_LENGTH];

// Recursive sum of elements in array
int recursiveSum(tArray array, int index) {
    if (index == ARRAY_LENGTH -1) return array[index];
    else{
        return array[index] + recursiveSum(array, index + 1);
    }
}

// Recursive function to check if an element is part of an array
bool recursiveElem(tArray array, int index, int a){
    if (index == ARRAY_LENGTH) return false;
    else{
        return array[index] == a || recursiveElem(array, index + 1, a);
    }
}

// quicksort algorithm using recursion
typedef struct{
    tArray array;
    int length;
} tUnfilledArray;

void quicksort(tUnfilledArray &array){
    if (array.length > 1) {
        int pivot = array.array[array.length / 2];
        tUnfilledArray lowerSort;
        tUnfilledArray greaterSort;
        lowerSort.length = 0;
        greaterSort.length = 0;
        for (int i = 0; i < array.length; i++) {
            if (array.array[i] < pivot) {
                lowerSort.array[lowerSort.length] = array.array[i];
                lowerSort.length++;
            } else if (array.array[i] > pivot) {
                greaterSort.array[greaterSort.length] = array.array[i];
                greaterSort.length++;
            }
        }
        // Fill the original array
        quicksort(lowerSort);
        quicksort(greaterSort);
        for (int i = 0; i < lowerSort.length; i++) {
            array.array[i] = lowerSort.array[i];
        }
        array.array[lowerSort.length] = pivot;
        for (int i = 0; i < greaterSort.length; i++) {
            array.array[i + lowerSort.length + 1] = greaterSort.array[i];
        }
    }
}

// zip using recursion
typedef int tPair[2];
typedef tPair tZippedList[ARRAY_LENGTH];

void zip(tArray array1, tArray array2, tZippedList output, int index){
    if (index != ARRAY_LENGTH){
        output[index][0] = array1[index];
        output[index][1] = array2[index];
        zip(array1, array2, output, index + 1);
    }
}

// join two lists with a function using recursion
void joinWith(tArray array1, tArray array2, int (*func)(int, int), tArray output, int index){
    if (index != ARRAY_LENGTH){
        output[index] = func(array1[index], array2[index]);
        joinWith(array1, array2, func, output, index + 1);
    }

}

// Factorial
int fact(int n){
    if (n == 1) return 1;
    return n*fact(n-1);
}

// Fibonacci
int fib(int n){
    if (n == 0 || n == 1) return 1;
    else return fib(n-2) + fib(n-1);
}

// max of an array function using recursion
int max(tArray array, int index){
    if (index == ARRAY_LENGTH - 1) return array[index];
    int rec_max = max(array, index + 1);
    return (array[index] > rec_max) ? array[index] : rec_max;
}

int main(){

    return 0;
}

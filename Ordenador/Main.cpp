#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include "Ordenador.h"

using namespace std;

class SortingArray {
public:
    SortingArray(int* A, int n) : A(A), n(n) {}

    int* A;
    int n;
};

class SortingRunner {
public:
    SortingRunner(string name, void (*algorithm)(Ordenador&, int*, int), Ordenador& ordenador) : name(name), algorithm(algorithm), ordenador(ordenador) {}

    string name;
    void (*algorithm)(Ordenador&, int*, int);
    Ordenador& ordenador;
};

using MS = chrono::milliseconds;
using Clock = chrono::steady_clock;
using Timestamp = chrono::steady_clock::time_point;

static const size_t NUM_ARRAYS{ 4 };
static const size_t NUM_ALGOS{ 3 };
static const size_t NUM_REPS{ 3 };

void initialize(SortingArray arrays[NUM_ARRAYS]);
void takeTimes(long long times[NUM_REPS][NUM_ALGOS][NUM_ARRAYS]);
void finalize(SortingArray arrays[NUM_ARRAYS]);

void fillArrays(SortingArray arrays[NUM_ARRAYS]);
void fill(SortingArray& sa);
MS duration(const SortingRunner& sortingRunner, SortingArray& sortingArray);

void selectionSort(Ordenador& ord, int *A, int n);
void insertionSort(Ordenador& ord, int* A, int n);
void mergeSort(Ordenador& ord, int* A, int n);

int main() {

    Ordenador ordenador;

    const SortingRunner algorithms[NUM_ALGOS]{ 
        SortingRunner{ "Selection Sort", selectionSort, ordenador},
        SortingRunner{ "Insertion Sort", insertionSort, ordenador },
        SortingRunner{ "Merge sort", mergeSort, ordenador}
    };

	SortingArray arrays[NUM_ARRAYS]{
		SortingArray{ NULL, 50000},
		SortingArray{ NULL, 100000 },
		SortingArray{ NULL, 150000 },
		SortingArray{ NULL, 200000 }
	};

    long long times[NUM_REPS][NUM_ALGOS][NUM_ARRAYS];

    initialize(arrays);

    for (size_t i = 0; i < NUM_REPS; ++i) {
        cout << "----------------------------------------------------" << endl;
        cout << "Repetition " << to_string(i + 1) << ":" << endl;
        cout << "----------------------------------------------------" << endl;

        for (size_t j = 0; j < NUM_ALGOS; ++j) {
            cout << algorithms[j].name << ": | ";

            fillArrays(arrays);

            for (size_t k = 0; k < NUM_ARRAYS; ++k) {
                long long interval = duration(algorithms[j], arrays[k]).count();

                times[i][j][k] = interval;

                cout << to_string(interval) << " ms | ";
            }
            cout << endl;
        }
    }

    finalize(arrays);
}

void initialize(SortingArray arrays[NUM_ARRAYS]) {
    for (int i = 0; i < NUM_ARRAYS; ++i) {
        arrays[i].A = (int*)calloc(arrays[i].n, sizeof(int));
    }
}

void finalize(SortingArray arrays[NUM_ARRAYS]) {
    for (int i = 0; i < NUM_ARRAYS; ++i) {
        free(arrays[i].A);
    }
}

void fillArrays(SortingArray arrays[NUM_ARRAYS]) {
    for (int i = 0; i < NUM_ARRAYS; ++i) {
        fill(arrays[i]);
    }
}

void fill(SortingArray& sortingArray) {
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(0, sortingArray.n - 1);

    for (int i = 0; i < sortingArray.n; ++i) {
        sortingArray.A[i] = dist(mt);
    }
}

MS duration(const SortingRunner& sortingAlgorithm, SortingArray& sortingArray) {
    Timestamp start = Clock::now();
    invoke(sortingAlgorithm.algorithm, sortingAlgorithm.ordenador, sortingArray.A, sortingArray.n);
    return chrono::duration_cast<MS>(Clock::now() - start);
}

void selectionSort(Ordenador& ord, int* A, int n) {
    ord.seleccion(A, n);
}

void insertionSort(Ordenador& ord, int* A, int n) {
    ord.insercion(A, n);
}

void mergeSort(Ordenador& ord, int* A, int n) {
    ord.mergesort(A, n);
}
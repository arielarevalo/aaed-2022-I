#include <chrono>
#include <fstream>
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
static const size_t NUM_ALGOS{ 1 };
static const size_t NUM_REPS{ 5 };
static const int RAND{200000};

void initialize(SortingArray arrays[NUM_ARRAYS]);
void takeTimes(SortingArray(&arrays)[NUM_ARRAYS], const SortingRunner(&algorithms)[NUM_ALGOS], long long times[NUM_REPS][NUM_ALGOS][NUM_ARRAYS]);
void finalize(SortingArray arrays[NUM_ARRAYS]);

void fillArrays(SortingArray arrays[NUM_ARRAYS]);
void fill(SortingArray& sa);
MS duration(const SortingRunner& sortingRunner, SortingArray& sortingArray);

void selectionSort(Ordenador& ord, int* A, int n);
void insertionSort(Ordenador& ord, int* A, int n);
void mergeSort(Ordenador& ord, int* A, int n);
void heapSort(Ordenador& ord, int* A, int n);
void quickSort(Ordenador& ord, int* A, int n);
void radixSort(Ordenador& ord, int* A, int n);

int main() {

	Ordenador ordenador;

	const SortingRunner algorithms[NUM_ALGOS]{
		SortingRunner{ "Radix Sort", radixSort, ordenador }
	};

	SortingArray arrays[NUM_ARRAYS]{
		SortingArray{ NULL, 50000},
		SortingArray{ NULL, 100000 },
		SortingArray{ NULL, 150000 },
		SortingArray{ NULL, 200000 }
	};

	long long times[NUM_REPS][NUM_ALGOS][NUM_ARRAYS];

	initialize(arrays);

	takeTimes(arrays, algorithms, times);

	finalize(arrays);
}

void initialize(SortingArray arrays[NUM_ARRAYS]) {
	for (int i = 0; i < NUM_ARRAYS; ++i) {
		arrays[i].A = (int*)calloc(arrays[i].n, sizeof(int));
	}
}

void takeTimes(SortingArray(&arrays)[NUM_ARRAYS], const SortingRunner(&algorithms)[NUM_ALGOS], long long times[NUM_REPS][NUM_ALGOS][NUM_ARRAYS]) {
	ofstream latex;
	latex.open("latex.txt");

	for (size_t i = 0; i < NUM_ALGOS; ++i) {
		cout << "-----------------------------------------------------------------" << endl;
		cout << " Algoritmo: " << algorithms[i].name << endl;
		cout << "-----------------------------------------------------------------" << endl;

		latex << algorithms[i].name << endl;

		for (size_t j = 0; j < NUM_ARRAYS; ++j) {
			int size{ arrays[j].n / 1000 };
			cout << "   " << to_string(size) << ": | ";
			latex << " & $" << to_string(size) << "$";

			int average{ 0 };

			for (size_t k = 0; k < NUM_REPS; ++k) {
				fill(arrays[j]);

				long long interval = duration(algorithms[i], arrays[j]).count();

				times[i][j][k] = interval;

				latex << " & $" << to_string(interval) << "$";
				cout << to_string(interval) << " ms | ";

				average += interval;
			}
			average /= NUM_REPS;
			latex << " & $" << to_string(average) << "$";
			latex << "\\tabularnewline" << endl;
			cout << endl;
		}
		latex << "\\midrule" << endl;
	}
	latex.close();
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
	uniform_int_distribution<int> dist(-RAND, RAND);

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

void heapSort(Ordenador& ord, int* A, int n) {
	ord.heapsort(A, n);
}

void quickSort(Ordenador& ord, int* A, int n) {
	ord.quicksort(A, n);
}

void radixSort(Ordenador& ord, int* A, int n) {
	ord.radixsort(A, n);
}
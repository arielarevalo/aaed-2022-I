#ifndef Ordenador_h
#define Ordenador_h

#include <vector>

class Ordenador{
	private:
    // Defina aqui los metodos auxiliares de los algoritmos de ordenamiento solamente.
    // Puede definir cuantos metodos quiera.A
		void swap(int *A, int a, int b);

		void merge(int *A, int p, int q, int r);

		void recursive_mergesort(int* A, int p, int r);
	
	public:
	Ordenador(){};
	~Ordenador(){};
	// Si piensa no implementar algunos de los metodos de ordenamiento, no los borre,
	// simplemente dejelos con el cuerpo vacio para evitar errores de compilacion, ya
	// que se va a ejecutar el mismo main para todas las tareas.
    // Implemente los algoritmos en este archivo  (no en un CPP aparte).
	void seleccion(int *A, int n);
	void insercion(int *A, int n);
	void mergesort(int *A, int n);
	void heapsort(int *A, int n);
	void quicksort(int *A, int n);
	void radixsort(int *A, int n);
};

void Ordenador::swap(int *A, int a, int b) {
	int temp = A[a];

	A[a] = A[b];

	A[b] = temp;
}

void Ordenador::merge(int* A, int p, int q, int r) {
	int n_0 = q - p + 1;
	int n_1 = r - q;

	std::vector<int> L(n_0);
	std::vector<int> R(n_1);

	for (int i = 0; i < n_0; ++i) {
		L[i] = A[p + i];
	}

	for (int j = 0; j < n_1; ++j) {
		R[j] = A[q + j + 1];
	}

	int i;
	int j;
	int k;
	for (i = 0, j = 0, k = p; k < r + 1; ++k) {
		if (i < n_0 && (j >= n_1 || L[i] <= R[j])) {
			A[k] = L[i];
			++i;
		}
		else {
			A[k] = R[j];
			++j;
		}
	}
}

void Ordenador::recursive_mergesort(int* A, int p, int r) {
	if (p < r) {
		int q = (p + r) / 2;
		recursive_mergesort(A, p, q);
		recursive_mergesort(A, q + 1, r);
		merge(A, p, q, r);
	}
}

void Ordenador::seleccion(int *A, int n) {
	for (int i = 0; i < n; ++i) {

		int min = i;  // Index of minimum
		for (int j = i + 1; j < n; ++j) {
			if (A[j] < A[min]) {
				min = j;
			}
		}

		if (min != i) {
			swap(A, i, min);
		}
	}
}

void Ordenador::insercion(int *A, int n) {
	for (int i = 1; i < n; ++i) {

		int next = A[i];  // Next element to sort
		int j;
		for (j = i - 1; j > -1 && A[j] > next; --j) {
			A[j + 1] = A[j];
		}
		A[j + 1] = next;
	}
}

void Ordenador::mergesort(int* A, int n) {
	recursive_mergesort(A, 0, n - 1);
}
#endif

#ifndef Ordenador_h
#define Ordenador_h

#include <vector>
#include <cmath>

class Ordenador {
private:
	// Defina aqui los metodos auxiliares de los algoritmos de ordenamiento
	// solamente. Puede definir cuantos metodos quiera.

	void swap(int* A, int a, int b);

	void recursive_mergesort(int* A, int p, int r);

	void merge(int* A, int p, int q, int r);

	void max_heapify(int* A, int h, int i);

	void build_max_heap(int* A, int n);

	int parent(int i);

	int left(int i);

	int right(int i);

	void recursive_quicksort(int* A, int p, int r);

	int partition(int* A, int p, int r);

	void counting_sort_on_digit_for_base(int* A, int* B, int n, int d, int b);

	int max_value(int* A, int n);

	int min_value(int* A, int n);

public:
	Ordenador() {};
	~Ordenador() {};
	// Si piensa no implementar algunos de los metodos de ordenamiento, no los
	// borre, simplemente dejelos con el cuerpo vacio para evitar errores de
	// compilacion, ya que se va a ejecutar el mismo main para todas las tareas.
	// Implemente los algoritmos en este archivo  (no en un CPP aparte).
	void seleccion(int* A, int n);
	void insercion(int* A, int n);
	void mergesort(int* A, int n);
	void heapsort(int* A, int n);
	void quicksort(int* A, int n);
	void radixsort(int* A, int n);
};

void Ordenador::seleccion(int* A, int n)
{
	for (int i{ 0 }; i < n; ++i)
	{
		int min{ i };
		for (int j{ i + 1 }; j < n; ++j)
		{
			if (A[j] < A[min])
			{
				min = j;
			}
		}

		if (min != i)
		{
			swap(A, i, min);
		}
	}
}

void Ordenador::insercion(int* A, int n)
{
	for (int i{ 1 }; i < n; ++i)
	{
		int next{ A[i] };
		int j;
		for (j = i - 1; j > -1 && A[j] > next; --j)
		{
			A[j + 1] = A[j];
		}
		A[j + 1] = next;
	}
}

void Ordenador::mergesort(int* A, int n)
{
	recursive_mergesort(A, 0, n - 1);
}

void Ordenador::recursive_mergesort(int* A, int p, int r)
{
	if (p < r)
	{
		int q{ (p + r) / 2 };
		recursive_mergesort(A, p, q);
		recursive_mergesort(A, q + 1, r);
		merge(A, p, q, r);
	}
}

void Ordenador::merge(int* A, int p, int q, int r)
{
	int n_0{ q - p + 1 };
	int n_1{ r - q };

	std::vector<int> L(n_0);
	std::vector<int> R(n_1);

	for (int i{ 0 }; i < n_0; ++i)
	{
		L[i] = A[p + i];
	}

	for (int j{ 0 }; j < n_1; ++j)
	{
		R[j] = A[q + j + 1];
	}

	int i;
	int j;
	int k;
	for (i = 0, j = 0, k = p; k < r + 1; ++k)
	{
		if (i < n_0 && (j >= n_1 || L[i] <= R[j]))
		{
			A[k] = L[i];
			++i;
		}
		else
		{
			A[k] = R[j];
			++j;
		}
	}
}

void Ordenador::heapsort(int* A, int n)
{
	int h{ n };
	build_max_heap(A, n);
	for (int i{ n - 1 }; i > 0; --i)
	{
		swap(A, 0, i);
		--h;
		max_heapify(A, h, 0);
	}
}

void Ordenador::build_max_heap(int* A, int n)
{
	for (int i{ parent(n - 1) }; i > -1; --i)
	{
		max_heapify(A, n, i);
	}
}

void Ordenador::max_heapify(int* A, int h, int i)
{ // A[parent(i)] >= A[i] for every node other than root
	int l{ left(i) };
	int r{ right(i) };
	int largest{ i };

	if (l < h && A[l] > A[largest])
	{
		largest = l;
	}
	if (r < h && A[r] > A[largest])
	{
		largest = r;
	}
	if (i != largest)
	{
		swap(A, i, largest);
		max_heapify(A, h, largest);
	}
}

int Ordenador::parent(int i)
{
	return i % 2 ? i >> 1 : (i >> 1) - 1;
}

int Ordenador::left(int i)
{
	return (i << 1) + 1;
}

int Ordenador::right(int i)
{
	return left(i) + 1;
}

void Ordenador::quicksort(int* A, int n)
{
	recursive_quicksort(A, 0, n - 1);
}

void Ordenador::recursive_quicksort(int* A, int p, int r)
{
	if (p < r)
	{
		int q{ partition(A, p, r) };
		recursive_quicksort(A, p, q - 1);
		recursive_quicksort(A, q + 1, r);
	}
}

int Ordenador::partition(int* A, int p, int r)
{
	int x{ A[r] };
	int i{ p - 1 };
	for (int j{ p }; j < r; ++j)
	{
		if (A[j] <= x)
		{
			++i;
			swap(A, i, j);
		}
	}
	swap(A, i + 1, r);
	return i + 1;
}

void Ordenador::radixsort(int* A, int n)
{
	if (n > 0) {
		int k{ max_value(A, n) };
		int b{ 2 << (int)log2(n - 1) }; // en base 2^lgn
		int d{ (int)log(k) / (int)log(b) + 1 };

		int* B{ new int[n] {} };

		for (int i = 1; i <= d; ++i) {
			counting_sort_on_digit_for_base(A, B, n, i, b);
		}
	}
}

void Ordenador::counting_sort_on_digit_for_base(int* A, int* B, int n, int d, int b)
{
	int k{ b - 1 };
	int m{ -k };
	int pow{ (int)log2(b) * d };

	int C_size{ k - m + 1 };

	int* C{ new int[C_size] };

	for (int i{ 0 }; i < C_size; ++i)
	{
		C[i] = 0;
	}
	for (int i{ 0 }; i < n; ++i)
	{
		++C[A[i] % (2 << pow - 1) - m];
	}
	for (int i{ 1 }; i < C_size; ++i)
	{
		C[i] += C[i - 1];
	}
	for (int i{ n - 1 }; i > -1; --i)
	{
		--C[A[i] % (2 << pow - 1) - m];
		B[C[A[i] % (2 << pow - 1) - m]] = A[i];
	}
	for (int i{ 0 }; i < n; ++i) {
		A[i] = B[i];
	}
}

int Ordenador::max_value(int* A, int n) {
	int max{ A[0] };
	for (int i{ 1 }; i < n; ++i)
	{
		if (A[i] > max)
		{
			max = A[i];
		}
	}
	return max;
}

int Ordenador::min_value(int* A, int n) {
	int min{ A[0] };
	for (int i{ 1 }; i < n; ++i)
	{
		if (A[i] < min)
		{
			min = A[i];
		}
	}
	return min;
}

void Ordenador::swap(int* A, int a, int b)
{
	int temp{ A[a] };

	A[a] = A[b];

	A[b] = temp;
}
#endif

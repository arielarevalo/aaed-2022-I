#ifndef HASH_CLASS
#define HASH_CLASS
#include <stddef.h>
#include <list>
#include <vector>
#include <iostream>

using namespace std;

template <typename T>
class hasht {
public:
	// Constructor que especifica el numero de cubetas (entradas) 
	// en la tabla
	hasht(int nEntradas) : numEntradas(nEntradas), tabla(nEntradas) {
	};

	// Destructor (borra la tabla)
	~hasht() {
	};

	// Retorna un puntero a la llave o NULL si no se encuentra
	T* search(const T& item) {
		for (T& t : tabla[hash(item)]) {
			if (t == item) {
				return &t;
			}
		}
		return NULL;
	};

	// Inserta el elemento en la tabla
	void insert(const T& item) {
		tabla[hash(item)].push_back(item);
	};

	size_t sizeOfLargestChain() {
		size_t largest{ 0 };

		for (list<T> l : tabla) {
			if (l.size() > largest) {
				largest = l.size();
			}
		}

		return largest;
	}

private:
	size_t hash(const T& item) {
		return item % numEntradas;
	}

	// N�mero de entradas en la tabla
	int numEntradas;

	// La tabla es un vector de listas de STL
	vector<list<T>> tabla;
};
#endif

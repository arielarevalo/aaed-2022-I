#ifndef LINKED_LIST_llist
#define LINKED_LIST_llist
#include <iostream>

// Nodos de la lista:
template <typename T>
class llnode {
public:
	// Esta clase es para ser usada por otras clases.
	// Por eficiencia los atributos se dejan publicos.
	T key;
	llnode<T>* prev, * next;
	//enum colors color;

	// Constructor por omision.
	llnode() {
	};

	// Inicializacion de los datos miembro.
	llnode(const T& k, llnode<T>* w = NULL, llnode<T>* y = NULL) :key(k), prev(w), next(y) {};

	~llnode() {
	}
};

// Lista enlazada con nodo centinela:
template <typename T>
class llist {
public:
	// Constructor (crea una lista vacia)
	llist() {
		nil = new llnode<T>();
		nil->prev = nil;
		nil->next = nil;
	};

	// Destructor (borra la lista)
	~llist() {
		llnode<T>* x = nil;
		x->prev->next = NULL;

		while (x) {
			llnode<T>* y{ x->next };
			delete x;
			x = y;
		}
	};

	// Busca la llave iterativamente. Si la encuentra, devuelve un
	// apuntador al nodo que la contiene; sino devuelve NULL.
	llnode<T>* listSearch(const T& k) {
		llnode<T>* x{ nil->next };

		while (x != nil && x->key != k) {
			x = x->next;
		}
		return nil == x ? NULL : x;
	};

	// Inserta el nodo x en la lista.
	void listInsert(llnode<T>* x) {
		x->next = nil->next;
		x->next->prev = x;

		nil->next = x;
		x->prev = nil;
	};

	// Saca de la lista la llave contenida en el nodo apuntado por x.
	// Devuelve la direccion del nodo eliminado para que se pueda
	// disponer de el.
	llnode<T>* listDelete(llnode<T>* x) {
		x->prev->next = x->next;
		x->next->prev = x->prev;

		return x;
	};

	// Devuelve el nodo centinela. (Para efectos de revision de la tarea).
	llnode<T>* getNil() const {
		return this->nil;
	};

private:

	llnode<T>* nil;        // nodo centinela

};

#endif    // LINKED_LIST_llist

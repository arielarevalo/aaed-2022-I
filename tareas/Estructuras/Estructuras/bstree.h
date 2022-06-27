#ifndef BINARY_SEARCH_Tree
#define BINARY_SEARCH_Tree
#include <iostream>

using namespace std;

// Nodos del arbol:
template <typename T>
class node {
public:
	// Esta clase es usada por otras clases.
	// Para mayor eficiencia, los atributos se hacen publicos.
	T key;
	node<T>* p, * left, * right;

	// Constructor por omision
	node() {
	};

	// Inicializacion de datos miembro
	node(const T& k, node<T>* w = NULL, node<T>* y = NULL, node<T>* z = NULL) :key(k), p(w), left(y), right(z) {};

	~node() {
	}
};

// Arbol:
template <typename T>
class tree {
public:
	// Constructor. Crea un arbol vacio
	tree() {
	};

	// Destructor (borra el arbol)
	~tree() {
		postOrderTreeDelete(root);
	};

	// Efectua un recorrido en orden del sub�rbol cuya raiz es apuntada
	// por x, imprimiendo en cada visita la llave de cada nodo.
	void inorderTreeWalk(node<T>* x) {
		if (x) {
			inorderTreeWalk(x->left);
			std::cout << x->key << " ";
			inorderTreeWalk(x->right);
		}
	};

	// Busca la llave recursivamente; si la encuentra, devuelve un
	// apuntador al nodo que la contiene, sino devuelve NULL
	node<T>* treeSearch(const T& k) {
		return treeSearchRecurse(root, k);
	};

	// Lo mismo que en el anterior pero usando un procedimiento
	// iterativo
	node<T>* iterativeTreeSearch(const T& k) {
		node<T>* x{ root };

		while (x && k != x->key) {
			if (k < x->key) {
				x = x->left;
			}
			else {
				x = x->right;
			}
		}
		return x;
	};

	// Devuelve el nodo que tiene la llave menor.
	// Si el arbol est� vacio devuelve NULL.
	node<T>* treeMinimum() {
		return subTreeMinimum(root);
	};

	// Devuelve el nodo que tiene la llave mayor.
	// Si el arbol esta vacio devuelve NULL.
	node<T>* treeMaximum() {
		return subTreeMaximum(root);
	};

	// Devuelve el nodo cuya llave es la que le sigue a la
	// del nodo x. Si no existe tal nodo devuelve NULL.
	node<T>* treeSuccessor(const node<T>* x) {
		if (x->right) {
			return subTreeMinimum(x->right);
		}

		node<T>* y{ x->p };

		while (y && x == y->right) {
			x = y;
			y = y->p;
		}
		return y;
	};

	// Inserta el nodo z en la posicion que le corresponde en el arbol.
	void treeInsert(node<T>* z) {
		node<T>* y{ NULL };
		node<T>* x{ root };

		while (x) {
			y = x;
			if (z->key < x->key) {
				x = x->left;
			}
			else {
				x = x->right;
			}
		}

		z->p = y;

		if (!y) {
			root = z;
		}
		else if (z->key < y->key) {
			y->left = z;
		}
		else {
			y->right = z;
		}

	};

	// Saca del arbol la llave contenida en el nodo apuntado por z.
	// Devuelve la direccion del nodo eliminado para que se pueda
	// disponer de ella.
	node<T>* treeDelete(node<T>* z) {
		if (!z->left) {
			transplant(z, z->right);
		}
		else if (!z->right) {
			transplant(z, z->left);
		}
		else {
			node<T>* y{ subTreeMinimum(z->right) };

			if (y->p != z) {
				transplant(y, y->right);
				y->right = z->right;
				y->right->p = y;
			}
			transplant(z, y);
			y->left = z->left;
			y->left->p = y;
		}
		return z;
	};

	// Devuelve la raiz del arbol. (Para efectos de revisi�n de la tarea).
	node<T>* getRoot() const {
		return this->root;
	};

private:
	node<T>* treeSearchRecurse(node<T>* x, const T& k) {
		if (x == NULL || k == x->key) {
			return x;
		}
		if (k < x->key) {
			return treeSearchRecurse(x->left, k);
		}
		else {
			return treeSearchRecurse(x->right, k);
		}
	};

	node<T>* subTreeMinimum(node<T>* x) {
		while (x->left != NULL) {
			x = x->left;
		}
		return x;
	};

	node<T>* subTreeMaximum(node<T>* x) {
		while (x->right != NULL) {
			x = x->right;
		}
		return x;
	};

	void transplant(node<T>* u, node<T>* v) {
		if (!u->p) {
			root = v;
		}
		else if (u == u->p->left) {
			u->p->left = v;
		}
		else {
			u->p->right = v;
		}
		if (v) {
			v->p = u->p;
		}
	}

	void postOrderTreeDelete(node<T>* x) {
		if (x) {
			postOrderTreeDelete(x->left);
			postOrderTreeDelete(x->right);
			delete x;
		}
	};

	node<T>* root;    // root of the Tree

};
#endif    // BINARY_SEARCH_Tree

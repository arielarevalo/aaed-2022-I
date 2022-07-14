#ifndef RED_BLACK_rbtree
#define RED_BLACK_rbtree
#include <iostream>

using namespace std;

enum colors { RED, BLACK };

// Nodos del arbol:
template <typename T>
class rbnode {
public:
	// Esta clase es para ser usada por otras clases.
	// Por eficiencia se hacen los atributos publicos.
	T key;
	rbnode<T>* p, * left, * right;
	enum colors color;

	// Constructor por omision.
	rbnode() {
	};

	//Inicializacion de datos miembro.
	rbnode(const T& k, rbnode<T>* w = NULL, rbnode<T>* y = NULL, rbnode<T>* z = NULL, enum colors c = RED) : key(k), p(w), left(y), right(z), color(c) {};

	~rbnode() {

	}
};

// Arbol:
template <typename T>
class rbtree {
public:

	// Constructor (crea un arbol vacio)
	rbtree() : nil(new rbnode<T>{T{}, NULL, NULL, NULL, BLACK}) {
		nil->p = nil;
		nil->left = nil;
		nil->right = nil;
		root = nil;
	};

	// Destructor (borra el arbol)
	~rbtree() {
		postOrderTreeDelete(root);
		delete nil;
	};

	// Efectua un recorrido en orden del sub�rbol cuya raiz es apuntada
	// por x, imprimiendo en cada visita la llave de cada nodo.
	void inorderTreeWalk(rbnode<T>* x) {
		if (x != nil) {
			inorderTreeWalk(x->left);
			std::cout << x->key << " ";
			inorderTreeWalk(x->right);
		}
	};

	// Busca la llave recursivamente, si la encuentra devuelve un 
	// puntero al nodo que la contiene, sino devuelve NULL.
	rbnode<T>* treeSearch(const T& k) {
		return treeSearchRecurse(root, k);
	};

	// Igual que en el anterior pero usa un procedimiento iterativo.
	rbnode<T>* iterativeTreeSearch(const T& k) {
		rbnode<T>* x{ root };

		while (x != nil && k != x->key) {
			if (k < x->key) {
				x = x->left;
			}
			else {
				x = x->right;
			}
		}
		return x == nil ? NULL : x;
	};

	// Devuelve el nodo con la llave menor.
	// Si el arbol esta vacio devuelve NULL.	
	rbnode<T>* treeMinimum() {
		return subTreeMinimum(root);
	};

	// Devuelve el nodo con la llave mayor.
	// Si el arbol esta vacio devuelve NULL.
	rbnode<T>* treeMaximum() {
		return subTreeMaximum(root);
	};

	// Devuelve el nodo cuya llave es la siguiente mas grande que 
	// la del nodo x. Si no existe tal nodo devuelve NULL.
	rbnode<T>* treeSuccessor(const rbnode<T>* x) {
		if (x->right != nil) {
			return subTreeMinimum(x->right);
		}

		rbnode<T>* y{ x->p };

		while (y != nil && x == y->right) {
			x = y;
			y = y->p;
		}
		return y == nil ? NULL : y;
	};

	// Inserta el nodo z en la posicion que le corresponde en el arbol.
	void treeInsert(rbnode<T>* z) { //aux es y, actual es x.
		rbnode<T>* y{ nil };
		rbnode<T>* x{ root };

		while (x != nil) {
			y = x;

			if (z->key < x->key) {
				x = x->left;
			}
			else {
				x = x->right;
			}
		}
		z->p = y;

		if (y == nil) {
			root = z;
		}
		else if (z->key < y->key) {
			y->left = z;
		}
		else {
			y->right = z;
		}
		z->left = nil;
		z->right = nil;
		z->color = RED;

		RBinsertFixup(z);
	};

	// Devuelve la raiz del arbol. (Para efectos de revision de la tarea).
	rbnode<T>* getRoot() const {
		return this->root;
	};

	// Devuelve T.nil. (Para efectos de revision de la tarea).
	rbnode<T>* getNil() const {
		return this->nil;
	};


private:
	rbnode<T>* treeSearchRecurse(rbnode<T>* x, const T& k) {
		if (x == nil || k == x->key) {
			return x == nil ? NULL : x;
		}
		if (k < x->key) {
			return treeSearchRecurse(x->left, k);
		}
		else {
			return treeSearchRecurse(x->right, k);
		}
	};

	rbnode<T>* subTreeMinimum(rbnode<T>* x) {
		while (x->left != nil) {
			x = x->left;
		}
		return x == nil ? NULL : x;
	};

	rbnode<T>* subTreeMaximum(rbnode<T>* x) {
		while (x->right != nil) {
			x = x->right;
		}
		return x == nil ? NULL : x;
	};

	void leftRotate(rbnode<T>* x) {
		rbnode<T>* y{ x->right };
		x->right = y->left;

		if (y->left != nil) {
			y->left->p = x;
		}
		y->p = x->p;

		if (x->p == nil) {
			root = y;
		}
		else if (x == x->p->left) {
			x->p->left = y;
		}
		else {
			x->p->right = y;
		}

		y->left = x;
		x->p = y;
	}

	void rightRotate(rbnode<T>* x) {
		rbnode<T>* y{ x->left };
		x->left = y->right;

		if (y->right != nil) {
			y->right->p = x;
		}
		y->p = x->p;

		if (x->p == nil) {
			root = y;
		}
		else if (x == x->p->right) {
			x->p->right = y;
		}
		else {
			x->p->left = y;
		}

		y->right = x;
		x->p = y;
	}

	void RBinsertFixup(rbnode<T>* z) {
		while (z->p->color == RED) {
			if (z->p == z->p->p->left) {
				rbnode<T>* y{ z->p->p->right };

				if (y->color == RED) {
					z->p->color = BLACK;
					y->color = BLACK;
					z->p->p->color = RED;
					z = z->p->p;
				}
				else {
					if (z == z->p->right) {
						z = z->p;
						leftRotate(z);
					}
					z->p->color = BLACK;
					z->p->p->color = RED;
					rightRotate(z->p->p);
				}
			}
			else {
				rbnode<T>* y{ z->p->p->left };

				if (y->color == RED) {
					z->p->color = BLACK;
					y->color = BLACK;
					z->p->p->color = RED;
					z = z->p->p;
				}
				else {
					if (z == z->p->left) {
						z = z->p;
						rightRotate(z);
					}
					z->p->color = BLACK;
					z->p->p->color = RED;
					leftRotate(z->p->p);
				}
			}
		}
		root->color = BLACK;
	}

	void RBtransplant(rbnode<T>* u, rbnode<T>* v) {
		if (u->p == nil) {
			root = v;
		}
		else if (u == u->p->left) {
			u->p->left = v;
		}
		else {
			u->p->right = v;
			v->p = u->p;
		}
	}

	void postOrderTreeDelete(rbnode<T>* x) {
		if (x != nil) {
			postOrderTreeDelete(x->left);
			postOrderTreeDelete(x->right);
			delete x;
		}
	};

	rbnode<T>* root;	// raiz del arbol
	rbnode<T>* nil;	    // nodo nil (hoja) del arbol
};

#endif	// RED_BLACK_rbtree

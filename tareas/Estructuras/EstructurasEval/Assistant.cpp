#include <vector>
#include <iostream>
#include <chrono>
#include <stack>
#include <algorithm>
#include <random>
#include "llist.h"
#include "bstree.h"
/*#include "rbtree.h"
#include "hasht.h"*/

using namespace std;
static random_device rd;
static mt19937 generator{ rd() };

int generateRandomNumber(int min, int max)
{
	static uniform_int_distribution <int> dist(min, max - 1);
	return dist(generator);
}

void list_test(vector <string>& puntos)
{

	llnode<int>* paraBorrar = new llnode<int>();

	try
	{
		cout << "Creando lista..." << endl;
		llist<int>* l3 = new llist<int>;
		cout << "Creacion exitosa!" << endl;
		puntos.push_back("Constructor (1)");
	}
	catch (const std::exception& e)
	{
		puntos.push_back("Constructor (0)");
		std::cerr << e.what() << '\n';
	}

	cout << "\nTest #1: Lista generada aleatoria" << endl;

	int elements_q = 1000000, searched_elements = 0;

	cout << "Insertando elementos en la lista..." << endl;

	llist<int>* l1 = new llist<int>;
	try
	{
		for (int i = 0; i < elements_q; i++)
		{
			int random = generateRandomNumber(0, 2 * elements_q);
			llnode<int>* node = new llnode<int>(random);
			l1->listInsert(node);
		}
		puntos.push_back("Insercion (4)");
	}
	catch (const std::exception& e)
	{
		puntos.push_back("Insercion (0)");
		std::cerr << e.what() << '\n';
	}

	cout << "Elementos insertados!" << endl
		<< "Buscando elementos aleatorios..." << endl;

	try
	{
		auto time_start1 = chrono::steady_clock::now();
		while (true)
		{
			int random = generateRandomNumber(0, 2 * elements_q);
			llnode<int>* search_for = l1->listSearch(random);
			searched_elements++;
			if (search_for != NULL) {
				paraBorrar = search_for;
			}
			if (chrono::steady_clock::now() - time_start1 > chrono::seconds(10))
			{
				break;
			}
		}
		puntos.push_back("Busqueda (3)");
		puntos.push_back("Prueba 1 (1)");
	}
	catch (const std::exception& e)
	{
		puntos.push_back("Busqueda (0)");
		puntos.push_back("Prueba 1 (0)");
		std::cerr << e.what() << '\n';
	}

	cout << "Se lograron realizar " << searched_elements << " busquedas!" << endl;

	cout << "\nTest #2: Lista secuencial" << endl;

	llist<int> l2;
	searched_elements = 0;

	cout << "Insertando elementos en la lista..." << endl;

	for (int i = 0; i < elements_q; i++)
	{
		llnode<int>* node = new llnode<int>(i);
		l2.listInsert(node);
	}

	cout << "Elementos insertados!" << endl
		<< "Buscando elementos..." << endl;

	try
	{
		auto time_start2 = chrono::steady_clock::now();
		while (true)
		{
			int random = generateRandomNumber(0, 2 * elements_q);
			llnode<int>* search_for = l2.listSearch(random);
			searched_elements++;
			if (chrono::steady_clock::now() - time_start2 > chrono::seconds(10))
			{
				break;
			}
		}
		puntos.push_back("Prueba 2 (1)");
	}
	catch (const std::exception& e)
	{
		puntos.push_back("Prueba 2 (0)");
		std::cerr << e.what() << '\n';
	}

	cout << "Se lograron realizar " << searched_elements << " busquedas" << endl;

	try
	{
		cout << "Borrando el elemento: " << paraBorrar->key << endl;
		llnode<int>* borrado = l1->listDelete(paraBorrar);
		cout << "Borrado exitoso! " << endl;
		puntos.push_back("Borrado (4)");
	}
	catch (const std::exception& e)
	{
		puntos.push_back("Borrado (0)");
		std::cerr << e.what() << '\n';
	}

	try
	{
		cout << "Operacion de delete sobre lista: l1" << endl;
		delete l1;
		cout << "Delete exitoso!" << endl;
		puntos.push_back("Destructor (3)");
	}
	catch (const std::exception& e)
	{
		puntos.push_back("Destructor (0)");
		std::cerr << e.what() << '\n';
	}

	cout << endl;

	iter_swap(puntos.begin() + 1, puntos.begin() + 6);
	iter_swap(puntos.begin() + 2, puntos.begin() + 6);
	iter_swap(puntos.begin() + 3, puntos.begin() + 6);
	iter_swap(puntos.begin() + 4, puntos.begin() + 5);
	iter_swap(puntos.begin() + 5, puntos.begin() + 6);

	if (puntos.size() == 7)
	{
		puntos.push_back("Informe (3)");
	}
	else
	{
		puntos.push_back("Informe (0)");
	}

	cout << endl
		<< endl;
}

void btree_test(vector <string>& puntos)
{
	try
	{
		cout << "Creando arbol..." << endl;
		tree<int>* tp = new tree <int>;
		cout << "Creacion exitosa!" << endl;
		puntos.push_back("Constructor (1)");
	}
	catch (const std::exception& e)
	{
		puntos.push_back("Constructor (0)");
		std::cerr << e.what() << '\n';
	}

	cout << "\nTest #1: Arbol generado aleatoriamente" << endl;

	tree<int>* t1 = new tree<int>;
	int elements_q = 100, searched_elements = 0, t = 0;

	cout << "Insertando elementos en el arbol..." << endl;

	try
	{
		for (int i = 0; i < elements_q; i++)
		{
			int random = generateRandomNumber(0, 2 * elements_q);
			node<int>* n = new node<int>(random);
			t1->treeInsert(n);
		}
		puntos.push_back("Insercion (4)");
	}
	catch (const std::exception& e)
	{
		puntos.push_back("Insercion (0)");
		std::cerr << e.what() << '\n';
	}

	cout << "Elementos insertados!" << endl
		<< "Buscando elementos aleatorios..." << endl;

	try
	{
		auto time_start1 = chrono::steady_clock::now();
		while (true)
		{
			int random = generateRandomNumber(0, 2 * elements_q);
			node<int>* search_for = t1->iterativeTreeSearch(random);
			searched_elements++;
			if (search_for != NULL)
			{
				t = search_for->key;
			}
			if (chrono::steady_clock::now() - time_start1 > chrono::seconds(10))
			{
				break;
			}
		}
		puntos.push_back("Busqueda iterativa (5)");
		puntos.push_back("Prueba 1 (1)");
	}
	catch (const std::exception& e)
	{
		puntos.push_back("Busqueda iterativa (0)");
		puntos.push_back("Prueba 1 (0)");
		std::cerr << e.what() << '\n';
	}

	cout << "Se lograron realizar " << searched_elements << " busquedas" << endl;

	try
	{
		cout << "Elementos del arbol de mayor a menor: " << endl;
		t1->inorderTreeWalk(t1->getRoot());
		puntos.push_back("Recorrido (3)");
	}
	catch (const std::exception& e)
	{
		puntos.push_back("Recorrido (0)");
		std::cerr << e.what() << '\n';
	}

	cout << endl;

	try
	{
		node<int>* e = t1->iterativeTreeSearch(t);
		node<int>* s = t1->treeDelete(e);

		cout << ((e == NULL) ? "No encontrado" : "Encontrado") << endl;
		cout << ((s == NULL) ? "No borrado" : "Borrado") << endl;

		/*node<int> *es = t1->iterativeTreeSearch(t);
		node<int> *ss = t1->treeDelete(es);

		cout << ((es == NULL) ? "No encontrado" : "Encontrado") << endl;
		cout << ((ss == NULL) ? "No borrado" : "Borrado") << endl;*/

		puntos.push_back("Borrado (5)");
	}
	catch (const std::exception& e)
	{
		puntos.push_back("Borrado (5)");
		std::cerr << e.what() << '\n';
	}

	cout << "\nTest #2: Arbol secuencial" << endl;

	tree <int>* t2 = new tree <int>;
	node <int>* b;
	int a = 0;
	searched_elements = 0;

	cout << "Insertando elementos en el arbol..." << endl;

	for (int i = 0; i < elements_q; i++)
	{
		node<int>* n = new node<int>(i);
		t2->treeInsert(n);
	}

	cout << "Elementos insertados!" << endl
		<< "Buscando elementos..." << endl;

	try
	{
		auto time_start2 = chrono::steady_clock::now();
		while (true)
		{
			int random = generateRandomNumber(0, 2 * elements_q);
			node<int>* search_for2 = t2->iterativeTreeSearch(random);
			searched_elements++;
			if (search_for2 != NULL)
			{
				a = search_for2->key;
				b = search_for2;
			}
			if (chrono::steady_clock::now() - time_start2 > chrono::seconds(10))
			{
				break;
			}
		}
		puntos.push_back("Prueba 2 (1)");
	}
	catch (const std::exception& e)
	{
		puntos.push_back("Prueba 2 (0)");
		std::cerr << e.what() << '\n';
	}

	cout << "Se lograron realizar " << searched_elements << " busquedas" << endl;

	cout << "Elementos del arbol de mayor a menor: " << endl;
	t2->inorderTreeWalk(t2->getRoot());

	cout << endl;

	try
	{
		node<int>* e2 = t2->iterativeTreeSearch(a);
		node<int>* s2 = t2->treeDelete(e2);

		cout << ((e2 == NULL) ? "No encontrado" : "Encontrado") << endl;
		cout << ((s2 == NULL) ? "No borrado" : "Borrado") << endl;

		/*node<int> *es2 = t2->iterativeTreeSearch(a);
		node<int> *ss2 = t2->treeDelete(es2);

		cout << ((es2 == NULL) ? "No encontrado" : "Encontrado") << endl;
		cout << ((ss2 == NULL) ? "No borrado" : "Borrado") << endl;*/
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	try
	{
		node <int>* min = t1->treeMinimum();
		cout << "Minimo de t1 es:" << min->key << endl;
		puntos.push_back("Busqueda minimo (1)");
	}
	catch (const std::exception& e)
	{
		puntos.push_back("Busqueda minimo (0)");
		std::cerr << e.what() << '\n';
	}

	try
	{
		node <int>* max = t1->treeMaximum();
		cout << "Maximo de t1 es:" << max->key << endl;
		puntos.push_back("Busqueda maximo (1)");
	}
	catch (const std::exception& e)
	{
		puntos.push_back("Busqueda maximo (0)");
		std::cerr << e.what() << '\n';
	}

	try
	{
		node <int>* su1 = t1->treeSuccessor(b);
		cout << "El sucesor de " << b->key << " es: " << su1->key << endl;
		puntos.push_back("Sucesor (2)");
	}
	catch (const std::exception& e)
	{
		puntos.push_back("Sucesor (0)");
		std::cerr << e.what() << '\n';
	}

	try
	{
		cout << "Operacion de delete sobre arbol: t1" << endl;
		delete t1;
		cout << "Delete exitoso!" << endl;
		puntos.push_back("Destructor (3)");
	}
	catch (const std::exception& e)
	{
		puntos.push_back("Destructor (0)");
		std::cerr << e.what() << '\n';
	}

	cout << endl;

	//iter_swap(puntos.begin() + , puntos.begin() + );
	iter_swap(puntos.begin() + 1, puntos.begin() + 10);
	iter_swap(puntos.begin() + 2, puntos.begin() + 10);
	iter_swap(puntos.begin() + 3, puntos.begin() + 5);
	iter_swap(puntos.begin() + 4, puntos.begin() + 10);
	iter_swap(puntos.begin() + 5, puntos.begin() + 8);
	iter_swap(puntos.begin() + 6, puntos.begin() + 7);
	iter_swap(puntos.begin() + 7, puntos.begin() + 9);
	iter_swap(puntos.begin() + 8, puntos.begin() + 10);
	iter_swap(puntos.begin() + 9, puntos.begin() + 10);

	if (puntos.size() == 11)
	{
		puntos.push_back("Informe (1)");
		puntos.push_back("Informe (2)");
	}
	else
	{
		puntos.push_back("Informe (0)");
		puntos.push_back("Informe (0)");
	}

	cout << endl
		<< endl;
}

//Program main

int main()
{
	vector <string> puntosA, puntosB, puntosC, puntosD;

	list_test(puntosA);
	btree_test(puntosB);

	for (size_t i = 0; i < puntosA.size(); i++)
	{
		cout << puntosA[i] << endl;
	}

	cout << endl << endl;

	for (size_t i = 0; i < puntosB.size(); i++)
	{
		cout << puntosB[i] << endl;
	}

	cout << endl << endl;

	return 0;
}
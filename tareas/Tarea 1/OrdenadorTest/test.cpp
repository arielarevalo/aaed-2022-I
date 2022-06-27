#include "pch.h"
#include "OrdenadorTest.h"

TEST_F(OrdenadorTest, Seleccion) {
	ordenador.seleccion(A, SIZE);
	for (int i{ 1 }; i < SIZE; ++i) {
		ASSERT_FALSE(A[i] < A[i - 1]);
	}
}

TEST_F(OrdenadorTest, Insercion) {
	ordenador.insercion(A, SIZE);
	for (int i{ 1 }; i < SIZE; ++i) {
		ASSERT_FALSE(A[i] < A[i - 1]);
	}
}

TEST_F(OrdenadorTest, Mergesort) {
	ordenador.mergesort(A, SIZE);
	for (int i{ 1 }; i < SIZE; ++i) {
		ASSERT_FALSE(A[i] < A[i - 1]);
	}
}

TEST_F(OrdenadorTest, Heapsort) {
	ordenador.heapsort(A, SIZE);
	for (int i{ 1 }; i < SIZE; ++i) {
		ASSERT_FALSE(A[i] < A[i - 1]);
	}
}

TEST_F(OrdenadorTest, Quicksort) {
	ordenador.quicksort(A, SIZE);
	for (int i{ 1 }; i < SIZE; ++i) {
		ASSERT_FALSE(A[i] < A[i - 1]);
	}
}

TEST_F(OrdenadorTest, Radixsort) {
	ordenador.radixsort(A, SIZE);
	for (int i{ 1 }; i < SIZE; ++i) {
		ASSERT_FALSE(A[i] < A[i - 1]);
	}
}

//TEST_F(OrdenadorTest, Countingsort) {
//	int B[13]{};
//	for each (int* E in ARRAYS) {
//		ordenador.counting_sort(E, B, SIZE, 6, -6);
//		for (int i = 0; i < SIZE; ++i) {
//			ASSERT_EQ(B[i], S[i]);
//		}
//	}
//}
#pragma once

#include "pch.h"
#include "../Ordenador/Ordenador.h"

class OrdenadorTest : public ::testing::Test {
protected:
	const int SIZE{ 50000 };
	const int RAND{ 200000 };
	int* A{ new int[SIZE] };

	Ordenador ordenador;

	OrdenadorTest() {
		srand((unsigned int) time(0));
		for (int i = 0; i < SIZE; i++) {
			A[i] = (rand() % RAND);
			if (rand() % 2 == 0) {
				A[i] *= -1;
			}
		}
	}
};
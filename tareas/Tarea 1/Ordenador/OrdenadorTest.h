#pragma once

#include <gtest/gtest.h>
#include "../Ordenador/Ordenador.h"

/**
 * Contiene estados y variables necesarios para llevar a cabo la pruebas sobre la clase M_Laberinto.
*/
class OrdenadorTest : public ::testing::Test {

    int A[13]{ 1, 3, 5, -3, 4, -6, 2, 0, -4, -2, -1, 6, -5 };
    int B[13]{ 3, -4, 1, 2, -2, -1, -5, -6, 4, 6, -3, 5, 0 };
    int C[13]{ 0, 6, 5, -2, -5, 1, 3, -3, 2, -1, 4, -6, -4 };
    int D[13]{ -2, 2, -4, -1, -6, 4, -5, -3, 5, 6, 1, 3, 0 };

    int S[13]{ -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6 };

    int* ARRAYS[4]{ A, B, C, D };

    Ordenador ordenador;
};
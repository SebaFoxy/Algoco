#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <chrono>

using namespace std;
using namespace chrono;


// Función para sumar dos matrices
void add(vector< vector<int> > &matrixA, 
         vector< vector<int> > &matrixB, 
         vector< vector<int> > &matrixC, unsigned int mSize) {
    // Recorre cada elemento de las matrices y suma sus valores
    for (int i = 0; i < mSize; i++) {
        for (int j = 0; j < mSize; j++) {
            matrixC[i][j] = matrixA[i][j] + matrixB[i][j];
        }
    }
}

// Función para restar dos matrices
void sub(vector< vector<int> > &matrixA, 
         vector< vector<int> > &matrixB, 
         vector< vector<int> > &matrixC, unsigned int mSize) {
    
    for (int i = 0; i < mSize; i++) {
        for (int j = 0; j < mSize; j++) {
            matrixC[i][j] = matrixA[i][j] - matrixB[i][j];
        }
    }   
}

// Función recursiva del algoritmo de multiplicación de matrices de Strassen
void strassenR(vector< vector<int> > &matrixA,
            vector< vector<int> > &matrixB,
            vector< vector<int> > &matrixC,
            unsigned int mSize) {

    // Caso base: si la matriz es de tamaño 1x1, simplemente multiplica los dos elementos
    if (mSize == 1) {
        matrixC[0][0] = matrixA[0][0] * matrixB[0][0];
        return;
    }
    else {
        // Divide la matriz en submatrices de tamaño más pequeño
        int newMSize = mSize / 2;
        vector<int> innerVector(newMSize, 0);

        // Inicializa las submatrices de A, B, C y las matrices temporales necesarias para Strassen
        vector< vector<int> > matrixA11(newMSize, innerVector),
                            matrixA12(newMSize, innerVector),
                            matrixA21(newMSize, innerVector),
                            matrixA22(newMSize, innerVector),
                            matrixB11(newMSize, innerVector),
                            matrixB12(newMSize, innerVector),
                            matrixB21(newMSize, innerVector),
                            matrixB22(newMSize, innerVector),
                            matrixC11(newMSize, innerVector),
                            matrixC12(newMSize, innerVector),
                            matrixC21(newMSize, innerVector),
                            matrixC22(newMSize, innerVector),
                            s1(newMSize, innerVector),
                            s2(newMSize, innerVector),
                            s3(newMSize, innerVector),
                            s4(newMSize, innerVector),
                            s5(newMSize, innerVector),
                            s6(newMSize, innerVector),
                            s7(newMSize, innerVector),
                            s8(newMSize, innerVector),
                            s9(newMSize, innerVector),
                            s10(newMSize, innerVector),
                            p1(newMSize, innerVector),
                            p2(newMSize, innerVector),
                            p3(newMSize, innerVector),
                            p4(newMSize, innerVector),
                            p5(newMSize, innerVector),
                            p6(newMSize, innerVector),
                            p7(newMSize, innerVector),
                            tempMatrixA(newMSize, innerVector),
                            tempMatrixB(newMSize, innerVector);

        // Divide las matrices A y B en 4 submatrices cada una
        for (int i = 0; i < newMSize; i++) {
            for (int j = 0; j < newMSize; j++) {
                matrixA11[i][j] = matrixA[i][j];
                matrixA12[i][j] = matrixA[i][j + newMSize];
                matrixA21[i][j] = matrixA[i + newMSize][j];
                matrixA22[i][j] = matrixA[i + newMSize][j + newMSize];

                matrixB11[i][j] = matrixB[i][j];
                matrixB12[i][j] = matrixB[i][j + newMSize];
                matrixB21[i][j] = matrixB[i + newMSize][j];
                matrixB22[i][j] = matrixB[i + newMSize][j + newMSize];
            }
        }

        // Calcula las matrices intermedias S y P de acuerdo con el algoritmo de Strassen
        sub(matrixB12, matrixB22, s1, newMSize); // s1 = b12 - b22
        add(matrixA11, matrixA12, s2, newMSize); // s2 = a11 + a12
        add(matrixA21, matrixA22, s3, newMSize); // s3 = a21 + a22
        sub(matrixB21, matrixB11, s4, newMSize); // s4 = b21 - b11
        add(matrixA11, matrixA22, s5, newMSize); // s5 = a11 + a22
        add(matrixB11, matrixB22, s6, newMSize); // s6 = b11 + b22
        sub(matrixA12, matrixA22, s7, newMSize); // s7 = a12 - a22
        add(matrixB21, matrixB22, s8, newMSize); // s8 = b21 + b22
        sub(matrixA11, matrixA21, s9, newMSize); // s9 = a11 - a21
        add(matrixB11, matrixB12, s10, newMSize);// s10 = b11 + b12

        // Calcula los productos P utilizando las submatrices y las matrices intermedias S
        strassenR(matrixA11, s1, p1, newMSize); // p1 = a11 * s1
        strassenR(s2, matrixB22, p2, newMSize); // p2 = s2 * b22
        strassenR(s3, matrixB11, p3, newMSize); // p3 = s3 * b11
        strassenR(matrixA22, s4, p4, newMSize); // p4 = a22 * s4
        strassenR(s5, s6, p5, newMSize); // p5 = s5 * s6
        strassenR(s7, s8, p6, newMSize); // p6 = s7 * s8
        strassenR(s9, s10, p7, newMSize);// p7 = s9 * s10

        // Calcula las submatrices C usando los productos P
        add(p5, p4, tempMatrixA, newMSize);
        add(tempMatrixA, p6, tempMatrixB, newMSize);
        sub(tempMatrixB, p2, matrixC11, newMSize); // c11 = p5 + p4 + p6 - p2
        add(p1, p2, matrixC12, newMSize);          // c12 = p1 + p2
        add(p3, p4, matrixC21, newMSize);          // c21 = p3 + p4
        add(p5, p1, tempMatrixA, newMSize);
        sub(tempMatrixA, p3, tempMatrixB, newMSize);
        sub(tempMatrixB, p7, matrixC22, newMSize); // c22 = p5 + p1 - p3 - p7

        // Combina las submatrices C en una sola matriz C
        for (int i = 0; i < newMSize ; i++) {
            for (int j = 0 ; j < newMSize ; j++) {
                matrixC[i][j] = matrixC11[i][j];
                matrixC[i][j + newMSize] = matrixC12[i][j];
                matrixC[i + newMSize][j] = matrixC21[i][j];
                matrixC[i + newMSize][j + newMSize] = matrixC22[i][j];
            }
        }
    }
}

// Llama a la función recursiva de Strassen
void strassen(vector< vector<int> > &matrixA, 
              vector< vector<int> > &matrixB, 
              vector< vector<int> > &matrixC,
              unsigned int mSize) {
    
    strassenR(matrixA, matrixB, matrixC, mSize); 
}

int main() {
    int n = 1000; // Tamaño de las matrices
    vector<vector<int>> A(n, vector<int>(n, 0));
    vector<vector<int>> B(n, vector<int>(n, 0));
    vector< vector<int> > matrixC(n, vector<int> (n, 0));

    srand(time(0)); // Inicializa el generador de números aleatorios

    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {         //LLenado de matrices con
            A[i][j] = rand() % 100;           //numeros randoms
            B[i][j] = rand() % 100;  
        }
    }
    
    
    auto s1 = high_resolution_clock::now();
    strassen(A,B,matrixC,n);                  //Calcular tiempo que demora la operacion
    auto e1 = high_resolution_clock::now();
    duration<double,milli> d1 = e1 - s1;
    cout << "Tiempo de ejecución: " << d1.count() << " milli" << endl;
    
}


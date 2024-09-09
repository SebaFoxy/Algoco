#include <iostream>
#include <vector>
#include <random>
#include <chrono>

using namespace std;
using namespace chrono;

vector<vector<int>> traspo(vector<vector<int>> A){
    int tam = A.size();
    vector<vector<int>> nueva(tam, vector<int>(tam, 0));
    //Se traspone la matriz A cambiando las filas por columnas
    //y las columnas por filas y se retorna la nueva matriz traspuesta
    for (int i = 0; i < tam; ++i) {
        for (int j = 0; j < tam; ++j) {
            nueva[j][i] = A[i][j];
        }
    }
    return nueva;

}

vector<vector<int>> multi(vector<vector<int>> A,vector<vector<int>> B){
    int n = A.size();
    int suma = 0;
    vector<vector<int>> C(n, vector<int>(n, 0));

    //Se recorre las filas de la matriz A y B
    //y se guarda el resultado de la multiplicacion en C
    // Y se retorna la matriz C
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            suma = 0;
            for(int k=0;k<n;k++){
                suma += A[i][k]*B[i][k];
            
            }
            C[i][j] = suma;
            
        }
        
    }
    return (C);
}


int main() {
    int n = 20;   //Tamaño de matriz cuadrada
    double total1 = 0; 
    int pruebas = 30;   //Cantidad de pruebas
    
    for(int c=0;c<pruebas;c++){
 
        vector<vector<int>> A(n, vector<int>(n, 0));
        vector<vector<int>> B(n, vector<int>(n, 0));    //Se definen los vectores a usar
        vector<vector<int>> C(n, vector<int>(n, 0));
        srand(time(0));

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                A[i][j] = rand() % 100;     //LLenado de matrices con
                B[i][j] = rand() % 100;     //numeros randoms
            }
        }
        auto s1 = high_resolution_clock::now();
        C = multi(A,B);                          //Calcular tiempo que demora la operacion
        auto e1 = high_resolution_clock::now();
        duration<double,milli> d1 = e1 - s1;
        total1 += d1.count();               //Lo suma al total
    }
    cout<<total1/pruebas<<endl;             //Promedio tiempo
}
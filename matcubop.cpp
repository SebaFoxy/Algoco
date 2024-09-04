#include <iostream>
#include <vector>
#include <random>
#include <chrono>

using namespace std;
using namespace chrono;

vector<vector<int>> traspo(vector<vector<int>> A){
    int tam = A.size();
    vector<vector<int>> nueva(tam, vector<int>(tam, 0));
    for (int i = 0; i < tam; ++i) {
        for (int j = 0; j < tam; ++j) {
            nueva[j][i] = A[i][j];
        }
    }
    return nueva;

}

void multi(vector<vector<int>> A,vector<vector<int>> B){
    int n = A.size();
    int suma = 0;
    vector<vector<int>> C(n, vector<int>(n, 0));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            suma = 0;
            for(int k=0;k<n;k++){
                suma += A[i][k]*B[i][k];
            
            }
            C[i][j] = suma;
            
        }
        
    }
}


int main() {
    int n = 5;
    for(int r=0;r<30;r++){

        vector<vector<int>> A(n, vector<int>(n, 0));
        vector<vector<int>> B(n, vector<int>(n, 0));
        srand(time(0));

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                A[i][j] = rand() % 100;
                B[i][j] = rand() % 100;  
            }
        }
        vector<vector<int>> C(n, vector<int>(n, 0));
       
        auto s1 = high_resolution_clock::now();
        multi(A,traspo(B));
        auto e1 = high_resolution_clock::now();
        duration<double,milli> d1 = e1 - s1;
        cout << "Tiempo de ejecución: " << d1.count() << " milli" << endl;
        }
    }
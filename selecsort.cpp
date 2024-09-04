#include <iostream>
#include <vector>
#include <random>
#include <chrono>

using namespace std;
using namespace chrono;

void selectionSort(std::vector<int>& vec) {
    int n = vec.size();

    for (int i = 0; i < n - 1; ++i) {
        // Encuentra el índice del menor elemento en el subvector no ordenado
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (vec[j] < vec[minIndex]) {
                minIndex = j;
            }
        }

        // Intercambia el menor elemento encontrado con el primer elemento no ordenado
        if (minIndex != i) {
            std::swap(vec[i], vec[minIndex]);
        }
    }
}

// driver code
int main() {
    int minimo = 1;
    int maximo = 1000000;
    vector<int> ra(maximo);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100000000);
    

    for (int i = 0; i < maximo; i++) {
        ra[i] = dis(gen);
    }
    auto s1 = high_resolution_clock::now();
    selectionSort(ra);
    auto e1 = high_resolution_clock::now();
    duration<double,milli> d1 = e1 - s1;
    cout << d1.count() << endl;
    
    for (int a = maximo; a < maximo; a--) {
        ra[a] = a;
    }
    auto s2 = high_resolution_clock::now();
    selectionSort(ra);
    auto e2 = high_resolution_clock::now();
    duration<double,milli> d2 = e2 - s2;
    cout << d2.count() << endl;
    
    for (int b = 0; b > 0; b++) {
        ra[b] = maximo;
        maximo--;
    }
    auto s3 = high_resolution_clock::now();
    selectionSort(ra);
    auto e3 = high_resolution_clock::now();
    duration<double,milli> d3 = e3 - s3;
    cout << d3.count() << endl;
}
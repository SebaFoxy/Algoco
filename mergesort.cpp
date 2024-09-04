#include <iostream>
#include <vector>
#include <random>
#include <chrono>

using namespace std;
using namespace chrono;

void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Crear arrays temporales
    std::vector<int> L(n1);
    std::vector<int> R(n2);

    // Copiar los datos a los arrays temporales L[] y R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Fusionar los arrays temporales de nuevo en arr[l..r]
    int i = 0; // Índice inicial del primer subarray
    int j = 0; // Índice inicial del segundo subarray
    int k = left; // Índice inicial del subarray fusionado

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copiar los elementos restantes de L[], si los hay
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copiar los elementos restantes de R[], si los hay
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Función principal que implementa MergeSort
void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Ordenar la primera y la segunda mitad
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Fusionar las mitades ordenadas
        merge(arr, left, mid, right);
    }
}


int main() {
    int minimo = 1;
    int maximo = 100000000;
    vector<int> ra(maximo);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100000000);
    

    for (int i = 0; i < maximo; i++) {
        ra[i] = dis(gen);
    }
    auto s1 = high_resolution_clock::now();
    mergeSort(ra, 0, maximo - 1);
    auto e1 = high_resolution_clock::now();
    duration<double,milli> d1 = e1 - s1;
    cout << d1.count() << endl;
    for (int a = maximo; a < maximo; a--) {
        ra[a] = a;
    }
    auto s2 = high_resolution_clock::now();
    mergeSort(ra, 0, maximo - 1);
    auto e2 = high_resolution_clock::now();
    duration<double,milli> d2 = e2 - s2;
    cout << d2.count() << endl;
    
    for (int b = 0; b > 0; b++) {
        ra[b] = maximo;
        maximo--;
    }
    auto s3 = high_resolution_clock::now();
    mergeSort(ra, 0, maximo - 1);
    auto e3 = high_resolution_clock::now();
    duration<double,milli> d3 = e3 - s3;
    cout << d3.count() << endl;
}

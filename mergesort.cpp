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
    vector<int> L(n1);
    vector<int> R(n2);

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
    int maximo = 100000000; //Largo del vector
    double azar = 0;   //Total de las pruebas con numeros ordenados al azar
    double ascen = 0;   //Total de las pruebas con numeros ordenados ascendentemente
    double desce = 0;   //Total de las pruebas con numeros ordenados descendentemente
    int pruebas = 2;     //Numeros de pruebas a hacer 
    vector<int> ra(maximo);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, maximo);
   
    for(int c=0;c<pruebas;c++){
        for (int i = 0; i < maximo; i++) {          //Llenar vector con numeros al azar
            ra[i] = dis(gen);
            
        }
        
        auto s1 = high_resolution_clock::now();
        mergeSort(ra,0,maximo-1);                   //QuickSort ordenado al azar
        auto e1 = high_resolution_clock::now();
        duration<double,milli> d1 = e1 - s1;
        
        azar += d1.count();                       //Suma al total de la prueba al azar
        for (int a = 0; a < maximo; a++) {
            ra[a] = a;                             //Llenar vector con numeoros ascendentemente
        }
    
        auto s2 = high_resolution_clock::now();
        mergeSort(ra,0,maximo-1);                    //QuickSort ordenado ascendentemente
        auto e2 = high_resolution_clock::now();
        duration<double,milli> d2 = e2 - s2;
        
        ascen += d2.count();                       //Suma al total de la prueba ascendente
        int numero = maximo;
        for (int b = 0; b<maximo; b++) {
            ra[b] = numero;                         //Llenar vector con numeros descendentemente
            numero--;

        }
        auto s3 = high_resolution_clock::now();
        mergeSort(ra,0,maximo-1);                    //QuickSort ordenado descendentemente
        auto e3 = high_resolution_clock::now();
        duration<double,milli> d3 = e3 - s3;
    
        desce += d3.count();                       //Suma al total de la prueba descendente
    }
    cout << azar/pruebas << endl;
    cout << ascen/pruebas << endl;                  //Promedios
    cout << desce/pruebas << endl;

}

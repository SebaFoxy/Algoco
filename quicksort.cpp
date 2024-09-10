#include <iostream>
#include <vector>
#include <random>
#include <chrono>

using namespace std;
using namespace chrono;

int partition(vector<int> &vec, int low, int high) {

    // Selecciona el ultimo elemento como pivote
    int pivot = vec[high];

    // Indice del elemento justo antes del último elemento
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {

        // Si el elemento es mas pequeño
        // o igual al pivote los cambia de posicion
        if (vec[j] <= pivot) {
            i++;
            swap(vec[i], vec[j]);
        }
    }

    // Coloca el pivote el pivote en la posicion que le toca
    swap(vec[i + 1], vec[high]);

    // Retorna el indice de la particion
    return (i + 1);
}

void quickSort(vector<int> &vec, int low, int high) {

    if (low < high) {

        // p es el índice de partición, después de la llamada, vec[p] está en su lugar correcto
        int p = partition(vec, low, high);

        // Ordena los elementos antes y despues de p recursivamente
        quickSort(vec, low, p - 1);
        quickSort(vec, p + 1, high);
    }
}




int main() {
    int maximo = 100000000; //Largo del vector
    double azar = 0;   //Total de las pruebas con numeros ordenados al azar
    double ascen = 0;   //Total de las pruebas con numeros ordenados ascendentemente
    double desce = 0;   //Total de las pruebas con numeros ordenados descendentemente
    int pruebas = 3;     //Numeros de pruebas a hacer 
    vector<int> ra(maximo);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, maximo);
   
    for(int c=0;c<pruebas;c++){
        for (int i = 0; i < maximo; i++) {          //Llenar vector con numeros al azar
            ra[i] = dis(gen);
            
        }
        
        auto s1 = high_resolution_clock::now();
        quickSort(ra,0,maximo-1);                   //QuickSort ordenado al azar
        auto e1 = high_resolution_clock::now();
        duration<double,milli> d1 = e1 - s1;
        
        azar += d1.count();                       //Suma al total de la prueba al azar
        for (int a = 0; a < maximo; a++) {
            ra[a] = a;                             //Llenar vector con numeoros ascendentemente
        }
    
        auto s2 = high_resolution_clock::now();
        //quickSort(ra,0,maximo-1);                  //QuickSort ordenado ascendentemente
        auto e2 = high_resolution_clock::now();
        duration<double,milli> d2 = e2 - s2;
        
        ascen += d2.count();                       //Suma al total de la prueba ascendente
        int numero = maximo;
        for (int b = 0; b<maximo; b++) {
            ra[b] = numero;                         //Llenar vector con numeros descendentemente
            numero--;

        }
        auto s3 = high_resolution_clock::now();
        //quickSort(ra,0,maximo-1);                  //QuickSort ordenado descendentemente
        auto e3 = high_resolution_clock::now();
        duration<double,milli> d3 = e3 - s3;
    
        desce += d3.count();                       //Suma al total de la prueba descendente
    }
    cout << azar/pruebas << endl;
    cout << ascen/pruebas << endl;                  //Promedios
    cout << desce/pruebas << endl;

}



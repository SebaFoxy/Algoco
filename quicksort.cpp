#include <iostream>
#include <vector>
#include <random>
#include <chrono>

using namespace std;
using namespace chrono;

int partition(vector<int> &vec, int low, int high) {

    // Selecting last element as the pivot
    int pivot = vec[high];

    // Index of elemment just before the last element
    // It is used for swapping
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {

        // If current element is smaller than or
        // equal to pivot
        if (vec[j] <= pivot) {
            i++;
            swap(vec[i], vec[j]);
        }
    }

    // Put pivot to its position
    swap(vec[i + 1], vec[high]);

    // Return the point of partition
    return (i + 1);
}

void quickSort(vector<int> &vec, int low, int high) {

    // Base case: This part will be executed till the starting
    // index low is lesser than the ending index high
    if (low < high) {

        // p is partitioning index, arr[p] is now at
        // right place
        int p = partition(vec, low, high);

        // Separately sort elements before and after the
        // partition index p
        quickSort(vec, low, p - 1);
        quickSort(vec, p + 1, high);
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
    quickSort(ra, 0, maximo - 1);
    auto e1 = high_resolution_clock::now();
    duration<double,milli> d1 = e1 - s1;
    cout <<d1.count()<< endl;
    for (int a = maximo; a < maximo; a--) {
        ra[a] = a;
    }
    auto s2 = high_resolution_clock::now();
    //quickSort(ra, 0, maximo - 1);
    auto e2 = high_resolution_clock::now();
    duration<double,milli> d2 = e2 - s2;
    cout <<d2.count()<< endl;
    
    for (int b = 0; b > 0; b++) {
        ra[b] = maximo;
        maximo--;
    }
    auto s3 = high_resolution_clock::now();
    //quickSort(ra, 0, maximo - 1);
    auto e3 = high_resolution_clock::now();
    duration<double,milli> d3 = e3 - s3;
    cout <<d3.count()<< endl;
}


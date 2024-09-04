#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace chrono;

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
    sort(ra.begin(),ra.end());
    auto e1 = high_resolution_clock::now();
    duration<double,milli> d1 = e1 - s1;
    cout << d1.count() << endl;
    for (int a = maximo; a < maximo; a--) {
        ra[a] = a;
    }
    auto s2 = high_resolution_clock::now();
    sort(ra.begin(),ra.end());
    auto e2 = high_resolution_clock::now();
    duration<double,milli> d2 = e2 - s2;
    cout <<  d2.count() << endl;
    
    for (int b = 0; b > 0; b++) {
        ra[b] = maximo;
        maximo--;
    }
    auto s3 = high_resolution_clock::now();
    sort(ra.begin(),ra.end());
    auto e3 = high_resolution_clock::now();
    duration<double,milli> d3 = e3 - s3;
    cout <<  d3.count() <<  endl;
}
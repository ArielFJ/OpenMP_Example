#include <iostream>
#include <omp.h>
#include <chrono>
#include <cmath>

using namespace std;

#define N 100000000

void fillArrays(double* arr1, double* arr2);
void arrMath(double* arr1, double* arr2);
void arrMathParallel(double* arr1, double* arr2);

int main()
{
    omp_set_num_threads(8);
    double* arr1 = new double[N];
    double* arr2 = new double[N];
    
    fillArrays(arr1, arr2);
    
    arrMath(arr1, arr2);

    arrMathParallel(arr1, arr2);
    
    system("pause");
}


void fillArrays(double* arr1, double* arr2) {
    for (auto n = 0; n < N; n++) {
        arr1[n] = n;
        arr2[n] = n;
    }
    cout << "Arrays 1 y 2 llenos.\n";
}


void arrMath(double* arr1, double* arr2) {
    double* arr3 = new double[N];

    auto start = chrono::steady_clock::now();

    for (auto i = 0; i < N; i++) {
        arr3[i] = (sin(arr1[i]) + cos(arr2[i]))
                    / tan(arr1[i] + arr2[i]) ;
    }

    auto end = chrono::steady_clock::now();
    chrono::duration<double> seconds = end - start;
    cout << "Tiempo para sumar elementos \n de 2 arrays e introducirlos en un tercero\n de " << N << " posiciones: " << seconds.count() << " s\n";
}

void arrMathParallel(double* arr1, double* arr2) {
    double* arr3 = new double[N];

    auto start = chrono::steady_clock::now();
    #pragma omp parallel for default(shared)
    for (auto i = 0; i < N; i++) {
        arr3[i] = (sin(arr1[i]) + cos(arr2[i])) / tan(arr1[i] + arr2[i]);
    }

    auto end = chrono::steady_clock::now();
    chrono::duration<double> seconds = end - start;
    cout << "Tiempo para sumar elementos \n de 2 arrays e introducirlos en un tercero\n de " << N << " posiciones de forma paralela: " << seconds.count() << " s\n";
}
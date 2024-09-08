#include <iostream>
#include <pthread.h>
#include <vector>
#include <math.h>

struct ThreadData {
    int n;
    double result;
};

void* calcularTermino(void* arg) {
    ThreadData* data = (ThreadData* )(arg);
    int n = data->n;

    data->result = pow(-1, n + 1) / (double)(n);

    pthread_exit(arg);
    return (NULL);
}

int main() {
    int maxN;
    std::cout << "Ingrese el valor máximo de n: ";
    std::cin >> maxN;

    std::vector<pthread_t> hilos(maxN);
    std::vector<ThreadData> datos(maxN);

    for (int i = 1; i <= maxN; ++i) {
        datos[i - 1].n = i; 
        pthread_create(&hilos[i - 1], nullptr, calcularTermino, &datos[i - 1]);
    }

    double resultadoTotal = 0.0;

    for (int i = 1; i <= maxN; ++i) {
        void* retVal;
        pthread_join(hilos[i - 1], &retVal);
        ThreadData* resultData = (ThreadData*)(retVal);
        resultadoTotal += resultData->result;
    }

    std::cout << "El valor de convergencia de la serie es: " << resultadoTotal << std::endl;

    return 0;
}

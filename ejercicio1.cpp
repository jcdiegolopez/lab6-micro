#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

struct FiboArgs {
    int max;
    std::vector<int> fibo_list;
};

void *calculateFibo(void *args){
    FiboArgs *fiboargs;
    fiboargs = (FiboArgs *)args;

    int a = 0, b = 1;
    if (fiboargs->max >=0) fiboargs -> fibo_list.push_back(a);
    if (fiboargs->max >=1) fiboargs -> fibo_list.push_back(b);

    while(true){
        int next = a + b;
        if(next > fiboargs->max) break;
        fiboargs -> fibo_list.push_back(next);
        a = b;
        b = next;   
    } 
    pthread_exit(NULL);
    return NULL;
}

int main(){
    int n;
    std::cout << "Ingrese un valor entre 0 a 100 para encontrar la serie de fibonacci:";
    std::cin >> n;
    if( n > 0 && n <100){
        pthread_t fib_thread;
        FiboArgs fibo_args;
        fibo_args.max = n;

        pthread_create(&fib_thread, NULL, calculateFibo, (void *) &fibo_args);
        
        
        std::cout << "Las iteraciones de fibonacci entre 0 y " << n << " son: " << std::endl;
        int suma = 0;
        for(int i = 0; i < fibo_args.fibo_list.size(); i++){
            std::cout << "Iteracion " << i << ": -> " <<fibo_args.fibo_list[i] << " " << std::endl;
            suma += fibo_args.fibo_list[i];
        }
        std::cout << "La suma de los valores de la serie de fibonacci es: " << suma << std::endl;
    }else{
        std::cout << "El valor ingresado no es valido";
    }
}
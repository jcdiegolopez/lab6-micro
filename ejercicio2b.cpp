#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> // Incluye para usar intptr_t
#include <cmath>

#define NUM_THREADS 10

void *PrintHello(void *idParam){
    //cast de puntero a void hacia puntero a int
    int *id;        //puntero a int
    id = (int *)idParam;



    printf("Hello world thread No. %d\n", *id);
    pthread_exit(NULL);
    return (NULL);

}

int main(int argc, char *argv[]){
    // Usar ID psra identificar c/hilo de manera segura
    pthread_t threadsID[NUM_THREADS];

    //Parametro a compartir equivalente al num del n hilo
    int rc, t, param[NUM_THREADS];

    //Crear atributo
    pthread_attr_t attr;

    //Inicializar atributos 
    pthread_attr_init(&attr);

    //Modificar atributos
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);

    //Cada hilo se crea individualmente
    for (t = 0; t<NUM_THREADS; t++){
        printf("En rutina Principal: creando el thread #%d\n", t);
        param[t] = t;

        //pthread create (id, atrr, subrutina, valorAoperar-param de paso)
        rc = pthread_create(&threadsID[t], &attr, PrintHello, (void *) &param[t]);

        //verificar si ocurrio error al creal algun hilo
        if(rc){
            printf("ERROR: codigo de retorno desde pthread_create %d\n", rc);
            exit(-1);
        
        } //Fin del if
        
    }
    for (t = 0; t<NUM_THREADS; t++){
        rc = pthread_join(threadsID[t], NULL);
        if(rc){
            printf("ERROR: codigo de retorno desde pthread_join %d\n", rc);
            exit(-1);
        }//Fin del if
    }
    
    //Fin del for
    pthread_attr_destroy(&attr);
    //Destroy
}
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdatomic.h>

atomic_int platanos = 10;

void* frutero(void* arg) {
    int id = *(int*)arg;
    for (;;) {
        int anterior = atomic_fetch_sub(&platanos, 1);
        if (anterior <= 0){ //No había plátanos
	    atomic_fetch_add(&platanos, 1); //devuelve el plátano
	    printf("Frutero %d no encuentra plátanos\n", id);
            break;
	}
	else {
            printf("Frutero %d vende un plátano (quedaban %d)\n", id, anterior);
            usleep(100000);
	}
    }
    return NULL;
}

int main() {
    pthread_t hilos[3];
    int ids[3] = {1, 2, 3};

    for (int i = 0; i < 3; i++)
        pthread_create(&hilos[i], NULL, frutero, &ids[i]);

    for (int i = 0; i < 3; i++)
        pthread_join(hilos[i], NULL);

    printf("Plátanos restantes: %d\n", atomic_load(&platanos));
    return 0;
}

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdatomic.h>

atomic_int platanos = 5;
atomic_int naranjas = 5;
atomic_int fruta = 10;

void* frutero(void* arg) {
    int id = *(int*)arg;
    for (;;) {
        int antes_platanos = atomic_fetch_sub(&platanos, 1);
        if (antes_platanos <= 0) { // ya no quedaban
            atomic_fetch_add(&platanos, 1);
            atomic_fetch_add(&fruta, 1);
            printf("Frutero %d no encuentra plátanos\n", id);
            break;
        }
        printf("Frutero %d vende un plátano (quedaban %d)\n", id, antes_platanos);
        atomic_fetch_sub(&fruta, 1);

        int antes_naranjas = atomic_fetch_sub(&naranjas, 1);
        if (antes_naranjas <= 0) {
            atomic_fetch_add(&naranjas, 1);
            atomic_fetch_add(&fruta, 1);
            printf("Frutero %d no encuentra naranjas\n", id);
            break;
        }
        printf("Frutero %d vende una naranja (quedaban %d)\n", id, antes_naranjas);
	atomic_fetch_sub(&fruta, 1);
        usleep(100000);
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

    printf("Plátanos: %d, Naranjas: %d, Fruta total: %d\n",
           atomic_load(&platanos), atomic_load(&naranjas), atomic_load(&fruta));
    return 0;
}

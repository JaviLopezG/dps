#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

int platanos = 5;
int naranjas = 5;
int fruta = 10;
sem_t sem;

void* frutero(void* arg) {
    int id = *(int*)arg;
    int temp = 0;
    for (;;) {
        sem_wait(&sem); // sección crítica
        if (platanos > 0) {
	    temp = platanos;
            platanos--;
            fruta--;
            printf("Frutero %d vende un plátano (quedaban %d)\n", id, temp);
        } else if (naranjas > 0) {
	    temp = naranjas;
            naranjas--;
            fruta--;
            printf("Frutero %d vende una naranja (quedaban %d)\n", id, temp);
        } else {
            sem_post(&sem);
            printf("Frutero %d no encuentra fruta disponible\n", id);
            break;
        }
        sem_post(&sem);
        usleep(100000);
    }
    return NULL;
}

int main() {
    pthread_t hilos[3];
    int ids[3] = {1, 2, 3};

    sem_init(&sem, 0, 1);

    for (int i = 0; i < 3; i++)
        pthread_create(&hilos[i], NULL, frutero, &ids[i]);

    for (int i = 0; i < 3; i++)
        pthread_join(hilos[i], NULL);

    sem_destroy(&sem);

    printf("Plátanos: %d, Naranjas: %d, Fruta total: %d\n", platanos, naranjas, fruta);
    return 0;
}

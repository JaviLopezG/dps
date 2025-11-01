#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int platanos = 10;

void* frutero(void* arg) {
    int id = *(int*)arg;
    for (;;) {
        if (platanos <= 0)
            break;
        printf("Frutero %d vende un plátano (quedaban %d)\n", id, platanos);
        platanos--; // acceso sin sincronizar
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

    printf("Plátanos restantes: %d\n", platanos);
    return 0;
}

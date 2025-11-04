// vulnerable.c
#include <stdio.h>
#include <string.h>

void funcion_vulnerable(char *entrada) {
    char buffer[128]; // Buffer de 128 bytes
    printf("Copiando cadena de entrada %p a %p...\n", entrada, &buffer);
    // La vulnerabilidad reside aquí: strcpy no comprueba límites.
    strcpy(buffer, entrada); 
    printf("Copia terminada.\n");
}

int main(int argc, char *argv[]) {
    // Comprobamos que se pasó el argumento necesario
    if (argc != 2) {
        printf("Uso: %s <cadena_de_prueba>\n", argv[0]);
        return 1;
    }
    
    funcion_vulnerable(argv[1]);
    
    printf("Fin del programa.\n");
    return 0;
}

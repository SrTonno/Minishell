#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sigint_handler(int sig) {
    // Manejo de la señal SIGINT (Ctrl + C) aquí
    // Puedes agregar la lógica que necesites para cancelar el read()
    printf("\nSe recibió la señal SIGINT. Cancelando el read()...\n");
}

int main() {
    char buffer[1024];
    int n;

    struct sigaction sa;
    sa.sa_handler = sigint_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("Error en sigaction");
        return 1;
    }

    printf("Ingrese una cadena de texto:\n");

    while (1) {
        n = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);

        if (n == -1) {
            if (errno == EINTR) {
                // La función read() fue interrumpida por la señal SIGINT
                printf("\nLa función read() fue cancelada por la señal SIGINT.\n");
                break;
            } else {
                perror("Error en read");
                return 1;
            }
        } else {
            break;
        }
    }

    buffer[n] = '\0';
    printf("Lectura exitosa: %s\n", buffer);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sigint_handler(int sig) {
    // Manejo de la señal SIGINT (Ctrl + C) aquí
    // Puedes agregar la lógica que necesites para cancelar el read()
    printf("\nSe recibió la señal SIGINT. Cancelando el read()...\n");
}

int main() {
    char buffer[1024];
    int n;

    struct sigaction sa;
    sa.sa_handler = sigint_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("Error en sigaction");
        return 1;
    }

    printf("Ingrese una cadena de texto:\n");

    while (1) {
        n = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);

        if (n == -1) {
            if (errno == EINTR) {
                // La función read() fue interrumpida por la señal SIGINT
                printf("\nLa función read() fue cancelada por la señal SIGINT.\n");
                break;
            } else {
                perror("Error en read");
                return 1;
            }
        } else {
            break;
        }
    }

    buffer[n] = '\0';
    printf("Lectura exitosa: %s\n", buffer);

    return 0;
}

#include <stdio.h>
#include "max_m10s.h"
#include "pico/stdlib.h"

int main() {
    // Inicializar GPIO, UART y stdio
    stdio_init_all(); // Inicializar todos los pines de E/S estándar
    max_m10s_init(); // Inicializar UART

    printf("Inicializando MAX-M10S...\n");

    while (1) {
        // Leer datos del GPS y procesarlos
        max_m10s_read_data();

        sleep_ms(100); // Reducir la carga del CPU esperando 100 ms
    }

    return 0;
}
#include <stdio.h>
#include "isl29125.h"
#include "pico/stdlib.h"

int main() {
    // Inicialización de la comunicación y pines I2C
    stdio_init_all();

    printf("Inicializando ISL29125...\n");
    isl29125_init(); // Inicializar el sensor ISL29125
    sleep_ms(500);   // Esperar medio segundo para asegurarse de que la inicialización esté completa

    while (1) {
        // Leer los datos de color del sensor
        uint16_t red = isl29125_read_color(ISL29125_RED_DATA_LSB);
        uint16_t green = isl29125_read_color(ISL29125_GREEN_DATA_LSB);
        uint16_t blue = isl29125_read_color(ISL29125_BLUE_DATA_LSB);

        // Imprimir los valores de los colores en la consola
        printf("Rojo: %d, Verde: %d, Azul: %d\n", red, green, blue);

        sleep_ms(1000); // Esperar 1 segundo entre lecturas
    }

    return 0;
}
#include <stdio.h>
#include "veml6030.h"
#include "pico/stdlib.h"

int main() {
    stdio_init_all();

    printf("Inicializando VEML6030...\n");
    veml6030_init(); // Inicializar el sensor VEML6030
    sleep_ms(500);   // Esperar medio segundo para completar la inicialización

    while (1) {
        // Leer la intensidad de luz
        uint16_t light = veml6030_read_light();

        // Convertir a lux según el factor de conversión
        float lux = light * 0.0576; // Escalado según el datasheet para Gain x1, 100ms
        printf("Intensidad de luz: %.2f lux\n", lux);

        sleep_ms(1000); // Esperar 1 segundo entre lecturas
    }

    return 0;
}
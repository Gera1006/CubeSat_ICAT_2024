#include <stdio.h>
#include "ms5803.h"
#include "pico/stdlib.h"

int main() {
    stdio_init_all();

    ms5803_init(); // Inicializa el sensor y la comunicación I2C

    while (1) {
        float pressure, temperature;
        ms5803_read(&pressure, &temperature);

        printf("Presión: %.2f hPa, Temperatura: %.2f °C\n", pressure, temperature);

        sleep_ms(1000); // Esperar 1 segundo entre lecturas
    }

    return 0;
}
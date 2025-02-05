#include <stdio.h>
#include "mlx90393.h"
#include "pico/stdlib.h"

int main() {
    stdio_init_all();

    mlx90393_init(); // Inicializa el sensor y la comunicación I2C

    while (1) {
        float x, y, z;
        mlx90393_read_magnetic_field(&x, &y, &z);

        printf("Campo Magnético (µT): X=%.2f, Y=%.2f, Z=%.2f\n", x, y, z);

        sleep_ms(1000); // Esperar 1 segundo entre lecturas
    }

    return 0;
}
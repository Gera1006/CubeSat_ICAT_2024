#include <stdio.h>
#include "mpu9250.h"
#include "pico/stdlib.h"

int main() {
    stdio_init_all();

    mpu9250_init(); // Inicializa el sensor y la comunicación I2C

    while (1) {
        float ax, ay, az;
        mpu9250_read_acceleration(&ax, &ay, &az);

        printf("Aceleración (g): X=%.2f, Y=%.2f, Z=%.2f\n", ax, ay, az);

        sleep_ms(1000); // Esperar 1 segundo entre lecturas
    }

    return 0;
}
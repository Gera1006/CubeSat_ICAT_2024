#include <stdio.h>
#include "uvm30a.h"
#include "pico/stdlib.h"

int main() {
    stdio_init_all();

    uvm30a_init(); // Inicializar el sensor UVM-30A

    while (1) {
        float uv_index = uvm30a_read_uv();

        printf("Índice UV: %.2f\n", uv_index);

        sleep_ms(1000); // Esperar 1 segundo antes de la siguiente lectura
    }

    return 0;
}
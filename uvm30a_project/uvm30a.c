#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

// Canal ADC para la lectura del sensor UVM-30A
#define UVM30A_PIN 26 // GP26/ADC0

// Función para inicializar el sensor UVM-30A
void uvm30a_init() {
    adc_init();                 // Inicializar el módulo ADC
    adc_gpio_init(UVM30A_PIN);  // Configurar el pin para el ADC
    adc_select_input(0);        // Seleccionar el canal ADC 0
}

// Función para leer el índice UV del sensor UVM-30A
float uvm30a_read_uv() {
    uint16_t raw = adc_read();  // Leer valor crudo del ADC
    float voltage = raw * (3.3 / (1 << 12)); // Convertir el valor crudo a voltaje
    float uv_index = voltage * 10.0;         // Convertir el voltaje a índice UV (conversión básica)
    return uv_index;
}

int main() {
    // Inicializar todas las funciones de entrada/salida estándar
    stdio_init_all();
    // Inicializar el sensor UVM-30A
    uvm30a_init();

    while (1) {
        // Leer el índice UV
        float uv_index = uvm30a_read_uv();
        // Imprimir el índice UV en la consola
        printf("Índice UV: %.2f\n", uv_index);
        // Esperar 1 segundo antes de la siguiente lectura
        sleep_ms(1000);
    }

    return 0;
}

#include "uvm30a.h"
#include "pico/stdlib.h"
#include "hardware/adc.h"

// Inicializar el sensor UVM-30A
void uvm30a_init() {
    adc_init();             // Inicializar el módulo ADC
    adc_gpio_init(UVM30A_PIN); // Configurar el pin para el ADC
    adc_select_input(0);     // Seleccionar el canal ADC 0 (ADC0)
}

// Función para leer el índice UV del sensor UVM-30A
float uvm30a_read_uv() {
    uint16_t raw = adc_read();    // Leer valor crudo del ADC
    float voltage = raw * (3.3 / (1 << 12)); // Convertir el valor crudo a voltaje (3.3V es la tensión de referencia)
    float uv_index = voltage * 10.0;        // Convertir el voltaje a índice UV (conversión básica)
    return uv_index;
}
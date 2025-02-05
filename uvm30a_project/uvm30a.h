#ifndef UVM30A_H
#define UVM30A_H

#include <stdint.h>
#include <stdbool.h>

// Pin ADC para la lectura del sensor UVM-30A
#define UVM30A_PIN 26 // GP26/ADC0

// Inicializar el sensor UVM-30A
void uvm30a_init();

// Leer el índice UV del sensor UVM-30A
float uvm30a_read_uv();

#endif
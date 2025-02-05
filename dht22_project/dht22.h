#ifndef DHT22_H
#define DHT22_H

#include <stdio.h>
#include "pico/stdlib.h"

// Configuración del pin del DHT22
#define DHT_PIN 15

// Función para leer el sensor
int read_dht22(uint8_t *data);

// Función para obtener la temperatura y humedad
int get_dht22_data(float *temperature, float *humidity);

#endif  // DHT22_H
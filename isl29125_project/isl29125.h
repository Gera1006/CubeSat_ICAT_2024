#ifndef ISL29125_H
#define ISL29125_H

#include <stdint.h>
#include <stdbool.h>

// Direcciones y registros del ISL29125
#define ISL29125_ADDR 0x44
#define ISL29125_CONFIG_1 0x01
#define ISL29125_CONFIG_2 0x02
#define ISL29125_CONFIG_3 0x03
#define ISL29125_RED_DATA_LSB 0x09
#define ISL29125_GREEN_DATA_LSB 0x0B
#define ISL29125_BLUE_DATA_LSB 0x0D

// Pines I2C (pueden ser configurados externamente)
#define ISL29125_I2C_PORT i2c0
#define ISL29125_SDA_PIN 4
#define ISL29125_SCL_PIN 5

// Función para inicializar el sensor ISL29125
void isl29125_init();

// Función para leer datos de color del sensor ISL29125
uint16_t isl29125_read_color(uint8_t lsb_register);

#endif
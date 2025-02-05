#ifndef VEML6030_H
#define VEML6030_H

#include <stdint.h>
#include <stdbool.h>

// Direcciones y registros del VEML6030
#define VEML6030_ADDR 0x48
#define VEML6030_ALS_CONF_REG 0x00
#define VEML6030_ALS_DATA_LSB_REG 0x04
#define VEML6030_ALS_DATA_MSB_REG 0x05

// Pines I2C (pueden ser configurados externamente)
#define VEML6030_I2C_PORT i2c0
#define VEML6030_SDA_PIN 4
#define VEML6030_SCL_PIN 5

// Función para inicializar el sensor VEML6030
void veml6030_init();

// Función para leer la intensidad de luz del sensor VEML6030
uint16_t veml6030_read_light();

#endif
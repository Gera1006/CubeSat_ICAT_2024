#ifndef MS5803_H
#define MS5803_H

#include <stdint.h>
#include <stdbool.h>

// Dirección I2C del MS5803-14BA
#define MS5803_ADDR 0x76

// Comandos del MS5803-14BA
#define MS5803_CMD_RESET 0x1E
#define MS5803_CMD_READ_PRESSURE 0x48
#define MS5803_CMD_READ_TEMPERATURE 0x58

// Pines I2C (pueden ser configurados externamente)
#define MS5803_I2C_PORT i2c0
#define MS5803_SDA_PIN 4
#define MS5803_SCL_PIN 5

// Inicializar el sensor MS5803-14BA
void ms5803_init();

// Leer datos del ADC del sensor
uint16_t ms5803_read_adc(uint8_t cmd);

// Leer presión y temperatura del sensor
void ms5803_read(float *pressure, float *temperature);

#endif
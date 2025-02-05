#include "ms5803.h"
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include <stdio.h> // Para printf (si se usa en la inicialización o depuración)

// Inicializar el sensor MS5803-14BA
void ms5803_init() {
    uint8_t cmd = MS5803_CMD_RESET;

    i2c_init(MS5803_I2C_PORT, 100 * 1000); // 100 kHz
    gpio_set_function(MS5803_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(MS5803_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(MS5803_SDA_PIN);
    gpio_pull_up(MS5803_SCL_PIN);

    i2c_write_blocking(MS5803_I2C_PORT, MS5803_ADDR, &cmd, 1, false); // Enviar comando de reinicio
    sleep_ms(10); // Esperar tiempo de reinicio
}

// Función para leer datos del ADC del sensor
uint16_t ms5803_read_adc(uint8_t cmd) {
    uint8_t buffer[2];
    i2c_write_blocking(MS5803_I2C_PORT, MS5803_ADDR, &cmd, 1, true); // Enviar comando de lectura
    sleep_ms(10); // Esperar tiempo de conversión
    i2c_read_blocking(MS5803_I2C_PORT, MS5803_ADDR, buffer, 2, false); // Leer 2 bytes de datos
    return (buffer[0] << 8) | buffer[1]; // Combinar bytes en un valor de 16 bits
}

// Función para leer presión y temperatura del sensor
void ms5803_read(float *pressure, float *temperature) {
    uint16_t raw_pressure = ms5803_read_adc(MS5803_CMD_READ_PRESSURE); // Leer datos de presión
    uint16_t raw_temperature = ms5803_read_adc(MS5803_CMD_READ_TEMPERATURE); // Leer datos de temperatura

    // Conversión básica de valores crudos a unidades físicas
    *pressure = raw_pressure / 100.0;
    *temperature = raw_temperature / 100.0;
}
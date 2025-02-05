#include "veml6030.h"
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include <stdio.h> // Para printf (si se usa en la inicialización o depuración)

// Función para inicializar el sensor VEML6030
void veml6030_init() {
    uint8_t config[3];

    i2c_init(VEML6030_I2C_PORT, 100 * 1000); // Configurar I2C a 100 kHz
    gpio_set_function(VEML6030_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(VEML6030_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(VEML6030_SDA_PIN);
    gpio_pull_up(VEML6030_SCL_PIN);

    // Configurar el registro ALS_CONF
    config[0] = VEML6030_ALS_CONF_REG; // Dirección del registro de configuración
    config[1] = 0x00;                // MSB: Gain x1, 100ms integration time
    config[2] = 0x00;                // LSB: Normal mode
    i2c_write_blocking(VEML6030_I2C_PORT, VEML6030_ADDR, config, 3, false);
}

// Función para leer la intensidad de luz del sensor VEML6030
uint16_t veml6030_read_light() {
    uint8_t buffer[2];

    // Leer los registros LSB y MSB de los datos de luz
    i2c_write_blocking(VEML6030_I2C_PORT, VEML6030_ADDR, &VEML6030_ALS_DATA_LSB_REG, 1, true);
    i2c_read_blocking(VEML6030_I2C_PORT, VEML6030_ADDR, buffer, 2, false);

    // Combinar LSB y MSB en un solo valor de 16 bits
    return (buffer[1] << 8) | buffer[0];
}
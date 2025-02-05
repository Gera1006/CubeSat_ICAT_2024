#include "isl29125.h"
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include <stdio.h> // Para printf (si se usa en la inicialización o depuración)

// Función para inicializar el sensor ISL29125
void isl29125_init() {
    uint8_t config[2];

    i2c_init(ISL29125_I2C_PORT, 100 * 1000); // Configurar I2C a 100 kHz
    gpio_set_function(ISL29125_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(ISL29125_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(ISL29125_SDA_PIN);
    gpio_pull_up(ISL29125_SCL_PIN);

    // Configuración del modo RGB: Modo RGB, resolución de 10 bits, operación normal
    config[0] = ISL29125_CONFIG_1;
    config[1] = 0x05;
    i2c_write_blocking(ISL29125_I2C_PORT, ISL29125_ADDR, config, 2, false);

    // Configuración adicional: Sin filtro IR, rango de 10k lux, operación normal
    config[0] = ISL29125_CONFIG_2;
    config[1] = 0x00;
    i2c_write_blocking(ISL29125_I2C_PORT, ISL29125_ADDR, config, 2, false);

    // Configuración del registro 3: Sin interrupciones activadas
    config[0] = ISL29125_CONFIG_3;
    config[1] = 0x00;
    i2c_write_blocking(ISL29125_I2C_PORT, ISL29125_ADDR, config, 2, false);
}

// Función para leer datos de color del sensor ISL29125
uint16_t isl29125_read_color(uint8_t lsb_register) {
    uint8_t buffer[2]; // Buffer para almacenar los datos leídos
    i2c_write_blocking(ISL29125_I2C_PORT, ISL29125_ADDR, &lsb_register, 1, true); // Escribir la dirección del registro de datos LSB
    i2c_read_blocking(ISL29125_I2C_PORT, ISL29125_ADDR, buffer, 2, false); // Leer dos bytes de datos del registro

    // Combinar LSB y MSB en un solo valor de 16 bits
    return (buffer[1] << 8) | buffer[0];
}
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

// Dirección I2C del MS5803-14BA
#define MS5803_ADDR 0x76
#define CMD_RESET 0x1E
#define CMD_READ_PRESSURE 0x48
#define CMD_READ_TEMPERATURE 0x58

// Pines I2C
#define I2C_PORT i2c0
#define SDA_PIN 4
#define SCL_PIN 5

// Función para inicializar el sensor MS5803-14BA
void ms5803_init() {
    uint8_t cmd = CMD_RESET;
    i2c_write_blocking(I2C_PORT, MS5803_ADDR, &cmd, 1, false); // Enviar comando de reinicio
    sleep_ms(10); // Esperar tiempo de reinicio
}

// Función para leer datos del ADC del sensor
uint16_t ms5803_read_adc(uint8_t cmd) {
    uint8_t buffer[2];
    i2c_write_blocking(I2C_PORT, MS5803_ADDR, &cmd, 1, true); // Enviar comando de lectura
    sleep_ms(10); // Esperar tiempo de conversión
    i2c_read_blocking(I2C_PORT, MS5803_ADDR, buffer, 2, false); // Leer 2 bytes de datos
    return (buffer[0] << 8) | buffer[1]; // Combinar bytes en un valor de 16 bits
}

// Función para leer presión y temperatura del sensor
void ms5803_read(float *pressure, float *temperature) {
    uint16_t raw_pressure = ms5803_read_adc(CMD_READ_PRESSURE); // Leer datos de presión
    uint16_t raw_temperature = ms5803_read_adc(CMD_READ_TEMPERATURE); // Leer datos de temperatura

    // Conversión básica de valores crudos a unidades físicas
    *pressure = raw_pressure / 100.0;
    *temperature = raw_temperature / 100.0;
}

int main() {
    // Inicializar todos los pines de E/S estándar
    stdio_init_all();
    // Inicializar I2C a 100 kHz
    i2c_init(I2C_PORT, 100 * 1000);
    // Configurar los pines SDA y SCL para la función I2C
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    // Habilitar resistencias de pull-up en los pines SDA y SCL
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);

    // Inicializar el sensor MS5803-14BA
    ms5803_init();

    while (1) {
        float pressure, temperature;
        // Leer los valores de presión y temperatura
        ms5803_read(&pressure, &temperature);
        // Imprimir los valores de presión y temperatura en la consola
        printf("Presión: %.2f hPa, Temperatura: %.2f °C\n", pressure, temperature);
        // Esperar 1 segundo antes de la siguiente lectura
        sleep_ms(1000);
    }

    return 0;
}

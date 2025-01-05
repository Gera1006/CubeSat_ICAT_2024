#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

// Direcciones y registros del VEML6030
#define VEML6030_ADDR          0x48
#define ALS_CONF_REG           0x00
#define ALS_DATA_LSB_REG       0x04
#define ALS_DATA_MSB_REG       0x05

// Pines I2C
#define I2C_PORT i2c0
#define SDA_PIN  4
#define SCL_PIN  5

// Función para inicializar el sensor VEML6030
void veml6030_init() {
    uint8_t config[3];

    // Configurar el registro ALS_CONF
    config[0] = ALS_CONF_REG;  // Dirección del registro de configuración
    config[1] = 0x00;          // MSB: Gain x1, 100ms integration time
    config[2] = 0x00;          // LSB: Normal mode
    i2c_write_blocking(I2C_PORT, VEML6030_ADDR, config, 3, false);
}

// Función para leer la intensidad de luz del sensor VEML6030
uint16_t veml6030_read_light() {
    uint8_t buffer[2];

    // Leer los registros LSB y MSB de los datos de luz
    i2c_write_blocking(I2C_PORT, VEML6030_ADDR, &ALS_DATA_LSB_REG, 1, true);
    i2c_read_blocking(I2C_PORT, VEML6030_ADDR, buffer, 2, false);

    // Combinar LSB y MSB en un solo valor de 16 bits
    return (buffer[1] << 8) | buffer[0];
}

int main() {
    // Inicialización del GPIO y del I2C
    stdio_init_all();
    i2c_init(I2C_PORT, 100 * 1000); // Configurar I2C a 100 kHz
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);

    printf("Inicializando VEML6030...\n");
    veml6030_init(); // Inicializar el sensor VEML6030
    sleep_ms(500); // Esperar medio segundo para completar la inicialización

    while (1) {
        // Leer la intensidad de luz
        uint16_t light = veml6030_read_light();

        // Convertir a lux según el factor de conversión
        float lux = light * 0.0576; // Escalado según el datasheet para Gain x1, 100ms
        printf("Intensidad de luz: %.2f lux\n", lux);

        sleep_ms(1000); // Esperar 1 segundo entre lecturas
    }

    return 0;
}

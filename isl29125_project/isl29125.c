#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

// Direcciones y registros del ISL29125
#define ISL29125_ADDR        0x44
#define CONFIG_1             0x01
#define CONFIG_2             0x02
#define CONFIG_3             0x03
#define RED_DATA_LSB         0x09
#define GREEN_DATA_LSB       0x0B
#define BLUE_DATA_LSB        0x0D

// Pines I2C
#define I2C_PORT i2c0
#define SDA_PIN  4
#define SCL_PIN  5

// Función para inicializar el sensor ISL29125
void isl29125_init() {
    uint8_t config[2];

    // Configuración del modo RGB: Modo RGB, resolución de 10 bits, operación normal
    config[0] = CONFIG_1;
    config[1] = 0x05; 
    i2c_write_blocking(I2C_PORT, ISL29125_ADDR, config, 2, false);

    // Configuración adicional: Sin filtro IR, rango de 10k lux, operación normal
    config[0] = CONFIG_2;
    config[1] = 0x00; 
    i2c_write_blocking(I2C_PORT, ISL29125_ADDR, config, 2, false);

    // Configuración del registro 3: Sin interrupciones activadas
    config[0] = CONFIG_3;
    config[1] = 0x00;
    i2c_write_blocking(I2C_PORT, ISL29125_ADDR, config, 2, false);
}

// Función para leer datos de color del sensor ISL29125
uint16_t read_color(uint8_t lsb_register) {
    uint8_t buffer[2]; // Buffer para almacenar los datos leídos
    i2c_write_blocking(I2C_PORT, ISL29125_ADDR, &lsb_register, 1, true); // Escribir la dirección del registro de datos LSB
    i2c_read_blocking(I2C_PORT, ISL29125_ADDR, buffer, 2, false); // Leer dos bytes de datos del registro

    // Combinar LSB y MSB en un solo valor de 16 bits
    return (buffer[1] << 8) | buffer[0];
}

// Función principal
int main() {
    // Inicialización de la comunicación y pines I2C
    stdio_init_all();
    i2c_init(I2C_PORT, 100 * 1000); // Configurar I2C a 100 kHz
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);

    printf("Inicializando ISL29125...\n");
    isl29125_init(); // Inicializar el sensor ISL29125
    sleep_ms(500); // Esperar medio segundo para asegurarse de que la inicialización esté completa

    while (1) {
        // Leer los datos de color del sensor
        uint16_t red = read_color(RED_DATA_LSB);
        uint16_t green = read_color(GREEN_DATA_LSB);
        uint16_t blue = read_color(BLUE_DATA_LSB);

        // Imprimir los valores de los colores en la consola
        printf("Rojo: %d, Verde: %d, Azul: %d\n", red, green, blue);

        sleep_ms(1000); // Esperar 1 segundo entre lecturas
    }

    return 0;
}



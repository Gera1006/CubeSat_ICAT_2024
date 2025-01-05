#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

// Dirección I2C del MLX90393
#define MLX90393_ADDR          0x0C

// Comandos del sensor MLX90393
#define CMD_START_MEASUREMENT  0x3E
#define CMD_READ_MEASUREMENT   0x4E
#define CMD_RESET              0x06

// Pines I2C
#define I2C_PORT i2c0
#define SDA_PIN  4
#define SCL_PIN  5

// Función para enviar un comando al sensor
void mlx90393_send_command(uint8_t command) {
    i2c_write_blocking(I2C_PORT, MLX90393_ADDR, &command, 1, false);
}

// Función para leer datos del sensor
void mlx90393_read_data(uint8_t *buffer, size_t length) {
    i2c_read_blocking(I2C_PORT, MLX90393_ADDR, buffer, length, false);
}

// Inicializar el sensor MLX90393
void mlx90393_init() {
    printf("Inicializando el sensor MLX90393...\n");
    mlx90393_send_command(CMD_RESET); // Reiniciar el sensor
    sleep_ms(10);                     // Esperar que el sensor se reinicie
}

// Leer los valores de los ejes magnéticos
void mlx90393_read_magnetic_field(float *x, float *y, float *z) {
    uint8_t buffer[7] = {0};
    mlx90393_send_command(CMD_START_MEASUREMENT); // Iniciar medición
    sleep_ms(10); // Tiempo de espera típico para completar la medición

    mlx90393_send_command(CMD_READ_MEASUREMENT); // Leer los datos
    mlx90393_read_data(buffer, 7);

    // Combinar los datos para X, Y y Z
    int16_t raw_x = (buffer[1] << 8) | buffer[2];
    int16_t raw_y = (buffer[3] << 8) | buffer[4];
    int16_t raw_z = (buffer[5] << 8) | buffer[6];

    // Convertir a valores de campo magnético (depende de la configuración de escala)
    float sensitivity = 0.15; // Sensibilidad típica en microteslas por bit (consultar datasheet)
    *x = raw_x * sensitivity;
    *y = raw_y * sensitivity;
    *z = raw_z * sensitivity;
}

int main() {
    // Inicializar GPIO y I2C
    stdio_init_all();
    i2c_init(I2C_PORT, 100 * 1000); // 100 kHz
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);

    // Inicializar el sensor
    mlx90393_init();

    while (1) {
        float x, y, z;
        mlx90393_read_magnetic_field(&x, &y, &z);

        // Imprimir los valores del campo magnético
        printf("Campo Magnético (µT): X=%.2f, Y=%.2f, Z=%.2f\n", x, y, z);

        sleep_ms(1000); // Esperar 1 segundo entre lecturas
    }

    return 0;
}

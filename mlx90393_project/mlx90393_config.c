#include "mlx90393.h"
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include <stdio.h> // Para printf (si se usa en la inicialización o depuración)

// Función para enviar un comando al sensor
static void mlx90393_send_command(uint8_t command) {
    i2c_write_blocking(MLX90393_I2C_PORT, MLX90393_ADDR, &command, 1, false);
}

// Función para leer datos del sensor
static void mlx90393_read_data(uint8_t *buffer, size_t length) {
    i2c_read_blocking(MLX90393_I2C_PORT, MLX90393_ADDR, buffer, length, false);
}

// Inicializar el sensor MLX90393
void mlx90393_init() {
    printf("Inicializando el sensor MLX90393...\n");
    i2c_init(MLX90393_I2C_PORT, 100 * 1000); // 100 kHz
    gpio_set_function(MLX90393_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(MLX90393_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(MLX90393_SDA_PIN);
    gpio_pull_up(MLX90393_SCL_PIN);

    mlx90393_send_command(MLX90393_CMD_RESET); // Reiniciar el sensor
    sleep_ms(10);                               // Esperar que el sensor se reinicie
}

// Leer los valores de los ejes magnéticos
void mlx90393_read_magnetic_field(float *x, float *y, float *z) {
    uint8_t buffer[7] = {0};
    mlx90393_send_command(MLX90393_CMD_START_MEASUREMENT); // Iniciar medición
    sleep_ms(10); // Tiempo de espera típico para completar la medición

    mlx90393_send_command(MLX90393_CMD_READ_MEASUREMENT); // Leer los datos
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
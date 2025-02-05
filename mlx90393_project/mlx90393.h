#ifndef MLX90393_H
#define MLX90393_H

#include <stdint.h>
#include <stdbool.h>

// Dirección I2C del MLX90393
#define MLX90393_ADDR 0x0C

// Comandos del sensor MLX90393
#define MLX90393_CMD_START_MEASUREMENT 0x3E
#define MLX90393_CMD_READ_MEASUREMENT  0x4E
#define MLX90393_CMD_RESET            0x06

// Pines I2C (pueden ser configurados externamente)
#define MLX90393_I2C_PORT i2c0
#define MLX90393_SDA_PIN 4
#define MLX90393_SCL_PIN 5

// Inicializar el sensor MLX90393
void mlx90393_init();

// Leer los valores de los ejes magnéticos
void mlx90393_read_magnetic_field(float *x, float *y, float *z);

#endif
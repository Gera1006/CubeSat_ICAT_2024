#include "mpu9250.h"
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include <stdio.h> // Para printf (si se usa en la inicialización o depuración)

// Inicializar el sensor MPU9250
void mpu9250_init() {
    uint8_t data[2];

    i2c_init(MPU9250_I2C_PORT, 100 * 1000); // 100 kHz
    gpio_set_function(MPU9250_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(MPU9250_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(MPU9250_SDA_PIN);
    gpio_pull_up(MPU9250_SCL_PIN);

    // Salir del modo de suspensión configurando el registro PWR_MGMT_1
    data[0] = MPU9250_PWR_MGMT_1;
    data[1] = 0x00;
    i2c_write_blocking(MPU9250_I2C_PORT, MPU9250_ADDR, data, 2, false);
}

// Función para leer datos de un registro específico del MPU9250
void mpu9250_read_register(uint8_t reg, uint8_t *buffer, size_t length) {
    i2c_write_blocking(MPU9250_I2C_PORT, MPU9250_ADDR, &reg, 1, true);
    i2c_read_blocking(MPU9250_I2C_PORT, MPU9250_ADDR, buffer, length, false);
}

// Función para leer la aceleración en los ejes X, Y y Z
void mpu9250_read_acceleration(float *ax, float *ay, float *az) {
    uint8_t buffer[6];
    // Leer 6 bytes de datos de los registros de aceleración
    mpu9250_read_register(MPU9250_ACCEL_XOUT_H, buffer, 6);

    // Convertir los datos crudos en valores de aceleración
    int16_t raw_ax = (buffer[0] << 8) | buffer[1];
    int16_t raw_ay = (buffer[2] << 8) | buffer[3];
    int16_t raw_az = (buffer[4] << 8) | buffer[5];

    float sensitivity = 16384.0; // Sensibilidad típica en ±2g
    *ax = raw_ax / sensitivity;
    *ay = raw_ay / sensitivity;
    *az = raw_az / sensitivity;
}
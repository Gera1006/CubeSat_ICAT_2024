#ifndef MPU9250_H
#define MPU9250_H

#include <stdint.h>
#include <stdbool.h>

// Dirección I2C del MPU9250
#define MPU9250_ADDR 0x68

// Registros del MPU9250
#define MPU9250_WHO_AM_I_REG 0x75
#define MPU9250_PWR_MGMT_1   0x6B
#define MPU9250_ACCEL_XOUT_H 0x3B

// Pines I2C (pueden ser configurados externamente)
#define MPU9250_I2C_PORT i2c0
#define MPU9250_SDA_PIN 4
#define MPU9250_SCL_PIN 5

// Inicializar el sensor MPU9250
void mpu9250_init();

// Leer datos de un registro específico del MPU9250
void mpu9250_read_register(uint8_t reg, uint8_t *buffer, size_t length);

// Leer la aceleración en los ejes X, Y y Z
void mpu9250_read_acceleration(float *ax, float *ay, float *az);

#endif
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

// Dirección I2C del MPU9250
#define MPU9250_ADDR 0x68
#define WHO_AM_I_REG 0x75
#define PWR_MGMT_1  0x6B
#define ACCEL_XOUT_H 0x3B

// Pines I2C
#define I2C_PORT i2c0
#define SDA_PIN 4
#define SCL_PIN 5

// Función para inicializar el MPU9250
void mpu9250_init() {
    uint8_t data[2];

    // Salir del modo de suspensión configurando el registro PWR_MGMT_1
    data[0] = PWR_MGMT_1;
    data[1] = 0x00;
    i2c_write_blocking(I2C_PORT, MPU9250_ADDR, data, 2, false);
}

// Función para leer datos de un registro específico del MPU9250
void mpu9250_read_register(uint8_t reg, uint8_t *buffer, size_t length) {
    i2c_write_blocking(I2C_PORT, MPU9250_ADDR, &reg, 1, true);
    i2c_read_blocking(I2C_PORT, MPU9250_ADDR, buffer, length, false);
}

// Función para leer la aceleración en los ejes X, Y y Z
void mpu9250_read_acceleration(float *ax, float *ay, float *az) {
    uint8_t buffer[6];
    // Leer 6 bytes de datos de los registros de aceleración
    mpu9250_read_register(ACCEL_XOUT_H, buffer, 6);

    // Convertir los datos crudos en valores de aceleración
    int16_t raw_ax = (buffer[0] << 8) | buffer[1];
    int16_t raw_ay = (buffer[2] << 8) | buffer[3];
    int16_t raw_az = (buffer[4] << 8) | buffer[5];

    float sensitivity = 16384.0; // Sensibilidad típica en ±2g
    *ax = raw_ax / sensitivity;
    *ay = raw_ay / sensitivity;
    *az = raw_az / sensitivity;
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

    // Inicializar el sensor MPU9250
    mpu9250_init();

    while (1) {
        float ax, ay, az;
        // Leer los valores de aceleración
        mpu9250_read_acceleration(&ax, &ay, &az);
        // Imprimir los valores de aceleración en la consola
        printf("Aceleración (g): X=%.2f, Y=%.2f, Z=%.2f\n", ax, ay, az);
        // Esperar 1 segundo antes de la siguiente lectura
        sleep_ms(1000);
    }

    return 0;
}

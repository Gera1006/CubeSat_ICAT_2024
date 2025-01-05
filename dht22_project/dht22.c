#include <stdio.h>
#include "pico/stdlib.h"

// Configuración del pin para el DHT22
#define DHT_PIN 15

// Función para leer datos del DHT22
int read_dht22(uint8_t *data) {
    uint32_t cycles[80];
    uint8_t index = 0, byte = 0, bit = 7;

    // Envío de señal inicial
    gpio_set_dir(DHT_PIN, GPIO_OUT);
    gpio_put(DHT_PIN, 0);
    sleep_ms(20);  // Mantener señal baja durante 20 ms
    gpio_put(DHT_PIN, 1);
    sleep_us(40);
    gpio_set_dir(DHT_PIN, GPIO_IN);  // Cambiar a modo entrada

    // Captura de ciclos para sincronización
    for (uint8_t i = 0; i < 80; i++) {
        while (gpio_get(DHT_PIN) == (i % 2) && cycles[i] < 1000) {
            cycles[i]++;
        }
        if (cycles[i] == 1000) {
            return -1;  // Timeout
        }
    }

    // Procesar datos recibidos
    for (uint8_t i = 0; i < 40; i++) {
        uint32_t high_time = cycles[2 * i + 1];
        data[index] |= (high_time > 50) << bit;
        if (bit == 0) {
            bit = 7;
            index++;
        } else {
            bit--;
        }
    }

    // Verificar checksum
    if (data[4] != ((data[0] + data[1] + data[2] + data[3]) & 0xFF)) {
        return -2;  // Error de checksum
    }

    return 0;  // Lectura exitosa
}

int main() {
    stdio_init_all();  // Inicializar comunicación USB para la consola
    gpio_init(DHT_PIN);
    gpio_pull_up(DHT_PIN);

    uint8_t data[5] = {0};

    while (1) {
        if (read_dht22(data) == 0) {
            float temperature = ((data[2] & 0x7F) << 8 | data[3]) * 0.1;
            if (data[2] & 0x80) temperature = -temperature;  // Si es negativo
            float humidity = (data[0] << 8 | data[1]) * 0.1;

            printf("Temperature: %.1f °C, Humidity: %.1f %%\n", temperature, humidity);
        } else {
            printf("Error reading DHT22\n");
        }

        sleep_ms(2000);  // Espera 2 segundos para la próxima lectura
    }
}

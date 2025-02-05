#include "dht22.h"

// Función para leer datos en bruto del DHT22
int read_dht22(uint8_t *data) {
    uint32_t cycles[80] = {0};
    uint8_t index = 0, byte = 0, bit = 7;

    // Envío de señal inicial
    gpio_set_dir(DHT_PIN, GPIO_OUT);
    gpio_put(DHT_PIN, 0);
    sleep_ms(20);
    gpio_put(DHT_PIN, 1);
    sleep_us(40);
    gpio_set_dir(DHT_PIN, GPIO_IN);

    // Captura de ciclos
    for (uint8_t i = 0; i < 80; i++) {
        while (gpio_get(DHT_PIN) == (i % 2) && cycles[i] < 1000) {
            cycles[i]++;
        }
        if (cycles[i] == 1000) return -1;  // Timeout
    }

    // Procesar datos
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

    return 0;  // Éxito
}

// Función para obtener temperatura y humedad
int get_dht22_data(float *temperature, float *humidity) {
    uint8_t data[5] = {0};

    if (read_dht22(data) == 0) {
        *temperature = ((data[2] & 0x7F) << 8 | data[3]) * 0.1;
        if (data[2] & 0x80) *temperature = -*temperature;  // Si es negativo
        *humidity = (data[0] << 8 | data[1]) * 0.1;
        return 0;
    }
    
    return -1;  // Error en la lectura
}
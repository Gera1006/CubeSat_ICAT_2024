#include "dht22.h"

int main() {
    stdio_init_all();
    gpio_init(DHT_PIN);
    gpio_pull_up(DHT_PIN);

    float temperature, humidity;

    while (1) {
        if (get_dht22_data(&temperature, &humidity) == 0) {
            printf("Temperature: %.1f °C, Humidity: %.1f %%\n", temperature, humidity);
        } else {
            printf("Error reading DHT22\n");
        }

        sleep_ms(2000);
    }
}
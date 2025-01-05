#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"

// Configuración de UART para el MAX-M10S
#define UART_ID uart1
#define BAUD_RATE 9600
#define UART_TX_PIN 8 // GP8 (TX Pico → RX MAX-M10S)
#define UART_RX_PIN 9 // GP9 (RX Pico ← TX MAX-M10S)

// Buffer para almacenar datos del GPS
#define BUFFER_SIZE 1024
char gps_buffer[BUFFER_SIZE];
int buffer_index = 0;

// Función para inicializar UART
void init_uart() {
    uart_init(UART_ID, BAUD_RATE); // Inicializar UART con la tasa de baudios especificada
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART); // Configurar el pin TX para UART
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART); // Configurar el pin RX para UART
    uart_set_fifo_enabled(UART_ID, true); // Habilitar FIFO de UART
}

// Función para leer datos del GPS
void read_gps_data() {
    while (uart_is_readable(UART_ID)) { // Verificar si hay datos disponibles en el UART
        char c = uart_getc(UART_ID); // Leer un carácter desde UART
        
        // Almacenar el carácter en el buffer si hay espacio disponible
        if (buffer_index < BUFFER_SIZE - 1) {
            gps_buffer[buffer_index++] = c;
            gps_buffer[buffer_index] = '\0'; // Agregar terminador nulo para formar una cadena válida
        }

        // Reiniciar el buffer si se detecta un fin de línea
        if (c == '\n') {
            printf("%s", gps_buffer); // Imprimir la línea completa (sentencias NMEA)
            buffer_index = 0; // Reiniciar el índice del buffer
        }
    }
}

int main() {
    // Inicializar GPIO, UART y stdio
    stdio_init_all(); // Inicializar todos los pines de E/S estándar
    init_uart(); // Inicializar UART

    printf("Inicializando MAX-M10S...\n");

    while (1) {
        // Leer datos del GPS y procesarlos
        read_gps_data();

        sleep_ms(100); // Reducir la carga del CPU esperando 100 ms
    }

    return 0;
}

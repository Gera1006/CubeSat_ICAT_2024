#include "max_m10s.h"
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include <stdio.h>
#include <string.h> // Para memset

// Buffer para almacenar datos del GPS
static char gps_buffer[MAX_M10S_BUFFER_SIZE];
static int buffer_index = 0;

// Función para inicializar UART
void max_m10s_init() {
    uart_init(MAX_M10S_UART_ID, MAX_M10S_BAUD_RATE); // Inicializar UART con la tasa de baudios especificada
    gpio_set_function(MAX_M10S_UART_TX_PIN, GPIO_FUNC_UART); // Configurar el pin TX para UART
    gpio_set_function(MAX_M10S_UART_RX_PIN, GPIO_FUNC_UART); // Configurar el pin RX para UART
    uart_set_fifo_enabled(MAX_M10S_UART_ID, true); // Habilitar FIFO de UART
}

// Función para leer datos del GPS
void max_m10s_read_data() {
    while (uart_is_readable(MAX_M10S_UART_ID)) { // Verificar si hay datos disponibles en el UART
        char c = uart_getc(MAX_M10S_UART_ID); // Leer un carácter desde UART

        // Almacenar el carácter en el buffer si hay espacio disponible
        if (buffer_index < MAX_M10S_BUFFER_SIZE - 1) {
            gps_buffer[buffer_index++] = c;
            gps_buffer[buffer_index] = '\0'; // Agregar terminador nulo para formar una cadena válida
        }

        // Reiniciar el buffer si se detecta un fin de línea
        if (c == '\n') {
            printf("%s", gps_buffer); // Imprimir la línea completa (sentencias NMEA)
            buffer_index = 0; // Reiniciar el índice del buffer
            memset(gps_buffer, 0, MAX_M10S_BUFFER_SIZE); // Limpiar el buffer
        }
    }
}

// Función para obtener el buffer de datos GPS (para acceder desde otros módulos)
char* max_m10s_get_buffer() {
    return gps_buffer;
}
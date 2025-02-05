#ifndef MAX_M10S_H
#define MAX_M10S_H

#include <stdint.h>
#include <stdbool.h>

// Configuración de UART para el MAX-M10S
#define MAX_M10S_UART_ID uart1
#define MAX_M10S_BAUD_RATE 9600
#define MAX_M10S_UART_TX_PIN 8 // GP8 (TX Pico → RX MAX-M10S)
#define MAX_M10S_UART_RX_PIN 9 // GP9 (RX Pico ← TX MAX-M10S)

// Buffer para almacenar datos del GPS
#define MAX_M10S_BUFFER_SIZE 1024

// Función para inicializar UART
void max_m10s_init();

// Función para leer datos del GPS
void max_m10s_read_data();

// Función para obtener el buffer de datos GPS (para acceder desde otros módulos)
char* max_m10s_get_buffer();

#endif
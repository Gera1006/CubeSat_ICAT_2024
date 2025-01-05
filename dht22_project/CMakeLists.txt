cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)

project(dht22_project)

pico_sdk_init()

add_executable(dht22
    dht22.c
)

# Include standard and hardware libraries
target_link_libraries(dht22 pico_stdlib hardware_gpio)

# Enable USB output, disable UART output
pico_enable_stdio_usb(dht22 1)
pico_enable_stdio_uart(dht22 0)

# Create additional outputs (UF2, bin, hex)
pico_add_extra_outputs(dht22)

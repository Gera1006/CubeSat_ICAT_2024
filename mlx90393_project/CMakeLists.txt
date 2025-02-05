cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)

project(mlx90393_project)

pico_sdk_init()

add_executable(mlx90393
    mlx90393_config.c
    mlx90393_ejemplo.c
)

target_link_libraries(mlx90393 pico_stdlib hardware_i2c)

pico_enable_stdio_usb(mlx90393 1)
pico_enable_stdio_uart(mlx90393 0)

pico_add_extra_outputs(mlx90393)

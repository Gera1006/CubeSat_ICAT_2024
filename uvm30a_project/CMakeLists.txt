cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)

project(uvm30a_project)

pico_sdk_init()

add_executable(uvm30a
    uvm30a.c
)

target_link_libraries(uvm30a pico_stdlib hardware_adc)

pico_enable_stdio_usb(uvm30a 1)
pico_enable_stdio_uart(uvm30a 0)

pico_add_extra_outputs(uvm30a)

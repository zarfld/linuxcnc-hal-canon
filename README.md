# linuxcnc-hal-canon

Helper library for implementing Canonical Device Interfaces (CDI) in LinuxCNC HAL components.

This library provides C structs and utility functions to simplify the creation of HAL components that follow the standard interfaces defined in the LinuxCNC HAL manual, such as:

- `digout` (digital output)
- `digin` (digital input)
- `adcout` (analog output)
- `adcin` (analog input)
- and others...

## Features

- Unified `struct` templates for canonical devices
- Helper functions for exporting HAL pins and parameters
- Optional registration of HAL functions (`hal_export_funct`)
- Supports components with or without runtime functions (e.g., logicless GPIOs)

## Example

```c
hal_digout_t led;
hal_export_digout(&led, "led", 0, comp_id);
led.write = hal_digout_default_write;
hal_register_digout_func("led.0", &led, "base-thread", 0);
```

##License
MIT 


---

## ✅ **CMakeLists.txt (minimal)**

```cmake
cmake_minimum_required(VERSION 3.5)
project(linuxcnc-hal-canon C)

add_library(halcanon
    src/hal_digout.c
)

target_include_directories(halcanon PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

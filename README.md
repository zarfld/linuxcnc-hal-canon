# hal_canon – Canonical Device Interface Helpers for LinuxCNC HAL

This library provides ready-to-use C structs and helper functions to export and register **Canonical Device Interfaces (CDI)** in [LinuxCNC](https://linuxcnc.org)'s HAL (Hardware Abstraction Layer).

The goal is to make HAL component development simpler, more robust, and consistent by enforcing the [canonical naming and behavior rules](https://linuxcnc.org/docs/html/hal/canonical-devices.html) defined by LinuxCNC.

---

## Features

- Unified `struct` templates for canonical devices
- Helper functions for exporting HAL pins and parameters
- Optional registration of HAL functions (`hal_export_funct`)
- Supports components with or without runtime functions (e.g., logicless GPIOs)

## ✨ Supported Interfaces

### ✅ Digital Input (`digin`)
| Pin Name       | Type | Description                         |
|----------------|------|-------------------------------------|
| `in`           | bit  | Direct input state                  |
| `in-not`       | bit  | Inverted input state                |

### ✅ Digital Output (`digout`)
| Name       | Type | Description                          |
|------------|------|--------------------------------------|
| `out`      | bit  | Output value                         |
| `invert`   | bit  | Inverts logic level if true (param)  |

### ✅ Analog Input (`adcin`)
| Name           | Type   | Description                         |
|----------------|--------|-------------------------------------|
| `value`        | float  | Scaled input value                  |
| `scale`        | float  | Multiplier                         |
| `offset`       | float  | Additive offset                    |
| `bit-weight`   | float  | Resolution of one LSB              |
| `hw-offset`    | float  | Value present at 0V input          |

### ✅ Analog Output (`adcout`)
| Name           | Type   | Description                         |
|----------------|--------|-------------------------------------|
| `value`        | float  | Desired analog output               |
| `enable`       | bit    | If false, output is forced to 0     |
| `scale`        | float  | Multiplier                         |
| `offset`       | float  | Additive offset                    |
| `high-limit`   | float  | Maximum output value               |
| `low-limit`    | float  | Minimum output value               |
| `bit-weight`   | float  | DAC resolution (e.g. volts per LSB)|
| `hw-offset`    | float  | Value produced at logical 0        |

### ✅ Encoder
| Name                | Type   | Description                             |
|---------------------|--------|-----------------------------------------|
| `count`             | s32    | Raw encoder count                       |
| `position`          | float  | Scaled position                         |
| `velocity`          | float  | Velocity estimate                       |
| `reset`             | bit    | Set to true to reset count              |
| `index-enable`      | bit    | Bidirectional handshake for index pulse |
| `scale`             | float  | Counts-to-position scale                |
| `max-index-vel`     | float  | Velocity limit for valid index reset    |
| `velocity-resolution` | float| Output resolution for velocity          |

---

## 🚀 How to Use

In your HAL component:

```c
#include "hal_canon.h"

hal_digin_t button;
hal_export_digin(&button, "gpio.0", 0, comp_id);
hal_register_digin_func("gpio.0", 0, my_read_function, &button, comp_id);


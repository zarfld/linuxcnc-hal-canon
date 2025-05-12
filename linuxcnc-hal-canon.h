#ifndef LINUXCNC_HAL_CANON_H
#define LINUXCNC_HAL_CANON_H

#include <hal.h>
#include <rtapi.h>
#include <rtapi_string.h>

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------
// Digital Input (digin)
// ----------------------
typedef struct {
    hal_bit_t *in;       // state of hardware input
    hal_bit_t *in_not;   // inverted state of input
    int (*read)(void *self); // optional function to update in/in_not from hardware
    void *user_data;
} hal_digin_t;

// ----------------------
// Digital Output (digout)
// ----------------------
typedef struct {
    hal_bit_t *out;       // value to be written
    hal_bit_t *invert;    // if TRUE, out is inverted before hardware write
    int (*write)(void *self); // optional function to write out/invert to hardware
    void *user_data;
} hal_digout_t;

// ----------------------
// Analog Input (adcin)
// ----------------------
typedef struct {
    hal_float_t *value;      // scaled and offset analog value
    hal_float_t *scale;      // multiplier
    hal_float_t *offset;     // subtraction after scaling
    hal_float_t *bit_weight; // value of one LSB
    hal_float_t *hw_offset;  // value present when 0V applied
    int (*read)(void *self); // optional read function
    void *user_data;
} hal_adcin_t;

// ----------------------
// Analog Output (adcout)
// ----------------------
typedef struct {
    hal_float_t *value;      // input to hardware (after scale/offset)
    hal_bit_t   *enable;     // if false, output 0
    hal_float_t *offset;     // added to value before hardware write
    hal_float_t *scale;      // scale applied to value
    hal_float_t *high_limit; // optional upper clamp
    hal_float_t *low_limit;  // optional lower clamp
    hal_float_t *bit_weight; // LSB value
    hal_float_t *hw_offset;  // physical output when 0 written
    int (*write)(void *self); // optional write function
    void *user_data;
} hal_adcout_t;

#ifdef __cplusplus
}
#endif

#endif // LINUXCNC_HAL_CANON_H

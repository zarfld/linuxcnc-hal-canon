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
    hal_bit_t *in;       // Pin: state of hardware input
    hal_bit_t *in_not;   // Pin: inverted state of input
    int (*read)(void *self); // optional function: to update in/in_not from hardware
    void *user_data;
} hal_digin_t;

// ----------------------
// Digital Output (digout)
// ----------------------
typedef struct {
    hal_bit_t *out;       // value to be written
    hal_bit_t invert;    // Parameter: if TRUE, out is inverted before hardware write
#ifdef RTAPI#ifdef RTAPI
    int (*write)(void *self); // optional function: to write out/invert to hardware
#endif
    void *user_data;
} hal_digout_t;

// ----------------------
// Analog Input (adcin)
// ----------------------
typedef struct {
    hal_float_t *value;      // Pin: scaled and offset analog value
    hal_float_t scale;      // Parameter: multiplier
    hal_float_t offset;     // Parameter: subtraction after scaling
    hal_float_t bit_weight; // Parameter: value of one LSB
    hal_float_t hw_offset;  // Parameter: value present when 0V applied
#ifdef RTAPI
    int (*read)(void *self); // optional function: read function
#endif
    void *user_data;
} hal_adcin_t;

// ----------------------
// Analog Output (adcout)
// ----------------------
typedef struct {
    hal_float_t *value;      // Pin: input to hardware (after scale/offset)
    hal_bit_t   *enable;     // Pin: if false, output 0
    hal_float_t *offset;     // Parameter: added to value before hardware write
    hal_float_t scale;      // Parameter: scale applied to value
    hal_float_t high_limit; // Parameter: optional upper clamp
    hal_float_t low_limit;  // Parameter: optional lower clamp
    hal_float_t bit_weight; // Parameter: LSB value
    hal_float_t hw_offset;  // Parameter: physical output when 0 written
#ifdef RTAPI
    int (*write)(void *self); // optional Function: write function
#endif
    void *user_data;
} hal_adcout_t;

// ----------------------
// Encoder (encoder)
// ----------------------
typedef struct {
    hal_s32_t    *count;               // Pin: raw encoder count
    hal_float_t  *position;            // Pin: scaled position
    hal_float_t  *velocity;            // Pin: velocity in pos-units/s
    hal_bit_t    *reset;               // Pin: force reset counter to 0
    hal_bit_t    *index_enable;        // Pin: handshake index reset
    hal_float_t  scale;               // Parameter: counts per position unit
    hal_float_t  max_index_vel;       // optional Parameter: max velocity for index reset
    hal_float_t  velocity_resolution; // optional Parameter: quantization step of velocity
#ifdef RTAPI
    int (*read)(void *self);           // optional Function: Capture counts, update position and velocity
#endif
    void *user_data;                   // for hardware context or state
} hal_encoder_t;

#ifdef __cplusplus
}
#endif

#endif // LINUXCNC_HAL_CANON_H

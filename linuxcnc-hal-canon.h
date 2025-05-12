#ifndef LINUXCNC_HAL_CANON_H
#define LINUXCNC_HAL_CANON_H

#include <hal.h>
#include <rtapi.h>
#include <rtapi_string.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup hal_digital Canonical Digital I/O
 * @brief Export and registration helpers for canonical digital input/output.
 * @{
 */

/**
 * @defgroup hal_digin Canonical Digital Input
 * @brief Canonical HAL interface for binary hardware inputs.
 *
 * The canonical digital input (`digin`) provides a standardized interface
 * for reading binary values from hardware. Drivers implementing this interface
 * must provide the following pins:
 *
 * - `in` (BIT):  state of the hardware input
 * - `in-not` (BIT): inverse of the input state
 *
 * No HAL parameters are defined.
 *
 * The optional `read` function should update both pins from hardware input.
 *
 * @see https://linuxcnc.org/docs/html/hal/canonical-devices.html#_digital_input
 */
typedef struct {
    hal_bit_t *in;       // Pin: state of hardware input
    hal_bit_t *in_not;   // Pin: inverted state of input
} hal_digin_t;

/**
 * @brief Export canonical digin pins & parameter.
 */
int hal_export_digin(hal_digin_t *digin, const char *prefix, int index, int comp_id);

/**
 * @brief Register canonical digin read function.
 */
#ifdef RTAPI
int hal_register_digin_func(const char *prefix, int index,
                            void (*read_func)(void *, long),
                            void *inst, int comp_id);
#endif


/**
 * @brief Canonical digital output interface struct.
 * @ingroup hal_digital
 *
 * This structure represents a single canonical digital output channel
 * as defined in the LinuxCNC HAL canonical device interface specification.
 *
 * ### Pins
 * - `out` (BIT, HAL_OUT): The output value to be written to hardware.
 *
 * ### Parameters
 * - `invert` (BIT, HAL_RW): If TRUE, the `out` value is inverted before being sent to hardware.
 *
 * ### Behavior
 * The optional `write` function (registered via `hal_register_digout_func`) should read the
 * `out` and `invert` fields and apply the resulting value to the real hardware.
 *
 * @see https://linuxcnc.org/docs/html/hal/canonical-devices.html#_digital_output
 */
typedef struct {
    hal_bit_t *out;       // value to be written
    hal_bit_t invert;    // Parameter: if TRUE, out is inverted before hardware write
} hal_digout_t;

/**
 * @brief Export canonical digout pins and parameters.
 */
int hal_export_digout(hal_digout_t *digout, const char *prefix, int index, int comp_id);

/**
 * @brief Register canonical digout write function.
 */
#ifdef RTAPI
int hal_register_digout_func(const char *prefix, int index,
                             void (*write_func)(void *, long),
                             void *inst, int comp_id);
#endif

/** @} */ // end of hal_digital

// ----------------------
// Analog Input (adcin)
// ----------------------
typedef struct {
    hal_float_t *value;      // Pin: scaled and offset analog value
    hal_float_t scale;      // Parameter: multiplier
    hal_float_t offset;     // Parameter: subtraction after scaling
    hal_float_t bit_weight; // Parameter: value of one LSB
    hal_float_t hw_offset;  // Parameter: value present when 0V applied
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


#ifdef RTAPI

#endif

#ifdef __cplusplus
}
#endif

#endif // LINUXCNC_HAL_CANON_H

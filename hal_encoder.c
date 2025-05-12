int hal_export_encoder(hal_encoder_t *enc, const char *prefix, int index, int comp_id) {
    int ret;
    char buf[HAL_NAME_LEN];

    // --- Pins ---

    // count
    rtapi_snprintf(buf, sizeof(buf), "%s.encoder.%d.count", prefix, index);
    ret = hal_pin_s32_newf(HAL_OUT, &enc->count, comp_id, buf);
    if (ret != 0) return ret;

    // position
    rtapi_snprintf(buf, sizeof(buf), "%s.encoder.%d.position", prefix, index);
    ret = hal_pin_float_newf(HAL_OUT, &enc->position, comp_id, buf);
    if (ret != 0) return ret;

    // velocity
    rtapi_snprintf(buf, sizeof(buf), "%s.encoder.%d.velocity", prefix, index);
    ret = hal_pin_float_newf(HAL_OUT, &enc->velocity, comp_id, buf);
    if (ret != 0) return ret;

    // reset
    rtapi_snprintf(buf, sizeof(buf), "%s.encoder.%d.reset", prefix, index);
    ret = hal_pin_bit_newf(HAL_IO, &enc->reset, comp_id, buf);
    if (ret != 0) return ret;

    // index-enable
    rtapi_snprintf(buf, sizeof(buf), "%s.encoder.%d.index-enable", prefix, index);
    ret = hal_pin_bit_newf(HAL_IO, &enc->index_enable, comp_id, buf);
    if (ret != 0) return ret;

    // --- Parameters ---

    // scale
    rtapi_snprintf(buf, sizeof(buf), "%s.encoder.%d.scale", prefix, index);
    ret = hal_param_float_newf(HAL_RW, &enc->scale, comp_id, buf);
    if (ret != 0) return ret;

    // max-index-vel
    rtapi_snprintf(buf, sizeof(buf), "%s.encoder.%d.max-index-vel", prefix, index);
    ret = hal_param_float_newf(HAL_RW, &enc->max_index_vel, comp_id, buf);
    if (ret != 0) return ret;

    // velocity-resolution
    rtapi_snprintf(buf, sizeof(buf), "%s.encoder.%d.velocity-resolution", prefix, index);
    ret = hal_param_float_newf(HAL_RW, &enc->velocity_resolution, comp_id, buf);
    if (ret != 0) return ret;

    return 0;
}

int hal_register_encoder_func(const char *prefix, int index,
                              void (*read_func)(void *, long),
                              void *inst, int comp_id) {
    if (!read_func) return 0;

    char buf[HAL_NAME_LEN];
    rtapi_snprintf(buf, sizeof(buf), "%s.encoder.%d.read", prefix, index);

    return hal_export_funct(buf, read_func, inst, 1, 0, comp_id);  // uses_fp = 1
}

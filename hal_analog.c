int hal_export_adcin(hal_adcin_t *adcin, const char *prefix, int index, int comp_id) {
    int ret;
    char buf[HAL_NAME_LEN];

    // value (output)
    rtapi_snprintf(buf, sizeof(buf), "%s.adcin.%d.value", prefix, index);
    ret = hal_pin_float_newf(HAL_OUT, &adcin->value, comp_id, buf);
    if (ret != 0) return ret;

    // scale
    rtapi_snprintf(buf, sizeof(buf), "%s.adcin.%d.scale", prefix, index);
    ret = hal_param_float_newf(HAL_RW, &adcin->scale, comp_id, buf);
    if (ret != 0) return ret;

    // offset
    rtapi_snprintf(buf, sizeof(buf), "%s.adcin.%d.offset", prefix, index);
    ret = hal_param_float_newf(HAL_RW, &adcin->offset, comp_id, buf);
    if (ret != 0) return ret;

    // bit_weight
    rtapi_snprintf(buf, sizeof(buf), "%s.adcin.%d.bit-weight", prefix, index);
    ret = hal_param_float_newf(HAL_RW, &adcin->bit_weight, comp_id, buf);
    if (ret != 0) return ret;

    // hw_offset
    rtapi_snprintf(buf, sizeof(buf), "%s.adcin.%d.hw-offset", prefix, index);
    ret = hal_param_float_newf(HAL_RW, &adcin->hw_offset, comp_id, buf);
    if (ret != 0) return ret;

    return 0;
}

int hal_register_adcin_func(const char *prefix, int index,
                            void (*read_func)(void *, long),
                            void *inst, int comp_id) {
    if (!read_func) return 0;

    char buf[HAL_NAME_LEN];
    rtapi_snprintf(buf, sizeof(buf), "%s.adcin.%d.read", prefix, index);

    return hal_export_funct(buf, read_func, inst, 1, 0, comp_id);
}

int hal_export_adcout(hal_adcout_t *adcout, const char *prefix, int index, int comp_id) {
    int ret;
    char buf[HAL_NAME_LEN];

    // value
    rtapi_snprintf(buf, sizeof(buf), "%s.adcout.%d.value", prefix, index);
    ret = hal_pin_float_newf(HAL_IN, &adcout->value, comp_id, buf);
    if (ret != 0) return ret;

    // enable
    rtapi_snprintf(buf, sizeof(buf), "%s.adcout.%d.enable", prefix, index);
    ret = hal_pin_bit_newf(HAL_IN, &adcout->enable, comp_id, buf);
    if (ret != 0) return ret;

    // offset
    rtapi_snprintf(buf, sizeof(buf), "%s.adcout.%d.offset", prefix, index);
    ret = hal_param_float_newf(HAL_RW, &adcout->offset, comp_id, buf);
    if (ret != 0) return ret;

    // scale
    rtapi_snprintf(buf, sizeof(buf), "%s.adcout.%d.scale", prefix, index);
    ret = hal_param_float_newf(HAL_RW, &adcout->scale, comp_id, buf);
    if (ret != 0) return ret;

    // high_limit
    rtapi_snprintf(buf, sizeof(buf), "%s.adcout.%d.high-limit", prefix, index);
    ret = hal_param_float_newf(HAL_RW, &adcout->high_limit, comp_id, buf);
    if (ret != 0) return ret;

    // low_limit
    rtapi_snprintf(buf, sizeof(buf), "%s.adcout.%d.low-limit", prefix, index);
    ret = hal_param_float_newf(HAL_RW, &adcout->low_limit, comp_id, buf);
    if (ret != 0) return ret;

    // bit_weight
    rtapi_snprintf(buf, sizeof(buf), "%s.adcout.%d.bit-weight", prefix, index);
    ret = hal_param_float_newf(HAL_RW, &adcout->bit_weight, comp_id, buf);
    if (ret != 0) return ret;

    // hw_offset
    rtapi_snprintf(buf, sizeof(buf), "%s.adcout.%d.hw-offset", prefix, index);
    ret = hal_param_float_newf(HAL_RW, &adcout->hw_offset, comp_id, buf);
    if (ret != 0) return ret;

    return 0;
}

int hal_register_adcout_func(const char *prefix, int index,
                             void (*write_func)(void *, long),
                             void *inst, int comp_id) {
    if (!write_func) return 0;

    char buf[HAL_NAME_LEN];
    rtapi_snprintf(buf, sizeof(buf), "%s.adcout.%d.write", prefix, index);

    return hal_export_funct(buf, write_func, inst, 1, 0, comp_id);
}

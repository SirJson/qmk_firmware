#ifdef RGB_MATRIX_KEYREACTIVE_ENABLED

RGB_MATRIX_EFFECT(REACTIVE_SAT)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static HSV REACTIVE_SAT_math(HSV hsv, int16_t dx, int16_t dy, uint8_t dist, uint16_t tick) {
    uint16_t effect = tick - dist;
    if (effect > 255) effect = 255;
    if (dist > 72) effect = 255;
    if ((dx > 8 || dx < -8) && (dy > 8 || dy < -8)) effect = 255;
    hsv.h = rgb_matrix_config.hsv.h + dy / 4;
    hsv.s = qadd8(hsv.s, 255 - effect);
    return hsv;
}

static bool REACTIVE_SAT(effect_params_t* params) {
    return effect_runner_reactive_splash(0, params, &REACTIVE_SAT_math);
}


#endif
#endif

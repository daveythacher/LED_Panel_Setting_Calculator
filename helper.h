#ifndef HELPER_H
#define HELPER_H

#include <stdint.h>
#include "config.h"

static uint8_t get_max_dot_correction_bits() {
    float target = 1.0 - max_dot_correction_accuracy;

    for (uint8_t i = 1; i <= 7; i++) {
        float num = 1.0 / (1 << i);

        if (num < target)
            return i;
    }

    return 0;
}

#endif
#include <iostream>
#include "helper.h"

int main(int argc, char **argv) {
    if (target_cols) {
        cols_low = target_cols;
        cols_high = target_cols;
    }

    if (target_refresh) {
        refresh_low = target_refresh;
        refresh_high = target_refresh;
    }

    if (target_scan) {
        scan_low = target_scan;
        scan_high = target_scan;
    }

    if (isS_PWM) {
        min_bpp_bits_low = std::max((int16_t) s_pwm_bits_per_seg - (int16_t) get_min_dot_correction_bits(), 1);
    }

    std::cout << "Valid results will be shown below: (LED Driver Generation ";
        std::cout << (int) LED_driver_generation << ")" << std::endl;

    switch (LED_driver_generation) {
        case 1:
            process_gen1();
            break;
        case 2:
            process_gen2();
            break;
        case 3:
            process_gen3();
        default:
            break;
    }

    std::cout << result_counter << " Results found" << std::endl;

    return 0;
}
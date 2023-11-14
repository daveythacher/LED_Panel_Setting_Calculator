#include <algorithm>
#include "helper.h"

static bool is_clk_valid(uint8_t scan, uint16_t cols, uint16_t refresh, uint8_t bits, float *clk_mhz) {
    uint64_t temp = cols / columns_per_driver;
    temp *= max_impedance * fanout_per_clk * min_harmonics * max_par_cap_pf;
    float hz_limit = 1000000.0 / (temp * 1.0);
    hz_limit = std::min(max_clk_mhz, hz_limit) * 1000000;
    *clk_mhz = hz_limit / 1000000.0;
    hz_limit /= refresh * get_refresh_overhead(scan, refresh, bits) * cols * scan * (1 << (bits + get_min_dot_correction_bits()));
    *clk_mhz /= hz_limit;
    return hz_limit >= 1.0;
}

static bool is_grayscale_valid(uint8_t scan, uint16_t cols, uint16_t refresh, uint8_t bits) {
    return ((1 << max_grayscale_bits) / ((1 << (bits + get_min_dot_correction_bits())) * scan)) >= 1;
}

static bool is_gen_1_valid(uint8_t scan, uint16_t cols, uint16_t refresh, uint8_t bits, float *clk_mhz, float *gclk_mhz, float *brightness) {
    float led_rise_us = (max_led_impedance * min_led_harmonics * max_led_cap_pf * scan) / 1000000.0;
    float period_us = 1000000.0 / (refresh * scan);
    *gclk_mhz = 0.0;

    if (isBCM)
        *brightness = (period_us - (led_rise_us * (bits + get_min_dot_correction_bits())) - blank_time_us) / period_us;
    else
        *brightness = (period_us - led_rise_us - blank_time_us) / period_us;

    return (is_clk_valid(scan, cols, refresh, bits, clk_mhz) &&
        *brightness > target_brightness &&
        is_grayscale_valid(scan, cols, refresh, bits));
}

void process_gen1() {
    // Order of bottlneck: refresh, multiplexing, grayscale, pixels.
    for (uint16_t refresh = refresh_low; refresh <= refresh_high; refresh += 100) {
        for (uint8_t scan = scan_low; scan <= scan_high; scan *= 2) {
            for (uint8_t bits = min_bpp_bits_low; bits <= max_grayscale_bits; bits++) {
                for (uint16_t cols = cols_low; cols <= cols_high; cols *= 2) {
                    float clk, gclk, brightness;

                    if ((scan * 2 > cols) && !showAll)
                        continue;
                    else if (is_gen_1_valid(scan, cols, refresh, bits, &clk, &gclk, &brightness))
                        print_result(scan, cols, refresh, bits, clk, gclk, brightness);
                    else 
                        break;
                }
            }
        }
    }
}
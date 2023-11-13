#include <algorithm>
#include "helper.h"
#include "config.h"

static bool is_clk_valid(uint8_t scan, uint16_t cols, uint16_t refresh, uint8_t bits) {
    uint64_t temp = cols / columns_per_driver;
    temp *= max_impedance * fanout_per_clk * min_harmonics * max_par_cap_pf;
    float hz_limit = 1000000.0 / (temp * 1.0);
    hz_limit = std::min(max_clk_mhz, hz_limit) * 1000000;
    hz_limit /= refresh * cols * scan;
    if (is12bitTi)
        hz_limit /= 12;
    else
        hz_limit /= 16;
    return hz_limit >= 1.0;
}

static bool is_gclk_valid(uint8_t scan, uint16_t cols, uint16_t refresh, uint8_t bits) {
    uint64_t temp = cols / columns_per_driver;
    temp *= max_impedance * fanout_per_gclk * min_harmonics * max_par_cap_pf;
    float hz_limit = 1000000.0 / (temp * 1.0);
    hz_limit = std::min(max_gclk_mhz, hz_limit) * 1000000;
    hz_limit /= refresh * (1.0 + refresh_overhead) * scan * (1 << (bits + get_max_dot_correction_bits()));
    return hz_limit >= 1.0;
}

static bool is_grayscale_valid(uint8_t scan, uint16_t cols, uint16_t refresh, uint8_t bits) {
    return ((1 << max_grayscale_bits) / ((1 << (bits + get_max_dot_correction_bits())) * scan)) >= 1;
}

static bool is_gen_2_valid(uint8_t scan, uint16_t cols, uint16_t refresh, uint8_t bits) {
    return (is_clk_valid(scan, cols, refresh, bits) &&
        is_gclk_valid(scan, cols, refresh, bits) &&
        is_grayscale_valid(scan, cols, refresh, bits));
}

void process_gen2() {
    // Order of bottlneck: pixels, multiplexing, refresh, grayscale.
    for (uint16_t cols = cols_low; cols <= cols_high; cols *= 2) {
        for (uint8_t scan = scan_low; scan <= scan_high; scan *= 2) {
            for (uint16_t refresh = refresh_low; refresh <= refresh_high; refresh += 100) {
                for (uint8_t bits = min_bpp_bits; bits <= max_grayscale_bits; bits++) {
                    if ((scan * 2 > cols) && !showAll)
                        continue;
                    else if (is_gen_2_valid(scan, cols, refresh, bits))
                        print_result(scan, cols, refresh, bits);
                    else 
                        break;
                }
            }
        }
    }
}
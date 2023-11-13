#include <iostream>
#include "helper.h"

uint16_t cols_low = columns_per_driver;
uint16_t cols_high = 2048;
uint16_t refresh_low = 100;
uint16_t refresh_high = max_refresh_hz;
uint8_t scan_low = 1;
uint8_t scan_high = 32;
uint8_t min_bpp_bits_low = min_bpp_bits;
uint32_t result_counter = 0;

uint8_t get_min_dot_correction_bits() {
    float target = 1.0 - min_dot_correction_accuracy;

    for (uint8_t i = 1; i <= 7; i++) {
        float num = 1.0 / (1 << i);

        if (num < target)
            return i;
    }

    return 0;
}

float get_refresh_overhead(uint8_t scan, uint16_t refresh, uint8_t bits) {
    float refresh_overhead = 1000000.0 / (scan * refresh);
    if (isS_PWM)
        refresh_overhead /= 1 << std::max((int16_t) bits - (int16_t) s_pwm_bits_per_seg + (int16_t) get_min_dot_correction_bits(), 0);
    refresh_overhead /= refresh_overhead - blank_time_us;
    return refresh_overhead;
}

void print_result(uint8_t scan, uint16_t cols, uint16_t refresh, uint8_t bits, float clk_mhz, float gclk_mhz) {
    std::cout << "\t Columns: " << cols;
    std::cout << "\t Scan: " << (int) scan;
    std::cout << "\t Pixels: " << scan * 2 * cols;
    std::cout << "\t Configuration: " << scan * 2 << "x" << cols;
    std::cout << "\t Refresh: " << refresh;
    std::cout << "\t Bits per color: " << (int) bits;
    std::cout << "\t Steps per LED: " << (1 << (get_min_dot_correction_bits() + bits)) * scan;
    std::cout << "\t Clock (MHz): " << clk_mhz;
    if (gclk_mhz != 0.0)
        std::cout << "\t Grayscale Clock (MHz): " << gclk_mhz;
    std::cout << std::endl;
    ++result_counter;
}
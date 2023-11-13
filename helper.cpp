#include <iostream>
#include "helper.h"
#include "config.h"

uint16_t cols_low = columns_per_driver;
uint16_t cols_high = 2048;
uint16_t refresh_low = 100;
uint16_t refresh_high = max_refresh_hz;
uint8_t scan_low = 1;
uint8_t scan_high = 32;

uint8_t get_max_dot_correction_bits() {
    float target = 1.0 - min_dot_correction_accuracy;

    for (uint8_t i = 1; i <= 7; i++) {
        float num = 1.0 / (1 << i);

        if (num < target)
            return i;
    }

    return 0;
}

void print_result(uint8_t scan, uint16_t cols, uint16_t refresh, uint8_t bits) {
    std::cout << "Columns " << cols << " - Scan " << (int) scan;
    std::cout << " - Pixels " << scan * 2 * cols;
    std::cout << " - " << scan * 2 << "x" << cols;
    std::cout << " - Refresh " << refresh;
    std::cout << " - Bits per color " << (int) bits << std::endl;
}

void init() {
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
}
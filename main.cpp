#include <iostream>
#include "config.h"
using namespace std;

extern bool is_gen_1_valid(uint8_t scan, uint16_t cols, uint16_t refresh, uint8_t bits);
extern bool is_gen_2_valid(uint8_t scan, uint16_t cols, uint16_t refresh, uint8_t bits);
extern bool is_gen_3_valid(uint8_t scan, uint16_t cols, uint16_t refresh, uint8_t bits);

int main(int argc, char **argv) {
    uint16_t cols_low = columns_per_driver;
    uint16_t cols_high = 2048;
    uint16_t refresh_low = 100;
    uint16_t refresh_high = max_refresh_hz;
    uint8_t scan_low = 1;
    uint8_t scan_high = 32;

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

    for (uint8_t bits = min_bpp_bits; bits <= max_grayscale_bits; bits++) {
        for (uint16_t refresh = refresh_low; refresh <= refresh_high; refresh += 100) {
            for (uint8_t scan = scan_low; scan <= scan_high; scan *= 2) {
                for (uint16_t cols = cols_low; cols <= cols_high; cols *= 2) {
                    bool isValid = false;

                    if ((scan * 2 > cols) && !showAll)
                        continue;

                    switch (LED_driver_generation) {
                        case 1:
                            isValid = is_gen_1_valid(scan, cols, refresh, bits);
                            break;
                        case 2:
                            isValid = is_gen_2_valid(scan, cols, refresh, bits);
                            break;
                        case 3:
                            isValid = is_gen_3_valid(scan, cols, refresh, bits);
                            break;
                        default:
                            break;
                    }

                    if (isValid) {
                        cout << "Columns " << cols << " - Scan " << (int) scan;
                        cout << " - Pixels " << scan * 2 * cols;
                        cout << " - " << scan * 2 << "x" << cols;
                        cout << " - Refresh " << refresh;
                        cout << " - Bits per color " << (int) bits << endl;
                    }
                    else {
                        break;
                    }
                }
            }
        }
    }

    return 0;
}
#ifndef HELPER_H
#define HELPER_H

#include <stdint.h>
#include "config.h"

void process_gen1();
void process_gen2();
void process_gen3();

uint8_t get_min_dot_correction_bits();
void print_result(uint8_t scan, uint16_t cols, uint16_t refresh, uint8_t bits, float clk_mhz, float gclk_mhz);

extern uint16_t cols_low;
extern uint16_t cols_high;
extern uint16_t refresh_low;
extern uint16_t refresh_high;
extern uint8_t scan_low;
extern uint8_t scan_high;
extern uint32_t result_counter;
#endif
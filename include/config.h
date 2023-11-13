#ifndef CONFIG_H
#define CONFIG_H

// Panel constants
constexpr float max_clk_mhz = 25.0;
constexpr float max_gclk_mhz = 25.0;
constexpr uint16_t max_grayscale_bits = 12;
constexpr uint8_t columns_per_driver = 16;
constexpr uint8_t fanout_per_clk = 6;
constexpr uint8_t fanout_per_gclk = 1;
constexpr uint8_t max_impedance = 50;
constexpr uint8_t max_par_cap_pf = 15;
constexpr uint8_t min_harmonics = 5;

// Application information
constexpr uint8_t LED_driver_generation = 3;
constexpr bool is12bitTi = false;
constexpr uint8_t frames_per_second = 30;
constexpr uint16_t max_refresh_hz = 3000;
constexpr float min_dot_correction_accuracy = 0.9;
constexpr float refresh_overhead = 0.3;


// Search parameters
constexpr uint8_t min_bpp_bits = 1;
constexpr uint16_t target_cols = 32;
constexpr uint16_t target_refresh = 3000;
constexpr uint8_t target_scan = 0;
constexpr bool showAll = false;

#endif
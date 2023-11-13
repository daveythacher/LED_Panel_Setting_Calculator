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
constexpr float min_dot_correction_accuracy = 0.9;
constexpr uint8_t blank_time_us = 10;
constexpr uint16_t max_refresh_hz = 3000;


// Application information
constexpr uint8_t LED_driver_generation = 3;
constexpr bool isS_PWM = true;                  // Required by most Generation 3 LED drivers and some Generation 2 LED Drivers
constexpr uint8_t s_pwm_bits_per_seg = 7;

// Application information (Generation 2 only)
constexpr bool is12bitTi = false;

// Application information (Generation 3 only)
constexpr uint8_t frames_per_second = 30;


// Search parameters
constexpr uint8_t min_bpp_bits = 1;             // Range: 1 to max_grayscale_bits
constexpr uint16_t target_cols = 0;             // To exclude parameter for filter set to zero
constexpr uint16_t target_refresh = 0;          // To exclude parameter for filter set to zero
constexpr uint8_t target_scan = 0;              // To exclude parameter for filter set to zero
constexpr bool showAll = false;                 // By default will only show valid HUB75 chains


// Comments:
//  You really do not want more than 4096 or 8192 pixels per HUB75 chain
//  Most Generation 2 and 3 LED drivers are happy with 1, 2, 4 or 8 scan configurations.
//  Generation 1 LED drivers care less about scan and support 1, 2, 4, 8. 16 and 32 scan configurations.

#endif
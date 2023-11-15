#ifndef CONFIG_H
#define CONFIG_H

// Panel constants
constexpr float max_clk_mhz = 25.0;
constexpr float max_gclk_mhz = 33.0;
constexpr uint8_t columns_per_driver = 16;
constexpr uint8_t fanout_per_clk = 6;
constexpr uint8_t fanout_per_gclk = 1;
constexpr uint8_t max_impedance = 50;
constexpr uint8_t max_par_cap_pf = 15;
constexpr uint8_t min_harmonics = 5;
constexpr uint8_t blank_time_us = 10;
constexpr uint16_t max_refresh_hz = 3000;


// LED constants
constexpr float min_dot_correction_accuracy = 0.96; // Reserve bits for dot correction (optional)
constexpr uint16_t max_led_impedance = 500;
constexpr uint8_t max_led_cap_pf = 15;
constexpr uint8_t min_led_harmonics = 5;


// Application information
constexpr uint8_t LED_driver_generation = 2;
constexpr uint16_t max_grayscale_bits = 12;
constexpr bool isS_PWM = false;                     // Required by most Generation 3 LED drivers and some Generation 2 LED Drivers
constexpr uint8_t s_pwm_bits_per_seg = 8;

// Application information (Generation 1 only)
constexpr bool isBCM = false;

// Application information (Generation 2 only)
constexpr bool is12bitTi = true;

// Application information (Generation 3 only)
constexpr uint8_t frames_per_second = 30;


// Search parameters
constexpr uint8_t min_bpp_bits = 1;                 // Range: 1 to max_grayscale_bits
constexpr uint16_t target_cols = 32;                // To exclude parameter from filter set to zero
constexpr uint16_t target_refresh = 3000;           // To exclude parameter from filter set to zero
constexpr uint8_t target_scan = 8;                  // To exclude parameter from filter set to zero
constexpr float target_brightness = 0.7;            // To exclude parameter from filter set to zero
constexpr bool showAll = false;                     // By default will only show valid HUB75 chains

#endif
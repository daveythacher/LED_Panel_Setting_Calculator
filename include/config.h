#ifndef CONFIG_H
#define CONFIG_H

// Panel constants
constexpr float max_clk_mhz = 25.0;
constexpr float max_gclk_mhz = 33.0;
constexpr uint8_t columns_per_driver = 16;
constexpr uint8_t fanout_per_clk = 6;
constexpr uint8_t fanout_per_gclk = 1;
constexpr uint8_t max_impedance = 50;               // For longer chains may need custom circuit board which adjusts this
constexpr uint8_t max_par_cap_pf = 16;              // For longer chains may need custom circuit board which adjusts this
constexpr uint8_t min_harmonics = 5;
constexpr uint8_t blank_time_us = 1;                // For high refresh rate you may need to increase this
constexpr uint16_t max_refresh_hz = 3000;


// LED constants
constexpr float min_dot_correction_accuracy = 0;    // Reserve bits for dot correction (optional)
constexpr uint16_t max_led_impedance = 500;
constexpr uint8_t max_led_cap_pf = 15;
constexpr uint8_t min_led_harmonics = 5;


// Application information
constexpr uint8_t LED_driver_generation = 1;
constexpr uint16_t max_grayscale_bits = 12;
constexpr bool isS_PWM = false;                     // Required by most Generation 3 LED drivers and some Generation 2 LED Drivers
                                                        // Do not use with Generation 1 LED drivers
constexpr uint8_t s_pwm_bits_per_seg = 6;

// Application information (Generation 1 only)
constexpr bool isBCM = false;

// Application information (Generation 2 only)
constexpr bool is12bitTi = true;

// Application informtation (Generation 3 only)
constexpr uint8_t frames_per_second = 30;


// Search parameters
constexpr uint8_t min_bpp_bits = 1;                 // Range: 1 to max_grayscale_bits
constexpr uint16_t target_cols = 0;                 // To exclude parameter from filter set to zero
constexpr uint16_t target_refresh = 0;              // To exclude parameter from filter set to zero
constexpr uint8_t target_scan = 0;                  // To exclude parameter from filter set to zero
constexpr float target_brightness = 0.7;            // To exclude parameter from filter set to zero
constexpr bool showAll = false;                     // By default will only show valid HUB75 chains


/*
    S-PWM is a technology used to reduce the PWM period.
    For example a 16 bit PWM counter on 25MHz only supports 381Hz which will flicker.
        To avoid flicker this PWM counter needs to be 12 bit.
    S-PWM divide the counter into sub counter bins which are evenly filled.
        This allows the software to call into however many bins it needs.
    8+8 S-PWM would allow a 16 bit counter to become 8, 9, 10, 11, 12, 13, 14, 15 or 16 bit counter.
        This not for free as you have a higher multiplexing rate for the same refresh and frame rate.

    Generation 1 LED drivers can change the PWM counter in software and therefore never need S-PWM.
*/

/*
    Studies have suggested that a refresh rate of at least 90Hz be used, however some people are 
        still capable of seeing flicker at this range.

    Stroboscopic effect is noted to be visible at very high frequencies requiring refresh rates
        as high as 1500 to 3000Hz.

    Cameras with fast shutters are capable of seeing lower refresh rates, but this generally
        reduces the amount of color depth available. Note the image shown may be not be lit
        evenly or accurate capture the image shown by the camera operator.
*/

#endif
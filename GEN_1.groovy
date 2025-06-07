package LED_Panel_Setting_Calculator

class GEN_1 extends Panel_Calculator {
    // Check multiplex, PMOS(s), driver(s) and LED array
    public boolean is_valid(short scan, int cols, int refresh, short bits) {
        double led_rise_us = (
            // Low side capacitors (Thru LEDs) - Turn on
            (max_led_column_impedance * min_led_harmonics * max_led_cap_pf * scan) / 1000000.0 +
            // High side capacitors
            (max_led_row_impedance * min_led_harmonics * max_led_cap_pf * cols) / 1000000.0
        );
        double led_fall_us = Math.max(
            // Low side capacitors (Thru LEDs) - Turn off
            (max_led_column_pullup * min_led_harmonics * max_led_cap_pf * scan) / 1000000.0,
            // High side capacitors
            (max_led_row_pulldown * min_led_harmonics * max_led_cap_pf * cols) / 1000000.0,
        );
        double period_us = 1000000.0 / (refresh * scan);
        brightness = period_us / (period_us + led_rise_us + led_fall_us);
        gclk_mhz = 0.0;
        clk_mhz = 0.0;

        return is_clk_valid(scan, cols, refresh, bits, brightness) &&
            is_multiplex_valid(scan, refresh, bits) &&
            is_gclk_valid(Math.max(
                (max_led_column_pullup * min_led_harmonics * max_led_cap_pf * scan) / 1000000.0, 
                (max_led_column_impedance * min_led_harmonics * max_led_cap_pf * scan) / 1000000.0), 
                scan, refresh, bits);
    }

    // Check multiplexer and PMOS - Must complete in single GCLK
    private boolean is_multiplex_valid(short scan, int refresh, short bits) {
        double clock_period_us = 1000000.0 / scan * refresh;
        double multiplex_rise_us = max_multiplex_charge_impedance * max_multiplex_gate_pf * min_multiplex_harmonics / 1000000.0;
        double multiplex_fall_us = max_multiplex_discharge_impedance * max_multiplex_gate_pf * min_multiplex_harmonics / 1000000.0;
        clock_period_us /= 1 << (bits + 1);

        return (multiplex_rise_us + multiplex_fall_us) < clock_period_us;
    }

    // Check low side discharge - Must complete in single GCLK
    private boolean is_gclk_valid(double uS, short scan, int refresh, short bits) {
        double temp = 1000000.0 / refresh;
        temp /= 1 << bits;
        temp /= scan;

        return temp > uS;
    }

    // Check Driver communications - Find max clock and verify configuration
    private boolean is_clk_valid(short scan, int cols, int refresh, short bits, double dimming) {
        // Calculate number of LED drivers in series.
        double temp = cols / columns_per_driver;
        
        // Calculate the cutoff period including subharmonics.
        temp *= max_impedance * fanout_per_clk * min_harmonics * max_par_cap_pf;

        // Calculate the max driver frequency
        double hz_limit = 1000000000000.0 / (temp * 1.0);
        hz_limit = Math.min(max_clk_mhz * 1000000.0, hz_limit);
        clk_mhz = hz_limit / 1000000.0;

        // Adjust the max driver frequency using settings
        hz_limit /= refresh;
        hz_limit /= cols;
        hz_limit /= scan;
        hz_limit /= (1 << bits);
        hz_limit *= dimming;

        // True, if a valid driver frequency was found
        return hz_limit >= 1.0;
    }
}

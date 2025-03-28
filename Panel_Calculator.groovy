package LED_Panel_Setting_Calculator

abstract class Panel_Calculator {
    public abstract boolean is_valid(short scan, int cols, int refresh, short bits);

    public double get_refresh_overhead(short scan, int refresh, short bits, boolean isS_PWM) {
        double refresh_overhead = 1000000.0 / (scan * refresh);
        if (isS_PWM)
            refresh_overhead /= 1 << Math.max((short) bits - (short) s_pwm_bits_per_seg + (short) get_min_dot_correction_bits(), 0);
        refresh_overhead /= refresh_overhead - blank_time_us;
        return refresh_overhead;
    }

    public short get_min_dot_correction_bits() {
        double target = 1.0 - min_dot_correction_accuracy;

        for (short i = 0; i <= 7; i++) {
            double num = 1.0 / (1 << i);

            if (num <= target)
                return i;
        }

        return 0;
    }

    public double clk_mhz;
    public double gclk_mhz;
    public double brightness;

    // Panel constants
    public double max_clk_mhz = 25.0;
    public double max_gclk_mhz = 33.0;
    public short columns_per_driver = 16;
    public short fanout_per_clk = 6;
    public short fanout_per_gclk = 6;
    public short max_impedance = 50;                   // For longer chains may need custom circuit board which adjusts this
    public short max_par_cap_pf = 16;                  // For longer chains may need custom circuit board which adjusts this
    public short min_harmonics = 10;                   // This should be at least 10 for square waves
    public short blank_time_us = 1;                    // For high refresh rate you may need to increase thi

    // LED constants
    public double min_dot_correction_accuracy = 0;     // Reserve bits for dot correction (optional)
    public int max_led_impedance = 500;
    public short max_led_cap_pf = 15;
    public short min_led_harmonics = 5;
}
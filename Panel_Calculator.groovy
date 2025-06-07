package LED_Panel_Setting_Calculator

// TODO: Clean this up
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
    public short columns_per_driver = 8;
    public short fanout_per_clk = 6;
    public short fanout_per_gclk = 1;
    public short max_impedance = 50;                   // For longer chains may need custom circuit board which adjusts this
    public short max_par_cap_pf = 30;                  // For longer chains may need custom circuit board which adjusts this
    public short min_harmonics = 10;                   // This should be at least 10 for square waves
    public short blank_time_us = 1;                    // For high refresh rate you may need to increase this // TODO: remove

    // LED constants
    public double min_dot_correction_accuracy = 0;     // Reserve bits for dot correction (optional) // TODO: remove remove
    public int max_led_column_impedance = 980;
    public int max_led_row_impedance = 5;
    public int max_led_column_pullup = 1000;
    public int max_led_row_pulldown = 10000;
    public short max_led_cap_pf = 30;
    public short min_led_harmonics = 5;

    // Multiplexer constants
    public int max_multiplex_gate_pf = 200;
    public int max_multiplex_discharge_impedance = 50;
    public int max_multiplex_charge_impedance = 50;
    public int min_multiplex_harmonics = 5;
}

package LED_Panel_Setting_Calculator

class GEN_3 extends Panel_Calculator {
    public boolean is_valid(short scan, int cols, int refresh, short bits) {
        double led_rise_us = (max_led_impedance * min_led_harmonics * max_led_cap_pf * scan) / 1000000.0;
        double period_us = 1000000.0 / (refresh * scan);
        brightness = ((period_us / get_refresh_overhead(scan, refresh, bits, isS_PWM)) - led_rise_us) / period_us;

        return (is_clk_valid(scan, cols, refresh, bits) &&
            is_gclk_valid(scan, cols, refresh, bits) &&
            is_grayscale_valid(scan, cols, refresh, bits));
    }

    private boolean is_clk_valid(short scan, int cols, int refresh, short bits) {
        double temp = cols / columns_per_driver;
        temp *= max_impedance * fanout_per_clk * min_harmonics * max_par_cap_pf;
        double hz_limit = 1000000.0 / (temp * 1.0);
        hz_limit = Math.min(max_clk_mhz, hz_limit) * 1000000;
        clk_mhz = hz_limit / 1000000.0;
        hz_limit /= frames_per_second * 2 * cols * scan * 16;
        clk_mhz /= hz_limit;
        return hz_limit >= 1.0;
    }

    private boolean is_gclk_valid(short scan, int cols, int refresh, short bits) {
        double temp = cols / columns_per_driver;
        temp *= max_impedance * fanout_per_gclk * min_harmonics * max_par_cap_pf;
        double hz_limit = 1000000.0 / (temp * 1.0);
        hz_limit = Math.min(max_gclk_mhz, hz_limit) * 1000000;
        gclk_mhz = hz_limit / 1000000.0;
        hz_limit /= refresh * get_refresh_overhead(scan, refresh, bits, isS_PWM) * scan * (1 << (bits + get_min_dot_correction_bits()));
        gclk_mhz /= hz_limit;
        return hz_limit >= 1.0;
    }

    private boolean is_grayscale_valid(short scan, int cols, int refresh, short bits) {
        return ((1 << max_grayscale_bits) / ((1 << (bits + get_min_dot_correction_bits())) * scan)) >= 1;
    }

    public short frames_per_second = 30;
    public boolean isS_PWM = true;
    public short s_pwm_bits_per_seg = 6;
    public int max_grayscale_bits = 16;
}
package LED_Panel_Setting_Calculator

// TODO: Clean this up
abstract class Panel_Calculator {
    public abstract boolean is_valid(short scan, int cols, int refresh, short bits);

    public double clk_mhz;
    public double gclk_mhz;
    public double brightness;

    // Panel constants
    public double max_clk_mhz = 25.0;
    public double max_gclk_mhz = 33.0;
    public short columns_per_driver = 16;
    public short fanout_per_clk = 8;
    public short fanout_per_gclk = 1;
    public short max_impedance = 50;                   // For longer chains may need custom circuit board which adjusts this
    public short max_par_cap_pf = 30;                  // For longer chains may need custom circuit board which adjusts this
    public short min_harmonics = 10;                   // This should be at least 10 for square waves

    // LED constants
    public int max_led_column_impedance = 980;
    public int max_led_row_impedance = 5;
    public int max_led_column_pullup = 1000;
    public int max_led_row_pulldown = 10000;
    public short max_led_cap_pf = 30;
    public short min_led_harmonics = 10;

    // Multiplexer constants
    public int max_multiplex_gate_pf = 200;
    public int max_multiplex_discharge_impedance = 50;
    public int max_multiplex_charge_impedance = 50;
    public int min_multiplex_harmonics = 5;
}

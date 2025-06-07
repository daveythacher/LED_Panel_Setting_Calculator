package LED_Panel_Setting_Calculator

// TODO: Clean this up

LED_driver_generation = 1;
result_counter = 0;
scan_target = 4;
cols_target = 8;
refresh_target = 3000;
bits_target = 0;

// These are used internally!
short scan = 0;
int cols = 0;
int refresh = 0;
short bits = 0;

def print_result(short scan, int cols, int refresh, short bits, double clk_mhz, double gclk_mhz, double brightness, short dc) {
    if ((scan * 2) <= cols) {
        print "\t Columns: " << cols;
        print "\t Scan: " << (int) scan;
        print "\t Pixels: " << scan * 2 * cols;
        print "\t Configuration: " << scan * 2 << "x" << cols;
        print "\t Refresh: " << refresh;
        print "\t BPP: " << (int) bits;
        print "\t Grayscale: " << (1 << (dc + bits)) * scan;
        print "\t CLK (MHz): " << clk_mhz;
        if (gclk_mhz != 0.0)
            print "\t GCLK (MHz): " << gclk_mhz;
        print "\t Brightness: " << brightness << "\n";
        ++result_counter;
    }
}

def process_scan() {
    scan_low = 1;
    scan_high = 32;

    if (scan_target != 0) {
        scan_low = scan_target;
        scan_high = scan_target;
    }

    for (scan = scan_low; scan <= scan_high; scan *= 2)
        process_cols();
}

def process_cols() {
    cols_low = 16;
    cols_high = 2048;

    if (cols_target != 0) {
        cols_low = cols_target;
        cols_high = cols_target;
    }

    for (cols = cols_low; cols <= cols_high; cols *= 2)
        process_refresh();
}

def process_refresh() {
    refresh_low = 100;
    refresh_high = 3000;

    if (refresh_target != 0) {
        refresh_low = refresh_target;
        refresh_high = refresh_target;
    }

    for (refresh = refresh_low; refresh <= refresh_high; refresh += 100)
        process_bits();
}

def process_bits() {
    bits_low = 1;
    bits_high = 16;

    if (bits_target != 0) {
        bits_low = bits_target;
        bits_high = bits_target;
    }

    for (bits = bits_low; bits <= bits_high; bits += 1)
        process_gen();
}

def process_gen() {
    switch (LED_driver_generation) {
        case 1:
            def calc = new GEN_1();
            if (calc.is_valid((short) scan, cols, refresh, (short) bits))
                print_result((short) scan, cols, refresh, (short) bits, calc.clk_mhz, calc.gclk_mhz, calc.brightness, (short) 0);
            break;
        case 2:
            def calc = new GEN_2();
            if (calc.is_valid((short) scan, cols, refresh, (short) bits))
                print_result((short) scan, cols, refresh, (short) bits, calc.clk_mhz, calc.gclk_mhz, calc.brightness, calc.get_min_dot_correction_bits());
            break;
        case 3:
            def calc = new GEN_3();
            if (calc.is_valid((short) scan, cols, refresh, (short) bits))
                print_result((short) scan, cols, refresh, (short) bits, calc.clk_mhz, calc.gclk_mhz, calc.brightness, calc.get_min_dot_correction_bits());
            break;
        default:
            break;
    }
}

println "Valid results will be shown below: (LED Driver Generation " + (int) LED_driver_generation + ")";
process_scan();
println result_counter + " Results found";

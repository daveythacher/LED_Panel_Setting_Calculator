#include "helper.h"
#include "config.h"

int main(int argc, char **argv) {
    init();

    switch (LED_driver_generation) {
        case 1:
            process_gen1();
            break;
        case 2:
            process_gen2();
            break;
        case 3:
            process_gen3();
        default:
            break;
    }

    return 0;
}
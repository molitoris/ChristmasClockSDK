#include <stdio.h>
#include <pico/stdlib.h>
#include <pico/binary_info.h>

#include "ChristmasClock.hpp"

int main() {
    stdio_init_all();
    for(int i = 8; i > 0; --i){
        printf("%d\n", i);
        sleep_ms(1000);
    } 

    printf("Generic error: %d\n", PICO_ERROR_GENERIC);
    printf("Timeout error: %d\n", PICO_ERROR_TIMEOUT);

    ChristmasClock::ChristmasClock clock;
    const int state = clock.init();
    if(state != 0) {
        printf("Could not initialize clock\n");
        return state;
    }
    
    // main loop
    while(true){
        clock.update();
        sleep_ms(500);
    }
    return -1;
}
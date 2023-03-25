#include "touch.hpp"

 #include <stdio.h>
#include <hardware/i2c.h>

namespace ChristmasClock {
// Default bus address of MPR121
const int ADDRESS = 0x5A;

uint8_t REG_TOUCH_STAT_0 = 0x00;     // ELE0-ELE7 Touch Status
uint8_t REG_TOUCH_STAT_1 = 0x01;     // ELE8-ELE11 ELEPROX Touch Status


CapacitiveTouch::CapacitiveTouch(unsigned int scl_pin, unsigned int sda_pin, unsigned int iqr_pin):
m_scl_pin(scl_pin),
m_sda_pin(sda_pin),
m_iqr_pin(iqr_pin) {
    // Initialize I2C in known state
    i2c_init(i2c_default, 100 * 1e3);

    // Ensure that not more buttons than there are physical buttons 
    assert(usedButtons < 12);
}
void CapacitiveTouch::config() {
    m_buf[0] = REG_CONF_0;
    m_buf[1] = (0 << 6) + 16;
    i2c_write_blocking(i2c_default, ADDRESS, m_buf, 2, false);
}

// void CapacitiveTouch::read_data() {
//     int res = write_blocking(ADDRESS, &rxdata, 1, false);
// }

// int write_blocking(const uint8_t* src, const std::size_t& size, const bool& nostop) {
//     uint8_t buf[2];
//     return i2c_write_blocking(i2c_default, ADDRESS, src, size, nostop);
//     return 1;
// }

void CapacitiveTouch::readTouchStatus() {
    // Read touch status
    // uint8_t res = i2c_read_blocking(i2c_default, ADDRESS, &REG_TOUCH_STAT_0, 2, false);

    // // Check every sensor if it was touched
    // for (uint8_t i = 0; i < usedButtons; ++i) {
    //     if ((res >> i) & 1) {
    //         printf("Button %d pressed", i);
    //     }
    // }
    printf("Check button\n");
}
}



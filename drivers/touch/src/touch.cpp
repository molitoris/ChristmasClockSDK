#include "touch.hpp"

#include <stdio.h>
#include <hardware/gpio.h>
#include <hardware/i2c.h>



namespace ChristmasClock {
// Default bus address of MPR121
const int ADDRESS = 0x5A;

uint8_t CapacitiveTouch::REG_TOUCH_STAT_0 = 0x00;     // ELE0-ELE7 Touch Status
uint8_t CapacitiveTouch::REG_TOUCH_STAT_1 = 0x01;     // ELE8-ELE11 ELEPROX Touch Status


CapacitiveTouch::CapacitiveTouch(unsigned int scl_pin, unsigned int sda_pin, unsigned int iqr_pin):
m_scl_pin(scl_pin),
m_sda_pin(sda_pin),
m_iqr_pin(iqr_pin) {

    // Ensure that not more buttons than there are physical buttons 
    assert(usedButtons < 12);

    // Configure GPIO pins
    gpio_set_function(m_sda_pin, GPIO_FUNC_I2C);
    gpio_set_function(m_scl_pin, GPIO_FUNC_I2C);
    gpio_pull_up(m_sda_pin);
    gpio_pull_up(m_scl_pin);

    // Initialize I2C bus
    i2c_init(i2c_default, 100 * 1e3);
    i2c_set_slave_mode(i2c_default, true, ADDRESS);

    // Enable interrupts on IRQ pin
    // gpio_set_irq_enabled_with_callback(m_irq_pin, GPIO_IRQ_EDGE_RISE, true, irq_handler);
}
int CapacitiveTouch::config() {
    m_buf[0] = REG_CONF_0;
    m_buf[1] = (0 << 8) | 16;
    auto res = i2c_write_timeout_us(i2c_default, ADDRESS, m_buf, 2, false, 100);

    return res;
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
    //Read touch status
    uint8_t res = i2c_read_timeout_us(i2c_default, ADDRESS, &REG_TOUCH_STAT_0, 2, false, 100);

    printf("Result %d pressed\n", res);

    // Check every sensor if it was touched
    for (uint8_t i = 0; i < usedButtons; ++i) {
        if ((res >> i) & 1) {
            printf("Button %d pressed\n", i);
        }
    }
}
}



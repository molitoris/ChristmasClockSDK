#include "touch.hpp"

#include <stdio.h>
#include <pico/stdlib.h>
#include <hardware/gpio.h>
#include <hardware/i2c.h>


namespace ChristmasClock {
// Bus address of MPR121 (ADDR is connected to VSS)
const int ADDRESS = 0x5A;

CapacitiveTouch::CapacitiveTouch(unsigned int scl_pin, unsigned int sda_pin, unsigned int iqr_pin):
m_scl_pin(scl_pin),
m_sda_pin(sda_pin),
m_iqr_pin(iqr_pin) {

    // Ensure that not more buttons than there are physical buttons 
    assert(usedButtons < 12);

    // // Set baudrate of I2C bus
    i2c_init(i2c1, 400000);

    // // Setup GPIO pins
    gpio_set_function(m_sda_pin, GPIO_FUNC_I2C);
    gpio_set_function(m_scl_pin, GPIO_FUNC_I2C);
    gpio_pull_up(m_sda_pin);
    gpio_pull_up(m_scl_pin);


    // Enable interrupts on IRQ pin
    // gpio_set_irq_enabled_with_callback(m_irq_pin, GPIO_IRQ_EDGE_RISE, true, irq_handler);
}
int CapacitiveTouch::init() {

    int res = 0;

    // Soft reset pf sensor
    res = write_register(REGISTER::SOFT_RESET, 0x63);
    if(res != 2) {
        printf("Soft reset failed: %d\n", res);
        return res;
    }

    set_threshold(12, 6);

    // Raising
    write_register(REGISTER::MHDR, 0x01);
    write_register(REGISTER::NHDR, 0x01);
    write_register(REGISTER::NCLR, 0x0E);
    write_register(REGISTER::FDLR, 0x00);

    // Falling
    write_register(REGISTER::MHDF, 0x01);
    write_register(REGISTER::NHDF, 0x05);
    write_register(REGISTER::NCLF, 0x01);
    write_register(REGISTER::FDLF, 0x00);

    // Touched
    write_register(REGISTER::NHDT, 0x00);
    write_register(REGISTER::NCLT, 0x00);
    write_register(REGISTER::FDLT, 0x00);

    // Auto-Configure sensor
    res = write_register(REGISTER::AUTOCONFIG, 0x0B);
    if(res != 2) {
        printf("Autoconfiguration failed: %d\n", res);
        return res;
    }

    write_register(REGISTER::UP_SIDE_LIMIT, 200);
    write_register(REGISTER::TARGET_LIMIT, 180);
    write_register(REGISTER::LOW_SIDE_LIMIT, 130);

    // Enable touch sensors
    const uint8_t erc_values = 0b10000000 + usedButtons;
    res = write_register(REGISTER::ECR, erc_values);
    if(res != 2) {
        printf("Failed to enable touch sensors: %d\n", res);
        return res;
    }

    return 0;
}

int CapacitiveTouch::write_register(const uint8_t reg, const uint8_t value) const {
    uint8_t buff[2];
    buff[0] = reg;
    buff[1] = value;

    return i2c_write_blocking(i2c1, ADDRESS, buff, 2, false);
}

void CapacitiveTouch::read_register(const uint8_t reg, uint8_t* data, uint8_t size) {
    i2c_write_blocking(i2c1, ADDRESS, &reg, 1, true);
    i2c_read_blocking(i2c1, ADDRESS, data, size, false);

}

void CapacitiveTouch::set_threshold(uint8_t touch, uint8_t release) {
    for (uint8_t i = 0; i < usedButtons; ++i) {
        write_register(REGISTER::TOUCH_THRESHOLD + 2 * i, touch);
        write_register(REGISTER::RELEASE_THRESHOLD + 2 * i, release);
  }
}

void CapacitiveTouch::readTouchStatus() {
    //Read touch status
    uint8_t data = 0x0;
    read_register(REGISTER::TOUCH_STAT_0, &data, 1);

    printf("Button data: %d\n", data);

    // Check every sensor if it was touched
    for (uint8_t i = 0; i < usedButtons; ++i) {
        if ((data >> i) & 1) {
            printf("Button %d pressed\n", i);
        }
    }
}
}



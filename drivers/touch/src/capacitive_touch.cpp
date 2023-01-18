#include "capacitive_touch.hpp"

#include "touch_event.hpp"

#include "hardware/i2c.h"

// Default bus address of MPR121
const int ADDRESS = 0x5A;



ChristmasClock::CapacitiveTouch::CapacitiveTouch(uint scl_pin, uint sda_pin, uint iqr_pin):
    m_scl_pin(scl_pin),
    m_sda_pin(sda_pin),
    m_iqr_pin(iqr_pin)
    {
        // Initialize I2C in known state
        i2c_init(i2c_default, 100 * 1e3);

        // Ensure that not more buttons than there are physical buttons 
        assert(usedButtons < 12);
    }

void ChristmasClock::CapacitiveTouch::config() {
    m_buf[0] = REG_CONF_0;
    m_buf[1] = (0 << 6) + 16
    i2c_write_blocking(i2c_default, ADDR, m_buf, m_buf.size(), False);
}

void ChristmasClock::CapacitiveTouch::read_data() {
    int res = write_blocking(ADDR, &rxdata, 1, false);
}

int write_blocking(const uint8_t* src, const std::size_t& size, const bool& nostop) {
    uint8_t buf[2];
    return i2c_write_blocking(i2c_default, ADDR, src, size, nostop);
}

void readTouchStatus()
{
    // Read touch status
    uint8_t res = i2c_read_blocking(i2c_default, ADDR, REG_TOUCH_STAT_0, 1, false);

    // Check every sensor if it was touched
    for (std::size_t i = 0; i < usedButtons; ++i) {
        if ((res >> i) & 1) {
            TouchEvent event;
            event.buttonIdentifier = i;
            notify(event);
        }
    }
}






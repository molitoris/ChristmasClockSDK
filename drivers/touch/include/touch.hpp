#pragma once

#include <stdint.h>

namespace ChristmasClock {

enum REGISTER {
    AUTOCONFIG = 0x7B,
    // VDD = 3.3V
    UP_SIDE_LIMIT,          // USL = (VDD-0.7) / VDD x 256
    TARGET_LIMIT,           // TL = USL x 0.9
    LOW_SIDE_LIMIT,         // LSL = USL x 0.65
    ECR = 0x5E,             // Electrode Configuration Register
    SOFT_RESET = 0x80,      // Soft reset
    TOUCH_STAT_0 = 0x00,    // Touch/release status of each electrode of first eight buttons
    TOUCH_STAT_1 = 0x01     // Touch/release status of each electrode of remaining five buttons
};

class CapacitiveTouch {
public:
    CapacitiveTouch(unsigned int scl_pin, unsigned int sda_pin, unsigned int m_iqr_pin);
    ~CapacitiveTouch() = default;

    int init();
    void readTouchStatus();
protected:
    int write_register(const uint8_t reg, const uint8_t value) const;
    void read_register(const uint8_t reg, uint8_t* data, uint8_t size);
private:
    unsigned int m_scl_pin;
    unsigned int m_sda_pin;
    unsigned int m_iqr_pin;
    
    static const unsigned int usedButtons = 6;
};
}

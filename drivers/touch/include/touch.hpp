#pragma once

#include <stdint.h>

namespace ChristmasClock {

enum REGISTER {
    ECR = 0x5E,
    SOFT_RESET = 0x80
};

class CapacitiveTouch {
public:
    CapacitiveTouch(unsigned int scl_pin, unsigned int sda_pin, unsigned int m_iqr_pin);
    ~CapacitiveTouch() = default;

    int config();
    void readTouchStatus();
protected:
    int write_register(const uint8_t reg, const uint8_t value, const uint8_t size = 1, const unsigned int timeout_us=500) const;
private:
    unsigned int m_scl_pin;
    unsigned int m_sda_pin;
    unsigned int m_iqr_pin;
    
    uint8_t m_buf[2]; // Used to write to sensor

    static const unsigned int usedButtons = 6;

    // Hardware registers
    static uint8_t REG_TOUCH_STAT_0;
    static uint8_t REG_TOUCH_STAT_1;
    static uint8_t REG_ECR;
    
    static const uint8_t REG_CONF_0 = 0x5c;         // Filter & Charge Discharge Current
    static const uint8_t REG_CONF_1 = 0x5D;         // Charge Discharge Time & Second Filter Iterations & Electrode Sample Interval
    

};
}

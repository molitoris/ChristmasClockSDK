#pragma once

#include <touch_event.hpp>
#include <publisher.hpp>

namespace ChristmasClock {
class CapacitiveTouch: Publisher<TouchEvent> {
public:
    CapacitiveTouch(uint scl_pin, uint sda_pin, uint m_iqr_pin);
    ~CapacitiveTouch() = default;

    void config();
    void read_data();
protected:
    int write_blocking();
private:
    uint m_scl_pin;
    uint m_sda_pin;
    uint m_iqr_pin;
    
    uint8_t m_buf[2]; // Used to write to sensor

    static const std::size_t usedButtons = 6;

    // Hardware registers
    static const uint8_t REG_TOUCH_STAT_0 = 0x00;     // ELE0-ELE7 Touch Status
    static const uint8_t REG_TOUCH_STAT_0 = 0x01;     // ELE8-ELE11 ELEPROX Touch Status
    
    static const uint8_t REG_CONF_0 = 0x5c;         // Filter & Charge Discharge Current
    static const uint8_t REG_CONF_1 = 0x5D;         // Charge Discharge Time & Second Filter Iterations & Electrode Sample Interval

};
}

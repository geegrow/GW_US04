#ifndef GW_US04_H
#define GW_US04_H

#include <Arduino.h>
#include <Wire.h>

#define I2C_DEFAULT_ADDR    0x0E

class GW_US04 {
    public:
        GW_US04(uint8_t _address = I2C_DEFAULT_ADDR);
        GW_US04(uint8_t _trig, uint8_t _echo);
        uint16_t scan();

    private:
        uint16_t (GW_US04::*scan_p)();
        uint16_t scan_i2c();
        uint16_t scan_trigecho();

        void rx_data();
        void tx_data(uint16_t timeDel);

        uint8_t address = 0;
        uint8_t trig = 0;
        uint8_t echo = 0;

        uint8_t data[2];
};

#endif /* GW_US04_H */
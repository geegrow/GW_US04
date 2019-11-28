#include "GW_US04.h"

GW_US04::GW_US04(uint8_t _address) {
    this->address = _address;
    this->scan_p = &GW_US04::scan_i2c;
    Wire.begin();
}

GW_US04::GW_US04(uint8_t _trig, uint8_t _echo) {
    this->trig = _trig;
    this->echo = _echo;
    this->scan_p = &GW_US04::scan_trigecho;
    pinMode(this->trig, OUTPUT);
    pinMode(this->echo, INPUT_PULLUP);
}

uint16_t GW_US04::scan() {
    return (this->*scan_p)();
}

uint16_t GW_US04::scan_i2c() {
    this->tx_data(1);
    delay(20);
    this->rx_data();
    return ( (this->data[0] << 8) | this->data[1]);
}

uint16_t GW_US04::scan_trigecho() {
    digitalWrite(this->trig, HIGH);
    delayMicroseconds(30);
    digitalWrite(this->trig, LOW);
    uint32_t time_us=pulseIn(this->echo, HIGH);
    return (uint16_t)(time_us/58);
}

void GW_US04::rx_data() {
    uint8_t idx = 0;
    Wire.requestFrom((uint8_t)this->address, (uint8_t)2);
    while(Wire.available()) {
        this->data[idx]=Wire.read();
        idx++;
    }
}

void GW_US04::tx_data(uint16_t timeDel) {
    uint8_t buf[2];
    buf[0] = timeDel >> 8;
    buf[1] = timeDel & 0xFF;
    Wire.beginTransmission(this->address);
    Wire.write(buf, 2);
    Wire.endTransmission(0);
}
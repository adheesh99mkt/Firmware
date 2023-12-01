// CRC16.h
#ifndef CRC16_H
#define CRC16_H

#include <Arduino.h>

class CRC16 {
public:
    CRC16();
    void update(uint8_t data);
    uint16_t finalize();

private:
    uint16_t crc;
};

#endif  // CRC16_H

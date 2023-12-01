// CRC16.cpp
#include "CRC16.h"

CRC16::CRC16() : crc(0xFFFF) {}

void CRC16::update(uint8_t data) {
    crc ^= static_cast<uint16_t>(data);

    for (int i = 0; i < 8; ++i) {
        if (crc & 0x0001) {
            crc = (crc >> 1) ^ 0xA001;
        } else {
            crc >>= 1;
        }
    }
}

uint16_t CRC16::finalize() {
    return crc;
}

#ifndef SERIAL_COMPAT_H
#define SERIAL_COMPAT_H

#include <stdio.h>
#include <stdint.h>

class HardwareSerial {
public:
    void begin(uint32_t baud) { (void)baud; }
    void print(const char* s) { printf("%s", s); }
    void println(const char* s) { printf("%s\n", s); }
    void print(unsigned long v) { printf("%lu", v); }
    void println(unsigned long v) { printf("%lu\n", v); }
};

extern HardwareSerial Serial;

#endif // SERIAL_COMPAT_H

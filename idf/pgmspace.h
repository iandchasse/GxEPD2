#ifndef PGM_P_COMPAT_H
#define PGM_P_COMPAT_H

#define PROGMEM
#define pgm_read_byte(addr) (*(const unsigned char*)(addr))

#endif // PGM_P_COMPAT_H

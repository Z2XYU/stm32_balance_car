#ifndef __INA226_H__
#define __INA226_h__

#include <stdint.h>

void ina226_init(void);
float ina226_read_volt(void);
float ina226_read_current(void);
float ina226_read_power(void);

#endif

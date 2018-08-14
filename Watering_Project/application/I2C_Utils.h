/*
 * I2C_Utils.h
 */

#ifndef APPLICATION_I2C_UTILS_H_
#define APPLICATION_I2C_UTILS_H_
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <ti/drivers/I2C.h>
#include "unistd.h"

uint8_t SensorI2C_WriteRead(uint8_t slave_address, I2C_Handle i2cHandle,
                            uint8_t *writeData, uint8_t writeLen,
                            uint8_t *readData, uint8_t readLen);

#endif /* APPLICATION_I2C_UTILS_H_ */

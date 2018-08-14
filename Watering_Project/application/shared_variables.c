/*
 * shared_variables.c
 *
 *  Created on: 21 áôáø× 2018
 *      Author: haite
 */
#include <stdint.h>
#include "shared_variables.h"

//to know when to stop tasks
uint8_t stop = 1;
//to know when humidity level
uint16_t humidity_level = 0;
//to know when there isn't enough light
uint8_t noLight = 0;
//to know when lux level
uint16_t lux_level = 0;

/*
 * Copyright (c) 2015-2017, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== gpiointerrupt.c ========
 */
#include <stdint.h>
#include <stddef.h>
#include "unistd.h"
#include <ti/devices/cc32xx/inc/hw_types.h>
#include <ti/devices/cc32xx/inc/hw_memmap.h>
#include <ti/devices/cc32xx/driverlib/timer.h>
/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/I2C.h>
#include <ti/display/Display.h>

/* Example/Board Header files */
#include "Board.h"
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Event.h>

#include <xdc/cfg/global.h>

//#include <xdc/std.h>
#include <xdc/runtime/system.h>
#include <stdio.h>
#include <stdlib.h>
#include "I2C_Utils.h"
#include "TSL2561.h"

/*
 *  ======== led_function ========
 */
//TSL2561 registers addresses
#define TSL2561_SLAVE_ADDR 0x39 //0x39 is the slave address sometimes 0x29 or 0x49
#define TSL2561_REG_ADDR 0xAC // 0x0A or 0xAC pretty sure it's 0xAC
#define TSL2561_REG_CONTROL_ADDR 0x00 //AC
#define TSL2561_REG_TIMING 0x01// register for setting the gain and Integration
//commands
#define TSL2561_CONTROL_COMMAND 0x80 //command for control reg
#define TSL2561_TIMING_COMMAND 0x81 //command for Timing reg

//channels 0 and 1 low and high for getting the lux back into normal values- might use it might not
#define TSL2561_REGISTER_CHAN0_LOW 0x0C
#define TSL2561_REGISTER_CHAN0_HIGH 0x0D
#define TSL2561_REGISTER_CHAN1_LOW 0x0E
#define TSL2561_REGISTER_CHAN1_HIGH 0x0F
////power on/off TSL2561_GAIN commands for control register
#define TLS2561_POWER_OFF 0x00
#define TLS2561_POWER_ON 0x03
//TSL2561 definitions
//like camera more gain for dimmer environments // tried no gain at first but readings were low
#define TSL2561_GAIN  0x00//no gain(low gain) = 0x00// 16x gain(high gain) = 0x10
//Integration time how long to sample -> like camera longer times get more light so longer for dimmer environments
#define TSL2561_TINT_INTERGRATIONTIME  0x02 //0x02 = 402ms | 0x01 = 101ms | 0x00 13.7ms
#define TSL2561_PACKAGE 1 //chose CS Package

#define SAMPLE_COUNT  100
#include "shared_variables.h"
volatile uint8_t i;
/*
 * A task function used to "talk" with the TSL2561 light sensor
 * Starts TSL2561 using function found on it's data sheet
 * Checks light with the sensor and sets the global noLight accordingly
 * Also uses semaphores to make sure it works properly with PWM
 */
void * i2c_function(void * args)
{

    uint16_t lux; //lux is illumination levels --> or just light in human
    uint8_t txData[20] = {0};
    uint8_t rxData[20] = {0};

    ///for power on/off
    uint8_t txConData[2]={0};
    //channels for the get lux function
    uint16_t ch0;
    uint16_t ch1;

    I2C_Handle i2c;
    I2C_Params i2cparams;
    I2C_Params_init(&i2cparams);
    i2cparams.bitRate = I2C_400kHz;

        i2c = I2C_open(Board_I2C0, &i2cparams);
//    //need to turn the sensor On first by sending ON command to control reg
       txConData[0] = TSL2561_REG_CONTROL_ADDR;//send to 0x00 reg 0x03 to turn on// do I need the command bit (0x80) ?
       txConData[1] = TLS2561_POWER_ON;
       SensorI2C_WriteRead(TSL2561_SLAVE_ADDR, i2c ,txConData, 2, rxData, 0);//why do you randomly fail?????? not random ti board isn't stable

////getting the light from here
    txData[0] = TSL2561_REG_ADDR ;//0xAC
    while(1){
        lux=0;
        //get a bounch of samples because TSL2561 isn't a stable sensor - making average to normalize
          for(i = 0 ;i<SAMPLE_COUNT;i++){
////              //integration time of 402ms
              SensorI2C_WriteRead(TSL2561_SLAVE_ADDR, i2c, txData, 1, rxData, 4);
////              //read low and high values of ch0 and ch1 into one
              ch0=((uint16_t)rxData[1]<<8)|rxData[0];
              ch1=((uint16_t)rxData[3]<<8)|rxData[2];
////              //get the lux value according to our specs
              lux += CalculateLux(TSL2561_GAIN, TSL2561_TINT_INTERGRATIONTIME, ch0, ch1, TSL2561_PACKAGE);

         }
          lux /= SAMPLE_COUNT;
          lux_level = lux;
          /*
           * using semaphores and bool to make sure led will stop if too much light
           */
          Semaphore_reset(pwmSem,0);

          if(lux>10 && noLight){
              Write_Message("Lots of light so stopping led");
                  noLight = 0;
                  Semaphore_post(pwmSem);

          }else if(lux<10){
              noLight = 1;
              Semaphore_post(pwmSem);
              Semaphore_pend(i2cSem,BIOS_WAIT_FOREVER);
          }

    ////Stopping task on sw3
          if(!stop){
               Task_setPri(Task_self(),-1);
         }
    }
    I2C_close(i2c);


    return 0;
}



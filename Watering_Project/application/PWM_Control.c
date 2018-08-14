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
/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/I2C.h>
#include <ti/drivers/Timer.h>
/* Example/Board Header files */
#include "Board.h"
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Event.h>

#include <xdc/cfg/global.h>

//#include <xdc/std.h>
#include <xdc/runtime/system.h>
#include <stdio.h>
#include <stdlib.h>
//#include ADCs
#include <ti/drivers/PWM.h>
//#include displays
#include <ti/display/Display.h>
////shared
#include "shared_variables.h"

static PWM_Handle pwm;
/*
 * A task function used to set PWM of LED D7
 * According to humidity sets the pwm (no water pulse fast, little light pulse bright less water less pulse)
 * Also stop the light if there is a light of light
 * Uses semaphores to work well with light sensor TSL2561
 */
void * PWM_function(void * args)
{
/*
 * Initializing pwm and it's parameters to work with pwm using the board
 */
    PWM_Params params;
    uint16_t period = 3000;
    uint16_t duty = 0;

    PWM_init();

    PWM_Params_init(&params);
    params.periodUnits = PWM_PERIOD_US;
    params.periodValue = period;
    params.dutyUnits = PWM_DUTY_US;
    params.dutyValue = duty;

    pwm = PWM_open(Board_PWM1, &params);
    if(pwm == NULL){
        //Error opening PWM
        while(1);
    }

    PWM_start(pwm);
    //need to sleep or blokes GPIO
    usleep(1);
    while(1){
        /*
         * using semaphores and bool to make sure led will stop if too much light
         * when there isn't light save energy by turning off led
         */
        if(!noLight){
             PWM_setDuty(pwm, 0);
         }

        Semaphore_post(i2cSem);
        Semaphore_pend(pwmSem, BIOS_WAIT_FOREVER);
        //setting led d7 power according to humidity level
                    if(humidity_level<2000)
                        PWM_setDuty(pwm, 0);
                    else if(humidity_level<2200)
                              PWM_setDuty(pwm, 500);
                    else if(humidity_level<2400)
                        PWM_setDuty(pwm, 1000);
                    else if(humidity_level<2600)
                        PWM_setDuty(pwm, 1500);
                    else if(humidity_level<2800)
                        PWM_setDuty(pwm, 2000);
                    else if(humidity_level < 2850)
                        PWM_setDuty(pwm, 3000);
                    else// if(humidity_level > 2849 && humidity_level < 4000)//higer than 4000 is an error
                    {
                        PWM_setDuty(pwm, 0);
                           usleep(10000);
                           PWM_setDuty(pwm, 1000);
                           usleep(10000);
                           PWM_setDuty(pwm, 2000);
                           usleep(10000);
                           PWM_setDuty(pwm, 3000);
                           usleep(10000);
                           PWM_setDuty(pwm, 2000);
                           usleep(10000);
                           PWM_setDuty(pwm, 1000);
                           usleep(10000);
                           PWM_setDuty(pwm, 0);
                    }

                    //Stopping task on sw3
                    if(!stop){
                        PWM_setDuty(pwm, 0);
                        Task_setPri(Task_self(),-1);
                    }

    }

    return 0;
}


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
#include <ti/display/Display.h>
#include <ti/drivers/Timer.h>
/* Example/Board Header files */
#include "Board.h"
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Event.h>

#include <xdc/cfg/global.h>

#include <xdc/runtime/system.h>
#include <stdio.h>
#include <stdlib.h>

////shared
#include "shared_variables.h"

//uart
#include <ti/drivers/uart/UARTCC32XX.h>

//sw2//wanted it to be for togeling d6 but i2c blocks d6
//instead it tells the status of tasks
void button_0_fxn(uint_least8_t index ){
        //timer for led_toggle
         Timer_start(Timer_Led);

}
//sw3 for suspending tasks
void button_1_fxn(uint_least8_t index ){
    if(GPIO_read(Board_GPIO_BUTTON1) == 1){
            if(stop){
                //suspend tasks
                Write_Message("Suspending tasks");
                stop = 0;
            }
            else{

                stop = 1;

            }
        }
    //timer for stop_toggle
    Timer_start(Timer_Stop);

}
//Only on "press" of the sw3 button and not "release" of the button
//thats why we check when button == 1
void stop_toggle(){
    //check if need alredy stoped if yes restert
        if(GPIO_read(Board_GPIO_BUTTON1) == 1){
            if(stop){
                Write_Message("Restarting tasks");
                //restart tasks
                Task_setPri(ADC_Task_Humidity , 10);
                Task_setPri(PWM_Task , 7);
                Task_setPri(I2C_Task , 4);

            }
        }

}

//we toggle the led only on "press" of sw2 the button and not "release" of the button
//thats why we check when button == 1

//i2c blocks d6 and d7 used for pwm so changed to tasks status notifier
void led_toggle(){
if(GPIO_read(Board_GPIO_BUTTON0) == 1){
        //LED/INDEX: D7/2 D6/3
        //GPIO_toggle(Board_GPIO_LED2);
    //check status and notify
if(stop)
        Write_Message("Tasks working");
else
    Write_Message("Tasks suspended");

    }
}



void * GPIO_function(void * args)
{


    //install SW2 & SW3 callback
    GPIO_setCallback(Board_GPIO_BUTTON0, button_0_fxn);
    GPIO_setCallback(Board_GPIO_BUTTON1, button_1_fxn);

    //enable SW2 & SW3 interrupts
    GPIO_enableInt(Board_GPIO_BUTTON0);
    GPIO_enableInt(Board_GPIO_BUTTON1);

    return 0;
}


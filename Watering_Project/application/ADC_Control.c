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
#include <ti/drivers/ADC.h>
//#include displays
#include <ti/display/Display.h>

/* ADC sample count */
#define ADC_SAMPLE_COUNT  (100)



/* ADC conversion result variables */
uint16_t adcValue0;
uint32_t adcValue0MicroVolt;


//adc units
uint16_t adc0Value;
uint32_t adc0ValueMicroVolt=0;
//to display the value on the screen
//static Display_Handle display;

////shared
#include "shared_variables.h"
/*
 * A task function used to "talk" with the humidity sensor
 * Change global humidity values from the humidity sensor
 */
void ADCTask_func(void)
{
    ADC_init();
//need to have space to print msg
    char ADC_msg[40];
//handling adc
        ADC_Handle   adc;
        ADC_Params   params;
        int_fast16_t res;

        ADC_Params_init(&params);
        adc = ADC_open(Board_ADC0, &params);

        if (adc == NULL) {
//Error initializing ADC channel
            while (1);
        }

        //get task to start - waited because they block each other if all start together
        Task_setPri(PWM_Task , 7);
        Task_setPri(I2C_Task , 4);
//starting my uart
        uart_function();

        while(1){
//get value from adc
            res = ADC_convert(adc, &adcValue0);

            if (res == ADC_STATUS_SUCCESS) {

//normalize value
                adcValue0MicroVolt = ADC_convertRawToMicroVolts(adc, adcValue0);

                humidity_level = adcValue0MicroVolt/423;
                /*
                 * We have a humidity sensor that returns resistance
                 * High resistance means we have low conductivity which is no water -> more water lower values
                 */
                //put the a nice message and humidity into the msg variable
//             sprintf( ADC_msg, "Humidity Resist ADC value %d uV",humidity_level);
                //write humidity status//can't read other msgs so don't print good for debug
//             Write_Message(ADC_msg);

          usleep(5000);
            }
            else {
//ADC channel  failed
            }
            //Stopping task on sw3
            if(!stop){
                Task_setPri(Task_self(),-1);
               }
        }
        ADC_close(adc);
}

/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-D21
 */

#include <xdc/std.h>

#include <ti/sysbios/heaps/HeapMem.h>
extern const ti_sysbios_heaps_HeapMem_Handle heap0;

#include <ti/sysbios/knl/Task.h>
extern const ti_sysbios_knl_Task_Handle ADC_Task_Humidity;

#include <ti/sysbios/knl/Task.h>
extern const ti_sysbios_knl_Task_Handle PWM_Task;

#include <ti/sysbios/knl/Task.h>
extern const ti_sysbios_knl_Task_Handle GPIO_Task;

#include <ti/sysbios/hal/Timer.h>
extern const ti_sysbios_hal_Timer_Handle Timer_Led;

#include <ti/sysbios/hal/Timer.h>
extern const ti_sysbios_hal_Timer_Handle Timer_Stop;

#include <ti/sysbios/knl/Semaphore.h>
extern const ti_sysbios_knl_Semaphore_Handle i2cSem;

#include <ti/sysbios/knl/Task.h>
extern const ti_sysbios_knl_Task_Handle I2C_Task;

#include <ti/sysbios/knl/Semaphore.h>
extern const ti_sysbios_knl_Semaphore_Handle pwmSem;

extern int xdc_runtime_Startup__EXECFXN__C;

extern int xdc_runtime_Startup__RESETFXN__C;


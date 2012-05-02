/*
    FreeRTOS V6.0.0 - Copyright (C) 2009 Real Time Engineers Ltd.

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.
    ***NOTE*** The exception to the GPL is included to allow you to distribute
    a combined work that includes FreeRTOS without being obliged to provide the
    source code for proprietary components outside of the FreeRTOS kernel.
    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
    more details. You should have received a copy of the GNU General Public 
    License and the FreeRTOS license exception along with FreeRTOS; if not it 
    can be viewed here: http://www.freertos.org/a00114.html and also obtained 
    by writing to Richard Barry, contact details for whom are available on the
    FreeRTOS WEB site.

    1 tab == 4 spaces!

    http://www.FreeRTOS.org - Documentation, latest information, license and
    contact details.

    http://www.SafeRTOS.com - A version that is certified for use in safety
    critical systems.

    http://www.OpenRTOS.com - Commercial support, development, porting,
    licensing and training services.
*/


/******************************************************************************
	See http://www.freertos.org/a00110.html for an explanation of the 
	definitions contained in this file.
******************************************************************************/

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#define configUSE_PREEMPTION					1
#define configTICK_RATE_HZ					((portTickType) 10000)
#define configPERIPHERAL_CLOCK_HZ				(40000000UL)
#define configCPU_CLOCK_HZ					(80000000UL)

#define configUSE_16_BIT_TICKS					0
#define configUSE_IDLE_HOOK						0
#define configUSE_TICK_HOOK						0
#define configUSE_TRACE_FACILITY				0
#define configUSE_COUNTING_SEMAPHORES			0
#define configUSE_MUTEXES						0

#define configMINIMAL_STACK_SIZE				( 500 )
#define configISR_STACK_SIZE					( 500 )
#define configKERNEL_INTERRUPT_PRIORITY			0x01
#define configMAX_SYSCALL_INTERRUPT_PRIORITY	0x04

#define configMAX_PRIORITIES					( ( unsigned portBASE_TYPE ) 6 )
#define configTOTAL_HEAP_SIZE					( ( size_t ) 24000 )
#define configMAX_TASK_NAME_LEN					( 30 )
#define configIDLE_SHOULD_YIELD					0
#define configCHECK_FOR_STACK_OVERFLOW			2

/* Co-routine definitions. */
#define configUSE_CO_ROUTINES 					0
#define configMAX_CO_ROUTINE_PRIORITIES 		( 2 )

/* Set the following definitions to 1 to include the API function, or zero 
to exclude the API function. */

#define INCLUDE_vTaskPrioritySet				0
#define INCLUDE_uxTaskPriorityGet				0
#define INCLUDE_vTaskDelete						0
#define INCLUDE_vTaskCleanUpResources			0
#define INCLUDE_vTaskSuspend					0
#define INCLUDE_vTaskDelayUntil					1
#define INCLUDE_vTaskDelay						1
#define INCLUDE_uxTaskGetStackHighWaterMark		0


/* User Part */

#define configRESEAU_STACK_SIZE				( 1000 )
#define configINTERFACE_HTTP_STACK_SIZE		(configMINIMAL_STACK_SIZE)
#define configASSERVISSEMENT_STACK_SIZE		(configMINIMAL_STACK_SIZE)
#define configAFFICHAGE_STACK_SIZE		    (configMINIMAL_STACK_SIZE)
#endif /* FREERTOS_CONFIG_H */



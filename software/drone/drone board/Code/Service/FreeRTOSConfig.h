/*
    FreeRTOS V202112.00
    All rights reserved

    VISIT http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation >>>> AND MODIFIED BY <<<< the FreeRTOS exception.

    ***************************************************************************
    >>!   NOTE: The modification to the GPL is included to allow you to     !<<
    >>!   distribute a combined work that includes FreeRTOS without being   !<<
    >>!   obliged to provide the source code for proprietary components     !<<
    >>!   outside of the FreeRTOS kernel.                                   !<<
    ***************************************************************************

    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  Full license text is available on the following
    link: http://www.freertos.org/a00114.html

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS provides completely free yet professionally developed,    *
     *    robust, strictly quality controlled, supported, and cross          *
     *    platform software that is more than just the market leader, it     *
     *    is the industry's de facto standard.                               *
     *                                                                       *
     *    Help yourself get started quickly while simultaneously helping     *
     *    to support the FreeRTOS project by purchasing a FreeRTOS           *
     *    tutorial book, reference manual, or both:                          *
     *    http://www.FreeRTOS.org/Documentation                              *
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org/FAQHelp.html - Having a problem?  Start by reading
    the FAQ page "My application does not run, what could be wrong?".  Have you
    defined configASSERT()?

    http://www.FreeRTOS.org/support - In return for receiving this top quality
    embedded software for free we request you assist our global community by
    participating in the support forum.

    http://www.FreeRTOS.org/training - Investing in training allows your team to
    be as productive as possible as early as possible.  Now you can receive
    FreeRTOS training directly from Richard Barry, CEO of Real Time Engineers
    Ltd, and the world's leading authority on the world's leading RTOS.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool, a DOS
    compatible FAT file system, and our tiny thread aware UDP/IP stack.

    http://www.FreeRTOS.org/labs - Where new FreeRTOS products go to incubate.
    Come and try FreeRTOS+TCP, our new open source TCP/IP stack for FreeRTOS.

    http://www.OpenRTOS.com - Real Time Engineers ltd. license FreeRTOS to High
    Integrity Systems ltd. to sell under the OpenRTOS brand.  Low cost OpenRTOS
    licenses offer ticketed support, indemnification and commercial middleware.

    http://www.SafeRTOS.com - High Integrity Systems also provide a safety
    engineered and independently SIL3 certified version for use in safety and
    mission critical applications that require provable dependability.

    1 tab == 4 spaces!
*/


#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H


/**
 * @reason: contains the 'printf' function with 2 important includes #include "stdio.h" and #include "ch32v20x.h"
*/
#include "debug.h"

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *
 * See http://www.freertos.org/a00110.html.
 *----------------------------------------------------------*/

/* See https://www.freertos.org/Using-FreeRTOS-on-RISC-V.html */

/* CH32V203C8T6 don't have MTIME (machine timer) */
#define configMTIME_BASE_ADDRESS 	 ( 0 )
#define configMTIMECMP_BASE_ADDRESS  ( 0 )

#define configUSE_PREEMPTION			1   /* Set to 1 to use the preemptive RTOS scheduler, or 0 to use the cooperative RTOS scheduler. */
#define configUSE_IDLE_HOOK				0   /* Set to 1 if you wish to use an idle hook, or 0 to omit an idle hook. */
#define configUSE_TICK_HOOK				0   /* Set to 1 if you wish to use an tick hook, or 0 to omit an tick hook.*/
#define configCPU_CLOCK_HZ				SystemCoreClock /* Enter the frequency in Hz at which the internal clock that drives the peripheral used to generate the tick interrupt will be executing.*/
#define configTICK_RATE_HZ				( ( TickType_t ) 500 ) /* The frequency of the RTOS tick interrupt. (interruption happens every tick)*/
#define configMAX_PRIORITIES			( 7 )   /* The number of priorities available to the application tasks. */
#define configMINIMAL_STACK_SIZE		( ( unsigned short ) 256 )  /* The size of the stack used by the idle task in words. Can be as low as 60 but some of the demo tasks that use this constant require it to be higher. */
#define configTOTAL_HEAP_SIZE			( ( size_t ) ( 12 * 1024 ) ) /* The total amount of RAM available in the FreeRTOS heap in bytes.*/
#define configMAX_TASK_NAME_LEN			( 32 ) /* The maximum permissible length of the descriptive name given to a task when the task is created. The length is specified in the number of characters including the NULL termination byte.*/
#define configUSE_TRACE_FACILITY		0   /* Set to 1 if you wish to include additional structure members and functions to assist with execution visualisation and tracing.*/
#define configUSE_16_BIT_TICKS			0   /* Defining configUSE_16_BIT_TICKS as 1 causes TickType_t to be defined (typedef'ed) as an unsigned 16bit type. Defining configUSE_16_BIT_TICKS as 0 causes TickType_t to be defined (typedef'ed) as an unsigned 32bit type.*/
#define configIDLE_SHOULD_YIELD			0   /* If configIDLE_SHOULD_YIELD is set to 1 then the idle task will yield immediately if any other task at the idle priority is ready to run. This ensures the minimum amount of time is spent in the idle task when application tasks are available for scheduling. Setting configIDLE_SHOULD_YIELD to 0 prevents the idle task from yielding processing time until the end of its time slice. This ensure all tasks at the idle priority are allocated an equal amount of processing time (if none of the tasks get pre-empted) - but at the cost of a greater proportion of the total processing time being allocated to the idle task.*/
#define configUSE_MUTEXES				1   /* Set to 1 to include mutex functionality in the build, or 0 to omit mutex functionality from the build.*/
#define configQUEUE_REGISTRY_SIZE		8   /* configQUEUE_REGISTRY_SIZE defines the maximum number of queues and semaphores that can be registered. Only those queues and semaphores that you want to view using a RTOS kernel aware debugger need be registered.*/
#define configCHECK_FOR_STACK_OVERFLOW	0   /* The stack overflow detection page (https://www.freertos.org/Stacks-and-stack-overflow-checking.html) describes the use of this parameter.*/
#define configUSE_RECURSIVE_MUTEXES		1   /* Set to 1 to include recursive mutex functionality in the build, or 0 to omit recursive mutex functionality from the build.*/
#define configUSE_MALLOC_FAILED_HOOK	0   /* if configUSE_MALLOC_FAILED_HOOK is set to 1 then the application must define a malloc() failed hook function. If configUSE_MALLOC_FAILED_HOOK is set to 0 then the malloc() failed hook function will not be called, even if one is defined. Malloc() failed hook functions must have the name and prototype shown below.*/
#define configUSE_APPLICATION_TASK_TAG	0   /* Setting configUSE_APPLICATION_TASK_TAG to 1 will include task tagging functionality and its associated API in the build. A 'tag' value can be assigned to each task.*/
#define configUSE_COUNTING_SEMAPHORES	1   /* Set to 1 to include counting semaphore functionality in the build, or 0 to omit counting semaphore functionality from the build.*/
#define configGENERATE_RUN_TIME_STATS	0   /* The Run Time Stats page (https://www.freertos.org/rtos-run-time-stats.html) describes the use of this parameter.*/
#define configUSE_PORT_OPTIMISED_TASK_SELECTION 0   /* Some FreeRTOS ports have two methods of selecting the next task to execute - a generic method, and a method that is specific to that port.*/

/* Co-routine definitions. */
#define configUSE_CO_ROUTINES 			0   /* Set to 1 to include co-routine functionality in the build, or 0 to omit co-routine functionality from the build. To include co-routines croutine.c must be included in the project.*/
#define configMAX_CO_ROUTINE_PRIORITIES ( 2 ) /*The number of priorities available to the application co-routines. Any number of co-routines can share the same priority. Tasks are prioritised separately - see configMAX_PRIORITIES.*/

/* Software timer definitions. */
#define configUSE_TIMERS				1   /* If configUSE_TIMERS and configUSE_DAEMON_TASK_STARTUP_HOOK are both set to 1 then the application must define a hook function that has the exact name and prototype as shown below. */
#define configTIMER_TASK_PRIORITY		( configMAX_PRIORITIES - 1 )    /* Sets the priority of the software timer service/daemon task. See the FreeRTOS software timers page for a full description.*/
#define configTIMER_QUEUE_LENGTH		4   /* Sets the length of the software timer command queue. See the FreeRTOS software timers page for a full description.*/
#define configTIMER_TASK_STACK_DEPTH	( configMINIMAL_STACK_SIZE )    /* Sets the stack depth allocated to the software timer service/daemon task. See the FreeRTOS software timers page for a full description.*/



/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */
#define INCLUDE_vTaskPrioritySet			1
#define INCLUDE_uxTaskPriorityGet			1
#define INCLUDE_vTaskDelete					1
#define INCLUDE_vTaskCleanUpResources		1
#define INCLUDE_vTaskSuspend				1
#define INCLUDE_vTaskDelayUntil				1
#define INCLUDE_vTaskDelay					1
#define INCLUDE_eTaskGetState				1
#define INCLUDE_xTimerPendFunctionCall		1
#define INCLUDE_xTaskAbortDelay				1
#define INCLUDE_xTaskGetHandle				1
#define INCLUDE_xSemaphoreGetMutexHolder	1
#define configSUPPORT_DYNAMIC_ALLOCATION    1   /* to include xQueueCreate function in the build*/

/* Normal assert() semantics without relying on the provision of an assert.h
header file. */
#define configASSERT( x ) if( ( x ) == 0 ) { taskDISABLE_INTERRUPTS(); printf("err at line %d of file \"%s\". \r\n ",__LINE__,__FILE__); while(1); }

/* Map to the platform printf function. */
#define configPRINT_STRING( pcString )  printf( pcString )


#endif /* FREERTOS_CONFIG_H */

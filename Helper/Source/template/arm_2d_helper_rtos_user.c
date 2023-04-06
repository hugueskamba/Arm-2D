/*
 * Copyright (c) 2009-2020 Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*============================ INCLUDES ======================================*/


#include "arm_2d_helper.h"
#include "arm_2d_disp_adapters.h"
#include "cmsis_os2.h"


#if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wunknown-warning-option"
#   pragma clang diagnostic ignored "-Wreserved-identifier"
#   pragma clang diagnostic ignored "-Wdeclaration-after-statement"
#   pragma clang diagnostic ignored "-Wsign-conversion"
#   pragma clang diagnostic ignored "-Wpadded"
#   pragma clang diagnostic ignored "-Wcast-qual"
#   pragma clang diagnostic ignored "-Wcast-align"
#   pragma clang diagnostic ignored "-Wmissing-field-initializers"
#   pragma clang diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"
#   pragma clang diagnostic ignored "-Wmissing-prototypes"
#   pragma clang diagnostic ignored "-Wunused-variable"
#   pragma clang diagnostic ignored "-Wgnu-statement-expression"
#   pragma clang diagnostic ignored "-Wmissing-variable-declarations"
#   pragma clang diagnostic ignored "-Wbad-function-cast"
#   pragma clang diagnostic ignored "-Wunreachable-code-break"
#   pragma clang diagnostic ignored "-Wshorten-64-to-32"
#   pragma clang diagnostic ignored "-Wdouble-promotion"
#elif __IS_COMPILER_ARM_COMPILER_5__
#elif __IS_COMPILER_GCC__
#   pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wformat="
#   pragma GCC diagnostic ignored "-Wpedantic"
#endif

/*============================ MACROS ========================================*/

//-------- <<< Use Configuration Wizard in Context Menu >>> -----------------

// <o>Target FPS <8-32767>
// <i> Try to lock framerate to a specified value
// <i> Default: 30
#ifndef LCD_TARGET_FPS
#   define LCD_TARGET_FPS       30
#endif

// <o>Arm-2D APP Stack Size <1024-32767>
// <i> Specify the arm-2d application thread stack size
// <i> Default: 2048
#ifndef APP_STACK_SIZE
#   define APP_STACK_SIZE       2048
#endif

// <<< end of configuration section >>>

/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
/*============================ GLOBAL VARIABLES ==============================*/
/*============================ PROTOTYPES ====================================*/
/*============================ LOCAL VARIABLES ===============================*/

/*============================ IMPLEMENTATION ================================*/

__OVERRIDE_WEAK
arm_2d_runtime_feature_t ARM_2D_RUNTIME_FEATURE = {
    .TREAT_OUT_OF_RANGE_AS_COMPLETE         = 1,
    .HAS_DEDICATED_THREAD_FOR_2D_TASK       = __ARM_2D_HAS_ASYNC__,
};


/*----------------------------------------------------------------------------*
 * RTOS Port                                                                  *
 *----------------------------------------------------------------------------*/
__OVERRIDE_WEAK
uintptr_t arm_2d_port_new_semaphore(void)
{
    /* put your code here to generate a new semaphore */
    return (uintptr_t)NULL;
}

__OVERRIDE_WEAK
void arm_2d_port_free_semaphore(uintptr_t pSemaphore)
{
    /* put your code here to free a new semaphore */
}

__OVERRIDE_WEAK
bool arm_2d_port_wait_for_semaphore(uintptr_t pSemaphore)
{
    /* put your code here to wait for a given semaphore */
    return true;
}

__OVERRIDE_WEAK
void arm_2d_port_set_semaphoret(uintptr_t pSemaphore)
{
    /* put your code here to set a given semaphore */
}


/*----------------------------------------------------------------------------*
 * Application main thread                                                    *
 *----------------------------------------------------------------------------*/
 
 __NO_RETURN
void app_2d_main_thread (void *argument) 
{

    ARM_2D_UNUSED(argument);

    while(1) {
        //! retrieve the number of system ticks
        //uint32_t wTick = osKernelGetTickCount();        
        while(arm_fsm_rt_cpl != disp_adapter0_task());
        
        //! lock frame rate
        //osDelayUntil(wTick + (1000 / LCD_TARGET_FPS));
    }
}

__NO_RETURN
void arm_2d_backend_thread(void *argument)
{

    ARM_2D_UNUSED(argument);

    arm_2d_helper_backend_task();
    
    //osThreadExit();
    while(1) __NOP();
}


void arm_2d_helper_rtos_init(void)
{

    arm_irq_safe {
        arm_2d_init();
    } 

    disp_adapter0_init();

    /* put your code here to Create arm-2d main thread 
    static uint64_t thread1_stk_1[APP_STACK_SIZE / sizeof(uint64_t)];
     
    const osThreadAttr_t thread1_attr = {
      .stack_mem  = &thread1_stk_1[0],
      .stack_size = sizeof(thread1_stk_1)
    };
    osThreadNew(app_2d_main_thread, NULL, &thread1_attr);
    */
    
    /* put your code here to Create arm-2d backend thread */
    //osThreadNew(arm_2d_backend_thread, NULL, NULL);
}

#if defined(__clang__)
#   pragma clang diagnostic pop
#endif


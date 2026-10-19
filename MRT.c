/*
 * MRT.c
 *
 *  Created on: 20 sep. 2026
 *      Author: Emilio
 *
 */

#include "MRT.h"
#include "fsl_mrt.h"


static void (*mrt_0_callback)(void) = 0;
static void (*mrt_1_callback)(void) = 0;
static void (*mrt_2_callback)(void) = 0;
static void (*mrt_3_callback)(void) = 0;

volatile static mrt_interrupt_flags_t g_intr_status_flag = {0};

void MRT0_IRQHandler(void)
{
    /*Revisar Canal 0*/
    if (MRT_GetStatusFlags(MRT0, kMRT_Channel_0) & kMRT_TimerInterruptFlag)
    {
        /* Limpiar bandera del Canal 0 */
        MRT_ClearStatusFlags(MRT0, kMRT_Channel_0, kMRT_TimerInterruptFlag);
        if(NULL != mrt_0_callback)
        {
        	g_intr_status_flag.MRT_Channel_0_flag = TRUE;
        	mrt_0_callback();
        }
    }

    /*Revisar Canal 1*/
    if (MRT_GetStatusFlags(MRT0, kMRT_Channel_1) & kMRT_TimerInterruptFlag)
    {
        /*Limpiar bandera del Canal 1 */
        MRT_ClearStatusFlags(MRT0, kMRT_Channel_1, kMRT_TimerInterruptFlag);
        if(NULL != mrt_1_callback)
        {
        	mrt_1_callback();
        }
    }

    /*Revisar Canal 2*/
    if (MRT_GetStatusFlags(MRT0, kMRT_Channel_2) & kMRT_TimerInterruptFlag)
    {
        /*Limpiar bandera del Canal 2 */
        MRT_ClearStatusFlags(MRT0, kMRT_Channel_2, kMRT_TimerInterruptFlag);
        if(NULL != mrt_2_callback)
        {
        	mrt_2_callback();
        }
    }

    /*Revisar Canal 3*/
    if (MRT_GetStatusFlags(MRT0, kMRT_Channel_3) & kMRT_TimerInterruptFlag)
    {
        /*Limpiar bandera del Canal 3 */
        MRT_ClearStatusFlags(MRT0, kMRT_Channel_3, kMRT_TimerInterruptFlag);
        if(NULL != mrt_3_callback)
        {
        	mrt_3_callback();
        }
    }

    /* Barrera de memoria recomendada para Cortex-M33 */
    SDK_ISR_EXIT_BARRIER;
}

void MRT_config()
{

    /* Structure of initialize MRT */
    mrt_config_t mrtConfig;
    /* mrtConfig.enableMultiTask = false; */
    MRT_GetDefaultConfig(&mrtConfig);
    /* Init mrt module */
    MRT_Init(MRT0, &mrtConfig);
    /* Enable at the NVIC */
    EnableIRQ(MRT0_IRQn);
}

void MRT_setup_channel(mrt_channel_t mrt_channel){

    switch(mrt_channel)
    {
	case MRT_Channel_0:
	    /* Setup Channel 0 to be repeated */
	    MRT_SetupChannelMode(MRT0, kMRT_Channel_0, kMRT_RepeatMode);
	    /* Enable timer interrupts for channel 0 */
	    MRT_EnableInterrupts(MRT0, kMRT_Channel_0, kMRT_TimerInterruptEnable);
		break;
	case MRT_Channel_1:
	    /* Setup Channel 1 to be repeated */
	    MRT_SetupChannelMode(MRT0, kMRT_Channel_1, kMRT_RepeatMode);
	    /* Enable timer interrupts for channel 1 */
	    MRT_EnableInterrupts(MRT0, kMRT_Channel_1, kMRT_TimerInterruptEnable);
	break;
	case MRT_Channel_2:
	    /* Setup Channel 2 to be repeated */
	    MRT_SetupChannelMode(MRT0, kMRT_Channel_2, kMRT_RepeatMode);
	    /* Enable timer interrupts for channel 2 */
	    MRT_EnableInterrupts(MRT0, kMRT_Channel_2, kMRT_TimerInterruptEnable);
	break;
	case MRT_Channel_3:
	    /* Setup Channel 3 to be repeated */
	    MRT_SetupChannelMode(MRT0, kMRT_Channel_3, kMRT_RepeatMode);
	    /* Enable timer interrupts for channel 3 */
	    MRT_EnableInterrupts(MRT0, kMRT_Channel_3, kMRT_TimerInterruptEnable);
	break;
    }
}

void MRT_callback_init(mrt_channel_t mrt_channel, void (*handler)(void))
{
	switch(mrt_channel)
	{
	case MRT_Channel_0:
		mrt_0_callback = handler;
	break;
	case MRT_Channel_1:
		mrt_1_callback = handler;
	break;
	case MRT_Channel_2:
		mrt_2_callback = handler;
	break;
	case MRT_Channel_3:
		mrt_3_callback = handler;
	break;
	}
}

void MRT_start(mrt_channel_t mrt_channel, uint32_t cycles)
{
	switch(mrt_channel)
	{
	case MRT_Channel_0:
		MRT_StartTimer(MRT0, kMRT_Channel_0, cycles);
		break;
	case MRT_Channel_1:
		MRT_StartTimer(MRT0, kMRT_Channel_1, cycles);
		break;
	case MRT_Channel_2:
		MRT_StartTimer(MRT0, kMRT_Channel_2, cycles);
		break;
	case MRT_Channel_3:
		MRT_StartTimer(MRT0, kMRT_Channel_3, cycles);
		break;
	}
}

bool_value_t MRT_get_irq_satus(mrt_channel_t channel)
{
	bool_value_t status = FALSE;
	if(MRT_Channel_0 == channel)
	{
		status = g_intr_status_flag.MRT_Channel_0_flag;
	}
	return (status);
}

void MRT_clear_irq_satus(mrt_channel_t channel)
{
	if(MRT_Channel_0 == channel)
	{
		g_intr_status_flag.MRT_Channel_0_flag = FALSE;
	}

}

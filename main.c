/*
 * Copyright 2016-2026 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file    examen_1.c
 * @brief   Application entry point.
 * Author: Emilio Ismael Renteria Mendez
 */
#include <stdio.h>
#include "MRT.h"
#include "GPIO.h"
#include "RGB.h"

#define MRT_CYECLES_FOR_100_MS 4800000U

//Enum de los 4 estados de la máquina
typedef enum
{
	START,
	BLINK_WHITE_LED,
	WAIT_SW2,
	SHOW_GREEN_1S,
	WAIT_7S,
	SHOW_COLOR,
}State_name_t;

typedef enum
{
	CYAN,
	YELLOW,
	RED,
	PURPLE,
	BLUE
}color_t;

color_t color = CYAN;

void GPIO_numbers_pressed_callback()
{
	if(BLUE >= color)
	{
		color++;
	}
}

void GPIO_show_green_callback()
{
	RGB_green();
}

int main(void) {
	State_name_t current_state = START;
	GPIO_init_switches_and_LEDs();
	MRT_config();
	MRT_setup_channel(MRT_Channel_0);
	MRT_start(MRT_Channel_0, MRT_CYECLES_FOR_100_MS);
	bool_value_t two_seconds = FALSE;
	uint32_t ticks = 0;

    while(1) {
    	switch(current_state)
    	{
    	case(START):
    		if(two_seconds)
    		{
    			current_state = BLINK_WHITE_LED;
    		}
		break;
    	case(BLINK_WHITE_LED):
		break;
    	case(WAIT_SW2):
		break;
    	case(SHOW_GREEN_1S):
		break;
    	case(WAIT_7S):
		break;
    	case(SHOW_COLOR):
		break;
    	}

    	switch(current_state)
    	{
    	case(START):
    		if(MRT_get_irq_satus())
    		{
    			ticks_++;
    		}
    		if(20 >= ticks)
    		{
    			two_seconds = TRUE;
    			ticks = 0;
    		}
		break;
    	case(BLINK_WHITE_LED):
		break;
    	case(WAIT_SW2):
		break;
    	case(SHOW_GREEN_1S):
		break;
    	case(WAIT_7S):
		break;
    	case(SHOW_COLOR):
		break;
    	}
    }
    return 0 ;
}

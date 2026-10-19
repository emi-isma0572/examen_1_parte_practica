/*
* RGB.c
*
*  Created on: 7 sep. 2026
*      Author: emili and Nath
*/

#include "fsl_gpio.h"
#include "frdm_mcxn947.h"
#include "RGB.h"
#include "GPIO.h"
#define MAX_TICKS_100_MS 200

static uint32_t g_ticks = 0;
static uint32_t g_total_ticks = 0;
static uint8_t g_index_seq_1 = 0;
void (*RGB_sequence_1[3])(void) = {RGB_yellow, RGB_red, RGB_purple};
static uint8_t g_index_seq_2 = 0;
void (*RGB_sequence_2[3])(void) = {RGB_green, RGB_red, RGB_white};
static uint8_t g_index_seq_3 = 0;
void (*RGB_sequence_3[3])(void) = {RGB_blue, RGB_green, RGB_white};


void RGB_red_led_on_off(uint8_t on_off)
{
	GPIO_write(GPIO_Port0, RED_LED_PIN, on_off);
}

void RGB_blue_led_on_off(uint8_t on_off)
{
	GPIO_write(GPIO_Port1, BLUE_LED_PIN, on_off);
}

void RGB_green_led_on_off(uint8_t on_off)
{
	GPIO_write(GPIO_Port0, GREEN_LED_PIN, on_off);
}


void RGB_red(void)
{
    RGB_red_led_on_off(0);
    RGB_green_led_on_off(1);
    RGB_blue_led_on_off(1);
}


void RGB_blue(void)
{
    RGB_red_led_on_off(1);
    RGB_green_led_on_off(1);
    RGB_blue_led_on_off(0);
}


void RGB_purple(void)
{
    RGB_red_led_on_off(0);
    RGB_green_led_on_off(1);
    RGB_blue_led_on_off(0);
}

void RGB_green(void)
{
    RGB_red_led_on_off(1);
    RGB_green_led_on_off(0);
    RGB_blue_led_on_off(1);
}

void RGB_yellow(void)
{
    RGB_red_led_on_off(0);
    RGB_green_led_on_off(0);
    RGB_blue_led_on_off(1);
}

void RGB_white(void)
{
    RGB_red_led_on_off(0);
    RGB_green_led_on_off(0);
    RGB_blue_led_on_off(0);
}

void RGB_off(void)
{
    RGB_red_led_on_off(1);
    RGB_green_led_on_off(1);
    RGB_blue_led_on_off(1);
}

void RGB_sequence_handler_1(void)
{
	g_total_ticks++;
	if(g_ticks < MAX_TICKS_100_MS)
	{
		g_ticks++;
		return;
	}
	RGB_sequence_1[g_index_seq_1 ++ % 3]();
	g_ticks = 0;
}

void RGB_sequence_handler_2(void)
{
	g_total_ticks++;
	if(g_ticks < MAX_TICKS_100_MS)
	{
		g_ticks++;
		return;
	}
	RGB_sequence_2[g_index_seq_2 ++ % 3]();
	g_ticks = 0;
}

void RGB_sequence_handler_3(void)
{
	g_total_ticks++;
	if(g_ticks < MAX_TICKS_100_MS)
	{
		g_ticks++;
		return;
	}
	RGB_sequence_3[g_index_seq_3 ++ % 3]();
	g_ticks = 0;
}

void RGB_add_to_ticks(void)
{
	g_total_ticks++;
}

void RGB_restart_seq_1(void)
{
	g_index_seq_1 = 0;
}

void RGB_restart_seq_2(void)
{
	g_index_seq_2 = 0;
}

void RGB_restart_seq_3(void)
{
	g_index_seq_3 = 0;
}

uint32_t get_ticks(void)
{
	return g_total_ticks;
}


/*
 * RGB.h
 *
 *  Created on: 7 sep. 2026
 *      Author: Emilio Renteria y Nathalie Marin
 *
 *      Este es el archivo header para el control del LED RGB.
 *      Contiene las funciones para encender, apagar y cambiar los colores.
 *
 */

#ifndef RGB_H_
#define RGB_H_

#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_clock.h"
#include "frdm_mcxn947.h"
#include "GPIO.h"
#include "NVIC.h"

void RGB_red_led_on_off(uint8_t on_off);
void RGB_blue_led_on_off(uint8_t on_off);
void RGB_green_led_on_off(uint8_t on_off);

void RGB_red(void);
void RGB_blue(void);
void RGB_purple(void);
void RGB_green(void);
void RGB_yellow(void);
void RGB_white(void);
void RGB_off(void);

void RGB_sequence_handler_1(void);
void RGB_sequence_handler_2(void);
void RGB_sequence_handler_3(void);

void RGB_restart_seq_1(void);
void RGB_restart_seq_2(void);
void RGB_restart_seq_3(void);

uint32_t get_ticks(void);
void RGB_add_to_ticks(void);

#endif /* RGB_H_ */

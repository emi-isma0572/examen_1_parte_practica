/*
 * Digital_Watch_Pins.h
 *
 *  Created on: 9 oct. 2026
 *      Author: Nathalie Marin
 *
 *      Este es el archivo header que define las conexiones de los pines fisicos para el reloj.
 *
 */

#ifndef DIGITAL_WATCH_PINS_H_
#define DIGITAL_WATCH_PINS_H_

#define SEG_A_PIN     16U
#define SEG_B_PIN     17U
#define SEG_C_PIN     18U
#define SEG_D_PIN     19U
#define SEG_E_PIN     20U
#define SEG_F_PIN     21U
#define SEG_G_PIN     22U

//GPIO0
#define TIME_STOPWATCH_PIN 14U
#define TIME_ALARM_PIN 22U

//GPIO4
#define CONFIG_TIME_PIN 23U
#define HOUR_START_PIN 22U

//GPIO3
#define MIN_STOP_PIN 5U
#define CLEAR_PIN 4U

#define PIN_SECONDS_UNITS PIN_7
#define PIN_SECONDS_TENS PIN_6
#define PIN_MINUTES_UNITS PIN_5
#define PIN_MINUTES_TENS PIN_4
#define PIN_HOURS_UNITS PIN_3
#define PIN_HOURS_TENS PIN_2


#endif /*DIGITAL_WATCH_PINS_H_ */

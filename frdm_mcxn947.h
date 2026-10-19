/*
 * frdm_mcxn947.h
 *
 *  Created on: 3 sep. 2026
 *      Author: Emilio Renteria y Nathalie Marin
 *
 *      Este es el archivo header de configuracion de la tarjeta FRDM-MCXN947.
 *
 */

#ifndef FRDM_MCXN947_H_
#define FRDM_MCXN947_H_
#include "GPIO.h"


#define RED_LED_GPIO (GPIO0)
#define GREEN_LED_GPIO (GPIO0)
#define BLUE_LED_GPIO (GPIO1)


#define RED_LED_PORT (PORT0)
#define GREEN_LED_PORT (PORT0)
#define BLUE_LED_PORT (PORT1)

#define  RED_LED_PIN  (10U)
#define  GREEN_LED_PIN  (27U)
#define  BLUE_LED_PIN   (2U)


#define SW2_GPIO (GPIO0)
#define SW3_GPIO (GPIO0)


#define SW1_PORT (PORT0)
#define SW2_PORT (PORT0)
#define SW3_PORT (PORT0)


#define SW2_PIN (23U)
#define SW3_PIN (6U)

#define DAC_PORT (PORT4)
#define DAC_PIN  (2U)

#define HIGH 1U
#define LOW 0U


typedef enum{
	FALSE,
	TRUE
} bool_value_t;



#endif /* FRDM_MCXN947_H_ */

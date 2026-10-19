/*
 * GPIO.h
 *
 *  Created on: 17 jun. 2026
 *      Author: Emilio Renteria y Nathalie Marin
 *
 *      Este es el archivo header para el manejo de pines GPIO.
 *      Contiene la configuracion de entradas, salidas, pines de botones
 *      y el control de sus banderas de interrupcion.
 *
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>
#include "fsl_gpio.h"
#include "fsl_port.h"

#define PIN_2 2u
#define PIN_3 3u
#define PIN_4 4u
#define PIN_5 5u
#define PIN_6 6u
#define PIN_7 7u

#define GPIO_ALL_BITS 0xFFFFFFFF


typedef enum
{
    GPIO_Port0 = 0,
    GPIO_Port1,
    GPIO_Port2,
    GPIO_Port3,
    GPIO_Port4,
    GPIO_Port5
} gpio_port_t;

typedef enum
{
    GPIO_Input,
    GPIO_Output
} gpio_direction_t;

typedef struct
{
	uint8_t flag_gpio_0_23: 1;
	uint8_t flag_gpio_0_6 : 1;
	uint8_t flag_gpio_0_14 : 1;
	uint8_t flag_gpio_0_22 : 1;
	uint8_t flag_gpio_3_4 : 1;
	uint8_t flag_gpio_3_5 : 1;
	uint8_t flag_gpio_4_22 : 1;
	uint8_t flag_gpio_4_23 : 1;

} gpio_interrupt_flags_t;


/*! These constants are used to select an specific port in the different API functions*/
typedef enum{GPIO_0, /*!< Definition to select GPIO A */
			 GPIO_1, /*!< Definition to select GPIO B */
			 GPIO_2, /*!< Definition to select GPIO C */
			 GPIO_3, /*!< Definition to select GPIO D */
			 GPIO_4, /*!< Definition to select GPIO E */
			 GPIO_5  /*!< Definition to select GPIO F */
} gpio_name_t;


void GPIO_init(void);
void GPIO_pin_init(gpio_port_t port, uint8_t pin, gpio_direction_t direction);
void GPIO_write(gpio_port_t port, uint8_t pin, uint8_t value);
uint8_t GPIO_read(gpio_port_t port, uint8_t pin);

void Button_init(gpio_port_t port, uint8_t pin);
void GPIO_init_switches_and_LEDs(void);
uint8_t GPIO_clear_irq_status(gpio_name_t gpio, uint8_t pin);
uint8_t GPIO_get_irq_status(gpio_name_t gpio, uint8_t pin );
void GPIO_callback_init(gpio_name_t gpio_name, void (*handler)(void));

#endif /* GPIO_H_ */


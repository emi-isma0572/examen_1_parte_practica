/*
 * GPIO.c
 *
 *  Created on: 17 jun. 2026
 *      Author: Emilio y Nathalie
 *
 *
 */

#include "GPIO.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "frdm_mcxn947.h"
#include "MCXN947_cm33_core0_COMMON.h"
#include "Digital_Watch_Pins.h"
#include "NVIC.h"

static void (*gpio_0_callback)(void) = 0;

volatile static gpio_interrupt_flags_t g_intr_status_flag = {0};

void GPIO_callback_init(gpio_name_t gpio_name, void (*handler)(void))
{
	if(GPIO_0 == gpio_name)
	{
		gpio_0_callback = handler;

	}
}

void GPIO00_IRQHandler (void)
{

	uint8_t status_sw2;
	uint8_t status_sw3;
	uint8_t status_stopwatch;
	uint8_t status_alarm;

	status_sw2 = GPIO_PinGetInterruptFlag (GPIO0, SW2_PIN);
	status_sw3 = GPIO_PinGetInterruptFlag (GPIO0, SW3_PIN);
	status_stopwatch = GPIO_PinGetInterruptFlag(GPIO0, TIME_STOPWATCH_PIN);
	status_alarm = GPIO_PinGetInterruptFlag(GPIO0, TIME_ALARM_PIN);

	if(status_sw2)
	{
		g_intr_status_flag.flag_gpio_0_23 =  TRUE;
	}
	if(status_sw3)
	{
		g_intr_status_flag.flag_gpio_0_6 =  TRUE;
	}
	if(status_stopwatch)
	{
		g_intr_status_flag.flag_gpio_0_14 = TRUE;
	}

	if(status_alarm)
	{
		g_intr_status_flag.flag_gpio_0_22 = TRUE;
	}

	if(gpio_0_callback)
	{
		gpio_0_callback();
	}

	GPIO_GpioClearInterruptFlags(GPIO0, GPIO_ALL_BITS);

}

void GPIO30_IRQHandler (void)
{

	uint8_t status_min_stop;
	uint8_t status_clear;

	status_min_stop = GPIO_PinGetInterruptFlag(GPIO3,MIN_STOP_PIN);
	status_clear = GPIO_PinGetInterruptFlag(GPIO3,CLEAR_PIN);

	if(status_min_stop)
	{
		g_intr_status_flag.flag_gpio_3_5 =  TRUE;
	}
	if(status_clear)
	{
		g_intr_status_flag.flag_gpio_3_4 =  TRUE;
	}

	GPIO_GpioClearInterruptFlags(GPIO3, GPIO_ALL_BITS);

}

void GPIO40_IRQHandler (void)
{

	uint8_t status_config_time;
	uint8_t status_hour_start;

	status_config_time = GPIO_PinGetInterruptFlag(GPIO4, CONFIG_TIME_PIN);
	status_hour_start = GPIO_PinGetInterruptFlag(GPIO4, HOUR_START_PIN);

	if(status_config_time)
	{
		g_intr_status_flag.flag_gpio_4_23 =  TRUE;
	}
	if(status_hour_start)
	{
		g_intr_status_flag.flag_gpio_4_22 =  TRUE;
	}

	GPIO_GpioClearInterruptFlags(GPIO4, GPIO_ALL_BITS);

}

uint8_t GPIO_clear_irq_status(gpio_name_t gpio, uint8_t pin)
{
	uint8_t status = FALSE;

	if(GPIO_0 == gpio)
	{
		if(SW2_PIN == pin)
		{
			g_intr_status_flag.flag_gpio_0_23 = FALSE;
			status = TRUE;
		}
		else if(SW3_PIN == pin)
		{
			g_intr_status_flag.flag_gpio_0_6 = FALSE;
			status = TRUE;
		}
		else if(TIME_STOPWATCH_PIN == pin)
		{
		    g_intr_status_flag.flag_gpio_0_14 = FALSE;
		    status = TRUE;
		}
		else if(TIME_ALARM_PIN == pin)
		{
		    g_intr_status_flag.flag_gpio_0_22 = FALSE;
		    status = TRUE;
		}
		else
		{
			status = FALSE;
		}
	}

	else if (GPIO_3 == gpio)
	{
		if (MIN_STOP_PIN == pin)
		{
			g_intr_status_flag.flag_gpio_3_5 = FALSE;
			status = TRUE;
		}
		else if (CLEAR_PIN == pin)
		{
			g_intr_status_flag.flag_gpio_3_4 = FALSE;
			status = TRUE;
		}
		else
		{
			status = FALSE;
		}
	}

	else if (GPIO_4 == gpio)
	{
		if (CONFIG_TIME_PIN == pin)
		{
			g_intr_status_flag.flag_gpio_4_23 = FALSE;
			status = TRUE;
		}
		else if (HOUR_START_PIN == pin)
		{
			g_intr_status_flag.flag_gpio_4_22 = FALSE;
			status = TRUE;
		}
		else
		{
			status = FALSE;
		}
	}

	return(status);
}

uint8_t GPIO_get_irq_status(gpio_name_t gpio, uint8_t pin)
{
	uint8_t status = FALSE;

	if(GPIO_0 == gpio)
	{
		if(SW2_PIN == pin)
		{
			status = g_intr_status_flag.flag_gpio_0_23;
		}
		else if(SW3_PIN == pin)
		{
			status = g_intr_status_flag.flag_gpio_0_6;
		}
		else if(TIME_STOPWATCH_PIN == pin)
		{
		    status = g_intr_status_flag.flag_gpio_0_14;
		}
		else if(TIME_ALARM_PIN == pin)
		{
		    status = g_intr_status_flag.flag_gpio_0_22;
		}
	}

	else if (GPIO_3 == gpio)
	{
		if (MIN_STOP_PIN == pin)
		{
			status = g_intr_status_flag.flag_gpio_3_5;
		}
		else if (CLEAR_PIN == pin)
		{
			status = g_intr_status_flag.flag_gpio_3_4;
		}
	}

	else if (GPIO_4 == gpio)
	{
		if (CONFIG_TIME_PIN == pin)
		{
			status = g_intr_status_flag.flag_gpio_4_23;
		}
		else if (HOUR_START_PIN == pin)
		{
			status = g_intr_status_flag.flag_gpio_4_22;
		}
	}
	return(status);

}


static GPIO_Type * GPIO_get_base(gpio_port_t port)
{
    switch(port)
    {
        case GPIO_Port0:
            return GPIO0;

        case GPIO_Port1:
            return GPIO1;

        case GPIO_Port2:
            return GPIO2;

        case GPIO_Port3:
            return GPIO3;

        case GPIO_Port4:
            return GPIO4;

        case GPIO_Port5:
            return GPIO5;

        default:
            return NULL;
    }
}

static PORT_Type * PORT_get_base(gpio_port_t port)
{
    switch(port)
    {
        case GPIO_Port0:
            return PORT0;

        case GPIO_Port1:
            return PORT1;

        case GPIO_Port2:
            return PORT2;

        case GPIO_Port3:
            return PORT3;

        case GPIO_Port4:
            return PORT4;

        case GPIO_Port5:
            return PORT5;

        default:
            return NULL;
    }
}

static clock_ip_name_t PORT_clock_get_name(gpio_port_t port)
{
	switch(port)
	{
		case GPIO_Port0:
			return kCLOCK_Port0;

		case GPIO_Port1:
			return kCLOCK_Port1;

		case GPIO_Port2:
			return kCLOCK_Port2;

		case GPIO_Port3:
			return kCLOCK_Port3;

		case GPIO_Port4:
			return kCLOCK_Port4;

		default:
			return kCLOCK_Port0;
	}
}


void Button_init(gpio_port_t port, uint8_t pin){

    GPIO_Type * gpio;
    PORT_Type * port_base;
    clock_ip_name_t clock;

    clock = PORT_clock_get_name(port);
    gpio = GPIO_get_base(port);
    port_base = PORT_get_base(port);

    CLOCK_EnableClock(clock);

	const port_pin_config_t button_config = {/* Internal pull-up/down resistor is disabled */
																  kPORT_PullUp,
																  /* Low internal pull resistor value is selected. */
																  kPORT_LowPullResistor,
																  /* Fast slew rate is configured */
																  kPORT_FastSlewRate,
																  /* Passive input filter is disabled */
																  kPORT_PassiveFilterEnable,
																  /* Open drain output is disabled */
																  kPORT_OpenDrainDisable,
																  /* Low drive strength is configured */
																  kPORT_LowDriveStrength,
																  /* Pin is configured as PIO0_10 */
																  kPORT_MuxAlt0,
																  /* Digital input enabled */
																  kPORT_InputBufferEnable,
																  /* Digital input is not inverted */
																  kPORT_InputNormal,
																  /* Pin Control Register fields [15:0] are not locked */
																  kPORT_UnlockRegister};

    if((gpio == NULL) || (port_base == NULL))
    {
        return;
    }

    gpio_pin_config_t gpio_config;

    gpio_config.pinDirection = kGPIO_DigitalInput;
    gpio_config.outputLogic = 0;

    PORT_SetPinConfig(port_base, pin, &button_config);
    GPIO_PinInit(gpio, pin, &gpio_config);


}


void GPIO_pin_init(gpio_port_t port, uint8_t pin, gpio_direction_t direction)
{
    GPIO_Type * gpio;
    PORT_Type * port_base;
    clock_ip_name_t clock;

    clock = PORT_clock_get_name(port);
    gpio = GPIO_get_base(port);
    port_base = PORT_get_base(port);

    CLOCK_EnableClock(clock);

    const port_pin_config_t output_config = {/* Internal pull-up/down resistor is disabled */
		                                                      kPORT_PullDisable,
		                                                      /* Low internal pull resistor value is selected. */
		                                                      kPORT_LowPullResistor,
		                                                      /* Fast slew rate is configured */
		                                                      kPORT_FastSlewRate,
		                                                      /* Passive input filter is disabled */
		                                                      kPORT_PassiveFilterDisable,
		                                                      /* Open drain output is disabled */
		                                                      kPORT_OpenDrainDisable,
		                                                      /* Low drive strength is configured */
		                                                      kPORT_LowDriveStrength,
		                                                      /* Pin is configured as PIO0_10 */
		                                                      kPORT_MuxAlt0,
		                                                      /* Digital input enabled */
		                                                      kPORT_InputBufferEnable,
		                                                      /* Digital input is not inverted */
		                                                      kPORT_InputNormal,
		                                                      /* Pin Control Register fields [15:0] are not locked */
		                                                      kPORT_UnlockRegister};

	const port_pin_config_t input_config = {/* Internal pull-up/down resistor is disabled */
															  kPORT_PullUp,
															  /* Low internal pull resistor value is selected. */
															  kPORT_LowPullResistor,
															  /* Fast slew rate is configured */
															  kPORT_FastSlewRate,
															  /* Passive input filter is disabled */
															  kPORT_PassiveFilterEnable,
															  /* Open drain output is disabled */
															  kPORT_OpenDrainDisable,
															  /* Low drive strength is configured */
															  kPORT_LowDriveStrength,
															  /* Pin is configured as PIO0_10 */
															  kPORT_MuxAlt0,
															  /* Digital input enabled */
															  kPORT_InputBufferEnable,
															  /* Digital input is not inverted */
															  kPORT_InputNormal,
															  /* Pin Control Register fields [15:0] are not locked */
															  kPORT_UnlockRegister};

    if((gpio == NULL) || (port_base == NULL))
    {
        return;
    }

    gpio_pin_config_t gpio_config;

    if(GPIO_Output == direction)
    {
        gpio_config.pinDirection = kGPIO_DigitalOutput;
        gpio_config.outputLogic = 0;
        PORT_SetPinConfig(port_base, pin, &output_config);
    }
    else
    {
        gpio_config.pinDirection = kGPIO_DigitalInput;
        gpio_config.outputLogic = 0;
        PORT_SetPinConfig(port_base, pin, &input_config);
    }

    GPIO_PinInit(gpio, pin, &gpio_config);
}

void GPIO_write(gpio_port_t port, uint8_t pin,uint8_t value)
{
    GPIO_Type *gpio = GPIO_get_base(port);

    if(gpio != NULL)
    {
        GPIO_PinWrite(gpio, pin, value);
    }
}

uint8_t GPIO_read(gpio_port_t port, uint8_t pin)
{
    GPIO_Type *gpio = GPIO_get_base(port);

    if(gpio != NULL)
    {
        return GPIO_PinRead(gpio, pin);
    }

    return 0;
}


void GPIO_init_switches_and_LEDs(void)
{
	/* Define the init structure for the output LED pin*/
		gpio_pin_config_t led_config = {
			kGPIO_DigitalOutput,
			1,
		};

		gpio_pin_config_t sw_config = {
			kGPIO_DigitalInput,
			0,
		};

		/* Enables the clock for PORT0 controller: Enables clock */
		CLOCK_EnableClock(kCLOCK_Port0);
		/* Enables the clock for PORT1: Enables clock */
		CLOCK_EnableClock(kCLOCK_Port1);

		const port_pin_config_t output_config = {/* Internal pull-up/down resistor is disabled */
			                                                      kPORT_PullDisable,
			                                                      /* Low internal pull resistor value is selected. */
			                                                      kPORT_LowPullResistor,
			                                                      /* Fast slew rate is configured */
			                                                      kPORT_FastSlewRate,
			                                                      /* Passive input filter is disabled */
			                                                      kPORT_PassiveFilterDisable,
			                                                      /* Open drain output is disabled */
			                                                      kPORT_OpenDrainDisable,
			                                                      /* Low drive strength is configured */
			                                                      kPORT_LowDriveStrength,
			                                                      /* Pin is configured as PIO0_10 */
			                                                      kPORT_MuxAlt0,
			                                                      /* Digital input enabled */
			                                                      kPORT_InputBufferEnable,
			                                                      /* Digital input is not inverted */
			                                                      kPORT_InputNormal,
			                                                      /* Pin Control Register fields [15:0] are not locked */
			                                                      kPORT_UnlockRegister};
		/* PORT0_10 (pin B12) is configured as PIO0_10 */
		PORT_SetPinConfig(RED_LED_PORT, RED_LED_PIN, &output_config);
		PORT_SetPinConfig(GREEN_LED_PORT, GREEN_LED_PIN, &output_config);
		PORT_SetPinConfig(BLUE_LED_PORT, BLUE_LED_PIN, &output_config);

		const port_pin_config_t input_config = {/* Internal pull-up/down resistor is disabled */
																  kPORT_PullUp,
																  /* Low internal pull resistor value is selected. */
																  kPORT_LowPullResistor,
																  /* Fast slew rate is configured */
																  kPORT_FastSlewRate,
																  /* Passive input filter is disabled */
																  kPORT_PassiveFilterEnable,
																  /* Open drain output is disabled */
																  kPORT_OpenDrainDisable,
																  /* Low drive strength is configured */
																  kPORT_LowDriveStrength,
																  /* Pin is configured as PIO0_10 */
																  kPORT_MuxAlt0,
																  /* Digital input enabled */
																  kPORT_InputBufferEnable,
																  /* Digital input is not inverted */
																  kPORT_InputNormal,
																  /* Pin Control Register fields [15:0] are not locked */
																  kPORT_UnlockRegister};


			PORT_SetPinConfig(SW2_PORT, SW2_PIN, &input_config);
			PORT_SetPinConfig(SW3_PORT, SW3_PIN, &input_config);

			GPIO_PinInit(RED_LED_GPIO, RED_LED_PIN, &led_config);
			GPIO_PinInit(GREEN_LED_GPIO, GREEN_LED_PIN, &led_config);
			GPIO_PinInit(BLUE_LED_GPIO, BLUE_LED_PIN, &led_config);

			GPIO_PinInit(SW2_GPIO, SW2_PIN, &sw_config);
			GPIO_PinInit(SW3_GPIO, SW3_PIN, &sw_config);

			GPIO_SetPinInterruptConfig(SW2_GPIO, SW2_PIN, kGPIO_InterruptFallingEdge);
			GPIO_SetPinInterruptConfig(SW3_GPIO, SW3_PIN, kGPIO_InterruptFallingEdge);

			NVIC_enable_interrupt_and_priotity(NVIC_GPIO00_IRQn, PRIORITY_4);

}




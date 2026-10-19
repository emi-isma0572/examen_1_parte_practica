/*
 * MRT.h
 *
 *  Created on: 20 sep. 2026
 *      Author: Emilio Renteria
 *
 *      Este es el archivo header para la configuracion del MRT.
 *      Contiene las funciones de inicializacion de canales y callbacks
 *
 */

#ifndef MRT_H_
#define MRT_H_
#include "fsl_mrt.h"
#include "frdm_mcxn947.h"

#define MRT_CLK_FREQ 48000000U

typedef enum {
	MRT_Channel_0,
	MRT_Channel_1,
	MRT_Channel_2,
	MRT_Channel_3
} mrt_channel_t;

typedef struct {
	uint8_t MRT_Channel_0_flag: 1;
	uint8_t MRT_Channel_1_flag: 1;
	uint8_t MRT_Channel_2_flag: 1;
	uint8_t MRT_Channel_3_flag: 1;
} mrt_interrupt_flags_t;

void MRT_config();
void MRT_setup_channel(mrt_channel_t mrt_channel);
void MRT_callback_init(mrt_channel_t mrt_channel, void (*handler)(void));
void MRT_start(mrt_channel_t mrt_channel, uint32_t cycles);
bool_value_t MRT_get_irq_satus(mrt_channel_t channel);
void MRT_clear_irq_satus(mrt_channel_t channel);


#endif /* MRT_H_ */

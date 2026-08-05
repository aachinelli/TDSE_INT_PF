/*
 * Copyright (c) 2026 Juan Manuel Cruz <jcruz@fi.uba.ar> <jcruz@frba.utn.edu.ar>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * @author : Juan Manuel Cruz <jcruz@fi.uba.ar> <jcruz@frba.utn.edu.ar>
 */

#ifndef TASK_SENSOR_ATTRIBUTE_H_
#define TASK_SENSOR_ATTRIBUTE_H_

/********************** CPP guard ********************************************/
#ifdef __cplusplus
extern "C" {
#endif

/********************** inclusions *******************************************/

/********************** macros ***********************************************/

/********************** typedef **********************************************/
/* Events to excite Task Sensor */
typedef enum task_sensor_ev {EV_BTN_UP,
							 EV_BTN_DOWN} task_sensor_ev_t;

/* States of Task Sensor */
typedef enum task_sensor_st {ST_BTN_UP,
							 ST_BTN_FALLING,
							 ST_BTN_DOWN,
						     ST_BTN_RISING} task_sensor_st_t;

/* Identifier of Task Sensor */
typedef enum task_sensor_id {
	ID_BTN_UP,      // Para D12
	ID_BTN_DOWN,    // Para D11
	ID_BTN_ENTER,   // Para D10
	ID_BTN_BACK     // Para D9
} task_sensor_id_t;

typedef struct
{
	task_sensor_id_t	identifier;
	GPIO_TypeDef *		gpio_port;
	uint16_t			pin;
	GPIO_PinState		pressed;
	uint32_t			tick_max;
	task_system_ev_t	signal_up;
	task_system_ev_t	signal_down;
} task_sensor_cfg_t;

typedef struct
{
	uint32_t			tick;
	task_sensor_st_t	state;
	task_sensor_ev_t	event;
} task_sensor_dta_t;

/* ---------------------------------------------------------------------------
 * DHT22 (Temperatura / Humedad) - Maquina de estados no bloqueante
 * ------------------------------------------------------------------------ */

/* Estados de la FSM del DHT22 */
typedef enum task_dht22_st {
	ST_DHT_IDLE,			/* Reposo: cuenta ticks hasta el proximo muestreo        */
	ST_DHT_TRIGGER_LOW,		/* Master baja la linea (OUTPUT), cuenta 20ms             */
	ST_DHT_TRIGGER_HIGH,	/* Handshake + lectura completa de 40 bits en una llamada */
	ST_DHT_DONE,			/* Trama completa: valida checksum y publica              */
	ST_DHT_ERROR			/* Timeout o checksum invalido: vuelve a IDLE             */
} task_dht22_st_t;

/* Cantidad total de bits de la trama DHT22 (5 bytes) */
#define DHT22_BIT_QTY		40u

typedef struct
{
	task_dht22_st_t		state;
	uint32_t			tick;			/* contador generico: ticks de 1ms (idle 2s, trigger 20ms, timeouts) */
	uint32_t			edge_time;		/* snapshot de TIM3 al iniciar la espera/medicion de un flanco */

	uint8_t				bit_index;		/* bit actual dentro de la trama, 0..39 */
	uint8_t				dht_bits[DHT22_BIT_QTY]; /* bits crudos leidos (0/1), antes de empaquetar en bytes */

	/* Bytes crudos de la trama, misma variante que el prototipo de prueba */
	uint8_t				Rh_byte1;
	uint8_t				Rh_byte2;
	uint8_t				Temp_byte1;
	uint8_t				Temp_byte2;
	uint8_t				SUM;

	float				Temperature;
	float				Humidity;
	bool				data_valid;		/* true cuando Temperature/Humidity son validos */
} task_dht22_dta_t;

/********************** external data declaration ****************************/
extern task_sensor_dta_t task_sensor_dta_list[];
extern task_dht22_dta_t   task_dht22_dta;

/********************** external functions declaration ***********************/

/********************** End of CPP guard *************************************/
#ifdef __cplusplus
}
#endif

#endif /* TASK_SENSOR_ATTRIBUTE_H_ */

/********************** end of file ******************************************/

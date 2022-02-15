/*
 * RPPU_GLONASS_SINT.h
 *
 *  Created on: 13 янв. 2019 г.
 *      Author: mouse
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "RPPU.h"

#ifndef RPPU_GLONASS_SINT_H_
#define RPPU_GLONASS_SINT_H_


enum
{
		L1,
		L2
}glonass_range;

enum
{
		p06=6,
		p05=5,
		p04=4,
		p03=3,
		p02=2,
		p01=1,
		p00=0,
		m01=-1,
		m02=-2,
		m03=-3,
		m04=-4,
		m05=-5,
		m06=-6,
}channel_num;



struct sint1_params
{
	uint32_t N;
	uint32_t FRAC;
	uint32_t MOD;
	uint32_t B; //  out divider
	uint32_t R; // ref divider

} ;

/*    настрйока синтезатора    */
uint32_t  rppu_glonass_sint_setup(  struct sint1_params *params,struct  rppu_rf *phy, uint8_t VS, uint8_t band);

uint32_t calculate_sint_regs(uint8_t range, uint8_t channel_num,double delta_f, struct sint1_params *params);

#endif /* RPPU_GLONASS_SINT_H_ */

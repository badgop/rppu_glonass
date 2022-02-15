/*
 * RPPU_API.h
 *
 *  Created on: 23 марта 2018 г.
 *      Author: Ivan
 */

#include "RPPU.h"
#include "RPPU_spi_write.h"
#include "stdint.h"


#ifndef SRC_RPPU_API_H_
#define SRC_RPPU_API_H_



/******************************Глобальные переменные для API***************************/
extern struct rppu_init_params  rppu_parameters;


/*структура для описания исходных параметров РППУ*/
struct rppu_init_params
{

	uint32_t ref_freq; /*Частота опорного сигнала*/


};



/*    обьявление структуры состояния РППУ и установка значений по умолчанию   */
int32_t  rppu_init(  struct  rppu_rf **rppy_rf_phy);






/*
 * Включение приемника для последующей коррекции DC-смещения
 */
int32_t rppu_1ch_dc_corr(struct  rppu_rf *phy);

/*
 * Включение коррекции постоянного смещения
 */
u32 enable_dc_correction(struct  rppu_rf *phy);



#endif /* SRC_RPPU_API_H_ */

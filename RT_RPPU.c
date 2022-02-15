/*
 * RT_RPPU.c
 *
 *  Created on: 19 марта 2018 г.
 *      Author: Ivan
 */

/*инициализация РППУ*/



#include "RT_AD.h"

#include "RT_RPPU.h"
#include "muxin.h"
#include "rppu.h"


struct rppu_init_params rppu_default_params=
{
		10000000
		/*Частота опорного сигнала*/
};





/*   настройка РППУ в режим приемопередатчика 1 канла   */
uint32_t  rppu_1ch_tr_rec_setup(  struct  rppu_rf *phy, uint8_t amplify)
{

	/*настройка приемника на прием сигналов 1 канала*/
	rppu_reciev_setup( phy, amplify );

	/*настройка передатчика на передачу сигнало 1 канала*/

	/*НЕЧЕГО НАСТРАИВАТЬ*/
	rppu_tranciev_setup(  phy);

	return 1;
}


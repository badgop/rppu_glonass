/*
 * RPPU_API.c
 *
 *  Created on: 23 марта 2018 г.
 *      Author: Ivan
 */

#include "RPPU_API.h"
#include "RPPU.h"
#include "stddef.h"


/*************************************************************************************/



/******************************Глобальные переменные для API***************************/



/*            Инициализация  структуры РППУ и установка значений по умолчанию       */
int32_t  rppu_init(  struct  rppu_rf **rppy_rf_phy)
{
	/* копия для выделения памяти и инициализации*/
	struct rppu_rf *phy;

	phy = (struct rppu_rf *)zmalloc(sizeof(*phy));
	if (!phy) {
			return -1;
		}


	/*Запись в РППУ значений регистров по умолчанию*/
	rppu_setup_by_default(phy);


	/*настройка делителя опорной частоты*/
	/*
	phy->input_parameters.ref_clk_freq=params->ref_freq;
	phy->sint1_reg3.reg_by_bit.RD=phy->input_parameters.ref_clk_freq/RPPU_PREDEF_FCOPM;
	rppu_setreg_sin1_reg3( phy);
*/
	/*Возвращаем структуру*/
	*rppy_rf_phy=phy;

	free(phy);

	return 0;
}













int32_t rppu_1ch_dc_corr(struct  rppu_rf *phy)
{


		//muxin_set_rppu_on((uint8_t) 0);
		 Xil_Out32((BA_muxin),        (u32)(0x1203601));

		rppu_init(&phy);

//		phy->rec_mixer1.reg_by_bit.CNT_I=cnt_i_corr;
//		phy->rec_mixer1.reg_by_bit.CNT_I=cnt_q_corr;

		rppu_1ch_dc_corr_enable(phy);

		return 1;

}
u32 enable_dc_correction(struct  rppu_rf *phy)
{
	u16 cnt_i = 0, cnt_q = 0;

	Xil_Out32((CH1_DC_LVL_PER), (u32)(2000));

	while (1)
	{
		measure_and_calc_correct_i_q_levels(1,1);
//		stop_transmission();
//		mdelay(1000);
		rppu_setup_by_default(phy);
//		mdelay(1000);
//		start_test_rcv((uint32_t) 3500, (uint32_t) 3);
		mdelay(1000);
		rppu_quad_demod_enable_with_leveling(phy, cnt_i, cnt_q);

//		while (1) {}
		cnt_i += 9999999;
		cnt_q += 9999999;

		xil_printf("Correction value = %u\n", cnt_i);
		mdelay(500);
	}
	return 1;
}
/*       ******************************************************************      */

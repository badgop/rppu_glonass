/*
 * glonass_tr.c
 *
 *  Created on: Dec 20, 2018
 *      Author: User1
 */


#include "glonass_tr.h"

void ch1_fir_tr_glo_load()
{


		/*20_mhz_0_511khz*/
		Xil_Out32((BA_T1k1+	0x0	),(u32)(-76		));
		Xil_Out32((BA_T1k1+	0x4	),(u32)(-116		));
		Xil_Out32((BA_T1k1+	0x8	),(u32)(-165		));
		Xil_Out32((BA_T1k1+	0xc	),(u32)(-221		));
		Xil_Out32((BA_T1k1+	0x10	),(u32)(-282		));
		Xil_Out32((BA_T1k1+	0x14	),(u32)(-344		));
		Xil_Out32((BA_T1k1+	0x18	),(u32)(-402		));
		Xil_Out32((BA_T1k1+	0x1c	),(u32)(-451		));
		Xil_Out32((BA_T1k1+	0x20	),(u32)(-483		));
		Xil_Out32((BA_T1k1+	0x24	),(u32)(-493		));
		Xil_Out32((BA_T1k1+	0x28	),(u32)(-471		));
		Xil_Out32((BA_T1k1+	0x2c	),(u32)(-411		));
		Xil_Out32((BA_T1k1+	0x30	),(u32)(-305		));
		Xil_Out32((BA_T1k1+	0x34	),(u32)(-145		));
		Xil_Out32((BA_T1k1+	0x38	),(u32)(71		));
		Xil_Out32((BA_T1k1+	0x3c	),(u32)(351		));
		Xil_Out32((BA_T1k1+	0x40	),(u32)(694		));
		Xil_Out32((BA_T1k1+	0x44	),(u32)(1101		));
		Xil_Out32((BA_T1k1+	0x48	),(u32)(1569		));
		Xil_Out32((BA_T1k1+	0x4c	),(u32)(2093		));
		Xil_Out32((BA_T1k1+	0x50	),(u32)(2664		));
		Xil_Out32((BA_T1k1+	0x54	),(u32)(3272		));
		Xil_Out32((BA_T1k1+	0x58	),(u32)(3905		));
		Xil_Out32((BA_T1k1+	0x5c	),(u32)(4548		));
		Xil_Out32((BA_T1k1+	0x60	),(u32)(5184		));
		Xil_Out32((BA_T1k1+	0x64	),(u32)(5798		));
		Xil_Out32((BA_T1k1+	0x68	),(u32)(6373		));
		Xil_Out32((BA_T1k1+	0x6c	),(u32)(6892		));
		Xil_Out32((BA_T1k1+	0x70	),(u32)(7340		));
		Xil_Out32((BA_T1k1+	0x74	),(u32)(7703		));
		Xil_Out32((BA_T1k1+	0x78	),(u32)(7971		));
		Xil_Out32((BA_T1k1+	0x7c	),(u32)(8135		));
		Xil_Out32((BA_T1k1+	0x80	),(u32)(8191		));

		mdelay(10);

}

uint32_t glonass_main(uint32_t * data_ptr, uint16_t table_len)
{
	uint32_t rez=0;
	uint32_t last_data_reg_mask=0x1FFFFF;

	ch1_fir_tr_glo_load();


	uint64_t cod_f=7191685654957;
	uint32_t cod_f_32=cod_f&0xFFFFFFFF;
	uint32_t cod_f_16=(cod_f>>32)&0xFFFF;

	/*     (2**32/(20MHz))*511kHz      */
	//Xil_Out32(GLONASS_COD_F,109736414);

	Xil_Out32(GLONASS_COD_F_32,cod_f_32);
	Xil_Out32(GLONASS_COD_F_16,cod_f_16);


	Xil_Out32(GLONASS_DELAY_COD,0);

	Xil_Out32(GLONASS_CONTR ,0x7);

	/* external pps synchronization OFF  */
	Xil_Out32(GLONASS_SYNC_EXT ,0x0);

	/* internal pps synchronization ON  */
	Xil_Out32(GLONASS_SYNC_INT  ,0x1);

	/* internal pps synchronization mode ON  */
	Xil_Out32(GLONASS_SYNC_MODE  ,0x1);

	Xil_Out32(GLONASS_DELAY_START,0x0);


	/*GLONASS TRANSMITTER ON*/
	Xil_Out32(GLONASS_START_REG,0x0000);

	Xil_Out32((BA_RC + 0x00), (u32)(0x0002));

	/*TR1 in GLONASS MODE ON*/
	/*need 4 but 5 is illegal mode*/
	Xil_Out32((BA_T1 + 0xC),0x0004);

	/*GLONASS TRANSMITTER ON*/
	Xil_Out32(GLONASS_START_REG,0x0001);

//	Xil_Out32((BA_RC + 0x00), (u32)(0x0002));






	uint32_t i=0;

	while(1)
	{
		//	ждем флага записи

		while((Xil_In32(GLONASS_RESTRICT_REC_FLAG)))
		{

		}


		/* DATA LOAD */
		xil_printf(" GLONASS_RESTRICT_REC_FLAG  %X \n", Xil_In32(GLONASS_RESTRICT_REC_FLAG));
		Xil_Out32(GLONASS_DATA_85_54,*(data_ptr+i));

		Xil_Out32(GLONASS_DATA_53_22,*(data_ptr+i+1));
		Xil_Out32(GLONASS_DATA_21_1,(*(data_ptr+i+2))&last_data_reg_mask);
		xil_printf(" DATA_LOADED  \n" );
		xil_printf(" GLONASS_RESTRICT_REC_FLAG  %X \n", Xil_In32(GLONASS_RESTRICT_REC_FLAG));
		i++;
		if (i>table_len)
		{
			i=0;
		}

		xil_printf(" GLONASS_CHIP_NUM  %X \n", Xil_In32(GLONASS_CHIP_NUM));

		xil_printf(" GLONASS_CHIP_FRAC  %X \n", Xil_In32(GLONASS_CHIP_FRAC));

		xil_printf(" GLONASS_TRANS_SYMB_CNT  %X \n", Xil_In32(GLONASS_TRANS_SYMB_CNT));
		xil_printf("  \n");

		//mdelay(1000);
	}




	return rez;
}

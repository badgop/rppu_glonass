/*
 * RPPU_GLONASS_SINT.c
 *
 *  Created on: 13 янв. 2019 г.
 *      Author: mouse
 */


struct sint1_params *sint_parameters;
#include "stddef.h"
#include "RPPU_GLONASS_SINT.h"
#include <stdint.h>
#include <math.h>
#include "RPPU.h"

struct sint1_params *sint1_parameters;


/*    настрйока синтезатора 1   */
uint32_t  rppu_glonass_sint_setup(  struct sint1_params *params, struct  rppu_rf *phy, uint8_t vs, uint8_t band)
{

	phy->sint1_reg1.reg_by_bit.FRAC=params->FRAC;
	phy->sint1_reg1.reg_by_bit.SP=0;
	phy->sint1_reg1.reg_by_bit.GPSP_SDM1=1;
	phy->sint1_reg1.reg_by_bit.SDM1_RST=0;



	phy->sint1_reg1.reg=rppu_setreg_sin1_reg1(  phy);
	xil_printf("REG1= %0x \n",phy->sint1_reg1.reg);

	phy->sint1_reg2.reg_by_bit.DT=0;
	phy->sint1_reg2.reg_by_bit.sdm_sel=0;
	phy->sint1_reg2.reg_by_bit.MOD=params->MOD;

	phy->sint1_reg2.reg=rppu_setreg_sin1_reg2(  phy);
	xil_printf("REG2= %0x \n",phy->sint1_reg2.reg);

	phy->sint1_reg3.reg_by_bit.MX=8;
	phy->sint1_reg3.reg_by_bit.PFD_T=3;
	phy->sint1_reg3.reg_by_bit.RD=params->R;
	phy->sint1_reg3.reg_by_bit.ND=params->N;
	phy->sint1_reg3.reg_by_bit.SDM_ST=0;

	phy->sint1_reg3.reg=rppu_setreg_sin1_reg3(  phy);
	xil_printf("REG3= %0x \n",phy->sint1_reg3.reg);

	phy->sint1_reg4.reg_by_bit.agca=1;
	phy->sint1_reg4.reg_by_bit.agcd=1;
	phy->sint1_reg4.reg_by_bit.agcm=1;
	phy->sint1_reg4.reg_by_bit.band=band;
	phy->sint1_reg4.reg_by_bit.tb=1;
	phy->sint1_reg4.reg_by_bit.vs=vs;
	phy->sint1_reg4.reg_by_bit.c0=1;
	phy->sint1_reg4.reg_by_bit.agcic=0;
	phy->sint1_reg4.reg=rppu_setreg_sin1_reg4(  phy);
	xil_printf("REG4= %0x \n",phy->sint1_reg4.reg);


	enum{
		x1=0x7,
		x2=0x6,
		x8=0x3,
		x16=0

	}divider_dm;

	uint8_t divider=0;

	switch(params->B)
	{
		case 1:
			divider=x1;

		break;
		case 2:
			divider=x2;

		break;

		case 8:
					divider=x8;

				break;
		case 16:
			divider=x16;

		break;

		default:

			xil_printf("UNSUPPORTED DIVIDER - SETTING B=1 S \n");
			divider=x1;
			break;

	}


	phy->freq_divider.reg_by_bit.DM=divider;
	phy->freq_divider.reg=rppu_setreg_freq_divider(  phy);
	xil_printf("freq_divider= %0x \n",phy->freq_divider.reg);

	return 1;
}

uint32_t calculate_sint_regs(uint8_t range, uint8_t channel_num,double delta_f, struct sint1_params *params)
{

	const double l1of=1602e6l;
	const double l2of=1246e6l;
	const double l1_delta_f=562.5e3l;
	const double l2_delta_f=437.5e3l;
	/*REFERENCE FREQUENCY*/
	const double f_ref=10e6l;
	/*CAMPARE FREQUENCY*/
	const double f_comp=5e6l;
	const uint8_t dividers[5]={1,2,4,8,16};
	const double   vco_low= 2.4e9l/2;
	const double  vco_high=5e9l/2;

	uint32_t N;
	uint32_t FRAC;
	uint32_t MOD;

	uint32_t R;


	uint64_t vco_out=0;

	double f_needed=0;
	uint8_t b_needed=0;
	double n_ost=0;


	switch(range)
	{
		case(L1):
				f_needed=l1of+l1_delta_f*channel_num;
		break;
		case(L2):
				f_needed=l2of+l2_delta_f*channel_num;
		break;

	}



	R=f_ref/f_comp;
	N=f_needed/f_comp;

	uint32_t i=0;

	for(i=0;i<(sizeof(dividers)/sizeof(dividers[0]));i++)
	{
		 vco_out=N*f_comp*dividers[i];
		 if((vco_out>= vco_low)&&(vco_out<=vco_high))
		 {
			 b_needed= dividers[i];
			 break;
		 }
	}

	MOD=(f_comp/(b_needed*delta_f));

	n_ost=((f_needed/f_comp - (float)N));
	FRAC=round((MOD*n_ost));



	/*DEBUG PURPOSES ONLY*/
//	printf("R= %d \n",R);
//	printf("N= %d \n",N);
//	printf("B= %d \n",b_needed);
//	printf("MOD= %d \n",MOD);
//	printf("FRAC= %d \n",FRAC);




	/*cheking memory*/
/*
	params= (struct sint1_params *) malloc (sizeof(*params));
	if(!params){
		return -1;
	}
*/

	params->N=N;
	params->R=R;
	params->FRAC=FRAC;
	params->MOD=MOD;
	params->B=b_needed;


	/*coping allocated structure*/
	//*params=sint_parameters_copy;
	//free(sint_parameters_copy);

	return 1;
}



/*
 * RPPU.c
 *
 *  Created on: 12 марта 2018 г.
 *      Author: Ivan
 */
#include "RT_AD.h"
#include "RPPU.h"
#include "RPPU_spi_write.h"





/*Главный экземпляр структры rppu_rf*/
struct rppu_rf *rppu_rf_phy;




/*Таблица значений границ диапазонов определяемых LC контуром
 *
 *  низ|верх|номер контура *
 *
 */

  uint32_t lcs_edge[LCS][3]=
{ {1126934900 , 1429496729, 0},
 {1482300000 , 2183740000, 1},
 {1990202000 , 3117062000, 2} };

/*
uint32_t lcs_edge[LCS][3]=
		{{0,0,0},
		{0,0,0},
		{0,0,0}};
		*/



/*Таблица значений границ частотных поддиапазонов синтезатора 1 для НИЖНЕГО контура в Гц
 *
 *
 *  низ|верх|номер поддипазона
 *  */
/*

uint32_t lower_LC[64][3]=
{
	{ 	1126939000,	1136961000,	0},
	{ 	1130682000,	1140818000,	1},
	{ 	5,	5,	5},
	{ 	1139661000,	115002000,	3},
	{ 	1145828000,	1156395000,	4},
	{ 	1149632000,	1160321000,	5},
	{ 	1154767000,	1165607000,	6},
	{ 	5,	5,	5},
	{ 	5,	5,	5},
	{ 	5,	5,	5},
	{ 	1175930000,	1187434000,	10},
	{ 	5,	5,	5},
	{ 	5,	5,	5},
	{ 	5,	5,	5},
	{ 	5,	5,	5},
	{ 	5,	5,	5},
	{ 	5,	5,	5},
	{ 	5,	5,	5},
	{ 	5,	5,	5},
	{ 	5,	5,	5},
	{ 	5,	5,	5},
	{ 	5,	5,	5},
	{ 	5,	5,	5},
	{ 	5,	5,	5},
	{ 	5,	5,	5},
	{ 	5,	5,	5},
	{ 	5,	5,	5},
	{ 	5,	5,	5},
	{ 	5,	5,	5},
	{ 	5,	5,	5},
	{ 	5,	5,	5},
	{ 	5,	5,	5},
	{ 	5,	5,	5},
	{ 	5,	5,	5},
	{ 	5,	5,	5},
	{ 	5,	5,	5},
	{ 	5,	5,	5},
	{ 	5,	5,	5},
	{ 	5,	5,	5},
	{ 	5,	5,	5},
	{ 	5,	5,	5},
	{ 	5,	5,	5},
	{ 	5,	5,	5},
	{ 	5,	5,	5},
	{ 	5,	5,	5},
	{ 	5,	5,	5},
	{ 	5,	5,	5},
	{ 	5,	5,	5},
	{ 	5,	5,	5},
	{ 	5,	5,	5},
	{ 	5,	5,	5},
	{ 	5,	5,	5},
	{ 	5,	5,	5},
	{ 	5,	5,	5},
	{ 	5,	5,	5},
	{ 	5,	5,	5},
	{ 	5,	5,	5},
	{ 	5,	5,	5},
	{ 	5,	5,	5},
	{ 	5,	5,	5},
	{ 	5,	5,	5},
	{ 	5,	5,	5},
	{ 	5,	5,	5},
	{ 	5,	5,	5},
	{ 	5,	5,	5}
};
*/

/*Таблица значений границ частотных поддиапазонов синтезатора 1 для СРЕ контура
 *
 *
 *  низ|верх|номер поддипазона
 *  */

/* uint32_t middle_LC[64][3];*/

/*Таблица значений границ частотных поддиапазонов синтезатора 1 для нижнего контура
 *
 *
 *  низ|верх|номер поддипазона
 *  */

 /*uint32_t upper_LC[64][3];*/

/*       ******************************************************************      */




 /*  ********************************************************************************     */
 /*  ********** **************Функции для устновки значения регистров РППУ    **************************     */
 /*  ********************************************************************************     */


 uint32_t  rppu_setreg_rec_rf_part(  struct  rppu_rf *phy)
 {
	 uint32_t reg=0;

	 reg=bit_field_pack_u32(reg,phy->rec_rf_part_reg.reg_by_bit.ADR,(u8)  0,(u8) 0x1F);
	 reg=bit_field_pack_u32(reg,phy->rec_rf_part_reg.reg_by_bit.ATT,(u8) RPPU_REC_RF_PART_ATT_SHR,(u8) 0x7 );
	 reg=bit_field_pack_u32(reg,phy->rec_rf_part_reg.reg_by_bit.CH_S,(u8) RPPU_REC_RF_PART_CH_S,(u8) 0x1 );
	 reg=bit_field_pack_u32(reg,phy->rec_rf_part_reg.reg_by_bit.IN_S,(u8) RPPU_REC_RF_PART_IN_S,(u8) 0x1 );

	 rppu_write_reg(reg);

	 return reg;
 }



 uint32_t  rppu_setreg_rec_mixer1(  struct  rppu_rf *phy)
 {
	 uint32_t reg=0;

	 reg=bit_field_pack_u32(reg,phy->rec_mixer1.reg_by_bit.ADR,(u8)  0,(u8) 0x1F);
	 reg=bit_field_pack_u32(reg,phy->rec_mixer1.reg_by_bit.CNT_I,(u8) RPPU_REC_MIXER1_CNT_I_SHR  ,(u16)0xFFF );
	 reg=bit_field_pack_u32(reg,phy->rec_mixer1.reg_by_bit.DM_S,(u8) RPPU_REC_MIXER1_DM_S_SHR  ,(u8)0x1 );

	 rppu_write_reg(reg);

	 return reg;
 }

 uint32_t  rppu_setreg_rec_mixer2(  struct  rppu_rf *phy)
 {
	 uint32_t reg=0;

	 reg=bit_field_pack_u32(reg,phy->rec_mixer2.reg_by_bit.ADR,(u8)  0,(u8) 0x1F);
	 reg=bit_field_pack_u32(reg,phy->rec_mixer2.reg_by_bit.CNT_Q,(u8) RPPU_REC_MIXER2_CNT_Q_SHR  ,(u16)0xFFF );
	 reg=bit_field_pack_u32(reg,phy->rec_mixer2.reg_by_bit.DC_U,(u8) RPPU_REC_MIXER2_DC_U_SHR  ,(u8)0x1 );

	 rppu_write_reg(reg);

	 return reg;
 }


 uint32_t  rppu_setreg_rec_filter(  struct  rppu_rf *phy)
 {
	 uint32_t reg=0;

	 reg=bit_field_pack_u32(reg,phy->rec_filter.reg_by_bit.ADR,(u8)  0,(u8) 0x1F);
	 reg=bit_field_pack_u32(reg,phy->rec_filter.reg_by_bit.CHR_S,(u8)  RPPU_REC_FILTER_CHR_S_SHR,(u8) 0x1);
	 reg=bit_field_pack_u32(reg,phy->rec_filter.reg_by_bit.BP_PD,(u8)  RPPU_REC_FILTER_BP_PD_SHR,(u8) 0x1);
	 reg=bit_field_pack_u32(reg,phy->rec_filter.reg_by_bit.LPF,(u8)  RPPU_REC_FILTER_LPF_SHR,(u8) 0x3);
	 reg=bit_field_pack_u32(reg,phy->rec_filter.reg_by_bit.F_PD,(u8)  RPPU_REC_FILTER_F_PD_SHR,(u8) 0x1);

	 rppu_write_reg(reg);

	 return reg;
 }

 uint32_t  rppu_setreg_rec_ifa(  struct  rppu_rf *phy)
 {
	 uint32_t reg=0;

	 reg=bit_field_pack_u32(reg,phy->rec_ifa.reg_by_bit.ADR,(u8)  0,(u8) 0x1F);
	 reg=bit_field_pack_u32(reg,phy->rec_ifa.reg_by_bit.CH_PD,(u8)  RPPU_REC_IFA_CH_PD_SHR,(u8) 0x1);
	 reg=bit_field_pack_u32(reg,phy->rec_ifa.reg_by_bit.OB_PD,(u8)  RPPU_REC_IFA_OB_PD_SHR,(u8) 0x1);
	 reg=bit_field_pack_u32(reg,phy->rec_ifa.reg_by_bit.IQ_s,(u8)  RPPU_REC_IFA_IQ_S_SHR,(u8) 0x1);
	 reg=bit_field_pack_u32(reg,phy->rec_ifa.reg_by_bit.S_R,(u8)  RPPU_REC_IFA_S_R_SHR,(u8) 0x1);
	 reg=bit_field_pack_u32(reg,phy->rec_ifa.reg_by_bit.UN_C,(u8)  RPPU_REC_IFA_UN_C_SHR,(u8) 0x1);
	 reg=bit_field_pack_u32(reg,phy->rec_ifa.reg_by_bit.IFA,(u8)  RPPU_REC_IFA_IFA_SHR,(u8) 0x3F);
	 reg=bit_field_pack_u32(reg,phy->rec_ifa.reg_by_bit.IFC,(u8)  RPPU_REC_IFA_IFC_SHR,(u8) 0x7);
	 reg=bit_field_pack_u32(reg,phy->rec_ifa.reg_by_bit.I_PD,(u8)  RPPU_REC_IFA_I_PD_SHR,(u8) 0x1);

	 rppu_write_reg(reg);

	 return reg;
 }

 uint32_t  rppu_setreg_rec_adc(  struct  rppu_rf *phy)
 {
	 uint32_t reg=0;

	 reg=bit_field_pack_u32(reg,phy->rec_adc.reg_by_bit.ADR,(u8)  0,(u8) 0x1F);
	 reg=bit_field_pack_u32(reg,phy->rec_adc.reg_by_bit.CH_PD,(u8)   RPPU_REC_IFA_CH_PD_SHR,(u8) 0x1);
	 rppu_write_reg(reg);

	 return reg;
 }

 uint32_t  rppu_setreg_tr_dac(  struct  rppu_rf *phy)
 {
	 uint32_t reg=0;

	 reg=bit_field_pack_u32(reg,phy->tr_dac.reg_by_bit.ADR,(u8)  0,(u8) 0x1F);
	 reg=bit_field_pack_u32(reg,phy->tr_dac.reg_by_bit.CHT_S,(u8)  RPPU_TR_DAC_CHT_S_SHR,(u8) 0x1);
	 reg=bit_field_pack_u32(reg,phy->tr_dac.reg_by_bit.DAC_S2,(u8)  RPPU_TR_DACS2_SHR,(u8) 0x1);
	 reg=bit_field_pack_u32(reg,phy->tr_dac.reg_by_bit.DAC_S1,(u8)  RPPU_TR_DACS1_SHR,(u8) 0x1);
	 reg=bit_field_pack_u32(reg,phy->tr_dac.reg_by_bit.VB2R,(u8)  RPPU_TR_VB2R_SHR ,(u8) 0x7);
	 reg=bit_field_pack_u32(reg,phy->tr_dac.reg_by_bit.IFST,(u8)  RPPU_TR_IFST_SHR ,(u8) 0x7F);

	 rppu_write_reg(reg);

	 return reg;
 }


 uint32_t  rppu_setreg_tr_mixer(  struct  rppu_rf *phy)
 {
	 uint32_t reg=0;

	 reg=bit_field_pack_u32(reg,phy->tr_mixer.reg_by_bit.ADR,(u8)  0,(u8) 0x1F);
	 reg=bit_field_pack_u32(reg,phy->tr_mixer.reg_by_bit.TC_S,(u8)  RPPU_TR_MIXER_TC_S,(u8) 0x1);

	 rppu_write_reg(reg);

	 return reg;
 }

 uint32_t  rppu_setreg_tr_preamp(  struct  rppu_rf *phy)
 {
	 uint32_t reg=0;

	 reg=bit_field_pack_u32(reg,phy->tr_preamp.reg_by_bit.ADR,(u8)  0,(u8) 0x1F);
	 reg=bit_field_pack_u32(reg,phy->tr_preamp.reg_by_bit.PR_A,(u8)  RPPU_TR_PREAMP_PR_A,(u8) 0x7);

	 rppu_write_reg(reg);

	 return reg;
 }

 uint32_t  rppu_setreg_sin1_reg1(  struct  rppu_rf *phy)
 {
	 uint32_t reg=0;

	 reg=bit_field_pack_u32(reg,phy->sint1_reg1.reg_by_bit.ADR,(u8)  0,(u8) 0x1F);
	 reg=bit_field_pack_u32(reg,phy->sint1_reg1.reg_by_bit.FRAC,(u8)  RPPU_SINT1_REG1_FRAC_SHR,(u32) 0xFFFFFF);
	 reg=bit_field_pack_u32(reg,phy->sint1_reg1.reg_by_bit.SP,(u8)  RPPU_SINT1_REG1_SP_SHR,(u8) 0x1);
	 reg=bit_field_pack_u32(reg,phy->sint1_reg1.reg_by_bit.GPSP_SDM1,(u8)  RPPU_SINT1_REG1_GPSP_SDM1_SHR,(u8) 0x1);
	 reg=bit_field_pack_u32(reg,phy->sint1_reg1.reg_by_bit.SDM1_RST,(u8)   RPPU_SINT1_REG1_SDM1_RST,(u8) 0x1);

	 rppu_write_reg(reg);

	 return reg;
 }

 uint32_t  rppu_setreg_sin1_reg2(  struct  rppu_rf *phy)
 {
	 uint32_t reg=0;

	 reg=bit_field_pack_u32(reg,phy->sint1_reg2.reg_by_bit.ADR,(u8)  0,(u8) 0x1F);
	 reg=bit_field_pack_u32(reg,phy->sint1_reg2.reg_by_bit.MOD,(u8)  RPPU_SINT1_REG2_MOD_SHR,(u32) 0xFFFFFF);
	 reg=bit_field_pack_u32(reg,phy->sint1_reg2.reg_by_bit.DT,(u8)  RPPU_SINT1_REG2_DT_SHR,(u8) 0x3);
	 reg=bit_field_pack_u32(reg,phy->sint1_reg2.reg_by_bit.sdm_sel,(u8)   RPPU_SINT1_REG2_SDM_SEL_SHR,(u8) 0x1);
	 rppu_write_reg(reg);

	 return reg;
 }

 uint32_t  rppu_setreg_sin1_reg3(  struct  rppu_rf *phy)
 {
	 uint32_t reg=0;

	 reg=bit_field_pack_u32(reg,phy->sint1_reg3.reg_by_bit.ADR,(u8)  0,(u8) 0x1F);
	 reg=bit_field_pack_u32(reg,phy->sint1_reg3.reg_by_bit.MX,(u8)  RPPU_SINT1_REG3_MX_SHR,(u8) 0xF);
	 reg=bit_field_pack_u32(reg,phy->sint1_reg3.reg_by_bit.PFD_T,(u8)  RPPU_SINT1_REG3_PFD_T_SHR,(u8) 0x3);
	 reg=bit_field_pack_u32(reg,phy->sint1_reg3.reg_by_bit.RD,(u8)  RPPU_SINT1_REG3_RD_SHR,(u8) 0x3F);
	 reg=bit_field_pack_u32(reg,phy->sint1_reg3.reg_by_bit.ND,(u8)  RPPU_SINT1_REG3_ND_SHR,(u16) 0x1FF);
	 reg=bit_field_pack_u32(reg,phy->sint1_reg3.reg_by_bit.SDM_ST,(u8)  RPPU_SINT1_REG3_SDM_ST_SHR,(u8) 0xF);

	 rppu_write_reg(reg);

	 return reg;
 }


 uint32_t  rppu_setreg_sin2_reg(  struct  rppu_rf *phy)
 {
	 uint32_t reg=0;

	 reg=bit_field_pack_u32(reg,phy->sint2_reg.reg_by_bit.ADR,(u8)  0,(u8) 0x1F);
	 reg=bit_field_pack_u32(reg,phy->sint2_reg.reg_by_bit.CLK_EN,(u8)  RPPU_SINT2_REG_CLK_EN_SHR,(u8) 0x1);
	 reg=bit_field_pack_u32(reg,phy->sint2_reg.reg_by_bit.FM,(u8)  RPPU_SINT2_REG_FM_SHR,(u8) 0x1);
	 reg=bit_field_pack_u32(reg,phy->sint2_reg.reg_by_bit.TD,(u8)  RPPU_SINT2_REG_TD_SHR,(u8) 0x3);
	 reg=bit_field_pack_u32(reg,phy->sint2_reg.reg_by_bit.RD,(u8)  RPPU_SINT2_REG_RD_SHR,(u8) 0xF);
	 reg=bit_field_pack_u32(reg,phy->sint2_reg.reg_by_bit.FD,(u8)  RPPU_SINT2_REG_FD_SHR,(u8) 0x1FF);
	 reg=bit_field_pack_u32(reg,phy->sint2_reg.reg_by_bit.FDR,(u8)  RPPU_SINT2_REG_FDR_SHR,(u8) 0x1);
	 reg=bit_field_pack_u32(reg,phy->sint2_reg.reg_by_bit.PLL_MODE,(u8)  RPPU_SINT2_REG_PLL2_MODE_SHR,(u8) 0x1);
	 reg=bit_field_pack_u32(reg,phy->sint2_reg.reg_by_bit.PLL2FREQ,(u8)  RPPU_SINT2_REG_PLL2FREQ_SHR,(u8) 0x1);

	 rppu_write_reg(reg);

	 return reg;
 }


 uint32_t  rppu_setreg_inout_reg(  struct  rppu_rf *phy)
 {
	 uint32_t reg=0;

	 reg=bit_field_pack_u32(reg,phy->inoutbuf.reg_by_bit.ADR,(u8)  0,(u8) 0x1F);
	 reg=bit_field_pack_u32(reg,phy->inoutbuf.reg_by_bit.inout_buf,(u8)   RPPU_SINT2_INOUTBUF_SHR,(u8) 0x1);
	 rppu_write_reg(reg);

	 return reg;
 }


 uint32_t  rppu_setreg_sin1_reg4(  struct  rppu_rf *phy)
 {
	 uint32_t reg=0;

	 reg=bit_field_pack_u32(reg,phy->sint1_reg4.reg_by_bit.ADR,(u8)  0,(u8) 0x1F);
	 reg=bit_field_pack_u32(reg,phy->sint1_reg4.reg_by_bit.band,(u8)  RPPU_SINT1_REG4_BAND_SHR,(u8) 0x3F);
	 reg=bit_field_pack_u32(reg,phy->sint1_reg4.reg_by_bit.vs,(u8)  RPPU_SINT1_REG4_VS_SHR,(u8) 0x3);
	 reg=bit_field_pack_u32(reg,phy->sint1_reg4.reg_by_bit.agcic,(u8)  RPPU_SINT1_REG4_AGCIC_SHR,(u8) 0x1F);
	 reg=bit_field_pack_u32(reg,phy->sint1_reg4.reg_by_bit.agcm,(u8)  RPPU_SINT1_REG4_AGCM_SHR,(u8) 0x1);
	 reg=bit_field_pack_u32(reg,phy->sint1_reg4.reg_by_bit.agcd,(u8)  RPPU_SINT1_REG4_AGCD_SHR,(u8) 0x1);
	 reg=bit_field_pack_u32(reg,phy->sint1_reg4.reg_by_bit.agca,(u8)  RPPU_SINT1_REG4_AGCA_SHR,(u8) 0x1);
	 reg=bit_field_pack_u32(reg,phy->sint1_reg4.reg_by_bit.tb,(u8)  RPPU_SINT1_REG4_TB_SHR,(u8) 0x1);
	 reg=bit_field_pack_u32(reg,phy->sint1_reg4.reg_by_bit.c0,(u8)  RPPU_SINT1_REG4_C0_SHR,(u8) 0x1);


	 rppu_write_reg(reg);

	 return reg;
 }

 uint32_t  rppu_setreg_freq_divider(  struct  rppu_rf *phy)
 {
	 uint32_t reg=0;

	 reg=bit_field_pack_u32(reg,phy->freq_divider.reg_by_bit.ADR,(u8)  0,(u8) 0x1F);
	 reg=bit_field_pack_u32(reg,phy->freq_divider.reg_by_bit.amp, (u8) RPPU_FREQ_DIVIDER_AMP,(u8) 0xFF);
	 reg=bit_field_pack_u32(reg,phy->freq_divider.reg_by_bit.phase,(u8)  RPPU_FREQ_DIVIDER_PHASE,(u8) 0xFF);
	 reg=bit_field_pack_u32(reg,phy->freq_divider.reg_by_bit.DM,(u8)  RPPU_FREQ_DIVIDER_DM,(u8) 0x7);
	 rppu_write_reg(reg);

	 return reg;
 }

/*    установка значений всех регистров РППУ    */
uint32_t  rppu_setup_by_default(  struct  rppu_rf *phy)
{
	/*инициализация адресов в структурах регистров*/
	phy->rec_rf_part_reg.reg_by_bit.ADR=RPPU_GET_REG_ADR(RPPU_PREDEF_REC_RF_PART);
	phy->rec_mixer1.reg_by_bit.ADR			=RPPU_GET_REG_ADR(RPPU_PREDEF_REC_MIXER1);
	phy->rec_mixer2.reg_by_bit.ADR			=RPPU_GET_REG_ADR(RPPU_PREDEF_REC_MIXER2);
	phy->rec_filter.reg_by_bit.ADR			=RPPU_GET_REG_ADR(RPPU_PREDEF_REC_FILTER);
	phy->rec_ifa.reg_by_bit.ADR			=RPPU_GET_REG_ADR(RPPU_PREDEF_REC_IFA);
	phy->rec_adc.reg_by_bit.ADR			=RPPU_GET_REG_ADR(RPPU_PREDEF_REC_ADC);
	phy->tr_dac.reg_by_bit.ADR				=RPPU_GET_REG_ADR(RPPU_PREDEF_TR_DAC);
	phy->tr_mixer.reg_by_bit.ADR			=RPPU_GET_REG_ADR(RPPU_PREDEF_TR_MIXER);
	phy->tr_preamp.reg_by_bit.ADR			=RPPU_GET_REG_ADR(RPPU_PREDEF_TR_PREAMP);
	phy->sint1_reg1.reg_by_bit.ADR			=RPPU_GET_REG_ADR(RPPU_PREDEF_SINT1_REG1);
	phy->sint1_reg2.reg_by_bit.ADR			=RPPU_GET_REG_ADR(RPPU_PREDEF_SINT1_REG2);
	phy->sint1_reg3.reg_by_bit.ADR			=RPPU_GET_REG_ADR(RPPU_PREDEF_SINT1_REG3);
	phy->sint1_reg4.reg_by_bit.ADR			=RPPU_GET_REG_ADR(RPPU_PREDEF_SINT1_REG4);
	phy->sint2_reg.reg_by_bit.ADR			=RPPU_GET_REG_ADR(RPPU_PREDEF_SINT2_REG);
	phy->inoutbuf.reg_by_bit.ADR			=RPPU_GET_REG_ADR(RPPU_PREDEF_INOUTBUF);
	phy->freq_divider.reg_by_bit.ADR		=RPPU_GET_REG_ADR(RPPU_PREDEF_SINT_FREQ_DIVIDER);

	/*Инициализация значемями по умочанию*/

	phy->rec_rf_part_reg.reg	=RPPU_PREDEF_REC_RF_PART;
	/*код для DC* коррекции*/
	phy->rec_mixer1.reg_by_bit.CNT_I=cnt_q_corr;//0x1;//0xFE0;
	//phy->rec_mixer1.reg_by_bit.DM_S=1;  /*спящий режим ВЫКЛ*/
	phy->rec_mixer1.reg=rppu_setreg_rec_mixer1(phy);
	phy->rec_mixer2.reg_by_bit.CNT_Q=cnt_i_corr;
	//phy->rec_mixer2.reg_by_bit.DC_U=1;
	phy->rec_mixer2.reg=rppu_setreg_rec_mixer2(phy);



	phy->rec_filter.reg			=RPPU_PREDEF_REC_FILTER;
	phy->rec_ifa.reg			=RPPU_PREDEF_REC_IFA;
	phy->rec_adc.reg			=RPPU_PREDEF_REC_ADC;
	phy->tr_dac.reg				=RPPU_PREDEF_TR_DAC;
	phy->tr_mixer.reg			=RPPU_PREDEF_TR_MIXER;
	phy->tr_preamp.reg			=RPPU_PREDEF_TR_PREAMP;
	phy->sint1_reg1.reg			=RPPU_PREDEF_SINT1_REG1;
	phy->sint1_reg2.reg			=RPPU_PREDEF_SINT1_REG2;
	phy->sint1_reg3.reg			=RPPU_PREDEF_SINT1_REG3;
	phy->sint1_reg4.reg			=RPPU_PREDEF_SINT1_REG4;
	phy->sint2_reg.reg			=RPPU_PREDEF_SINT2_REG;
	phy->inoutbuf.reg			=RPPU_PREDEF_INOUTBUF;
	phy->freq_divider.reg		=RPPU_PREDEF_SINT_FREQ_DIVIDER;



	/*Запись регистров в SPI*/
	rppu_write_reg(phy->rec_rf_part_reg.reg);
	rppu_write_reg(phy->rec_mixer1.reg);
	rppu_write_reg(phy->rec_mixer2.reg);
	rppu_write_reg(phy->rec_filter.reg);
	rppu_write_reg(phy->rec_ifa.reg);
	rppu_write_reg(phy->rec_adc.reg);
	rppu_write_reg(phy->tr_dac.reg);
	rppu_write_reg(phy->tr_mixer.reg);
	rppu_write_reg(phy->tr_preamp.reg);
	rppu_write_reg(phy->sint1_reg1.reg);
	rppu_write_reg(phy->sint1_reg2.reg);
	rppu_write_reg(phy->sint1_reg3.reg);
	rppu_write_reg(phy->sint1_reg4.reg);
	rppu_write_reg(phy->sint2_reg.reg);
	rppu_write_reg(phy->inoutbuf.reg);
	rppu_write_reg(phy->freq_divider.reg);

	return 0;
}


/*    Включение смесителя передатчика    */
uint32_t  rppu_tr_mixer_enable(struct  rppu_rf *phy)
{

	phy->tr_mixer.reg_by_bit.TC_S=1;

	rppu_setreg_tr_mixer(phy);

	return 1;

}

/*    Выключение смесителя передатчика    */
uint32_t  rppu_tr_mixer_disable(  struct  rppu_rf *phy)
{

	phy->tr_mixer.reg_by_bit.TC_S=0;

	rppu_setreg_tr_mixer(phy);

	return 1;
}


/*    Включение ЦАП в режим 1 канала    */
uint32_t rppu_DAC_1ch_enable(  struct  rppu_rf *phy)
{
	/*phy->tr_dac.reg =0xA6 ;*/

	phy->tr_dac.reg_by_bit.CHT_S=1;
	phy->tr_dac.reg_by_bit.DAC_S2=0;
	phy->tr_dac.reg_by_bit.DAC_S1=1;
	phy->tr_dac.reg_by_bit.VB2R=0;
	phy->tr_dac.reg_by_bit.IFST=0;

	rppu_setreg_tr_dac(phy);

	return 1;
}


/*Включение АЦП*/
uint32_t  rppu_ADC_enable(  struct  rppu_rf *phy)
{
	phy->rec_adc.reg_by_bit.CH_PD=1;
	phy->rec_adc.reg=rppu_setreg_rec_adc(phy);

	return 1;
}

/*    Включение МШУ2    */
uint32_t  rppu_lna2_1ch_enable(  struct  rppu_rf *phy)
{

	phy->rec_rf_part_reg.reg_by_bit.ATT=0;
	phy->rec_rf_part_reg.reg_by_bit.CH_S=0;
	phy->rec_rf_part_reg.reg_by_bit.IN_S=1;
	phy->rec_rf_part_reg.reg=rppu_setreg_rec_rf_part(phy);

	return 1;
}

/*    ВЫКЛЮЧЕНИЕ  МШУ    */
uint32_t  rppu_lna2_1ch_disable(  struct  rppu_rf *phy)
{

	phy->rec_rf_part_reg.reg_by_bit.ATT=0;
	phy->rec_rf_part_reg.reg_by_bit.CH_S=0;
	phy->rec_rf_part_reg.reg_by_bit.IN_S=0;
	phy->rec_rf_part_reg.reg=rppu_setreg_rec_rf_part(phy);

	return 1;


}


/*    Включение квадратурного демодулятора    */
uint32_t  rppu_quad_demod_enable(  struct  rppu_rf *phy)
{

	phy->rec_mixer1.reg_by_bit.CNT_I=cnt_q_corr;//0x1;//0xFE0;

	phy->rec_mixer1.reg_by_bit.DM_S=1;  /*спящий режим ВЫКЛ*/
	phy->rec_mixer1.reg=rppu_setreg_rec_mixer1(phy);

	phy->rec_mixer2.reg_by_bit.CNT_Q=cnt_i_corr;
	phy->rec_mixer2.reg_by_bit.DC_U=1;

	phy->rec_mixer2.reg=rppu_setreg_rec_mixer2(phy);

	return 1;


}

/*    Выключение квадратурного демодулятора    */
uint32_t  rppu_quad_demod_disable(  struct  rppu_rf *phy)
{
	phy->rec_mixer1.reg_by_bit.DM_S=0;  /*спящий режим ВЫКЛ*/
	phy->rec_mixer2.reg_by_bit.DC_U=1;
	phy->rec_mixer2.reg=rppu_setreg_rec_mixer2(phy);
	phy->rec_mixer2.reg=rppu_setreg_rec_mixer1(phy);

	return 1;
}

/*    Включение ФНЧ на прием 1 канала    */
uint32_t  rppu_lpf_1st_ch_enable(  struct  rppu_rf *phy)
{

	phy->rec_filter.reg_by_bit.CHR_S=1;
	phy->rec_filter.reg_by_bit.BP_PD=0; /*????*/
	phy->rec_filter.reg_by_bit.F_PD=1;
	phy->rec_filter.reg_by_bit.LPF=1;
	phy->rec_filter.reg=rppu_setreg_rec_filter(phy);
	return 1;
}

/*    Выключение ФНЧ на прием 1 канала    */
uint32_t  rppu_lpf_1st_ch_disable(  struct  rppu_rf *phy)
{


	phy->rec_filter.reg_by_bit.F_PD=0;

	phy->rec_filter.reg=rppu_setreg_rec_filter(phy);
	return 1;
}



/*    Включение УПЧ на прием 1 канала    */
uint32_t  rppu_if_amp_1st_ch_enable(  struct  rppu_rf *phy)
{
	phy->rec_ifa.reg_by_bit.CH_PD=1;
	phy->rec_ifa.reg_by_bit.OB_PD=1; /*ВЫХ БУФЕР ВЫКЛ*/
	phy->rec_ifa.reg_by_bit.IQ_s=1;
	phy->rec_ifa.reg_by_bit.S_R=0;
	phy->rec_ifa.reg_by_bit.UN_C=1;
	phy->rec_ifa.reg_by_bit.IFA=10; // УСИЛЕНИЕ <----------------------------------------------------
	phy->rec_ifa.reg_by_bit.IFC=0;
	phy->rec_ifa.reg_by_bit.I_PD=1;

	phy->rec_ifa.reg=rppu_setreg_rec_ifa(phy);

	return 1;
}


/*    Выключение УПЧ на прием 1 канала    */
uint32_t  rppu_if_amp_1st_ch_disable(  struct  rppu_rf *phy)
{

	phy->rec_ifa.reg_by_bit.I_PD=0;

	phy->rec_ifa.reg=rppu_setreg_rec_ifa(phy);

	return 1;
}



/*    настрйока приемника 1 кнала    */
uint32_t  rppu_reciev_setup(  struct  rppu_rf *phy,uint8_t amplify )
{

	/*настройка МШУ*/
	phy->rec_rf_part_reg.reg_by_bit.ATT=0;
	phy->rec_rf_part_reg.reg_by_bit.CH_S=0;  // 1 - МШУ1
	phy->rec_rf_part_reg.reg_by_bit.IN_S=1;
	phy->rec_rf_part_reg.reg=rppu_setreg_rec_rf_part(phy);


	/*настройка квадраутрного демодулятора*/
	phy->rec_mixer1.reg_by_bit.CNT_I=cnt_q_corr;//0x1;//0xFE0;
	phy->rec_mixer1.reg_by_bit.DM_S=1;  /*спящий режим ВЫКЛ*/
	phy->rec_mixer1.reg=rppu_setreg_rec_mixer1(phy);
	phy->rec_mixer2.reg_by_bit.CNT_Q=cnt_i_corr;
	phy->rec_mixer2.reg_by_bit.DC_U=1;
	phy->rec_mixer2.reg=rppu_setreg_rec_mixer2(phy);

	/*настройка квадраутрного ФНЧ*/
	phy->rec_filter.reg_by_bit.CHR_S=1;
	phy->rec_filter.reg_by_bit.BP_PD=0; /*????*/
	phy->rec_filter.reg_by_bit.F_PD=1;
	phy->rec_filter.reg_by_bit.LPF=1;
	phy->rec_filter.reg=rppu_setreg_rec_filter(phy);


	phy->rec_ifa.reg_by_bit.CH_PD=1;
	phy->rec_ifa.reg_by_bit.OB_PD=1; /*ВЫХ БУФЕР ВЫКЛ*/
	phy->rec_ifa.reg_by_bit.IQ_s=1;
	phy->rec_ifa.reg_by_bit.S_R=0;
	phy->rec_ifa.reg_by_bit.UN_C=1;
	phy->rec_ifa.reg_by_bit.IFA=amplify; // УСИЛЕНИЕ <----------------------------------------------------
	phy->rec_ifa.reg_by_bit.IFC=0;
	phy->rec_ifa.reg_by_bit.I_PD=1;

	phy->rec_ifa.reg=rppu_setreg_rec_ifa(phy);

	/*Выключение АЦП внутренненго*/
	phy->rec_adc.reg_by_bit.CH_PD=1;
	phy->rec_adc.reg=rppu_setreg_rec_adc(phy);

	return 1;
}

/*    настрйока приемника 1 кнала    */
uint32_t  rppu_tranciev_setup(  struct  rppu_rf *phy)
{

	rppu_tr_mixer_enable( phy);


	return 1;
}


/*   включение приемника первого канала в режим измерения DC смещения   */
uint32_t  rppu_1ch_dc_corr_enable(  struct  rppu_rf *phy)
{

	/*вЫкл ацп*/
	 rppu_ADC_enable(phy);
	/*Что-то сделать с УПЧ*/

	    rppu_lna2_1ch_disable(phy);
//		xil_printf("REG .... %08x \n", phy->rec_rf_part_reg.reg);
		rppu_quad_demod_enable(phy);
//		xil_printf("REG .... %08x \n", phy->rec_mixer1.reg);
		rppu_lpf_1st_ch_enable(phy);
//		xil_printf("REG .... %08x \n ", phy->rec_filter.reg);
		rppu_if_amp_1st_ch_enable(phy);
//		xil_printf("REG .... %08x \n ", phy->rec_ifa.reg);





		return 1;

}

/*   Установка частоты синтезатора 1
 * в  граничное значения поддиапазона
 * LC - номер контура
 * band_n - номер поддиапазона
 * edge  0/ >1  - НИЖНИЙ/ВЕРХНИЙ край
 *  */
uint32_t  rppu_sint1_edge_set(struct  rppu_rf *phy, uint8_t LC, uint8_t band_n, uint8_t edge)
{

	/*phy->sint1_reg3.reg			=0x2A0170B;*/

	phy->sint1_reg3.reg_by_bit.MX=0xC;

	if(edge>0)
	{
		phy->sint1_reg3.reg_by_bit.PFD_T=2;
	}
	else
	{
		phy->sint1_reg3.reg_by_bit.PFD_T=1;
	}
	rppu_setreg_sin1_reg3(phy);



	phy->sint1_reg4.reg_by_bit.vs=LC;
	phy->sint1_reg4.reg_by_bit.band=band_n;


	/*xil_printf("REG .... %08x \n "   , phy->sint1_reg4.reg);*/

	rppu_setreg_sin1_reg4(phy);


	return 0;
}




/*Вывод списка инициализации массива c частотным диапазоном контуров*/
uint32_t rppu__debug_edges_print(uint32_t *ptr,uint32_t rows, uint32_t columns)
{
	uint8_t i=0;
	uint8_t j=0;

	xil_printf("{\n"   );
	for(i=0;i<rows;i++)
	{
		xil_printf("\t{ "   );

		for (j=0;j<columns;j++)
			{
				xil_printf("\t%u", *(ptr+ j+ i*columns)   );

				if(j!=columns-1)
				{
					xil_printf(","  );
				}
			}

		xil_printf("}"   );

		if(i!=rows-1)
		{
			xil_printf(",\n"  );
		}

	}
	xil_printf("\n"   );
	xil_printf("};"   );

	return 0;
}


/*Обнуление массива c частотным диапазонами*/
uint32_t rppu__debug_edges_clear(uint32_t *ptr,uint32_t rows, uint32_t columns,uint8_t band_start, uint8_t band_end)
{
	uint8_t i=0;
	uint8_t j=0;

		for(i=band_start;i<band_end;i++)
		{
			for(j=0;j<columns;j++)
			{
				*(ptr+i*columns	+j)=5;
			}
		}
	return 1;

}


/*Определение номера поддиапазона ГУН
 * uint32_t VCO_out_freq_div2 - частота ГУН после делителя на 2
 * uint32_t *ptr - указатель на массив поддиапазонов
 * - остальное - размеры массива
 * Возвращает номер поддиапазона 0-rows-1
 * */
uint32_t  rppu_sint1_range_find(uint32_t *ptr,uint32_t rows, uint32_t columns,uint32_t VCO_out_freq_div2)
{

	uint8_t i=0;

	for(i=0;i<rows;i++)
	{

		if   (  (VCO_out_freq_div2>(*(ptr+columns*i))&&(VCO_out_freq_div2<(*(ptr+columns*i+1)))  ))
		{
						break;
		}

	}

	return i;
}

u32 measure_and_calc_correct_i_q_levels()
{
	if (enable_cnt_i_corr || enable_cnt_q_corr)
	{
		u16 lvl_measure_interval = 0;
		int32_t i_dc_lvl = 0, q_dc_lvl = 0;

		lvl_measure_interval = 200000;
		Xil_Out32((CH1_DC_LVL_PER), (u32)(lvl_measure_interval));

		mdelay(20);
	//	Xil_Out32((	CH1_PWR_PER	), (u32)(lvl_measure_interval));

	//	while (1)
	//	{
		i_dc_lvl = Xil_In32(CH1_DC_I_LVL);
		q_dc_lvl = Xil_In32(CH1_DC_Q_LVL);

		double i_lvl, q_lvl;
		i_lvl = i_dc_lvl / (double)lvl_measure_interval;
		q_lvl = q_dc_lvl / (double)lvl_measure_interval;

//		enable_cnt_i_corr = 0;
//		enable_cnt_q_corr = 0;

//		xil_printf("I_DC_LVL =  %d\n", i_lvl);
		if (enable_cnt_i_corr)
		{
			if (fabs(i_lvl) <= 5)
			{
				xil_printf("SUCCESS I = ");
				print_double(i_lvl, 8);
				xil_printf("\n");
				enable_cnt_i_corr = 0;
			}
//			xil_printf("I_DC_LVL = ");
//			print_double(i_lvl);
//			xil_printf("\n");
		}
		if (enable_cnt_q_corr)
		{
			if (fabs(q_lvl) <= 5)
			{
				xil_printf("SUCCESS Q = ");
				print_double(q_lvl, 8);
				xil_printf("\n");
				enable_cnt_q_corr = 0;
			}
//			xil_printf("Q_DC_LVL = ");
//			print_double(q_lvl);
//			xil_printf("\n");
		}

		// Так вот получаица, i и q где-то перепутаны местами
		if (enable_cnt_q_corr) {
			if (fabs(q_lvl) > 100)
				cnt_q_corr += 50;
			else
				cnt_q_corr += 2;
		}
		if (enable_cnt_i_corr) {
			if (fabs(i_lvl) > 100)
				cnt_i_corr += 50;
			else
				cnt_i_corr += 2;
		}
		if (!enable_cnt_i_corr && !enable_cnt_q_corr)
		{
			xil_printf("Successfully corrected I and Q levels!\n");
			return 0;
		}
//		xil_printf("Q_DC_LVL =  %d\n", q_lvl);
//		mdelay(500);
//	}
		return 1;
	}
	return 0;
}

u32  rppu_quad_demod_enable_with_leveling(struct rppu_rf *phy, u16 cnt_i, u16 cnt_q)
{
	phy->rec_mixer1.reg_by_bit.CNT_I = cnt_i; //11 разрядов, беззнаковое

	phy->rec_mixer1.reg_by_bit.DM_S=1;  /*спящий режим ВЫКЛ*/
	phy->rec_mixer1.reg=rppu_setreg_rec_mixer1(phy);

	phy->rec_mixer2.reg_by_bit.CNT_Q = cnt_q; //11 разрядов, беззнаковое
	phy->rec_mixer2.reg_by_bit.DC_U=1;

	phy->rec_mixer2.reg=rppu_setreg_rec_mixer2(phy);

	return 1;
}

u32 check_input_power()
{
	u16 pwr_measure_interval = 200000;
	Xil_Out32((CH1_PWR_PER), (u32)(pwr_measure_interval));

	u32 i = 0;

	for (i = 0; i < 5; i++)
	{
		mdelay(50);
		xil_printf("PWR = ");
		print_double(Xil_In32(CH1_PWR_BUFF) / (double)pwr_measure_interval, 8);
		xil_printf("\n");
	}

	return 0;
}

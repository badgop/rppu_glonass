/*
 * RPPU.h
 *
 *  Created on: 12 марта 2018 г.
 *      Author: Ivan
 */

#include "RT_AD.h"
#include "muxin.h"
#include "RT1_functions.h"





#ifndef SRC_RPPU_H_
#define SRC_RPPU_H_

/***************************************************************************/

#define RPPU_GET_REG_ADR(A) (A&0x1F)


/* Начальные значение регистров РППУ   в порядке возрастания адреса   */
//
//
///*    ********************************    */
//#define RPPU_PREDEF_REC_RF_PART (0x200)
//#define RPPU_PREDEF_REC_MIXER1 (0x1FC01)
//#define RPPU_PREDEF_REC_MIXER2 (0x1FC02)
//#define RPPU_PREDEF_REC_FILTER (0x203)
//#define RPPU_PREDEF_REC_IFA (0x802E4)
///*АЦП выключен по умолчаению - бит 6 в 1 инфа от 12.04.18*/
//#define RPPU_PREDEF_REC_ADC (0x25)
//#define RPPU_PREDEF_TR_DAC (0x26)
//#define RPPU_PREDEF_TR_MIXER (0x7)
//#define RPPU_PREDEF_TR_PREAMP (0x8)
//#define RPPU_PREDEF_SINT1_REG1 ( 0xC0000009)//(0x29) -- Это и ниже - банка на 451.5 МГц
//#define RPPU_PREDEF_SINT1_REG2  (0x8000000A) //(0xAA)
////#define RPPU_PREDEF_SINT1_REG3 (0x2A0270B)//(0x2D2270B)
//#define RPPU_PREDEF_SINT1_REG3     (0x360170B) /*5*432=2160 МГЦ  /16=135 МГЦ */
////#define RPPU_PREDEF_SINT2_REG ( 0x799158C)//(0x2F80CAE)
//#define RPPU_PREDEF_SINT2_REG (0x70A158C) // Для 10 клок и 135 МГц
//#define RPPU_PREDEF_INOUTBUF (0x2D)
////#define RPPU_PREDEF_SINT1_REG4 (0x2F80B0E)//(0x2F80CAE)
//#define RPPU_PREDEF_SINT1_REG4     (0x2F80FEE) /*32 банка ????*/
//#define RPPU_PREDEF_SINT_FREQ_DIVIDER (0x00000F) //(0xA0000F)
///*  ************************************     */

/* Начальные значение регистров РППУ   в порядке возрастания адреса   */

#define RCV
//#define TR
#define BAND_135
//#define BAND_2400
//#define BAND_1200
//#define BAND_800



/*    ********************************    */
#define RPPU_PREDEF_REC_RF_PART (0x0) //(0x200)
#define RPPU_PREDEF_REC_MIXER1 (0xFC01) //(0x1FC01)
#define RPPU_PREDEF_REC_MIXER2 (0x1FC02)
#define RPPU_PREDEF_REC_FILTER (0x203)
#define RPPU_PREDEF_REC_IFA (0x2E4)//(0x802E4)
/*АЦП выключен по умолчаению - бит 6 в 1 инфа от 12.04.18*/
#define RPPU_PREDEF_REC_ADC (0x25)
#define RPPU_PREDEF_TR_DAC (0x26)
#define RPPU_PREDEF_TR_MIXER (0x7)
#define RPPU_PREDEF_TR_PREAMP (0x8)

//#define RPPU_PREDEF_SINT1_REG3 (0x2A0270B)//(0x2D2270B)
#ifdef TR
	#ifdef BAND_135
		#define RPPU_PREDEF_SINT1_REG1 ( 0xC0000009)//(0x29) -- Это и ниже - банка на 451.5 МГц
		#define RPPU_PREDEF_SINT1_REG2  (0x8000000A) //(0xAA)
		#define RPPU_PREDEF_SINT1_REG3     (0x360170B) /*5*432=2160 МГЦ  /16=135 МГЦ */
		#define RPPU_PREDEF_SINT1_REG4     (0x2F80FEE) /*32 банка ????*/
		#define RPPU_PREDEF_SINT_FREQ_DIVIDER (0x00000F) //(0xA0000F)
	#endif
	#ifdef BAND_2400
		#define RPPU_PREDEF_SINT1_REG1 ( 0xC0000009)//(0x29) -- Это и ниже - банка на 451.5 МГц
		#define RPPU_PREDEF_SINT1_REG2  (0x8000000A) //(0xAA)
		#define RPPU_PREDEF_SINT1_REG3     (0x3C0170B) /*5*432=2160 МГЦ  /16=135 МГЦ */
		#define RPPU_PREDEF_SINT1_REG4     (0x2F813EE) /*32 банка ????*/
		#define RPPU_PREDEF_SINT_FREQ_DIVIDER (0xE0000F) //(0xA0000F)
	#endif
	#ifdef BAND_1200
		#define RPPU_PREDEF_SINT1_REG1 ( 0xC0000009)//(0x29) -- Это и ниже - банка на 451.5 МГц
		#define RPPU_PREDEF_SINT1_REG2  (0x8000000A) //(0xAA)
		#define RPPU_PREDEF_SINT1_REG3     (0x1E0170B) /*5*432=2160 МГЦ  /16=135 МГЦ */
		#define RPPU_PREDEF_SINT1_REG4     (0x2F801AE) /*32 банка ????*/
		#define RPPU_PREDEF_SINT_FREQ_DIVIDER (0xE0000F) //(0xA0000F)
	#endif
	#ifdef BAND_800
		#define RPPU_PREDEF_SINT1_REG1 ( 0xC0000009)//(0x29) -- Это и ниже - банка на 451.5 МГц
		#define RPPU_PREDEF_SINT1_REG2  (0x8000000A) //(0xAA)
		#define RPPU_PREDEF_SINT1_REG3     (0x280170B) /*5*432=2160 МГЦ  /16=135 МГЦ */
		#define RPPU_PREDEF_SINT1_REG4     (0x2F80A0E) /*32 банка ????*/
		#define RPPU_PREDEF_SINT_FREQ_DIVIDER (0xC0000F) //(0xA0000F)
	#endif
#endif
#ifdef RCV
	#ifdef BAND_135
		#define RPPU_PREDEF_SINT1_REG1 ( 0xC0000009)//(0x29) -- Это и ниже - банка на 451.5 МГц
		#define RPPU_PREDEF_SINT1_REG2  (0x8000000A) //(0xAA)
		#define RPPU_PREDEF_SINT1_REG3     (0x360170B) /*5*432=2160 МГЦ  /16=135 МГЦ */
//		#define RPPU_PREDEF_SINT1_REG3  (0x360270B) // 20 МГц
		#define RPPU_PREDEF_SINT1_REG4     (0x2F80FEE) /*32 банка ????*/
		#define RPPU_PREDEF_SINT_FREQ_DIVIDER (0x00000F) //(0xA0000F)
	#endif
	#ifdef BAND_2400
//		#define RPPU_PREDEF_SINT1_REG1 ( 0x29)//(0x29) -- Это и ниже - банка на 451.5 МГц
//		#define RPPU_PREDEF_SINT1_REG2  (0x8A) //(0xAA)
//		#define RPPU_PREDEF_SINT1_REG3     (0x3C0170B) /*5*432=2160 МГЦ  /16=135 МГЦ */
//		#define RPPU_PREDEF_SINT1_REG4     (0x2F813EE) /*32 банка ????*/
//		#define RPPU_PREDEF_SINT_FREQ_DIVIDER (0xE0000F) //(0xA0000F)
		#define RPPU_PREDEF_SINT1_REG1 ( 0xC0000009)//(0x29) -- Это и ниже - банка на 451.5 МГц
		#define RPPU_PREDEF_SINT1_REG2  (0x8000000A) //(0xAA)
		#define RPPU_PREDEF_SINT1_REG3     (0x3C0170B) /*5*432=2160 МГЦ  /16=135 МГЦ */
		#define RPPU_PREDEF_SINT1_REG4     (0x2F813EE) /*32 банка ????*/
		#define RPPU_PREDEF_SINT_FREQ_DIVIDER (0xE0000F) //(0xA0000F)
	#endif
	#ifdef BAND_1200
//		#define RPPU_PREDEF_SINT1_REG1 ( 0x29)//(0x29) -- Это и ниже - банка на 451.5 МГц
//		#define RPPU_PREDEF_SINT1_REG2  (0x8A) //(0xAA)
//		#define RPPU_PREDEF_SINT1_REG3     (0x1E0170B) /*5*432=2160 МГЦ  /16=135 МГЦ */
//		#define RPPU_PREDEF_SINT1_REG4     (0x2F801AE) /*32 банка ????*/
//		#define RPPU_PREDEF_SINT_FREQ_DIVIDER (0xE0000F) //(0xA0000F)
		#define RPPU_PREDEF_SINT1_REG1 ( 0xC0000009)//(0x29) -- Это и ниже - банка на 451.5 МГц
		#define RPPU_PREDEF_SINT1_REG2  (0x8000000A) //(0xAA)
		#define RPPU_PREDEF_SINT1_REG3     (0x1E0170B) /*5*432=2160 МГЦ  /16=135 МГЦ */
		#define RPPU_PREDEF_SINT1_REG4     (0x2F801AE) /*32 банка ????*/
		#define RPPU_PREDEF_SINT_FREQ_DIVIDER (0xE0000F) //(0xA0000F)
	#endif
	#ifdef BAND_800
//		#define RPPU_PREDEF_SINT1_REG1 ( 0x29)//(0x29) -- Это и ниже - банка на 451.5 МГц
//		#define RPPU_PREDEF_SINT1_REG2  (0x4A) //(0xAA)
//		#define RPPU_PREDEF_SINT1_REG3     (0x280170B) /*5*432=2160 МГЦ  /16=135 МГЦ */
//		#define RPPU_PREDEF_SINT1_REG4     (0x2F80A0E) //32 банка ???? ДЛЯ ПОМЕЧЕННОЙ ПЛАТЫ
//		#define RPPU_PREDEF_SINT_FREQ_DIVIDER (0xC0000F) //(0xA0000F)
		#define RPPU_PREDEF_SINT1_REG1 ( 0xC0000009)//(0x29) -- Это и ниже - банка на 451.5 МГц
		#define RPPU_PREDEF_SINT1_REG2  (0x8000000A) //(0xAA)
		#define RPPU_PREDEF_SINT1_REG3     (0x280170B) /*5*432=2160 МГЦ  /16=135 МГЦ */
		#define RPPU_PREDEF_SINT1_REG4     (0x2F80A0E) /*32 банка ????*/
		#define RPPU_PREDEF_SINT_FREQ_DIVIDER (0xC0000F) //(0xA0000F)
	#endif
#endif

//#define RPPU_PREDEF_SINT2_REG ( 0x799158C)//(0x2F80CAE)
#define RPPU_PREDEF_SINT2_REG (0x70A158C) // Для 10 клок и 135 МГц
//#define RPPU_PREDEF_SINT2_REG (0x78A158C) // синтезатора 2 отключен
#define RPPU_PREDEF_INOUTBUF (0x2D)
//#define RPPU_PREDEF_SINT1_REG4 (0x2F80B0E)//(0x2F80CAE)

/*  ************************************     */


/************************************************************/
/*Величины сдвигов для работы с битовыми полями*/
/***********REC_RF_PART SHIFT********/
#define RPPU_REC_RF_PART_ATT_SHR (0x5)
#define RPPU_REC_RF_PART_CH_S    (0x8)
#define RPPU_REC_RF_PART_IN_S    (0x9)

/***********REC_MIXER1 SHIFT********/
#define RPPU_REC_MIXER1_CNT_I_SHR (0x5)
#define RPPU_REC_MIXER1_DM_S_SHR  (0x10)

/***********REC_MIXER2 SHIFT********/
#define RPPU_REC_MIXER2_CNT_Q_SHR (0x5)
#define RPPU_REC_MIXER2_DC_U_SHR  (0x10)

/***********REC_FILTER SHIFT********/
#define RPPU_REC_FILTER_CHR_S_SHR (0x5)
#define RPPU_REC_FILTER_BP_PD_SHR (0x6)
#define RPPU_REC_FILTER_LPF_SHR   (0x7)
#define RPPU_REC_FILTER_F_PD_SHR  (0x9)

/***********REC_IFA SHIFT********/
#define RPPU_REC_IFA_CH_PD_SHR (0x5)
#define RPPU_REC_IFA_OB_PD_SHR (0x6)
#define RPPU_REC_IFA_IQ_S_SHR  (0x7)
#define RPPU_REC_IFA_S_R_SHR   (0x8)
#define RPPU_REC_IFA_UN_C_SHR  (0x9)
#define RPPU_REC_IFA_IFA_SHR   (0xA)
#define RPPU_REC_IFA_IFC_SHR   (0x10)
#define RPPU_REC_IFA_I_PD_SHR  (0x13)

/***********REC_ADC SHIFT********/
#define RPPU_REC_IFA_CH_PD_SHR (0x5)

/***********REC_TR_DAC SHIFT********/
#define RPPU_TR_DAC_CHT_S_SHR (0x5)
#define RPPU_TR_DACS2_SHR     (0x6)
#define RPPU_TR_DACS1_SHR     (0x7)
#define RPPU_TR_VB2R_SHR      (0x8)
#define RPPU_TR_IFST_SHR      (0xB)

/***********REC_TR_MIXER SHIFT********/
#define RPPU_TR_MIXER_TC_S (0x5)

/***********REC_TR_PREAMP SHIFT********/
#define RPPU_TR_PREAMP_PR_A (0x5)

/***********SINT1_REG1 SHIFT********/
#define RPPU_SINT1_REG1_FRAC_SHR (0x5)
#define RPPU_SINT1_REG1_SP_SHR (0x1D)
#define RPPU_SINT1_REG1_GPSP_SDM1_SHR (0x1E)
#define RPPU_SINT1_REG1_SDM1_RST (0x1F)

/***********SINT1_REG2 SHIFT********/
#define RPPU_SINT1_REG2_MOD_SHR (0x5)
#define RPPU_SINT1_REG2_DT_SHR (0x1D)
#define RPPU_SINT1_REG2_SDM_SEL_SHR (0x1F)

/***********SINT1_REG3 SHIFT********/
#define RPPU_SINT1_REG3_MX_SHR (0x5)
#define RPPU_SINT1_REG3_PFD_T_SHR (0x9)
#define RPPU_SINT1_REG3_RD_SHR (0xB)
#define RPPU_SINT1_REG3_ND_SHR (0x11)
#define RPPU_SINT1_REG3_SDM_ST_SHR (0x1A)


/***********SINT2_REG SHIFT********/
#define RPPU_SINT2_REG_CLK_EN_SHR (0x5)
#define RPPU_SINT2_REG_FM_SHR (0x6)
#define RPPU_SINT2_REG_TD_SHR (0x7)
#define RPPU_SINT2_REG_RD_SHR (0x9)
#define RPPU_SINT2_REG_FD_SHR (0xD)
#define RPPU_SINT2_REG_FDR_SHR (0x16)
#define RPPU_SINT2_REG_PLL2_MODE_SHR (0x17)
#define RPPU_SINT2_REG_PLL2FREQ_SHR (0x18)

/***********INOUTBUF SHIFT********/
#define RPPU_SINT2_INOUTBUF_SHR (0x5)


/***********SINT1_REG4 SHIFT********/
#define RPPU_SINT1_REG4_BAND_SHR (0x5)
#define RPPU_SINT1_REG4_VS_SHR (0xB)
#define RPPU_SINT1_REG4_AGCIC_SHR (0xD)
#define RPPU_SINT1_REG4_AGCM_SHR (0x12)
#define RPPU_SINT1_REG4_AGCD_SHR (0x13)
#define RPPU_SINT1_REG4_AGCA_SHR (0x14)
#define RPPU_SINT1_REG4_TB_SHR (0x15)
#define RPPU_SINT1_REG4_C0_SHR (0x16)

/***********FREQ_DIVIDER SHIFT********/
#define RPPU_FREQ_DIVIDER_AMP (0x5)
#define RPPU_FREQ_DIVIDER_PHASE (0xD)
#define RPPU_FREQ_DIVIDER_DM (0x15)


/************************************************************/

/*   Частота сравнения синтезатора 1       */
#define RPPU_PREDEF_FCOPM ((uint32_t)(5000000))

/*Нижняя и верхняя границы перестройки частотного диапазона*/
#define RPPU_SINT1_LOW ((uint32_t) (2500000000))
#define RPPU_SINT1_HIGH ((uint32_t)(5000000000))

/*Число контуров ГУН максимальное*/
#define LCS	3

/*Число частотных поддиапазонов*/
#define BANDS	64




/*  ************************************     */
/* Структура описывающая регистры (и состояние ) РППУ    */

struct rppu_rf{


/*--------------------------------------РЕГИСТРЫ РППУ-------------------------------------------------*/

	/*Шаблон для создания обьединения описывающего один регистр РППУ*/

	//struct  // СТРУКТУРА В КОТОРОЙ ХРАНИТЬСЯ ЗНАЧЕНИЯ РЕГИСТРА РППУ
	//{
	//	uint32_t reg;  // ПЕРЕМЕННАЯ ПОД КОТОРУЮ ВЫДЕЛИТЬСЯ ПАМЯТЬ 32 бита. Максимальный размер регистра РППУ - 26 бит.
	//
	//	struct{        //
	//	uint8_t ADR:5;  // АДРЕС 0x0
	//  				// Адрес - 5 МЛАДШИХ БИТ 32 рарядного числа [4:0]
	//	//ЗДЕСЬ ИДУТ ОСТАЬНЫЕ БИТЫ
	//
	//	}reg_by_bit; // - общеее название структуры представляющей битовой поле регистра

	//}ИМЯ РЕГИСТРА;

	/*конец шаблона*/




/* РЕГИСТР    rec_rf_part         "Управление МШУ приемника"  АДРЕС 0x0  */
/* **************************************         */
struct
{
	uint32_t reg;
	struct{
	uint8_t ADR:5;  // АДРЕС 0x0
	uint8_t ATT:3;  // коэфф ослабления аттенюатора субблока МШУ2 (дБ????)
	uint8_t CH_S:1; // Переключение субблоков МШУ   1/0  МШУ1/МШУ2
	uint8_t IN_S:1; // Спящий режим блока МШУ 1/0 ВКЛ/ВЫКЛ
	}reg_by_bit;
} rec_rf_part_reg;
/* **************************************         */



/* РЕГИСТР   rec_mixer1  "Управление квадартурным демодулятором приемника"  АДРЕС 0x01  */
/* **************************************         */
struct
{
	uint32_t reg;
	struct{
	uint8_t ADR:5;      /* АДРЕС 0x0 */
	uint16_t CNT_I:11;   /* Установка величины смещения в канале I  */
	uint8_t DM_S:1;   /* спящий режим демодулятора 1/0 ВКЛ/ВЫКЛ  */
	}reg_by_bit;
} rec_mixer1;
/* **************************************         */




/* РЕГИСТР   rec_mixer2  "Управление квадартурным демодулятором приемника"  АДРЕС 0x2  */
/* **************************************         */
struct
{
	uint32_t reg;
	struct{
	uint8_t ADR:5;      /* АДРЕС 0x0 */
	uint16_t CNT_Q:11;   /* Установка величины смещения в канале I  */
	uint8_t DC_U:1;   /* Выбор подавления зеркального канала  1/0  ЗК выше/ниже частоты гетеродина  */
	}reg_by_bit;
} rec_mixer2;
/* **************************************         */



/* РЕГИСТР   rec_filter  "Управление ФНЧ приемника"  АДРЕС 0x3  */
/* **************************************         */
struct
{
	uint32_t reg;
	struct{
	uint8_t ADR:5;     /* АДРЕС 0x0 */
	uint8_t CHR_S:1;   /* Выбор подавления зеркального канала 1/0 ЗК выше ниже частотыы гетеродина  */
	uint8_t BP_PD:1;   /* Управление полосового фильтра и блокои подавление ЗК  */
					   /*           1/0  фильтра  ВКЛ/ВЫКЛ (по "умолчанию" ПФ вкл, т.е после включения питвания*/
					   /*           его необходимо выключить)  */
	uint8_t LPF:2;	   /* Управление частотой среза ФНЧ . ум - 1,25 МГЦ  */
	uint8_t F_PD:1;	   /*Спящий режим ФНЧ   1/0 фильтр ВКЛ/ВЫКЛ  */


	}reg_by_bit;
} rec_filter;
/* **************************************         */




/* РЕГИСТР   rec_ifa  "Управление УПЧ приемника"  АДРЕС 0x4  */
/* **************************************         */
struct
{
	uint32_t reg;
	struct{
	uint8_t ADR:5;     /* АДРЕС 0x0 */
	uint8_t CH_PD:1;   /* Управление  I каналом УПЧ     1/0   канал ВКЛ/ВЫКЛ */
	uint8_t OB_PD:1;   /* Управление выходонго буфера  1/0 буфер ВКЛ/ВЫКЛ  */
	uint8_t IQ_s:1;    /* Канал I/Q  */
	uint8_t S_R:1;    /* Знак регулировки  */
	uint8_t UN_C:1;    /* Режим компенсации разбаланса 1/0 режим ВКЛ/ВЫКЛ  */
	uint8_t IFA:6;    /* Коэффициент усиления  */
	uint8_t IFC:3;    /* Управление УПЧ  */
	uint8_t I_PD:3;    /* Спящий режим УПЧ 1/0 УПЧ ВКЛ/ВЫКЛ  */

	}reg_by_bit;
} rec_ifa;
/* **************************************         */



/* РЕГИСТР   rec_adc  "Управление АЦП приемника"  АДРЕС 0x5  */
/* **************************************         */
struct
{
	uint32_t reg;
	struct{
	uint8_t ADR:5;     /* АДРЕС 0x0 */
	uint8_t CH_PD:1;     /* Спящий режим АЦП 0/1 АЦП ВКЛ ВЫКЛ */

	}reg_by_bit;
} rec_adc;
/* **************************************         */


/* РЕГИСТР   tr_dac  "Управление ЦАП передатчика"  АДРЕС 0x6  */
/* **************************************         */
struct
{
	uint32_t reg;
	struct{
	uint8_t ADR:5;     /* АДРЕС 0x0 */
	uint8_t CHT_S:1;     /* Выбор канала  1/0 ЦАП1/ЦАП2 */
	uint8_t DAC_S2:1;     /* Спящий режим ЦАП 2 КАНАЛА 1/0 ЦАП 2 КАНАЛА ВКЛ ВЫКЛ */
	uint8_t DAC_S1:1;     /* Спящий режим ЦАП 1 КАНАЛА 1/0 ЦАП 1 КАНАЛА ВКЛ ВЫКЛ */
	uint8_t VB2R:3;     /* Пдостройка внутреннего опорного напряжения ЦАП */
	uint8_t IFST:7;     /* УПравление током полной шкалы ЦАП  */

	}reg_by_bit;
} tr_dac;
/* **************************************         */


/* РЕГИСТР   tr_mixer  "Управление модулятором передатчика"  АДРЕС 0x7  */
/* **************************************         */
struct
{
	uint32_t reg;
	struct{
	uint8_t ADR:5;     /* АДРЕС 0x0 */
	uint8_t TC_S:1 ; 		   /* Спящий режим смесителей 1/0 смесители ВКЛ/ВЫКЛ  */

	}reg_by_bit;
} tr_mixer;
/* **************************************         */


/* РЕГИСТР   tr_preamp  "Управление ПрУМ передатчика"  АДРЕС 0x8  */
/* **************************************         */
struct
{
	uint32_t reg;
	struct{
	uint8_t ADR:5;     /* АДРЕС 0x0 */
	uint8_t PR_A:3 ; 		   /* Управление усилением блока ПрУМ 0x0 - 0 дБ  */

	}reg_by_bit;
} tr_preamp;
/* **************************************         */




/* РЕГИСТР   sin1_reg1  "Управление синтезатором частот 1"  АДРЕС 0x9  */
/* **************************************         */
struct
{
	uint32_t reg;
	struct{
	uint8_t ADR:5;     /* АДРЕС 0x0 */
	uint32_t FRAC :24 ; 		   /* Числитель дроби сигма дельта модулятора  */
	uint8_t SP :1 ; 		   /* РЕжим Сонга - Парка СДМ2  */
	uint8_t GPSP_SDM1 :1 ; 		   /* Генератор ПСП СДМ1 1/0 ВКЛ ВЫКЛ  */
	uint8_t SDM1_RST :1 ; 		   /* сброс СДМ1, 1 - сбросы    */

	}reg_by_bit;
} sint1_reg1;
/* **************************************         */

/* РЕГИСТР   sin1_reg2  "Управление синтезатором частот 1"  АДРЕС 0xA  */
/* **************************************         */
struct
{
	uint32_t reg;
	struct{
	uint8_t ADR:5;     /* АДРЕС 0x0 */
	uint32_t MOD :23 ; 		   /* Знаменатель дроби сигма дельта модулятора  */
	uint8_t DT:2;     /* Режим генератора ПСП СДМ2 */
	uint8_t sdm_sel:1;     /* выбор СДМ 0/1 СДМ1/СДМ2 */

	}reg_by_bit;
} sint1_reg2;
/* **************************************         */


/* РЕГИСТР   sin1_reg3  "Управление синтезатором частот 1"  АДРЕС 0xB  */
/* **************************************         */
struct
{
	uint32_t reg;
	struct{
	uint8_t ADR:5;     /* АДРЕС 0x0 */
	uint8_t MX:4;     /* Выходной мультиплексор */
	uint8_t PFD_T:2;     /* Управление ЧФД */
	uint8_t RD:6;     /* коэффициент деления опорного делителя */
	uint16_t ND:9;     /* коэфф деления делителя ГУН */
	uint16_t SDM_ST:4;     /* коэфф деления делителя ГУН */

	}reg_by_bit;
} sint1_reg3;
/* **************************************         */


/* РЕГИСТР   sint2_reg  "Управление синтезатором частот 2"  АДРЕС 0xC  */
/* **************************************         */
struct
{
	uint32_t reg;
	struct{
	uint8_t ADR:5;     /* АДРЕС 0x0 */
	uint8_t CLK_EN:1;     /*  ВКЛ тактовой частоты цепи коррекции постоянного смещения */
	uint8_t FM:1;     /*  Деление выходной частоты ФАПЧ2 0/1 деление на 5\10  10\20 */
	uint8_t TD:2;		/* управление ЧФД*/
	uint8_t RD:4;     /*  Коэффициент деления опорного делителя */
	uint16_t FD:9;     /*  Коэффициент делителя ГУН */
	uint8_t FDR:1;     /*  Сброс делителя ГУН 1 -сброс */
	uint8_t PLL_MODE:1;     /*  АКТИВАЦИЯ ФАПЧ2/УДВОИТЕЛЯ  1/0 ФАПЧ/УДВОИТЕЛЬ */
	uint8_t PLL2FREQ:3;     /*  Коэффициент деления доп делителя */

	}reg_by_bit;
} sint2_reg;
/* **************************************         */



/* РЕГИСТР   inoutbuf  "Управление блоком ввода - вывода "  АДРЕС 0xD  */
/* **************************************         */
struct
{
	uint32_t reg;
	struct{
	uint8_t ADR:5;     /* АДРЕС 0x0 */
	uint8_t inout_buf:1;     /* переключение нагрузочной способности 1/0 5пФ/20пФ */

	}reg_by_bit;
} inoutbuf;
/* **************************************         */


/* РЕГИСТР   sint1_reg4  "Управление синтезатором частот 1 "  АДРЕС 0xE  */
/* **************************************         */
struct
{
	uint32_t reg;
	struct{
	uint8_t ADR:5;     /* АДРЕС 0x0 */
	uint8_t band:6;     /* Выбор диапазона ГУН */
	uint8_t vs:2;     /* Выбор ГУН  */
	uint8_t agcic:5;     /* задание амплитуды ГУН в ручном режиме  */
	uint8_t agcm:1;     /* Режим регулировки 1-точный режим регулировки  */
	uint8_t agcd:1;     /* ВКл. цифровой режим регулировки ГУН  0/1 ручная/автоматическая*/
	uint8_t agca:1;     /* Вкл. детектор амплитуды ГУН 0/1 Вкл/Выкл  */
	uint8_t tb:1;     /* Тестовый буфер 0/1 Выкл/Вкл  */
	uint8_t c0:1;     /* Управление током токового ключа 0/1 0,5/1 мА  */
	}reg_by_bit;
} sint1_reg4;
/* **************************************         */



/* РЕГИСТР   freq_divider  "Управление квадратурным делителем частоты  "  АДРЕС 0xF  */
/* **************************************         */
struct
{
	uint32_t reg;
	struct{
	uint8_t ADR:5;     /* АДРЕС 0x0 */
	uint8_t amp:8;     /* Корреляция амплитуды */
	uint8_t phase:8;     /* Корреляция амплитуды */
	uint8_t DM:3;     /* Выходной делитель */

	}reg_by_bit;
} freq_divider;
/* **************************************         */




/*------------------------------------------------------------------------------------------------*/


/*Входные параметры РППУ*/
struct input_parameters
{
	uint32_t ref_clk_freq;

}input_parameters;



};

u32 cnt_q_corr, cnt_i_corr;
u32 enable_cnt_i_corr, enable_cnt_q_corr;

/*************************************************************/

/*  ********************************************************************************     */
/*  ********** **************Глобальные переменные для работы с РППУ    **************************     */
/*  ********************************************************************************     */


extern struct rppu_rf *rppu_rf_phy;
extern struct  input_parameters;
/*
extern uint32_t lcs_edge[LCS][3];
extern uint32_t lower_LC[64][3];
extern uint32_t middle_LC[64][3];
extern uint32_t upper_LC[64][3];
*/

/*  ********************************************************************************     */
/*  ********** **************Функции для устновки значения регистров РППУ    **************************     */
/*  ********************************************************************************     */

/*    установка значений по умолчанию во всех регистрах РППУ */
uint32_t  rppu_setup_by_default(  struct  rppu_rf *phy);

uint32_t  rppu_setreg_rec_rf_part(  struct  rppu_rf *phy);
uint32_t  rppu_setreg_rec_mixer1(  struct  rppu_rf *phy);
uint32_t  rppu_setreg_rec_mixer2(  struct  rppu_rf *phy);
uint32_t  rppu_setreg_rec_filter(  struct  rppu_rf *phy);
uint32_t  rppu_setreg_rec_ifa(  struct  rppu_rf *phy);
uint32_t  rppu_setreg_rec_adc(  struct  rppu_rf *phy);
uint32_t  rppu_setreg_tr_dac(  struct  rppu_rf *phy);
uint32_t  rppu_setreg_tr_mixer(  struct  rppu_rf *phy);
uint32_t  rppu_setreg_tr_preamp(  struct  rppu_rf *phy);
uint32_t  rppu_setreg_sin1_reg1(  struct  rppu_rf *phy);
uint32_t  rppu_setreg_sin1_reg2(  struct  rppu_rf *phy);
uint32_t  rppu_setreg_sin1_reg3(  struct  rppu_rf *phy);
uint32_t  rppu_setreg_sin2_reg(  struct  rppu_rf *phy);
uint32_t  rppu_setreg_inout_reg(  struct  rppu_rf *phy);
uint32_t  rppu_setreg_sin1_reg4(  struct  rppu_rf *phy);
uint32_t  rppu_setreg_freq_divider(  struct  rppu_rf *phy);


/*  ********************************************************************************     */
/*  ********** **************Функции для работы с РППУ    **************************     */
/*  ********************************************************************************     */








/*    Включение смесителя передатчика    */
uint32_t  rppu_tr_mixer_enable(  struct  rppu_rf *phy);

/*    Выключение смесителя передатчика    */
uint32_t  rppu_tr_mixer_disable(  struct  rppu_rf *phy);


/*    Включение ЦАП в режим 1 канала    */
uint32_t  rppu_DAC_1ch_enable(  struct  rppu_rf *phy);

/*Включение АЦП*/
uint32_t  rppu_ADC_enable(  struct  rppu_rf *phy);


/*    Включение МШУ1 на прием 1 канала    */
uint32_t  rppu_lna2_1ch_enable(  struct  rppu_rf *phy);

/*    ВЫКЛЮЧЕНИЕ  МШУ    */
uint32_t  rppu_lna2_1ch_disable(  struct  rppu_rf *phy);

/*    Включение квадратурного демодулятора    */
uint32_t  rppu_quad_demod_enable(  struct  rppu_rf *phy);

/*    Выключение квадратурного демодулятора    */
uint32_t  rppu_quad_demod_disable(  struct  rppu_rf *phy);

/*    Включение ФНЧ на прием 1 канала    */
uint32_t  rppu_lpf_1st_ch_enable(  struct  rppu_rf *phy);

/*    Выключение ФНЧ на прием 1 канала    */
uint32_t  rppu_lpf_1st_ch_disable(  struct  rppu_rf *phy);

/*    Включение УПЧ на прием 1 канала    */
uint32_t  rppu_if_amp_1st_ch_enable(  struct  rppu_rf *phy);

/*    Выключение УПЧ на прием 1 канала    */
uint32_t  rppu_if_amp_1st_ch_disable(  struct  rppu_rf *phy);


/*    настрйока приемника 1 кнала    */
uint32_t  rppu_reciev_setup(  struct  rppu_rf *phy,uint8_t amplify );


/*    настрйока приемника 1 кнала    */
uint32_t  rppu_tranciev_setup(  struct  rppu_rf *phy);

/*   включение приемника первого канала   */
//uint32_t  rppu_1ch_rec_enable(  struct  rppu_rf *phy);

/*   включение приемника первого канала в режим измерения DC смещения   */
uint32_t  rppu_1ch_dc_corr_enable(  struct  rppu_rf *phy);


/*   Установка частоты синтезатора 1
 * в  граничное значения поддиапазона
 * LC - номер контура
 * band_n - номер поддиапазона
 * edge  0/1  - НИЖНИЙ/ВЕРХНИЙ край
 *  */
uint32_t  rppu_sint1_edge_set(struct  rppu_rf *phy, uint8_t LC, uint8_t band_n, uint8_t edge);

/*Определение номера поддиапазона ГУН
 * uint32_t VCO_out_freq_div2 - частота ГУН после делителя на 2
 * uint32_t *ptr - указатель на массив поддиапазонов
 * - остальное - размеры массива
 * Возвращает номер поддиапазона 0-63
 * */
uint32_t  rppu_sint1_range_find(uint32_t *ptr,uint32_t rows, uint32_t columns,uint32_t VCO_out_freq_div2);


/*Фукции для вывывода отладочной информации*/

/*Вывод списка инициализации массива c частотным диапазонами*/
uint32_t rppu__debug_edges_print(uint32_t *ptr,uint32_t rows, uint32_t columns);

/*Обнуление массива c частотным диапазонами*/
uint32_t rppu__debug_edges_clear(uint32_t *ptr,uint32_t rows, uint32_t columns,uint8_t band_start, uint8_t band_end);

/* Коррекция уровня I и Q составляющих */
u32  rppu_quad_demod_enable_with_leveling(struct  rppu_rf *phy, u16 cnt_i, u16 cnt_q);

/* Измерение и вычисление значения коррекции уровня I и Q составляющих*/
u32 measure_and_calc_correct_i_q_levels();

u32 check_input_power();

/***************************************************************************/
#endif

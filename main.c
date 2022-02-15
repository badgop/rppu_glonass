
/*
 *
 * Лупбек работать не будет, закомментировны вызовы read_corr_buffer1()
 *
 */

#include "RT_AD.h"
#include "RT1_functions.h"
#include "RPPU.h"
#include "RT_RPPU.h"
#include "sync.h"
#include "DC_compensation.h"
#include "RPPU_GLONASS_SINT.h"
#include "glonass_tr.h"


#define DEBUG_OUTPUT

#define TABLE_LEN 128


extern struct sint1_params *sint1_parameters;

int main(void)
{
 	Xil_DCacheEnable();
 	xil_printf("---Entering main---\n\r");



 	set_initial_timing_conf();



  sint1_parameters= (struct sint1_params *) malloc (sizeof(*sint1_parameters));
 			if(!sint1_parameters){
 				return -1;
 			}



  Xil_Out32((BA_muxin),(u32)(0x1603801));//0x1203601

 /*Инициализация РППУ значениями по умолчанию */
  if (rppu_init(&rppu_rf_phy) == -1)
   				xil_printf("ERROR_RPPU_INIT!!!!!!!!!!\n");


  /*Настройка аналоговых трактов РППУ */
  rppu_1ch_tr_rec_setup(rppu_rf_phy,20);


  /*расчет параметров синтезатора */
  calculate_sint_regs(L1,p00,0.5e3,sint1_parameters);

#ifdef DEBUG_OUTPUT
  /*DEBUG PURPOSES ONLY*/
  xil_printf("R= %d \n",sint1_parameters->R);
  xil_printf("N= %d \n",sint1_parameters->N);
  xil_printf("B= %d \n",sint1_parameters->B);
  xil_printf("MOD= %d \n",sint1_parameters->MOD);
  xil_printf("FRAC= %d \n",sint1_parameters->FRAC);
#endif


  /*Запись регистров синтезатора  */

  /* структура, контур ГУН , номер банки */

  /* для нулевых каналов на моем экзепляре   */
  /* дипазон   VCO BAND   */
  /* L1        1   17   */
  /* L2        0   20   */

  uint8_t VCO=1;
  uint8_t band=15;

  rppu_glonass_sint_setup( sint1_parameters,rppu_rf_phy ,VCO,band);


  uint32_t data[3*TABLE_LEN]={0};

  data[0]=0xABCD;
  data[1]=0xBAFE;
  data[2]=0x0EDC;

  glonass_main(&data[0],TABLE_LEN);

 //enable_main_transmission_cycle();




	xil_printf("---Exiting main---\n\r");
	Xil_DCacheDisable();
	Xil_ICacheDisable();
	return 0;
}


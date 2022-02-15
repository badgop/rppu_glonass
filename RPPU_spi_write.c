/*
 * RPPU_spi_write.c
 *
 *  Created on: 12 марта 2018 г.
 *      Author: Ivan
 */


#include "RPPU_spi_write.h"

/*запись одного регистра РППУ*/
unsigned int rppu_write_reg(uint32_t reg_to_write)
{



	uint8_t i=1;
	uint32_t fl=0;




	/*ВКЛ SPI1M*/
	Xil_Out32((BA_RC+0x8),        (u32)(0x100));

	Xil_Out32((BA_SPI1 + 0x20), (u32)(0x0));

	Xil_Out32((BA_SPI1 + 0x4), (u32)(0x0C6));	// Режим 0; 32 бит данных; мин. частота


	/*Запись в FIFO буфер SPI контролера одного регистра в SPI*/

	if(((Xil_In32(BA_SPI1 + 0x30))&0x1) == 0)
		/*ПЕРЕПИСАТЬ*/
		   		{
						Xil_Out32((BA_SPI1 + 0x18), (u32)(reg_to_write));

		   		}



	/*старт SPI контролера*/
	Xil_Out32((BA_SPI1 + 0x20), (u32)(0x7));		// start

	while(i>0)
	{
		fl=Xil_In32((BA_SPI1  + 0x34));

		if(fl)
			{
					/*xil_printf("SPI write ok \n\r");*/
					goto EXIT_OK;
					/*ПЕРЕПИСАТЬ*/
			}
	}

EXIT_OK:

			Xil_Out32((BA_RC+0x8),        (u32)(0x000));


			return 0;

}

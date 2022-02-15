/*
 * glonass_tr.h
 *
 *  Created on: Dec 20, 2018
 *      Author: User1
 */

#ifndef SRC_GLONASS_TR_H_
#define SRC_GLONASS_TR_H_


/* defines for RT1 here   */
#include "RT_AD.h"

#define GLONASS_B (BA_T1+0x0C00)

#define GLONASS_COD_F_32 			(GLONASS_B+0x0000)
#define GLONASS_COD_F_16 			(GLONASS_B+0x0004)
#define GLONASS_DELAY_COD 			(GLONASS_B+0x0008)
#define GLONASS_DATA_85_54 			(GLONASS_B+0x000C)
#define GLONASS_DATA_53_22 			(GLONASS_B+0x0010)
#define GLONASS_DATA_21_1 			(GLONASS_B+0x0014)
#define GLONASS_CONTR 				(GLONASS_B+0x0018)
#define GLONASS_SYNC_EXT 			(GLONASS_B+0x001C)
#define GLONASS_SYNC_INT 			(GLONASS_B+0x0020)
#define GLONASS_SYNC_MODE 			(GLONASS_B+0x0024)
#define GLONASS_DELAY_START			(GLONASS_B+0x0028)
#define GLONASS_START_REG			(GLONASS_B+0x002C)
/*READ ONLY REGISTERS*/
#define GLONASS_CHIP_NUM			(GLONASS_B+0x0030)
#define GLONASS_CHIP_FRAC			(GLONASS_B+0x0034)
#define GLONASS_RESTRICT_REC_FLAG	(GLONASS_B+0x0038)
#define GLONASS_TRANS_SYMB_CNT		(GLONASS_B+0x003C)

void ch1_fir_tr_glo_load();
uint32_t glonass_main(uint32_t * data_ptr, uint16_t table_len);

#endif /* SRC_GLONASS_TR_H_ */

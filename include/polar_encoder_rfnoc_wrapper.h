#ifndef _POLAR_ENCODER_RFNOC_WRAPPER_H__
#define _POLAR_ENCODER_RFNOC_WRAPPER_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif



void CreateInstance();
void ReleaseInstance();		
void SetParams( 
			int taskid,
			int uldl_mode,
			int k,
			int e,
			int crc_select,
			int crc_init,
			int rnti_scrambling_en,
			int rnti,
			int npc,
			int npc_wm,
			int bypass_intlv);					
void Encode(
		 	uint64_t* tx_buf_ptr, 
		 	unsigned long long samples_to_encode, 
		 	unsigned long long num_requested_samples,
		 	uint64_t* rx_buf_ptr, 
		 	uint64_t* params_ptr);

#ifdef __cplusplus
}
#endif
#endif /* POLAR_ENCODER_RFNOC_HPP */

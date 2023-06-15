
#include "/root/rfnoc_test.ldpc/include/polar_encoder_rfnoc_wrapper.h"

//extern "C" {

#include "/root/rfnoc_test.ldpc/include/polar_encoder_rfnoc.hpp"
#include <vector>

//class polar_encoder;

void CreateInstance() {
    polar_encoder* encoder = polar_encoder::getInstance();
}


void ReleaseInstance(){
    polar_encoder::releaseInstance();
}
				
void SetParams(int taskid = 0, int uldl_mode = 0, int k = 0, int e = 0, int crc_select = 0, int crc_init = 0, 
	int rnti_scrambling_en = 0, int rnti = 0, int npc = 0, int npc_wm = 0, int bypass_intlv = 0){
		polar_encoder* encoder = polar_encoder::getInstance();
		encoder->set_params(taskid, uldl_mode, k, e, crc_select, crc_init, rnti_scrambling_en, rnti, npc, npc_wm, bypass_intlv);			
}
		
	    
void Encode(uint64_t* tx_buf_ptr = 0, unsigned long long samples_to_encode = 0, unsigned long long num_requested_samples = 0, uint64_t* rx_buf_ptr = 0, uint64_t* params_ptr = nullptr)
{
	polar_encoder* encoder = polar_encoder::getInstance();
	//std::vector<uint64_t> rx_buffer(num_requested_samples);
	encoder->encode(tx_buf_ptr, samples_to_encode, num_requested_samples, rx_buf_ptr, params_ptr);
	//rx_buf_ptr = &rx_buffer[0];
}
				
//}			

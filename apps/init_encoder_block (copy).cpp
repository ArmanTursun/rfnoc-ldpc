//
// Copyright 2019 Ettus Research, a National Instruments Brand
//
// SPDX-License-Identifier: GPL-3.0-or-later
//

// Example application to show how to write applications that depend on both UHD
// and out-of-tree RFNoC modules.
//
// It will see if a USRP is runnging the encoder block, if so, it will test to see
// if it can change the taskid.

#include <iostream>
#include <vector>

#include <rfnoc/example/polar_encoder_rfnoc.hpp>


///////////////////////////////////////////////////////////////////////////////

uint64_t swap_iq(unsigned i, std::vector<uint64_t> buffer){
    uint64_t cur_data, temp_data;
	
	cur_data = buffer[i];
	temp_data = 0;
	
	temp_data ^= (cur_data & 0x00000000000000FF) << 40;
	temp_data ^= (cur_data & 0x000000000000FF00) << 24;
	temp_data ^= (cur_data & 0x0000000000FF0000) << 40;	
	temp_data ^= (cur_data & 0x00000000FF000000) << 24;
	temp_data ^= (cur_data & 0x000000FF00000000) >> 24;
	temp_data ^= (cur_data & 0x0000FF0000000000) >> 40;
	temp_data ^= (cur_data & 0x00FF000000000000) >> 24;
	temp_data ^= (cur_data & 0xFF00000000000000) >> 40;
	
	//buffer[i] = temp_data;
	return temp_data;
}



int main()
{
    
    polar_encoder encoder;
    
    
   
	/************************************************************************
     * Send Data
     ***********************************************************************/
    size_t samples_to_encode_1 = 2;
    size_t samples_to_encode_2 = 2;
    size_t samples_to_encode_3 = 12;
    
    size_t num_requested_samples_1 = 4;
    size_t num_requested_samples_2 = 4;
    size_t num_requested_samples_3 = 34;
    

    // Create buffer
    std::vector<uint64_t> tx_buffer_1(samples_to_encode_1 / 2); // 64 bits, two 32 bits unsigned ints
    uint64_t* tx_buf_ptr_1 = &tx_buffer_1[0];
    std::vector<uint64_t> tx_buffer_2(samples_to_encode_2 / 2); // 64 bits, two 32 bits unsigned ints
    uint64_t* tx_buf_ptr_2 = &tx_buffer_2[0];
    std::vector<uint64_t> tx_buffer_3(samples_to_encode_3 / 2); // 64 bits, two 32 bits unsigned ints
    uint64_t* tx_buf_ptr_3 = &tx_buffer_3[0];
    
    tx_buffer_1[0] = 0xC17D4FAF3D390000;
    
	tx_buffer_2[0] = 0x81585E28E42D0000;
    
    tx_buffer_3[0] = 0x8C6F17AA69D5C00B;
	tx_buffer_3[1] = 0x4343FFD026A8E4DF;
	tx_buffer_3[2] = 0xBEFE900FB3231486;
	tx_buffer_3[3] = 0xDD9153D927F4BD2D;
	tx_buffer_3[4] = 0x151245B3F26F0F4C;
	tx_buffer_3[5] = 0x7C68BB970A000000; 	
    
    //std::cout << "Buffer_1 size:     " << tx_buffer_1.size() << std::endl;
    for (unsigned it = 0; it < tx_buffer_1.size(); ++it){
    	tx_buffer_1[it] = swap_iq(it, tx_buffer_1);
    	std::cout << "Sent Data_1 " << std::hex << tx_buffer_1[it] << "\n";
    }
    //std::cout << "Buffer_2 size:     " << tx_buffer_2.size() << std::endl;
    for (unsigned it = 0; it < tx_buffer_2.size(); ++it){
    	tx_buffer_2[it] = swap_iq(it, tx_buffer_2);
    	std::cout << "Sent Data_2 " << std::hex << tx_buffer_2[it] << "\n";
    }
    //std::cout << "Buffer_3 size:     " << tx_buffer_3.size() << std::endl;
    for (unsigned it = 0; it < tx_buffer_3.size(); ++it){
    	tx_buffer_3[it] = swap_iq(it, tx_buffer_3);
    	std::cout << "Sent Data_3 " << std::hex << tx_buffer_3[it] << "\n";
    }
    
    
    encoder.set_params(1, 0, 56, 112, 0, 0, 0, 0, 0, 0, 0);
    std::vector<uint64_t> rx_buf_ptr_1 = encoder.encode(tx_buf_ptr_1, samples_to_encode_1, num_requested_samples_1);    
    for (int i = 0; i < num_requested_samples_1 / 2; i++){
    	rx_buf_ptr_1[i] = swap_iq(i, rx_buf_ptr_1);
    	std::cout << rx_buf_ptr_1[i] << std::endl;
    }
    
    encoder.set_params(2, 0, 57, 114, 1, 0, 0, 0, 0, 0, 0);
    std::vector<uint64_t> rx_buf_ptr_2 = encoder.encode(tx_buf_ptr_2, samples_to_encode_2, num_requested_samples_2);
    for (int i = 0; i < num_requested_samples_2 / 2; i++){
    	rx_buf_ptr_2[i] = swap_iq(i, rx_buf_ptr_2);
    	std::cout << rx_buf_ptr_2[i] << std::endl;
    }
    
    encoder.set_params(3, 0, 365, 1046, 0, 0, 0, 0, 0, 0, 0);
    std::vector<uint64_t> rx_buf_ptr_3 = encoder.encode(tx_buf_ptr_3, samples_to_encode_3, num_requested_samples_3);
    for (int i = 0; i < num_requested_samples_3 / 2; i++){
    	rx_buf_ptr_3[i] = swap_iq(i, rx_buf_ptr_3);
    	std::cout << rx_buf_ptr_3[i] << std::endl;
    }
    
    return 0;
		
}

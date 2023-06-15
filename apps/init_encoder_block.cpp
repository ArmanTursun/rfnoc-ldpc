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
//#include <vector>
//#include <unistd.h>
//#include <thread>

#include <rfnoc/example/polar_encoder_rfnoc_wrapper.h>
//#include <rfnoc/example/send.hpp>


///////////////////////////////////////////////////////////////////////////////

void swap_iq(uint64_t* tx_buf_ptr, size_t vec_size){
    uint64_t temp_data;
	
	for (int i = 0; i < vec_size; i++) {
		temp_data = 0;
		
		temp_data |= (tx_buf_ptr[i] & 0x00000000000000FF) << 40;
		temp_data |= (tx_buf_ptr[i] & 0x000000000000FF00) << 24;
		temp_data |= (tx_buf_ptr[i] & 0x0000000000FF0000) << 40;	
		temp_data |= (tx_buf_ptr[i] & 0x00000000FF000000) << 24;
		temp_data |= (tx_buf_ptr[i] & 0x000000FF00000000) >> 24;
		temp_data |= (tx_buf_ptr[i] & 0x0000FF0000000000) >> 40;
		temp_data |= (tx_buf_ptr[i] & 0x00FF000000000000) >> 24;
		temp_data |= (tx_buf_ptr[i] & 0xFF00000000000000) >> 40;
		
		tx_buf_ptr[i] = temp_data;
	}
}
/*
void swap_iq_128(uint64_t* tx_buf_ptr, size_t vec_size){
    uint64_t temp_data;
	
	for (int i = 0; i < vec_size; i++) {
		temp_data = 0;
		
		temp_data |= (tx_buf_ptr[i] & 0x00000000000000FF) << 40;
		temp_data |= (tx_buf_ptr[i] & 0x000000000000FF00) << 24;
		temp_data |= (tx_buf_ptr[i] & 0x0000000000FF0000) << 40;	
		temp_data |= (tx_buf_ptr[i] & 0x00000000FF000000) << 24;
		temp_data |= (tx_buf_ptr[i] & 0x000000FF00000000) >> 24;
		temp_data |= (tx_buf_ptr[i] & 0x0000FF0000000000) >> 40;
		temp_data |= (tx_buf_ptr[i] & 0x00FF000000000000) >> 24;
		temp_data |= (tx_buf_ptr[i] & 0xFF00000000000000) >> 40;
		
		tx_buf_ptr[i] = temp_data;
	}
}
*/
/*
void nr_uint64_uint32(uint64_t *in, uint16_t arraySize, uint32_t *out){
	uint16_t size32 = ceil(arraySize / 32.0);
	uint16_t size64 = ceil(arraySize / 64.0);
	
	for (int i = 0; i < (size64-1); i++) {
		out[2 * i + 1] = 0;
		for (int j = 0; j < 32; j++) {	
			out[2 * i + 1] <<= 1;
			out[2 * i + 1] |= (in[i] >> j) & 1;
		}
		out[2 * i] = 0;
		for (int j = 0; j < 32; j++) {
			out[2 * i] <<= 1;
			out[2 * i] |= (in[i] >> (j + 32)) & 1;
		}
	}
	
	uint16_t left_bit   = arraySize - (size64 - 1) * 64;
	uint16_t shift_size = 64 - left_bit;
	if (left_bit > 32) {
		out[size32 - 2] = 0;
		for (int j = 0; j < 32; j++) {
			out[size32 - 2] <<= 1;
			out[size32 - 2] |= (in[size64 - 1] >> (j + 32)) & 1;
		}
		left_bit -= 32;	
	}
	
	out[size32 - 1] = 0;
	for (int j = 0; j < left_bit; j++) {
		out[size32 - 1] <<= 1;
		out[size32 - 1] |= (in[size64 - 1] >> (j + shift_size)) & 1;
	}
}

void nr_uint32_uint64(uint32_t *in, uint16_t arraySize, uint64_t *out){

	uint16_t size32 = ceil(arraySize / 32.0);
	uint16_t size64 = ceil(arraySize / 64.0);
	
	for (int i = 0; i < size64 - 1; i++) {
		out[i] = 0;
		for (int j = 0; j < 32; j++) {
			out[i] <<= 1;
			out[i] |= (in[2 * i] >> j) & 1;			
		}
		for (int j = 0; j < 32; j++) {
			out[i] <<= 1;
			out[i] |= (in[2 * i + 1] >> j) & 1;			
		}
	}
	
	uint16_t left_bit   = arraySize - (size64 - 1) * 64;
	uint16_t shift_size = 64 - left_bit;
	out[size64 - 1] = 0;
	if (left_bit > 32){
		for (int j = 0; j < 32; j++) {
			out[size64 - 1] <<= 1;
			out[size64 - 1] |= (in[2 * (size64 - 1)] >> j) & 1;		
		}
		left_bit -= 32;
	}
	
	for (int j = 0; j < left_bit; j++) {
		out[size64 - 1] <<= 1;
		out[size64 - 1] |= (in[size32 - 1] >> j) & 1;	
	}	
	out[size64 - 1] <<= shift_size;
}
*/

/*
void bit_reversal(uint64_t* tx_buf_ptr, size_t vec_size){
    
    for (int i = 0; i < vec_size; i++) {
    	for (int j = 0; j < 4; j++) {
    		uint8_t byte_i = (tx_buf_ptr[i] >> (8 * j)) & 0xFF;
        	uint8_t byte_j = (tx_buf_ptr[i] >> (8 * (7 - j))) & 0xFF;
        	tx_buf_ptr[i] &= ~(0xFFUL << (8 * j)) & ~(0xFFUL << (8 * (7 - j)));
        	tx_buf_ptr[i] |= (uint64_t)byte_j << (8 * j) | (uint64_t)byte_i << (8 * (7 - j));
    	}
    }

}
*/

uint64_t reverseBits(uint64_t number) {
    uint64_t reversed = 0;

    for (int i = 0; i < 64; ++i) {
        if ((number & (1ULL << i)) != 0)
            reversed |= (1ULL << (63 - i));
    }

    return reversed;
}

void send_packets(){
	
    //polar_encoder *encoder = GetInstance();	
    /************************************************************************
     * Send Data
     ***********************************************************************/
    //CreateInstance();
    size_t samples_to_encode_1 = 4;
//    size_t samples_to_encode_2 = 2;
//    size_t samples_to_encode_3 = 12;
    
    size_t num_requested_samples_1 = 4;
//    size_t num_requested_samples_2 = 4;
//    size_t num_requested_samples_3 = 34;
    

    // Create buffer
    uint64_t* tx_buffer_1;
    tx_buffer_1 = (uint64_t*)malloc((samples_to_encode_1 / 2) * sizeof(uint64_t));
    //std::vector<uint64_t> tx_buffer_1(samples_to_encode_1 / 2);
    //uint64_t  tx_buffer_1(samples_to_encode_1 / 2);
    uint64_t* tx_buf_ptr_1 = &tx_buffer_1[0];
    
//    uint64_t* tx_buffer_2;
//    tx_buffer_2 = (uint64_t*)malloc((samples_to_encode_2 / 2) * sizeof(uint64_t));
    //std::vector<uint64_t> tx_buffer_2(samples_to_encode_2 / 2);
//    uint64_t* tx_buf_ptr_2 = &tx_buffer_2[0];
    
//    uint64_t* tx_buffer_3;
//    tx_buffer_3 = (uint64_t*)malloc((samples_to_encode_3 / 2) * sizeof(uint64_t));
    //std::vector<uint64_t> tx_buffer_3(samples_to_encode_3 / 2);
//    uint64_t* tx_buf_ptr_3 = &tx_buffer_3[0];
    

    // FFFF7F00003E0000 0000000000000000
    // 0000000000000000 00007c0000feffff
    // out 0000000000000000 00029c0000feffff    
    //tx_buffer_1[0] = 0x00007c0000feffff;
    tx_buffer_1[0] = 0x3e063818009cffff;
    // 000000000000000000007c0000feffff
    tx_buffer_1[1] = 0x0000000083e08371;
    //tx_buffer_1[0] = 0xC17D4FAF3D390000;
    
//    tx_buffer_2[0] = 0x81585E28E42D0000;
    
//    tx_buffer_3[0] = 0x8C6F17AA69D5C00B;
//    tx_buffer_3[1] = 0x4343FFD026A8E4DF;
//    tx_buffer_3[2] = 0xBEFE900FB3231486;
//    tx_buffer_3[3] = 0xDD9153D927F4BD2D;
//    tx_buffer_3[4] = 0x151245B3F26F0F4C;
//    tx_buffer_3[5] = 0x7C68BB970A000000; 	
	
    //bit_reversal(tx_buf_ptr_1, 1);
    //bit_reversal(tx_buf_ptr_1, 1);
    for (unsigned it = 0; it < samples_to_encode_1 / 2; ++it){
    	std::cout << "Sent Data " << std::hex << tx_buffer_1[it] << "\n";
    	tx_buffer_1[it] = reverseBits(tx_buffer_1[it]);   	
    }
    swap_iq(tx_buf_ptr_1, 2);
//    swap_iq(tx_buf_ptr_2, 1);
//    swap_iq(tx_buf_ptr_3, 6);
    
    
    //for (unsigned it = 0; it < samples_to_encode_2 / 2; ++it){
    	//std::cout << "Sent Data_2 " << std::hex << tx_buffer_2[it] << "\n";
    //}
    //for (unsigned it = 0; it < samples_to_encode_3 / 2; ++it){
    	//std::cout << "Sent Data_3 " << std::hex << tx_buffer_3[it] << "\n";
    //}
    
    
    
    //SetParams(1, 0, 56, 112, 0, 0, 0, 0, 0, 0, 0);
    //std::vector<uint64_t> rx_buffer_1(num_requested_samples_1 / 2);
    // 00 000100 00000000 000000000 0 0 0000 000 000 000
    // 2    6       8         9     1 1  4    3   3   3
    //  \  /        |        \                       /
    //   04        00           000000   
    // xx000100 ~ xx101110
    uint64_t params[2] = {0x0000000400000001,0x1111111111111111};
    //uint64_t params[2] = {0b0000000000000000000000000000010000000000000011000110000000000000,0x1111111111111111};
    //                     |||    ||      ||       ||||  || || || |
    //                     r   mb     id       r    ho  r  bg z  z
    //                     xx101110
                                                      
    //swap_iq(&params[0], 2);
    uint64_t* params_ptr = params;
    //unsigned __int128 params = 0x0000000000000000 0000000400000000;
    //swap_iq(params_ptr, 4);
    
    uint64_t* rx_buffer_1;
    rx_buffer_1 = (uint64_t*)malloc((num_requested_samples_1 / 2) * sizeof(uint64_t));
    uint64_t* rx_buf_ptr_1 = &rx_buffer_1[0];
    Encode(tx_buf_ptr_1, samples_to_encode_1, num_requested_samples_1, rx_buf_ptr_1, params_ptr);  
    swap_iq(rx_buf_ptr_1, 2);  
    for (int i = 0; i < num_requested_samples_1 / 2; i++){
    	rx_buf_ptr_1[i] = reverseBits(rx_buf_ptr_1[i]);
    	std::cout << "Received Data " << rx_buf_ptr_1[i] << std::endl;
    }
    
    //SetParams(1, 0, 57, 114, 1, 0, 0, 0, 0, 0, 0);
    //std::vector<uint64_t> rx_buffer_2(num_requested_samples_2 / 2);
/*    uint64_t* rx_buffer_2;
    rx_buffer_2 = (uint64_t*)malloc((num_requested_samples_2 / 2) * sizeof(uint64_t));
    uint64_t* rx_buf_ptr_2 = &rx_buffer_2[0];
    Encode(tx_buf_ptr_2, samples_to_encode_2, num_requested_samples_2, rx_buf_ptr_2);
    swap_iq(rx_buf_ptr_2, 2);
    for (int i = 0; i < num_requested_samples_2 / 2; i++){
    	std::cout << rx_buf_ptr_2[i] << std::endl;
    }
*/
/*    
    //SetParams(1, 0, 365, 1046, 0, 0, 0, 0, 0, 0, 0);
    //std::vector<uint64_t> rx_buffer_3(num_requested_samples_3 / 2);
    uint64_t* rx_buffer_3;
    rx_buffer_3 = (uint64_t*)malloc((num_requested_samples_3 / 2) * sizeof(uint64_t));
    uint64_t* rx_buf_ptr_3 = &rx_buffer_3[0];
    Encode(tx_buf_ptr_3, samples_to_encode_3, num_requested_samples_3, rx_buf_ptr_3);
    swap_iq(rx_buf_ptr_3, 17);
    //bit_reversal(rx_buf_ptr_3, 17);
    for (int i = 0; i < num_requested_samples_3 / 2; i++){
    	std::cout << rx_buf_ptr_3[i] << std::hex << std::endl;
    }
*/       
    //std::vector<uint32_t> new_out(samples_to_encode_1);
    //nr_uint64_uint32(&rx_buffer_1[0], 112, &new_out[0]);
    //for (int i = 0; i < num_requested_samples_1; i++){
    	//uint32_t cur_data = new_out[i];
    	//std::cout << new_out[i] << std::endl;
    //}
    
    //nr_uint32_uint64(&new_out[0], 112, &rx_buffer_1[0]);
    //for (int i = 0; i < num_requested_samples_1 / 2; i++){
    	//uint32_t cur_data = new_out[i];
    	//std::cout << rx_buffer_1[i] << std::endl;
    //}

}


int main()
{
    CreateInstance();
    //polar_encoder *encoder1 = GetInstance();
    //polar_encoder *encoder2 = polar_encoder::getInstance();
    //polar_encoder *encoder3 = polar_encoder::getInstance();
    //polar_encoder *encoder4 = polar_encoder::getInstance();
    
    //std::thread t1(send_packets);
    //std::thread t2(send_packets);
    
    //t1.join();
    //t2.join();
    
    //send_one_packets();
    //send_packets();
    //send_one_packets();
    send_packets();
    //send_packets(encoder3);
    //send_packets(encoder4);
    
    ReleaseInstance();
    
    return 0;
		
}

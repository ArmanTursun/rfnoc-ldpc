// polar_encoder_rfnoc.h

#ifndef POLAR_ENCODER_RFNOC_HPP
#define POLAR_ENCODER_RFNOC_HPP

#pragma once

#include </root/rfnoc_test.ldpc/include/encoder_block_control.hpp>
#include <uhd/utils/graph_utils.hpp>
#include <mutex>

struct rfnoc_struc{

  // --------------------------------
  // variables for USRP configuration
  // --------------------------------
  //! USRP device pointer
  uhd::rfnoc::rfnoc_graph::sptr graph;
  
  //! RFNoC Block pointer
  rfnoc::example::encoder_block_control::sptr encoder_block;

  //create a send streamer and a receive streamer
  //! RFNoC TX Stream
  uhd::tx_streamer::sptr tx_stream;
  //! RFNoC RX Stream
  uhd::rx_streamer::sptr rx_stream;

  //! RFNoC TX Metadata
  uhd::tx_metadata_t tx_md;
  //! RFNoC RX Metadata
  uhd::rx_metadata_t rx_md;

};


class polar_encoder{
	public:
	
		static polar_encoder* getInstance();
		
		static void releaseInstance();
		
		const rfnoc_struc* getStruct() const;
		
		void set_params(
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
					
		void encode(
		 				uint64_t* tx_buf_ptr, 
		 				unsigned long long samples_to_encode, 
		 				unsigned long long num_requested_samples,
		 				uint64_t* rx_buf_ptr,
		 				uint64_t* params_ptr = nullptr);
		
	private:
	
		polar_encoder();
		
		polar_encoder(const polar_encoder&) = delete;
    	polar_encoder& operator=(const polar_encoder&) = delete;
		
		static polar_encoder* m_instance;
		static std::mutex mutex_;
		
		rfnoc_struc m_rfnoc_struc;
   	
};

#endif /* POLAR_ENCODER_RFNOC_HPP */

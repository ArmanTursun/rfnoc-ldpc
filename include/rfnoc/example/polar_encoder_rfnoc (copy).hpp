// polar_encoder_rfnoc.h

#ifndef POLAR_ENCODER_RFNOC_HPP
#define POLAR_ENCODER_RFNOC_HPP

#pragma once

#include <uhd/exception.hpp>
#include <uhd/rfnoc_graph.hpp>
#include <uhd/utils/safe_main.hpp>
#include <rfnoc/example/encoder_block_control.hpp>
#include <boost/program_options.hpp>
#include <uhd/rfnoc/block_id.hpp>
#include <uhd/rfnoc/mb_controller.hpp>
#include <uhd/types/tune_request.hpp>
#include <uhd/utils/graph_utils.hpp>
#include <uhd/utils/math.hpp>
#include <mutex>

typedef struct {

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

} rfnoc_state_t;


class polar_encoder{
	public:
		
		polar_encoder();
		
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
					
		std::vector<uint64_t> encode(
		 				uint64_t* tx_buf_ptr, 
		 				unsigned long long samples_to_encode, 
		 				unsigned long long num_requested_samples);
		
	private:
		   	
		uhd::rfnoc::rfnoc_graph::sptr graph;
    	std::vector<uhd::rfnoc::block_id_t> encoder_blocks;
    	
    	rfnoc::example::encoder_block_control::sptr encoder_block;
		uhd::device_addr_t streamer_args;
		
		uhd::tx_streamer::sptr tx_stream;
    	uhd::tx_metadata_t tx_md;
    	uhd::rx_streamer::sptr rx_stream;
    	uhd::rx_metadata_t rx_md;
   	
};

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
#include <chrono>
#include <csignal>
#include <fstream>
#include <iostream>
#include <thread>
#include <bitset>

#include <rfnoc/example/polar_encoder_rfnoc.hpp>



polar_encoder::polar_encoder(){
	graph = uhd::rfnoc::rfnoc_graph::make("type=n3xx,addr=192.168.10.2");
	encoder_blocks = graph->find_blocks<rfnoc::example::encoder_block_control>("");
	encoder_block = graph->get_block<rfnoc::example::encoder_block_control>(encoder_blocks.front());
		
	streamer_args["block_id"]   = encoder_block->get_block_id().to_string();
    streamer_args["block_port"] = std::to_string(0);
    		
    /************************************************************************
    * Set up tx_streamer to encoder block
    ***********************************************************************/
    uhd::stream_args_t stream_tx_args{"sc16", "sc16"};    	
    
    stream_tx_args.args            = streamer_args;
    stream_tx_args.channels        = {0};

    tx_stream = graph->create_tx_streamer(1, stream_tx_args);
    
    /************************************************************************
    * Set up rx_streamer to encoder block
    ***********************************************************************/
    uhd::stream_args_t stream_rx_args{"sc16", "sc16"};
	
	stream_rx_args.args            = streamer_args;
	stream_rx_args.channels        = {0};

    rx_stream = graph->create_rx_streamer(1, stream_rx_args);
    			
    /************************************************************************
    * Connect streamers
    ***********************************************************************/	    
    graph->connect(tx_stream, 0, encoder_block->get_block_id(), 0);
    graph->connect(encoder_block->get_block_id(), 0, rx_stream, 0);
    graph->commit();
}

	
		////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////
		//////                                                           ///////
		//////                 Set Parameters                            /////// 
		//////                                                           ///////
		////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////
		

		
void polar_encoder::set_params(
					int taskid = 0,
					int uldl_mode = 0,
					int k = 0,
					int e = 0,
					int crc_select = 0,
					int crc_init = 0,
					int rnti_scrambling_en = 0,
					int rnti = 0,
					int npc = 0,
					int npc_wm = 0,
					int bypass_intlv = 0)
{
       
    		// set taskid
    		//constexpr uint32_t new_taskid_value = taskid;
    		encoder_block->set_taskid_value(taskid);
    		const uint32_t taskid_value_read = encoder_block->get_taskid_value();
    

    		if (taskid_value_read != taskid) {
        		std::cout << "ERROR: Readback of encoder value not working! "
                  		<< "Expected: " << taskid << " Read: " << taskid_value_read
                  		<< std::endl;
    		}
    
    		// set uldl_mode
    		//constexpr uint32_t new_uldl_mode_value = uldl_mode;
    		encoder_block->set_uldl_mode_value(uldl_mode);
    		const uint32_t uldl_mode_value_read = encoder_block->get_uldl_mode_value();

    		if (uldl_mode_value_read != uldl_mode) {
        		std::cout << "ERROR: Readback of encoder value not working! "
                  		<< "Expected: " << uldl_mode << " Read: " << uldl_mode_value_read
                  		<< std::endl;
    		}
   
    		// set k
    		//constexpr uint32_t new_k_value = k;
    		encoder_block->set_k_value(k);
    		const uint32_t k_value_read = encoder_block->get_k_value();

    		if (k_value_read != k) {
        		std::cout << "ERROR: Readback of encoder value not working! "
                  		<< "Expected: " << k << " Read: " << k_value_read
                  		<< std::endl;
    		}
    
    
    		// set crc_select
    		//constexpr uint32_t new_crc_select_value = crc_select;
    		encoder_block->set_crc_select_value(crc_select);
    		const uint32_t crc_select_value_read = encoder_block->get_crc_select_value();

    		if (crc_select_value_read != crc_select) {
        		std::cout << "ERROR: Readback of encoder value not working! "
                  		<< "Expected: " << crc_select << " Read: " << crc_select_value_read
                  		<< std::endl;
    		}
    
    		// set crc_init
    		//constexpr uint32_t new_crc_init_value = crc_init;
    		encoder_block->set_crc_init_value(crc_init);
    		const uint32_t crc_init_value_read = encoder_block->get_crc_init_value();

    		if (crc_init_value_read != crc_init) {
        		std::cout << "ERROR: Readback of encoder value not working! "
                  		<< "Expected: " << crc_init << " Read: " << crc_init_value_read
                  		<< std::endl;
    		}
    
    		// set rnti_scrambling_en
    		//constexpr uint32_t new_rnti_scrambling_en_value = rnti_scrambling_en;
    		encoder_block->set_rnti_scrambling_en_value(rnti_scrambling_en);
    		const uint32_t rnti_scrambling_en_value_read = encoder_block->get_rnti_scrambling_en_value();

    		if (rnti_scrambling_en_value_read != rnti_scrambling_en) {
        		std::cout << "ERROR: Readback of encoder value not working! "
                  		<< "Expected: " << rnti_scrambling_en << " Read: " << rnti_scrambling_en_value_read
                  		<< std::endl;
    		}
    
    		// set rnti
    		//constexpr uint32_t new_rnti_value = rnti;
    		encoder_block->set_rnti_value(rnti);
    		const uint32_t rnti_value_read = encoder_block->get_rnti_value();

    		if (rnti_value_read != rnti) {
        		std::cout << "ERROR: Readback of encoder value not working! "
                  		<< "Expected: " << rnti << " Read: " << rnti_value_read
                  		<< std::endl;
    		}
    
    		// set npc
    		//constexpr uint32_t new_npc_value = npc;
    		encoder_block->set_npc_value(npc);
    		const uint32_t npc_value_read = encoder_block->get_npc_value();

    		if (npc_value_read != npc) {
        		std::cout << "ERROR: Readback of encoder value not working! "
                  		<< "Expected: " << npc << " Read: " << npc_value_read
                  		<< std::endl;
    		}
    
    		// set npc_wm
    		//constexpr uint32_t new_npc_wm_value = npc_wm;
    		encoder_block->set_npc_wm_value(npc_wm);
    		const uint32_t npc_wm_value_read = encoder_block->get_npc_wm_value();

    		if (npc_wm_value_read != npc_wm) {
        		std::cout << "ERROR: Readback of encoder value not working! "
                  		<< "Expected: " << npc_wm << " Read: " << npc_wm_value_read
                  		<< std::endl;
    		}
   
    		// set bypass_intlv
    		//constexpr uint32_t new_bypass_intlv_value = bypass_intlv;
    		encoder_block->set_bypass_intlv_value(bypass_intlv);
    		const uint32_t bypass_intlv_value_read = encoder_block->get_bypass_intlv_value();

    		if (bypass_intlv_value_read != bypass_intlv) {
        		std::cout << "ERROR: Readback of encoder value not working! "
                  		<< "Expected: " << bypass_intlv << " Read: " << bypass_intlv_value_read
                  		<< std::endl;
    		}
   
    		// set e
    		//constexpr uint32_t new_e_value = e;
    		encoder_block->set_e_value(e);
    		const uint32_t e_value_read = encoder_block->get_e_value();

    		if (e_value_read != e) {
        		std::cout << "ERROR: Readback of encoder value not working! "
                  		<< "Expected: " << e << " Read: " << e_value_read
                  		<< std::endl;
    		} 
    
    		// set core_start
    		encoder_block->set_core_start_value(1);
    
}
		
	    
	    ////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////
		//////                                                           ///////
		//////                 Encode Data                               /////// 
		//////                                                           ///////
		////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////
	    
std::vector<uint64_t> polar_encoder::encode(
		 				uint64_t* tx_buf_ptr, 
		 				unsigned long long samples_to_encode = 0, 
		 				unsigned long long num_requested_samples = 0)
{
    		/************************************************************************
     		* Send Data
     		***********************************************************************/
			//std::cout << "Sending data to be encoded..." << std::endl;
    		tx_md.start_of_burst = true;
    		tx_md.end_of_burst   = false;

    		size_t num_tx_samps  = tx_stream->send(tx_buf_ptr, samples_to_encode, tx_md);

    		if (num_tx_samps != samples_to_encode) {
        		std::cout << "ERROR: Unable to send " << samples_to_encode << " samples" << std::endl;
    		}
    		
    		/************************************************************************
     		* Recieve Data
     		***********************************************************************/
     		
    		unsigned long long num_total_samps = 0;

    		std::vector<uint64_t> rx_buffer(num_requested_samples);
    		uint64_t *rx_buf_ptr = &rx_buffer[0];
    		bool overflow_message = true;

    		// setup streaming
    		uhd::stream_cmd_t stream_cmd((num_requested_samples == 0)
                                     ? uhd::stream_cmd_t::STREAM_MODE_START_CONTINUOUS
                                     : uhd::stream_cmd_t::STREAM_MODE_NUM_SAMPS_AND_DONE);
    		stream_cmd.num_samps  = uint64_t(num_requested_samples);
    		stream_cmd.stream_now = true;
    		stream_cmd.time_spec  = uhd::time_spec_t();

    		rx_stream->issue_stream_cmd(stream_cmd);
	 
    		while (num_requested_samples != num_total_samps) {
        		const auto now = std::chrono::steady_clock::now();

        		size_t num_rx_samps = rx_stream->recv(&rx_buffer.front(), rx_buffer.size(), rx_md, 3.0);
        		

        		if (rx_md.error_code == uhd::rx_metadata_t::ERROR_CODE_TIMEOUT) {
            		std::cout << "Timeout while streaming" << std::endl;
            		break;
        		}
        		if (rx_md.error_code == uhd::rx_metadata_t::ERROR_CODE_OVERFLOW) {
            		if (overflow_message) {
                		overflow_message = false;
                		std::cerr << "Got an overflow indication. If writing to disk, your\n"
                             		"write medium may not be able to keep up.\n";
            		}
            		continue;
        		}
        		if (rx_md.error_code != uhd::rx_metadata_t::ERROR_CODE_NONE) {
            		const auto error = std::string("Receiver error: ") + rx_md.strerror();
                	throw std::runtime_error(error);
        		}
        		num_total_samps += num_rx_samps;
        
    		} 

    		stream_cmd.stream_mode = uhd::stream_cmd_t::STREAM_MODE_STOP_CONTINUOUS;
    		rx_stream->issue_stream_cmd(stream_cmd);

    
    		return rx_buffer;
}

					

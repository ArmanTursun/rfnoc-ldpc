
#include "/root/rfnoc_test.ldpc/include/polar_encoder_rfnoc.hpp"
#include <uhd/exception.hpp>
#include <uhd/rfnoc/block_id.hpp>
#include <uhd/utils/graph_utils.hpp>
#include <chrono>
#include <csignal>

polar_encoder* polar_encoder::m_instance = nullptr;
std::mutex polar_encoder::mutex_;


polar_encoder::polar_encoder(){
	
    m_rfnoc_struc.graph = uhd::rfnoc::rfnoc_graph::make("type=x4xx,addr=192.168.20.2");
    //auto null_blocks = m_rfnoc_struc.graph->find_blocks("Block");
    //if (null_blocks.empty()) { 
    	//std::cout << "No blocks found!" << std::endl; 
    //}
    
    //auto block_controller = m_rfnoc_struc.graph->get_block("0/MyBlock#0");
    
    
    std::vector<uhd::rfnoc::block_id_t> encoder_blocks = m_rfnoc_struc.graph->find_blocks<rfnoc::example::encoder_block_control>("");
    //std::cout << "Find block";
    std::cout << "Block found!" << std::endl; 
    m_rfnoc_struc.encoder_block = m_rfnoc_struc.graph->get_block<rfnoc::example::encoder_block_control>(encoder_blocks.front());
    
    std::cout << "Availabe input ports of block " << m_rfnoc_struc.encoder_block->get_num_input_ports() << std::endl;
    std::cout << "Availabe output ports of block " << m_rfnoc_struc.encoder_block->get_num_output_ports() << std::endl;
    
    
    //uhd::device_addr_t streamer_args;
    //streamer_args["block_id"]   = m_rfnoc_struc.encoder_block->get_block_id().to_string();
    //streamer_args["block_port"] = std::to_string(2);
    
    std::vector<uhd::rfnoc::graph_edge_t> static_connections = m_rfnoc_struc.graph->enumerate_static_connections();
    for (int i = 0; i < static_connections.size(); i++) {
        std::cout << "source: " << static_connections[i].src_blockid << static_connections[i].src_port << " ";
        std::cout << "dest: " << static_connections[i].dst_blockid << static_connections[i].dst_port << " ";
    }
    std::cout << std::endl;
    
    /************************************************************************
    * Set up tx_streamer to encoder block
    ***********************************************************************/
    uhd::stream_args_t stream_tx_args{"sc16", "sc16"};    	
    
    //stream_tx_args.args            = streamer_args;
    //stream_tx_args.channels        = {2};

    m_rfnoc_struc.tx_stream = m_rfnoc_struc.graph->create_tx_streamer(1, stream_tx_args);
    
    /************************************************************************
    * Set up rx_streamer to encoder block
    ***********************************************************************/
    uhd::stream_args_t stream_rx_args{"sc16", "sc16"};
	
    //stream_rx_args.args            = streamer_args;
    //stream_rx_args.channels        = {2};

    m_rfnoc_struc.rx_stream = m_rfnoc_struc.graph->create_rx_streamer(1, stream_rx_args);
    			
    /************************************************************************
    * Connect streamers
    ***********************************************************************/	    
    m_rfnoc_struc.graph->connect(m_rfnoc_struc.tx_stream, 0, m_rfnoc_struc.encoder_block->get_block_id(), 0);
    m_rfnoc_struc.graph->connect(m_rfnoc_struc.encoder_block->get_block_id(), 0, m_rfnoc_struc.rx_stream, 0);
    m_rfnoc_struc.graph->commit();
    
    std::vector<uhd::rfnoc::graph_edge_t> active_connections = m_rfnoc_struc.graph->enumerate_active_connections();
    for (int i = 0; i < active_connections.size(); i++) {
        std::cout << "source: " << active_connections[i].src_blockid << active_connections[i].src_port << " ";
        std::cout << "dest: " << active_connections[i].dst_blockid << active_connections[i].dst_port << " ";
    }
    std::cout << std::endl;
}

polar_encoder* polar_encoder::getInstance() {
    // Use double-checked locking to ensure thread safety and avoid unnecessary locking
    std::lock_guard<std::mutex> lock(mutex_);
    if (!m_instance) {
        m_instance = new polar_encoder();
    }
    return m_instance;
}

void polar_encoder::releaseInstance()
{
    polar_encoder* instance = polar_encoder::getInstance();
    delete instance;
}


const rfnoc_struc* polar_encoder::getStruct() const {
    return &m_rfnoc_struc;
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
    		m_rfnoc_struc.encoder_block->set_taskid_value(taskid);
    		const uint32_t taskid_value_read = m_rfnoc_struc.encoder_block->get_taskid_value();
    

    		if (taskid_value_read != taskid) {
        		std::cout << "ERROR: Readback of encoder value not working! "
                  		<< "Expected: " << taskid << " Read: " << taskid_value_read
                  		<< std::endl;
    		}
    
    		// set uldl_mode
    		//constexpr uint32_t new_uldl_mode_value = uldl_mode;
    		m_rfnoc_struc.encoder_block->set_uldl_mode_value(uldl_mode);
    		const uint32_t uldl_mode_value_read = m_rfnoc_struc.encoder_block->get_uldl_mode_value();

    		if (uldl_mode_value_read != uldl_mode) {
        		std::cout << "ERROR: Readback of encoder value not working! "
                  		<< "Expected: " << uldl_mode << " Read: " << uldl_mode_value_read
                  		<< std::endl;
    		}
   
    		// set k
    		//constexpr uint32_t new_k_value = k;
    		m_rfnoc_struc.encoder_block->set_k_value(k);
    		const uint32_t k_value_read = m_rfnoc_struc.encoder_block->get_k_value();

    		if (k_value_read != k) {
        		std::cout << "ERROR: Readback of encoder value not working! "
                  		<< "Expected: " << k << " Read: " << k_value_read
                  		<< std::endl;
    		}
    
    
    		// set crc_select
    		//constexpr uint32_t new_crc_select_value = crc_select;
    		m_rfnoc_struc.encoder_block->set_crc_select_value(crc_select);
    		const uint32_t crc_select_value_read = m_rfnoc_struc.encoder_block->get_crc_select_value();

    		if (crc_select_value_read != crc_select) {
        		std::cout << "ERROR: Readback of encoder value not working! "
                  		<< "Expected: " << crc_select << " Read: " << crc_select_value_read
                  		<< std::endl;
    		}
    
    		// set crc_init
    		//constexpr uint32_t new_crc_init_value = crc_init;
    		m_rfnoc_struc.encoder_block->set_crc_init_value(crc_init);
    		const uint32_t crc_init_value_read = m_rfnoc_struc.encoder_block->get_crc_init_value();

    		if (crc_init_value_read != crc_init) {
        		std::cout << "ERROR: Readback of encoder value not working! "
                  		<< "Expected: " << crc_init << " Read: " << crc_init_value_read
                  		<< std::endl;
    		}
    
    		// set rnti_scrambling_en
    		//constexpr uint32_t new_rnti_scrambling_en_value = rnti_scrambling_en;
    		m_rfnoc_struc.encoder_block->set_rnti_scrambling_en_value(rnti_scrambling_en);
    		const uint32_t rnti_scrambling_en_value_read = m_rfnoc_struc.encoder_block->get_rnti_scrambling_en_value();

    		if (rnti_scrambling_en_value_read != rnti_scrambling_en) {
        		std::cout << "ERROR: Readback of encoder value not working! "
                  		<< "Expected: " << rnti_scrambling_en << " Read: " << rnti_scrambling_en_value_read
                  		<< std::endl;
    		}
    
    		// set rnti
    		//constexpr uint32_t new_rnti_value = rnti;
    		m_rfnoc_struc.encoder_block->set_rnti_value(rnti);
    		const uint32_t rnti_value_read = m_rfnoc_struc.encoder_block->get_rnti_value();

    		if (rnti_value_read != rnti) {
        		std::cout << "ERROR: Readback of encoder value not working! "
                  		<< "Expected: " << rnti << " Read: " << rnti_value_read
                  		<< std::endl;
    		}
    
    		// set npc
    		//constexpr uint32_t new_npc_value = npc;
    		m_rfnoc_struc.encoder_block->set_npc_value(npc);
    		const uint32_t npc_value_read = m_rfnoc_struc.encoder_block->get_npc_value();

    		if (npc_value_read != npc) {
        		std::cout << "ERROR: Readback of encoder value not working! "
                  		<< "Expected: " << npc << " Read: " << npc_value_read
                  		<< std::endl;
    		}
    
    		// set npc_wm
    		//constexpr uint32_t new_npc_wm_value = npc_wm;
    		m_rfnoc_struc.encoder_block->set_npc_wm_value(npc_wm);
    		const uint32_t npc_wm_value_read = m_rfnoc_struc.encoder_block->get_npc_wm_value();

    		if (npc_wm_value_read != npc_wm) {
        		std::cout << "ERROR: Readback of encoder value not working! "
                  		<< "Expected: " << npc_wm << " Read: " << npc_wm_value_read
                  		<< std::endl;
    		}
   
    		// set bypass_intlv
    		//constexpr uint32_t new_bypass_intlv_value = bypass_intlv;
    		m_rfnoc_struc.encoder_block->set_bypass_intlv_value(bypass_intlv);
    		const uint32_t bypass_intlv_value_read = m_rfnoc_struc.encoder_block->get_bypass_intlv_value();

    		if (bypass_intlv_value_read != bypass_intlv) {
        		std::cout << "ERROR: Readback of encoder value not working! "
                  		<< "Expected: " << bypass_intlv << " Read: " << bypass_intlv_value_read
                  		<< std::endl;
    		}
   
    		// set e
    		//constexpr uint32_t new_e_value = e;
    		m_rfnoc_struc.encoder_block->set_e_value(e);
    		const uint32_t e_value_read = m_rfnoc_struc.encoder_block->get_e_value();

    		if (e_value_read != e) {
        		std::cout << "ERROR: Readback of encoder value not working! "
                  		<< "Expected: " << e << " Read: " << e_value_read
                  		<< std::endl;
    		} 
    
    		// set core_start
    		m_rfnoc_struc.encoder_block->set_core_start_value(1);
    
}
		
	    
	    ////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////
		//////                                                           ///////
		//////                 Encode Data                               /////// 
		//////                                                           ///////
		////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////
	    
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

void polar_encoder::encode(
		 				uint64_t* tx_buf_ptr = 0, 
		 				unsigned long long samples_to_encode = 0, 
		 				unsigned long long num_requested_samples = 0,
		 				uint64_t* rx_buf_ptr = 0,
		 				uint64_t* params_ptr = nullptr)
{
    		/************************************************************************
     		* Send Data
     		***********************************************************************/
			//std::cout << "Sending data to be encoded..." << std::endl;
    		m_rfnoc_struc.tx_md.start_of_burst = true;
    		m_rfnoc_struc.tx_md.end_of_burst   = false;
    		m_rfnoc_struc.tx_md.has_params = true;
    		
    		m_rfnoc_struc.tx_md.params_ptr = params_ptr;
    		//m_rfnoc_struc.tx_md.params = 0x11111111111111111111111111111111;

    		size_t num_tx_samps  = m_rfnoc_struc.tx_stream->send(tx_buf_ptr, samples_to_encode, m_rfnoc_struc.tx_md);
    		
    		//for (unsigned it = 0; it < samples_to_encode; ++it){
    			//std::cout << "Send " << std::hex << tx_buf_ptr[it] << "\n";
    		//}

    		if (num_tx_samps != samples_to_encode) {
        		std::cout << "ERROR: Unable to send " << samples_to_encode << " samples" << std::endl;
    		}
    		
    		/************************************************************************
     		* Recieve Data
     		***********************************************************************/
     		
    		unsigned long long num_total_samps = 0;

    		//std::vector<uint64_t> rx_buffer(num_requested_samples);
    		bool overflow_message = true;

    		// setup streaming
    		//uhd::stream_cmd_t stream_cmd((num_requested_samples == 0)
                                     //? uhd::stream_cmd_t::STREAM_MODE_START_CONTINUOUS
                                     //: uhd::stream_cmd_t::STREAM_MODE_NUM_SAMPS_AND_DONE);
               uhd::stream_cmd_t stream_cmd(uhd::stream_cmd_t::STREAM_MODE_START_CONTINUOUS);
    		stream_cmd.num_samps  = uint64_t(num_requested_samples);
    		stream_cmd.stream_now = true;
    		stream_cmd.time_spec  = uhd::time_spec_t();

    		m_rfnoc_struc.rx_stream->issue_stream_cmd(stream_cmd);
	 
    		while (num_requested_samples != num_total_samps) {
        		const auto now = std::chrono::steady_clock::now();

        		//size_t num_rx_samps = m_rfnoc_struc.rx_stream->recv(&rx_buffer.front(), rx_buffer.size(), m_rfnoc_struc.rx_md, 3.0);
        		size_t num_rx_samps = m_rfnoc_struc.rx_stream->recv(rx_buf_ptr, num_requested_samples, m_rfnoc_struc.rx_md, 3.0);
        		
        		//for (unsigned it = 0; it < num_requested_samples; ++it){
    				//std::cout << "receive " << std::hex << rx_buf_ptr[it] << "\n";
    			//}

        		if (m_rfnoc_struc.rx_md.error_code == uhd::rx_metadata_t::ERROR_CODE_TIMEOUT) {
            		std::cout << "Timeout while streaming" << std::endl;
            		break;
        		}
        		if (m_rfnoc_struc.rx_md.error_code == uhd::rx_metadata_t::ERROR_CODE_OVERFLOW) {
            		if (overflow_message) {
                		overflow_message = false;
                		std::cerr << "Got an overflow indication. If writing to disk, your\n"
                             		"write medium may not be able to keep up.\n";
            		}
            		continue;
        		}
        		if (m_rfnoc_struc.rx_md.error_code != uhd::rx_metadata_t::ERROR_CODE_NONE) {
            		const auto error = std::string("Receiver error: ") + m_rfnoc_struc.rx_md.strerror();
                	throw std::runtime_error(error);
        		}
        		num_total_samps += num_rx_samps;
        
    		} 

    		stream_cmd.stream_mode = uhd::stream_cmd_t::STREAM_MODE_STOP_CONTINUOUS;
    		m_rfnoc_struc.rx_stream->issue_stream_cmd(stream_cmd);

    		//uint64_t* rx_buf_ptr = &rx_buffer[0];
    		//return rx_buf_ptr;
}
					

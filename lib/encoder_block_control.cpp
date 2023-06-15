//
// Copyright 2019 Ettus Research, a National Instruments Brand
//
// SPDX-License-Identifier: GPL-3.0-or-later
//

// Include our own header:
#include "/root/rfnoc_test.ldpc/include/encoder_block_control.hpp"

// These two includes are the minimum required to implement a block:
#include <uhd/rfnoc/defaults.hpp>
#include <uhd/rfnoc/registry.hpp>

using namespace rfnoc::example;
using namespace uhd::rfnoc;

const uint32_t encoder_block_control::REG_TASKID_VALUE = 0x00;
const uint32_t encoder_block_control::REG_ULDL_MODE_VALUE = 0x04;
const uint32_t encoder_block_control::REG_K_VALUE = 0x08;
const uint32_t encoder_block_control::REG_E_VALUE = 0x0c;
const uint32_t encoder_block_control::REG_CRC_SELECT_VALUE = 0x10;
const uint32_t encoder_block_control::REG_CRC_INIT_VALUE = 0x14;
const uint32_t encoder_block_control::REG_RNTI_SCRAMBLING_EN_VALUE = 0x18;
const uint32_t encoder_block_control::REG_RNTI_VALUE = 0x1c;
const uint32_t encoder_block_control::REG_NPC_VALUE = 0x20;
const uint32_t encoder_block_control::REG_NPC_WM_VALUE = 0x24;
const uint32_t encoder_block_control::REG_BYPASS_INTLV_VALUE = 0x28;
const uint32_t encoder_block_control::REG_CORE_START_VALUE = 0x2c;



//const uint32_t encoder_block_control::REG_PARAM_READY_VALUE = 0x2c;

class encoder_block_control_impl : public encoder_block_control
{
public:
    RFNOC_BLOCK_CONSTRUCTOR(encoder_block_control) {}
	
	// set taskid
    void set_taskid_value(const uint32_t taskid)
    {
        regs().poke32(REG_TASKID_VALUE, taskid);
    }

    uint32_t get_taskid_value()
    {
        return regs().peek32(REG_TASKID_VALUE);
    }
    
    // set uldl_mode
        void set_uldl_mode_value(const uint32_t uldl_mode)
    {
        regs().poke32(REG_ULDL_MODE_VALUE, uldl_mode);
    }

    uint32_t get_uldl_mode_value()
    {
        return regs().peek32(REG_ULDL_MODE_VALUE);
    }
    
    // set k
        void set_k_value(const uint32_t k)
    {
        regs().poke32(REG_K_VALUE, k);
    }

    uint32_t get_k_value()
    {
        return regs().peek32(REG_K_VALUE);
    }
    
    // set e
        void set_e_value(const uint32_t e)
    {
        regs().poke32(REG_E_VALUE, e);
    }

    uint32_t get_e_value()
    {
        return regs().peek32(REG_E_VALUE);
    }
    
    // set crc_select
        void set_crc_select_value(const uint32_t crc_select)
    {
        regs().poke32(REG_CRC_SELECT_VALUE, crc_select);
    }

    uint32_t get_crc_select_value()
    {
        return regs().peek32(REG_CRC_SELECT_VALUE);
    }
    
    // set crc_init
        void set_crc_init_value(const uint32_t crc_init)
    {
        regs().poke32(REG_CRC_INIT_VALUE, crc_init);
    }

    uint32_t get_crc_init_value()
    {
        return regs().peek32(REG_CRC_INIT_VALUE);
    }

    
    // set rnti_scrambling_en
        void set_rnti_scrambling_en_value(const uint32_t rnti_scrambling_en)
    {
        regs().poke32(REG_RNTI_SCRAMBLING_EN_VALUE, rnti_scrambling_en);
    }

    uint32_t get_rnti_scrambling_en_value()
    {
        return regs().peek32(REG_RNTI_SCRAMBLING_EN_VALUE);
    }
    
    // set rnti
        void set_rnti_value(const uint32_t rnti)
    {
        regs().poke32(REG_RNTI_VALUE, rnti);
    }

    uint32_t get_rnti_value()
    {
        return regs().peek32(REG_RNTI_VALUE);
    }
    
    // set npc
        void set_npc_value(const uint32_t npc)
    {
        regs().poke32(REG_NPC_VALUE, npc);
    }

    uint32_t get_npc_value()
    {
        return regs().peek32(REG_NPC_VALUE);
    }
    
    // set npc_wm
        void set_npc_wm_value(const uint32_t npc_wm)
    {
        regs().poke32(REG_NPC_WM_VALUE, npc_wm);
    }

    uint32_t get_npc_wm_value()
    {
        return regs().peek32(REG_NPC_WM_VALUE);
    }
    
    
    // set bypass_intlv
        void set_bypass_intlv_value(const uint32_t bypass_intlv)
    {
        regs().poke32(REG_BYPASS_INTLV_VALUE, bypass_intlv);
    }

    uint32_t get_bypass_intlv_value()
    {
        return regs().peek32(REG_BYPASS_INTLV_VALUE);
    }
    
    // set core_start
        void set_core_start_value(const uint32_t core_start)
    {
        regs().poke32(REG_CORE_START_VALUE, core_start);
    }

//    uint32_t get_core_start_value()
//    {
//        return regs().peek32(REG_CORE_START_VALUE);
//    }
    

private:
};

UHD_RFNOC_BLOCK_REGISTER_DIRECT(
    encoder_block_control, 0x20230303, "ldpc", CLOCK_KEY_GRAPH, "bus_clk")

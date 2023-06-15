//
// Copyright 2019 Ettus Research, a National Instruments Brand
//
// SPDX-License-Identifier: GPL-3.0-or-later
//

#ifndef INCLUDED_RFNOC_EXAMPLE_ENCODER_BLOCK_CONTROL_HPP
#define INCLUDED_RFNOC_EXAMPLE_ENCODER_BLOCK_CONTROL_HPP

#include <uhd/config.hpp>
#include <uhd/rfnoc/noc_block_base.hpp>
#include <uhd/types/stream_cmd.hpp>


namespace rfnoc { namespace example {

/*! Block controller for the encoder block: Multiply amplitude of signal
 *
 * This block multiplies the signal input with a fixed encoder value.
 */
class UHD_API encoder_block_control : public uhd::rfnoc::noc_block_base
{
public:
    RFNOC_DECLARE_BLOCK(encoder_block_control)

    //! The register addresses
    static const uint32_t REG_TASKID_VALUE;
    static const uint32_t REG_ULDL_MODE_VALUE;
    static const uint32_t REG_K_VALUE;
    static const uint32_t REG_E_VALUE;
    static const uint32_t REG_CRC_SELECT_VALUE;
    static const uint32_t REG_CRC_INIT_VALUE;
    static const uint32_t REG_RNTI_SCRAMBLING_EN_VALUE;
    static const uint32_t REG_RNTI_VALUE;
    static const uint32_t REG_NPC_VALUE;
    static const uint32_t REG_NPC_WM_VALUE;
    static const uint32_t REG_BYPASS_INTLV_VALUE;
    static const uint32_t REG_CORE_START_VALUE;
    
    
//    static const uint32_t REG_PARAM_READY_VALUE;

    /*! Set the taskid value
     */
    virtual void set_taskid_value(const uint32_t taskid) = 0;
    virtual uint32_t get_taskid_value() = 0;
    
    /*! Set the uldl_mode value
     */
    virtual void set_uldl_mode_value(const uint32_t uldl_mode) = 0;
    virtual uint32_t get_uldl_mode_value() = 0;
    
    /*! Set the k value
     */
    virtual void set_k_value(const uint32_t k) = 0;
    virtual uint32_t get_k_value() = 0;
    
    /*! Set the e value
     */
    virtual void set_e_value(const uint32_t e) = 0;
    virtual uint32_t get_e_value() = 0;
    
    /*! Set the crc_select value
     */
    virtual void set_crc_select_value(const uint32_t crc_select) = 0;
    virtual uint32_t get_crc_select_value() = 0;
    
    /*! Set the crc_init value
     */
    virtual void set_crc_init_value(const uint32_t crc_init) = 0;
    virtual uint32_t get_crc_init_value() = 0;
    
    /*! Set the rnti_scrambling_en value
     */
    virtual void set_rnti_scrambling_en_value(const uint32_t rnti_scrambling_en) = 0;
    virtual uint32_t get_rnti_scrambling_en_value() = 0;
    
    /*! Set the rnti value
     */
    virtual void set_rnti_value(const uint32_t rnti) = 0;
    virtual uint32_t get_rnti_value() = 0;
    
    /*! Set the npc value
     */
    virtual void set_npc_value(const uint32_t npc) = 0;
    virtual uint32_t get_npc_value() = 0;
    
    /*! Set the npc_wm value
     */
    virtual void set_npc_wm_value(const uint32_t npc_wm) = 0;
    virtual uint32_t get_npc_wm_value() = 0;
    
    /*! Set the bypass_intlv value
     */
    virtual void set_bypass_intlv_value(const uint32_t bypass_intlv) = 0;
    virtual uint32_t get_bypass_intlv_value() = 0;
    
    /*! Set the core_start value
     */
    virtual void set_core_start_value(const uint32_t core_start) = 0;
    
};

}} // namespace rfnoc::example

#endif /* INCLUDED_RFNOC_EXAMPLE_ENCODER_BLOCK_CONTROL_HPP */

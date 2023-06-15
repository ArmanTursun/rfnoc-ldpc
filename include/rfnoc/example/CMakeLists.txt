#
# Copyright 2019 Ettus Research, a National Instruments Brand
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

# List all header files here (UHD and GNU Radio)
install(
    FILES
    encoder_block_control.hpp
    polar_encoder_rfnoc.hpp
    polar_encoder_rfnoc_wrapper.h
    send.hpp
    DESTINATION include/rfnoc/encoder
    COMPONENT headers
)

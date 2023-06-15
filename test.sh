#!/bin/bash

cd build
sudo make uninstall
make -j8
sudo make install
sudo ldconfig
cd apps
./init_encoder_block
#./init_encoder_block --args_rfnoc "type=n3xx,addr=192.168.10.2" --args_usrp "type=n3xx,addr=192.168.10.3" --taskid 1 --uldl_mode 0 --k 56 --e 112 --crc_select 0 --crc_init 0 --rnti 0 --npc 0 --npc_wm 0 --rnti_scrambling_en 0 --bypass_intlv 0
cd ..
cd ..

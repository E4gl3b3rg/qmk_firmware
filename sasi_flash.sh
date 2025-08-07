echo "Tölti a firmware-t 6 másodperc múlva..."

sleep 30

dfu-util --list

#dfu-util -a 0 -D .build/keychron_q8_ansi_Sasi_Q8_mod_1.bin --dfuse-address 0x08000000:leave --serial 208E386E5332
dfu-util -a 0 -s 0x08000000:leave -D .build/keychron_q8_ansi_Sasi_Q8_mod_1.bin --serial 208E386E5332



#debug
gdbstub: enabled=1, port=1234, text_base=0, data_base=0, bss_base=0

# rom image
romimage: file=/usr/local/share/bochs/BIOS-bochs-latest 
# cpu conf
#cpu: count=1, ips=50000000, reset_on_triple_fault=1, ignore_bad_msrs=1, msrs="msrs.def"
#cpuid: mmx=1, sep=1, sse=sse4_2, xapic=1, aes=1, movbe=1, xsave=1, cpuid_limit_winnt=0
# vga rom
vgaromimage: file=/usr/local/share/bochs/VGABIOS-lgpl-latest

# floppy driver
floppya: 1_44=anos.img, status=inserted
# boot from floppy
boot: floppy
# log messages

log: bochsout.txt
# disable mouse
mouse: enabled=0
# enable keyboard mapping
keyboard_mapping: enabled=0, map=/usr/local/share/bochs/keymaps/x11-pc-us.map
# set memory size
megs: 16

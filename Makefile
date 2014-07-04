#################################################
#	Make OS
#################################################
SUBDIRS = boot kernel

all: anos.img
	@echo "--------------------------------------"
	@echo "Successfully generate OS image"
	@echo "--------------------------------------"
	dd if=anos.img of=a.img bs=512 count=2048 conv=notrunc

anos.img: subdirs
	@echo "--------------------------------------"
	@echo "Generate anos-img"
	@echo "--------------------------------------"	
	cat boot/bootloader.bin kernel/kernel.bin > $@

subdirs: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

clean: 
	@echo "--------------------------------------"
	@echo "Start to clean temp files."
	@echo "--------------------------------------"		
	for dir in $(SUBDIRS); do \
		$(MAKE) clean -C $$dir; \
	done
	rm anos.img

.PHONY: all anos.image subdirs $(SUBDIRS) clean	
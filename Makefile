###############################################################################
# Rule to assemble and link all assembly files
###############################################################################
build:
	ca65 movingtank.asm -o movingtank.o
	ld65 -C nes.cfg movingtank.o -o movingtank.nes

###############################################################################
# Rule to remove all object (.o) and cartridge (.nes) files
###############################################################################
clean:
	rm *.o *.nes

###############################################################################
# Rule to run the final cartridge .nes file in the FCEUX emulator
###############################################################################
run:
	fceux movingtank.nes

CC=arm-none-eabi-gcc
MACH=cortex-m3
CFLAG=-mcpu=$(MACH) -mthumb -c

blinky0.o:blinky0.c
	$(CC) blinky0.c -o blinky0.0 $(CFLAG)
	
clean:
	del /S *.o *elf
	
load:
	openocd -f interface/stlink-v2.cfg -f board/stm32f103c8_blue_pill.cfg
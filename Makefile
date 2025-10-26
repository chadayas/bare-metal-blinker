TARGET = firmware
CC = arm-none-eabi-g++
AS = arm-none-eabi-as
FLAGS = -mcpu=cortex-m4 -mthumb 
LDSCRIPT = blink.ld

all:
	$(AS) $(FLAGS) blink_.s -o startup.o
	$(CC) $(FLAGS) -c blink.cpp -o main.o
	$(CC) $(FLAGS) -nostdlib -specs=nosys.specs -T $(LDSCRIPT) startup.o main.o -o $(TARGET).elf
	arm-none-eabi-objcopy -O binary $(TARGET).elf $(TARGET).bin
	arm-none-eabi-size $(TARGET).elf

clean:
	rm -f *.o *.elf *.bin *.map

flash: all
	st-flash write $(TARGET).bin 0x8000000

.PHONY: all clean flash

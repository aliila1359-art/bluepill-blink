CC = arm-none-eabi-gcc
CFLAGS = -mcpu=cortex-m3 -mthumb -specs=nosys.specs -T linker.ld -nostdlib

all:
	$(CC) $(CFLAGS) startup.c main.c -o firmware.elf
	arm-none-eabi-objcopy -O binary firmware.elf firmware.bin

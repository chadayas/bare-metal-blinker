# Hello Blinky
The first program usually written by embbeded devs. I've decided to blink the 
STM32F466RE Nucleo board using registers and bit manipulation which can be followed 
in the `blink.cpp` source code.

## GPIO
General input and output is our main peripheral on the within the memory map of the 
board that we will play with. This allows us to send data (in bits of course) to allow 
for certain operations

## Walkthrough
Define all our needed registers; `GPIOA`,`_MODER`, `_ODR`, `BSRR`, `OTYPER`, and etc. 
Some are could be used for the same purpose of blinking the LED but it does not hurt
to define them, we get the base address and add the offsets listed in the datasheets.

Define the RCC gate register, this opens the clock gates allowing the board to receive 
data. The GPIOA is under the AHB1 peripheral, so we find the base address of the RCC and 
apply the `RCC_AHB1` offset. Our functions ensure the correct bit manipulation on the 
GPIOA registers, bit manip for opening clock gates, and a delay function in order to 
blink our LED2 according to the length of the for loop.

## Tools

- **arm-none-eabi-g++** - ARM cross-compiler (C++) targeting the Cortex-M4
- **arm-none-eabi-as** - ARM assembler for the startup code (`blink_.s`)
- **arm-none-eabi-objcopy** - Converts the ELF to a raw binary for flashing
- **arm-none-eabi-size** - Reports firmware section sizes
- **st-flash** - STLink utility for flashing the binary to the board at `0x08000000`
- **GNU Make** - Build automation

## Compilation

The build is driven by the `Makefile` and targets the **Cortex-M4** with Thumb instructions (`-mcpu=cortex-m4 -mthumb`).

1. **Assemble** the startup code — `blink_.s` sets up the vector table and `Reset_Handler`, which initialises the stack pointer and calls `main`.
2. **Compile** `blink.cpp` — the application source that configures GPIOA registers via direct memory-mapped access and toggles PA5 through the BSRR register.
3. **Link** with `-nostdlib -specs=nosys.specs` using the custom linker script `blink.ld`, which maps Flash at `0x08000000` (512 K) and SRAM at `0x20000000` (112 K + 16 K).
4. **Objcopy** the ELF to a flat binary (`firmware.bin`).
5. **Flash** to the board with `st-flash write firmware.bin 0x8000000`.

```
make          # build
make flash    # build and flash
make clean    # remove build artifacts
```

## Video

https://github.com/user-attachments/assets/c48e5240-59bb-415b-9f53-a14b7e0136ac


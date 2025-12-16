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

## Video


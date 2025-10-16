# 7 Segments Display AVR MCU Library

## About
This is a repository with a microcontroller firmware C library for an Atmel MCU (ATMEGA328P). 
The code was written in C language and it was used the Atmel Studio IDE (GCC compiler) to compile and build the program. 
The code comments is in portuguese language.


## How it works
The device has a push button to select the counting mode. Pressing the button, the user can see a demonstration of a count using integer numbers, decimal number or string.
The main.c file was used to implement this demonstration.

Changing the #define in avr_display_7seg.h file the user can compile the code for use with common anode displays or common cathode displays.
The user can also define the decimal places of the decimal number displayed with #define modification.

The avr_display_7seg.h file shows the functions that the user has access to use in his final code.

### Library files:
- main.c     (test of the library)
- avr_macro.h  (header with macros)
- avr_debounce.c   (library for button debounce)
- avr_debounce.h   (header of the library for button debounce)
- avr_gpio.c       (library for use of AVR Atmel GPIOs)
- avr_gpio.h       (header of the library AVR Atmel GPIOs)
- avr_display_7seg.c  (library for use of 7 segments display)
- avr_display_7seg.h   (header of the library 7 segments display)


### Library Size
The complete firmware code has a size of 12KB. It can be modified a little for use with other microcontrollers. 
  

## DEMONSTRATION VIDEO

[![Watch the video.](https://i9.ytimg.com/vi_webp/A_VDRrmFAnU/mq2.webp?sqp=CJTQxMcG&rs=AOn4CLCO7SfW88MGza4UJEc4of3oDQ_WAA)](https://youtu.be/A_VDRrmFAnU)

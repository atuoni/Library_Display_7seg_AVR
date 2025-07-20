/*
 * Biblioteca de acionamento de GPIOs
 * para Atmel AVR
 *
 * Created: 29/06/2025 23:46:12
 * Author : Amauri Tuoni
 */


#include "avr_gpio.h" //header dessa biblioteca

 inline void GPIO_DisableGlobalPullUp()
 {
	 MCUCR |= 1<<PUD;
 }
 
 inline void GPIO_EnableGlobalPullUp()
 {
	 MCUCR &= ~(1<<PUD);
 }
 
 inline void GPIO_Init(volatile uint8_t* Port, uint8_t Pin, uint8_t PinMode)
 {
	 if (PinMode == GPIO_MODE_OUTPUT)
	 {
		 *(Port-0x01) |= Pin;
	 }
	 else if(PinMode == GPIO_MODE_INPUT_WITH_PULL_UP)
	 {
		 *(Port-0x01) &= ~(Pin);
		 *Port |= Pin;
		 GPIO_EnableGlobalPullUp();
	 }
	 else if(PinMode == GPIO_MODE_INPUT_WITHOUT_PULL_UP)
	 {
		 *(Port-0x01) &= ~(Pin);
		 *Port |= ~(Pin);
	 }
 }
 
 inline void GPIO_InitPin(uint8_t Pin, uint8_t PinMode)
 {
	 if (Pin < 8)            /* pin 0 = PD0, ..., 7 = PD7 */
	 {
		 GPIO_Init(&PORTD,(1<<Pin),PinMode);
	 }
	 else if (Pin < 14)      /* pin 8 = PB0, ..., 13 = PB5 (PB6 and PB7 reserved for External Clock) */
	 {
		 GPIO_Init(&PORTB,(1<<(Pin - 8)),PinMode);
	 }
	 else if (Pin < 21)      /* pin 14 = PC0, ..., 19 = PC5 (PC6 is Reset, PC7 doesn't exist) */
	 {
		 GPIO_Init(&PORTC,(1<<(Pin - 14)),PinMode);
	 }
 }
 
 inline void GPIO_DeInit(volatile uint8_t* Port, uint8_t Pin)
 {
	 *(Port-0x01) &= ~(Pin);
	 *(Port-0x02) &= ~(Pin);
	 *(Port) &= ~(Pin);
 }
 
 
 inline void GPIO_DeInitPin(uint8_t Pin)
 {
	 if (Pin < 8)            /* pin 0 = PD0, ..., 7 = PD7 */
	 {
		 GPIO_DeInit(&PORTD,(1<<Pin));
	 }
	 else if (Pin < 14)      /* pin 8 = PB0, ..., 13 = PB5 (PB6 and PB7 reserved for External Clock) */
	 {
		 GPIO_DeInit(&PORTB,(1<<(Pin - 8)));
	 }
	 else if (Pin < 21)      /* pin 14 = PC0, ..., 19 = PC5 (PC6 is Reset, PC7 doesn't exist) */
	 {
		 GPIO_DeInit(&PORTC,(1<<(Pin - 14)));
	 }
 }
 
 inline volatile uint8_t GPIO_Read(volatile uint8_t* Port, uint8_t Pin)
 {
	 return *(Port - 0x02) & (Pin);
 }
 
 inline void GPIO_Write(volatile uint8_t* Port, uint8_t Pin, uint8_t PinState)
 {
	 if (PinState == HIGH)
	 {
		 *Port |= Pin;
	 }
	 else if (PinState == LOW)
	 {
		 *Port &= ~(Pin);
	 }
	 else if (PinState == TOGGLE)
	 {
		 *(Port-0x02) = Pin;
	 }
 }
 
 inline void GPIO_Toggle(volatile uint8_t* Port, uint8_t Pin)
 {
	 *(Port-0x02) |= Pin; /* Uses a Single Instruction to Toggle a Bit */
	 
	 //*Port ^= Pin; /* Uses 4 Instructions to Toggle a Bit */
 }
 
 inline volatile uint8_t GPIO_ReadPin(uint8_t Pin)
 {
	 if (Pin < 8)            /* pin 0 = PD0, ..., 7 = PD7 */
	 {
		 return GPIO_Read(&PORTD,(1<<Pin));
	 }
	 else if (Pin < 14)      /* pin 8 = PB0, ..., 13 = PB5 (PB6 and PB7 reserved for External Clock) */
	 {
		 return GPIO_Read(&PORTB,(1<<(Pin - 8)));
	 }
	 else if (Pin < 21)      /* pin 14 = PC0, ..., 19 = PC5 (PC6 is Reset, PC7 doesn't exist) */
	 {
		 return GPIO_Read(&PORTC,(1<<(Pin - 14)));
	 }
		 return 0;   //pin doesn't exist      
 }
 
 inline void GPIO_WritePinHigh(uint8_t Pin)
 {
	 if (Pin < 8)            /* pin 0 = PD0, ..., 7 = PD7 */
	 {
		 GPIO_Write(&PORTD,(1<<Pin),HIGH);
	 }
	 else if (Pin < 14)      /* pin 8 = PB0, ..., 13 = PB5 (PB6 and PB7 reserved for External Clock) */
	 {
		 GPIO_Write(&PORTB,(1<<(Pin - 8)),HIGH);
	 }
	 else if (Pin < 21)      /* pin 14 = PC0, ..., 19 = PC5 (PC6 is Reset, PC7 doesn't exist) */
	 {
		 GPIO_Write(&PORTC,(1<<(Pin - 14)),HIGH);
	 }
 }
 
 inline void GPIO_WritePinLow(uint8_t Pin)
 {
	 if (Pin < 8)            /* pin 0 = PD0, ..., 7 = PD7 */
	 {
		 GPIO_Write(&PORTD,(1<<Pin),LOW);
	 }
	 else if (Pin < 14)      /* pin 8 = PB0, ..., 13 = PB5 (PB6 and PB7 reserved for External Clock) */
	 {
		 GPIO_Write(&PORTB,(1<<(Pin - 8)),LOW);
	 }
	 else if (Pin < 21)      /* pin 14 = PC0, ..., 19 = PC5 (PC6 is Reset, PC7 doesn't exist) */
	 {
		 GPIO_Write(&PORTC,(1<<(Pin - 14)),LOW);
	 }
 }
 
 inline void GPIO_WritePinToggle(uint8_t Pin)
 {
	 if (Pin < 8)            /* pin 0 = PD0, ..., 7 = PD7 */
	 {
		 GPIO_Write(&PORTD,(1<<Pin),TOGGLE);
	 }
	 else if (Pin < 14)      /* pin 8 = PB0, ..., 13 = PB5 (PB6 and PB7 reserved for External Clock) */
	 {
		 GPIO_Write(&PORTB,(1<<(Pin - 8)),TOGGLE);
	 }
	 else if (Pin < 21)      /* pin 14 = PC0, ..., 19 = PC5 (PC6 is Reset, PC7 doesn't exist) */
	 {
		 GPIO_Write(&PORTC,(1<<(Pin - 14)),TOGGLE);
	 }
 }
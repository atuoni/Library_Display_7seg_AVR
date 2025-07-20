 /*
 * Header da biblioteca acionamento de GPIOs
 * para Atmel AVR
 *
 * Created: 19/07/2025 23:46:12
 * Author : Amauri Tuoni
 */
 
 
 #ifndef AVR_GPIO_H_
 #define AVR_GPIO_H_
 
 #include <avr/io.h>  //biblioteca padrao AVR
 
 #pragma message ( "avr_gpio.h included" )
 
 #define GPIO_MODE_OUTPUT                0x00
 #define GPIO_MODE_TRI_STATE             0x02
 #define GPIO_MODE_INPUT_WITH_PULL_UP    0x01
 #define GPIO_MODE_INPUT_WITHOUT_PULL_UP 0x02
 #define LOW    0x00
 #define HIGH   0x01
 #define TOGGLE 0x02
 #define PB &PORTB
 #define PC &PORTC
 #define PD &PORTD
 
 #define P0  (1<<0)
 #define P1  (1<<1)
 #define P2  (1<<2)
 #define P3  (1<<3)
 #define P4  (1<<4)
 #define P5  (1<<5)
 #define P6  (1<<6)
 #define P7  (1<<7)
 #define ALL_PINS 0xFF
 
 
 #define D0  PD,P0
 #define D1  PD,P1
 #define D2  PD,P2
 #define D3  PD,P3
 #define D4  PD,P4
 #define D5  PD,P5
 #define D6  PD,P6
 #define D7  PD,P7
 #define D8  PB,P0
 #define D9  PB,P1
 #define D10 PB,P2
 #define D11 PB,P3
 #define D12 PB,P4
 #define D13 PB,P5
 #define D14 PC,P0
 #define D15 PC,P1
 #define D16 PC,P2
 #define D17 PC,P3
 #define D18 PC,P4
 #define D19 PC,P5
 #define A0  PC,P0
 #define A1  PC,P1
 #define A2  PC,P2
 #define A3  PC,P3
 #define A4  PC,P4
 #define A5  PC,P5
 
 #ifdef  PD0
 #undef  PD0
 #define PD0 0
 #endif
 #ifdef  PD1
 #undef  PD1
 #define PD1 1
 #endif
 #ifdef  PD2
 #undef  PD2
 #define PD2 2
 #endif
 #ifdef  PD3
 #undef  PD3
 #define PD3 3
 #endif
 #ifdef  PD4
 #undef  PD4
 #define PD4 4
 #endif
 #ifdef  PD5
 #undef  PD5
 #define PD5 5
 #endif
 #ifdef  PD6
 #undef  PD6
 #define PD6 6
 #endif
 #ifdef  PD7
 #undef  PD7
 #define PD7 7
 #endif
 #ifdef  PB0
 #undef  PB0
 #define PB0 8
 #endif
 #ifdef  PB1
 #undef  PB1
 #define PB1 9
 #endif
 #ifdef  PB2
 #undef  PB2
 #define PB2 10
 #endif
 #ifdef  PB3
 #undef  PB3
 #define PB3 11
 #endif
 #ifdef  PB4
 #undef  PB4
 #define PB4 12
 #endif
 #ifdef  PB5
 #undef  PB5
 #define PB5 13
 #endif
 #ifdef  PC0
 #undef  PC0
 #define PC0 14
 #endif
 #ifdef  PC1
 #undef  PC1
 #define PC1 15
 #endif
 #ifdef  PC2
 #undef  PC2
 #define PC2 16
 #endif
 #ifdef  PC3
 #undef  PC3
 #define PC3 17
 #endif
 #ifdef  PC4
 #undef  PC4
 #define PC4 18
 #endif
 #ifdef  PC5
 #undef  PC5
 #define PC5 19
 #endif
 
//**********************************************
// Functions Prototypes
//*********************************************
 void GPIO_DisableGlobalPullUp();         //unable all GPIO pullup 
 void GPIO_EnableGlobalPullUp();          //enable all GPIO pullup 
 void GPIO_Init(volatile uint8_t* Port,uint8_t Pin,uint8_t PinMode);
 void GPIO_InitPin(uint8_t Pin,uint8_t PinMode);
 void GPIO_DeInit(volatile uint8_t* Port,uint8_t Pin);
 void GPIO_DeInitPin(uint8_t Pin);
 volatile uint8_t GPIO_Read(volatile uint8_t* Port, uint8_t Pin);
 volatile uint8_t GPIO_ReadPin(uint8_t Pin);
 void GPIO_Write(volatile uint8_t* Port, uint8_t Pin, uint8_t PinState);
 void GPIO_Toggle(volatile uint8_t* Port, uint8_t Pin);
 void GPIO_WritePinLow(uint8_t Pin);
 void GPIO_WritePinHigh(uint8_t Pin);
 void GPIO_WritePinToggle(uint8_t Pin);


 #endif /* AVR_GPIO_H_ */
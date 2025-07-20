 /*
 * Header da biblioteca de Debounce para GPIOs Atmel AVR
 *
 * Created: 19/07/2025 23:46:12
 * Author : Amauri Tuoni
 */
 
 #ifndef AVR_DEBOUNCE_H_
 #define AVR_DEBOUNCE_H_
 
 //#include <avr/io.h>
 #include "avr_macro.h"  //biblioteca com macros 
 #include "avr_gpio.h"   //biblioteca para acesso aos GPIOs
 
 #pragma message ( "avr_debounce.h included" )
 
 #define DEBOUNCE_COUNT 5    //tempo do debounce do botao
 
 volatile uint8_t checked_keys;  //variavel externa com o nível dos GPIOs

//****************************
// Prototipos de funcoes
//****************************

 void Debounce_Keys(void);  
 
 #endif /* AVR_DEBOUNCE_H_ */
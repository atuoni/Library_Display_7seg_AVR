/*
 * Arquivo main.c (Biblioteca Display 7 segmentos)
 *
 * Created: 19/07/2025 23:46:12
 * Author : Amauri Tuoni
 */ 


#include "avr_macro.h"                   //biblioteca com Macros e clock do MCU
#include <util/delay.h>                  //biblioteca para uso do _delay_ms
#include "avr_gpio.h"                    //biblioteca com funcoes para GPIO
#include "avr_debounce.h"               //biblioteca para uso do GPIO debounce
#include "avr_display_7seg.h"           //biblioteca display 7 segmentos

extern volatile uint8_t checked_keys;   //variavel externa com os sinais dos GPIOs
uint8_t contador_timer = 0;    //valor inicial do contador de atualizacao do display
int contador_int = -999;        //valor inicial do contador de numeros inteiros
double contador_dec = -99.9;    //valor inicial do contador de numeros decimais

int main(void)
{
	Display_Setup();     //inicializa o display
	GPIO_Init(PB,P0,GPIO_MODE_INPUT_WITH_PULL_UP);  //Configura o PB0 como Botao
	volatile uint8_t mode = 0;  //inicializa com contagem de numeros inteiros
	
	while (1) 
    {
		Debounce_Keys();  //debounce do botao
		if(checked_keys == 0x01) //verifica se o botao foi acionado
		{
			if (mode == 3) // modo = 3?
				mode = 0; //volta para o modo de numeros inteiros
			else 
			{
				++mode; //incrementa o modo ao toque do botao
				contador_dec=-99.9;     //reinicia o contador de numeros decimais
				contador_int=-999;      //reinicia o contador de numeros inteiros
				contador_timer = 0;     //zera o contador de atualizacao do display
			}
		}
		switch(mode)   
		{
			case 0:  //modo de contagem de numeros inteiros
				Integer_Number_Display(contador_int);  //funcao de contagem de numeros inteiros
				if (contador_timer == 20)   //o contador de atualizacao do display é igual a 20?
				{
					contador_timer = 0;    //zera o contador de atualizacao do display
					if(contador_int < 9999) //o contador de numeros inteiros é menor que 9999?
						contador_int++;   //incrementa contador de numeros inteiros
					else
						contador_int=-999;  //inicializa o contador de numeros inteiros para o inicio(-999)
				}
				else
					contador_timer++;  //incrementa o contador de atualizacao do display
				break;
				
			case 1:   //modo de contagem de numeros decimais
				Decimal_Number_Display(contador_dec);  //função de contagem de numeros decimais
				if(contador_timer == 20)  //contador de atualizacao do display é igual a 20?
				{
					contador_timer = 0;   //zera o contador de atualizacao do display
					if(contador_dec < 999.9)   //contador de numeros decimais é menor que -999.9?
						contador_dec += 0.1;   //incrementa o contador de numeros decimais em 0.1
					else
						contador_dec=-99.9;  //inicializa o contador de numeros decimais para o inicio (-99.9)
				}
				else
					contador_timer++;  //incrementa o contador de atualização do display
				break;
				
			case 2:  //modo de escrita de string
				String_Display("0123456789_ABCDEFGHIJKLMNOPQRSTUVWXYZ-.=*   "); //funcao de escrita de string
				break;
				
			default:
				mode = 0; 
				break;
		}
		_delay_ms(5);   //base de tempo de 5ms (loop=5ms*20 = 100ms para atualizacao do display)
	}
}

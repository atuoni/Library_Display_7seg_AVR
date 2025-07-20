/*
 * Arquivo header de biblioteca acionamento de display de 7 segmentos
 * para Atmel AVR
 *
 * Created: 29/06/2025 23:46:12
 * Author : Amauri Tuoni
 */

#ifndef AVR_DISPLAY_7SEG_H_
#define AVR_DISPLAY_7SEG_H_

#include "avr_gpio.h"

#pragma message ("avr_display_7seg.h included")    //informacao que biblioteca de display foi incluida

#include <stdlib.h>    //biblioteca para uso de funções para conversao de numeros em string
#include <string.h>    //biblioteca para manipulação de string
#include <stdbool.h>   //biblioteca para uso de valores booleanos

#define ANODE_DISPLAY        //define o uso do display anodo comum
#define SCROLL  true         //define para rolar a string no display
#define NO_SCROLL false      //define para nao rola a string no display
#define STRING   true       //define o dado como string
#define NO_STRING false     //define o dado como numero
#define DISPLAY_SIZE 4       //define a qtd de digitos no display  
#define DECIMAL              //define o uso de numeros na base decimal 
#define CASAS_DECIMAIS 1     //define o numero de casas decimais para conversao na string
#define TAMANHO_STRING 45    //define o tamanho da string
#define SCROLL_TIME 200      //define o tempo de varredura do scroll no display
#define MUX_DISPLAY_4 PC3    //define o GPIO para o digito 4
#define MUX_DISPLAY_3 PC2    //define o GPIO para o digito 3
#define MUX_DISPLAY_2 PC1    //define o GPIO para o digito 2
#define MUX_DISPLAY_1 PC0    //define o GPIO para o digito 1
#define DECIMAL_POINT PD7    //define o GPIO do MCU para o ponto decimal

//*******************************************************************
// Prototipo de Funcoes disponiveis para uso 
//********************************************************************
void Display_Setup(void);     //prototipo de função configuração do display
void Decimal_Number_Display(const double value);    //prototipo de funcao para uso de numeros decimais
void Integer_Number_Display(const int value);    //prototipo de funcao para uso de numeros inteiros
void String_Display(const char *string);       //prototipo de funcao para uso de string
void Clock_Display(const uint16_t value);

#endif

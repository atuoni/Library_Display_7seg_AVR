/*
 * Biblioteca de acionamento de display de 7 segmentos
 * para Atmel AVR
 *
 * Created: 29/06/2025 23:46:12
 * Author : Amauri Tuoni
 */


#include "avr_display_7seg.h"   //header dessa biblioteca


#ifdef HEXADECIMAL          //base hexadecimal
#define BASE_NUM 10         //base numerica da função itoa()
#endif

#ifdef DECIMAL              //base decimal
#define BASE_NUM 10         //base numerica da funcao itoa()
#endif

#ifdef ANODE_DISPLAY     //display anodo comum       

const char anodeDisplay[42] =   //vetor com algarismos p/ display anodo comum
{
	0b11000000, //0
	0b11111001, //1
	0b10100100, //2
	0b10110000, //3
	0b10011001, //4
	0b10010010, //5
	0b10000010, //6
	0b11111000, //7
	0b10000000, //8
	0b10011000, //9
	0b10001000, //A
	0b10000011, //b
	0b11000110, //C
	0b10100001, //d
	0b10000110, //E
	0b10001110, //F
	0b11000010, //G
	0b10001011, //H
	0b11111001, //I
	0b11100001, //J
	0b10001010, //k
	0b11000111, //L
	0b11101010, //M
	0b11001000, //n
	0b10100011, //o
	0b10001100, //P
	0b10011000, //q
	0b10101111, //r
	0b10010010, //S
	0b10000111, //t
	0b11000001, //U
	0b11100011, //v
	0b11010101, //w
	0b10001001, //X
	0b10010001, //y
	0b10100100, //Z
	0b11111111, //space
	0b10111111, //-
	0b11110111, //_
	0b01111111,  //.
	0b10111110, //=
	0b10011100  //º
};
#endif

#ifdef CATHODE_DISPLAY    //display catodo comum 

const char cathodeDisplay[42] = //vetor com algarismos p/ display catodo comum
{
	0b00111111, //0
	0b00000110, //1
	0b01011011, //2
	0b01001111, //3
	0b01100110, //4
	0b01101101, //5
	0b01111101, //6
	0b00000111, //7
	0b01111111, //8
	0b01100111, //9
	0b01110111, //A
	0b01111100, //b
	0b00111001, //C
	0b01011110, //d
	0b01111001, //E
	0b01110001, //F
	0b00111101, //G
	0b01110100, //h
	0b00000110, //I
	0b00011110, //J
	0b01110101, //k
	0b00111000, //L
	0b00010101, //M
	0b00110111, //n
	0b01011100, //o
	0b01110011, //P
	0b01100111, //q
	0b01010000, //r
	0b01101101, //S
	0b01111000, //t
	0b00111110, //U
	0b00011100, //v
	0b00101010, //w
	0b01110110, //X
	0b01101110, //y
	0b01011011, //Z
	0b00000000, //space
	0b01000000, //-
	0b00001000, //_
	0b10000000, //.
	0b01000001, //=
	0b01100011  //º
};
#endif

//************************************************************
//Configuracao do I/Os do MCU com o display
//***********************************************************
void Display_Setup()
{
	GPIO_Init(PD,P0,GPIO_MODE_OUTPUT); //segmento a
	GPIO_Init(PD,P1,GPIO_MODE_OUTPUT); //segmento b
	GPIO_Init(PD,P2,GPIO_MODE_OUTPUT); //segmento c
	GPIO_Init(PD,P3,GPIO_MODE_OUTPUT); //segmento d
	GPIO_Init(PD,P4,GPIO_MODE_OUTPUT); //segmento e
	GPIO_Init(PD,P5,GPIO_MODE_OUTPUT); //segmento f
	GPIO_Init(PD,P6,GPIO_MODE_OUTPUT); //segmento g
	GPIO_Init(PD,P7,GPIO_MODE_OUTPUT); //DP
	
	GPIO_Init(PC,P0,GPIO_MODE_OUTPUT);    //GPIO para digito 4
	GPIO_Init(PC,P1,GPIO_MODE_OUTPUT);    //GPIO para digito 3
	GPIO_Init(PC,P2,GPIO_MODE_OUTPUT);    //GPIO para digito 2
	GPIO_Init(PC,P3,GPIO_MODE_OUTPUT);    //GPIO para digito 1
}

typedef struct Data{
	char number[TAMANHO_STRING];         //numero inteiro convertido
	uint8_t digits;          //qtd de digitos ou caracteres
	int8_t point_position;  //posicao do ponto decimal
	//bool is_string;       //determina se o dado é uma string
}Data;

char string[TAMANHO_STRING];   //string p/ armazenar numero convertido 

//**************************************************************
//Função de analise da string
//**************************************************************

void String_Parse(const char *string, Data *data, bool is_string)
{
	uint8_t point = 0;              //inicializa ponto decimal para 0 
	uint8_t number_digits = 0;      //inicializa qtd de digitos em 0
	size_t size_string = strlen(string)+1;  //armazena tamanho da string + '\0'
	for(uint8_t i=0; i<size_string; i++)   //varre string até o '\0'
	{
		if((string[i]=='.') && (is_string == false))   //caracter igual a '.' e nao eh string ?
		{
			point = i;  //guarda posição do ponto decimal na string
		}
		else
		{
			data->number[number_digits] = (int)string[i]; //copia caracter da string na struct convertendo em codigo ASCII
			number_digits++;        //incrementa o index do array number
		}
	}
	
	if(point == 0 || is_string == true) //o numero é inteiro ou string?
	{	
		data->point_position = -1;  //flag que indica que nao possui ponto decimal
	}
	else
		data->point_position = size_string - point - 2; //calcula posicao do ponto decimal (=tamanho da string - posicao do ponto) 
		
	data->digits = number_digits-1; //numero de digitos ou caracteres = (algarismos + sinal) - '\0'
}

//************************************************************************************************
//Função de escrita do dígito no display
//************************************************************************************************
void Display_Write(const uint8_t digit)
{
	#ifdef ANODE_DISPLAY    //display anodo comum?
	if(digit >= '0' && digit <= '9')  //escreve digito de '0' a '9'
	{
		PORTD = anodeDisplay[digit-'0']<< 0;  
	}
	else if (digit >= 'a' && digit <= 'z')   //escreve caracter de 'a' a 'z'
	{
		PORTD = anodeDisplay[digit - 'a' + 10] << 0;
	}
	else if(digit >= 'A' && digit <= 'Z')  //escreve caracter de 'A' a 'Z'
	{
		PORTD = anodeDisplay[digit - 'A'+ 10 ] << 0;
	}
	else if(digit == ' ')   //escreve o caracter espaço
	{
		PORTD = anodeDisplay[36] << 0;
	}
	else if (digit == '-')  //escreve o caracter '-'
	{
		PORTD = anodeDisplay[37] << 0;
	}
	else if (digit == '_')  //escreve o caracter '_'
	{
		PORTD = anodeDisplay[38] << 0;
	}
	else if (digit == '.') //escreve o caracter '.'
	{
		PORTD = anodeDisplay[39] << 0;	
	}
	else if (digit == '=') //escreve o caracter '='
	{
		PORTD = anodeDisplay[40] << 0;
	}
	
	else if (digit == '*')  //escreve o caracter '*'
	{
		PORTD = anodeDisplay[41] << 0;
	}
		
	//PORTD = (anodeDisplay[digit] << 0);   //rotaciona x bits do digito para adequar ao PORT
	
	#else   //display catodo comum?
	if(digit >= '0' && digit <= '9')   //escreve o digito de '0' a '9'
	{
		PORTD = cathodeDisplay[digit-'0'] << 0;   
	}
	else if (digit >= 'a' && digit <= 'z')  //escreve caracter de 'a' a 'z'
	{
		PORTD = cathodeDisplay[digit - 'a' + 10] << 0;
	}
	else if(digit >= 'A' && digit <= 'Z')  //escreve caracter de 'A' a 'Z'
	{
		PORTD = cathodeDisplay[digit - 'A'+ 10 ] << 0;
	}
	else if(digit == ' ')   //escreve o caracter espaço
	{
		PORTD = cathodeDisplay[36] << 0;
	}
	else if (digit == '-')  //escreve caracter '-'
	{
		PORTD = cathodeDisplay[37] << 0;
	}
	else if(digit == '_')  //escreve caracter '_'
	{
		PORTD = cathodeDisplay[38] << 0;
	}

	else if(digit == '.') // escreve o caracter '.'
	{
		PORTD = cathodeDisplay[39] << 0;
	}
	
	else if (digit == '=') //escreve o caracter '='
	{
		PORTD = cathodeDisplay[40] << 0;
	}
	
	else if (digit == '*')  //escreve o caracter '*'
	{
		PORTD = cathodeDisplay[41] << 0;
	}
	//PORTD = (cathodeDisplay[digit] << 0);  //rotaciona x bits do digito para adequar ao PORT
	#endif
}

//*****************************************************************************************
//Função de atualização do display com os dados da struct
//******************************************************************************************
void Display_Update(Data *data, bool scroll_on)
{
		GPIO_WritePinLow(MUX_DISPLAY_1);  //apaga digito 1
		GPIO_WritePinLow(MUX_DISPLAY_2);  //apaga digito 2
		GPIO_WritePinLow(MUX_DISPLAY_3);  //apaga digito 3
		GPIO_WritePinLow(MUX_DISPLAY_4);  //apaga digito 4
		//GPIO_WritePinHigh(DECIMAL_POINT); //apaga ponto decimal
		
		static uint8_t display = DISPLAY_SIZE;  //variável para guardar qual digito do número está sendo atualizado
		uint8_t n_digits = data->digits;  //copia a qtde de digitos ou caracteres da struct
		static uint8_t character = 0;  //zera o indice de caracters da string
		static uint8_t scroll_counter = 0;  //zera o contador do scroll
		switch(display)     
		{
			case DISPLAY_SIZE:     //atualiza dígito 4
			
				if(scroll_on == true)  //scroll ligado?
					Display_Write(data->number[character+3]);  //escreve o caracter no digito 4
				else
					Display_Write(data->number[n_digits-(DISPLAY_SIZE-3)]);  //escreve o algarismo no digito 4
					
				if(data->point_position != -1)	//eh numero decimal?
				{	
					#ifdef ANODE_DISPLAY  //display anodo comum?	
						data->point_position == 0 ? GPIO_WritePinLow(DECIMAL_POINT): GPIO_WritePinHigh(DECIMAL_POINT); //caso o ponto decimal for 0 liga o DP no display
					#else  //display catodo comum?
						data->point_position == 0 ? GPIO_WritePinHigh(DECIMAL_POINT): GPIO_WritePinLow(DECIMAL_POINT); //caso o ponto decimal for 0 liga o DP no display
					#endif
				}
				if(data->digits == 1)   //qtd de digitos igual a 1?
				{
					display = DISPLAY_SIZE;  //prox. digito do display (4)
				}
				else
				{
					display = DISPLAY_SIZE-1;  //prox. digito do display (3)
				}
			GPIO_WritePinHigh(MUX_DISPLAY_4);   //exibe dígito 4
			break;
			
//--------------------------------------------------------------------------------------------------------------			
			case DISPLAY_SIZE-1:  //atualiza digito 3
				if(scroll_on == true)		//scroll ligado?
					Display_Write(data->number[character+2]); //escreve o caracter no digito 3 
				else
					Display_Write(data->number[n_digits-(DISPLAY_SIZE-2)]);  //escreve o algarismo no digito 3
				
				if(data->point_position != -1)  //é numero decimal?
				{
					
					#ifdef ANODE_DISPLAY //display anodo comum?
						data->point_position == 1 ? GPIO_WritePinLow(DECIMAL_POINT) : GPIO_WritePinHigh(DECIMAL_POINT); //caso o ponto decimal for 1 liga o DP no display
					#else  //display catodo comum?
						data->point_position == 1 ? GPIO_WritePinHigh(DECIMAL_POINT): GPIO_WritePinLow(DECIMAL_POINT); //caso o ponto decimal for 1 liga o DP no display
					#endif
				}
				if(data->digits == 2)  //a qtd de digitos é igual a 2?
				{
						display = DISPLAY_SIZE; //prox. digito do display (4)
				}
				else  
				{
						display = DISPLAY_SIZE-2;  //prox. digito do display (2)
				}
			GPIO_WritePinHigh(MUX_DISPLAY_3);  //exibe digito 3
			break;

//-------------------------------------------------------------------------------------------------------------------------------------			
			case DISPLAY_SIZE-2:  //atualiza digito 2
				if(scroll_on == true) //scroll ligado?
					Display_Write(data->number[character+1]); //escreve o caracter no digito 2
				else
					Display_Write(data->number[n_digits-(DISPLAY_SIZE-1)]);  //escreve o algarismo no digito 2
					
				if(data->point_position != -1)  //eh numero decimal?
				{
					#ifdef ANODE_DISPLAY  //display anodo comum?
						data->point_position == 2 ? GPIO_WritePinLow(DECIMAL_POINT) : GPIO_WritePinHigh(DECIMAL_POINT); //caso o ponto decimal for 2 liga o DP no display
					#else
						data->point_position == 2 ? GPIO_WritePinHigh(DECIMAL_POINT): GPIO_WritePinLow(DECIMAL_POINT); //caso o ponto decimal for 2 liga o DP no display
					#endif
				}
				if(data->digits == 3)  //qtd de digitos do numero igual a 3?
				{
						display = DISPLAY_SIZE; //prox. digito do display (4)
				}
				else
				{
						display = DISPLAY_SIZE-3; //prox. digito do display (1)
				}
			
			GPIO_WritePinHigh(MUX_DISPLAY_2); //exibe digito 2
			break;

//--------------------------------------------------------------------------------------------------------------------------------			
			case DISPLAY_SIZE-3:  //atualiza digito 1
			
				if(scroll_on == true)  //scroll ligado?
					Display_Write(data->number[character]); //escreve o caracter no digito 1 no display
				else
					Display_Write(data->number[n_digits-DISPLAY_SIZE]);  //escreve o algarismo no digito 1
		
				if(data->point_position != -1)  //eh numero decimal?
				{
					#ifdef ANODE_DISPLAY  //display anodo comum?
						data->point_position == 3 ? GPIO_WritePinLow(DECIMAL_POINT) : GPIO_WritePinHigh(DECIMAL_POINT); //caso o ponto decimal for 3 liga o DP
					#else
						data->point_position == 3 ? GPIO_WritePinHigh(DECIMAL_POINT): GPIO_WritePinLow(DECIMAL_POINT); //caso o ponto decimal for 0 liga o DP
					#endif
				}
				if(data->digits == 4)    //qtd de digitos igual a 4?
				{
					
						display = DISPLAY_SIZE; //prox. digito do display (4)
				}
				else
				{
						display = DISPLAY_SIZE; //prox. digito do display (4)
				}
				GPIO_WritePinHigh(MUX_DISPLAY_1);  //exibe o digito 1
				break;
			
			default:
			display=DISPLAY_SIZE; //prox.digito do display (4)
			break;
		}
		if(scroll_on == true)   //scroll ligado?
		{
			scroll_counter++;   //incrementa o contador de scroll no display
			if (scroll_counter > SCROLL_TIME)  //contador de scroll maior que SCROLL_TIMER?
			{
				scroll_counter = 0;    //zera o contador do scroll
				character++;          //incrementa o indice do caracter da string
				if(character >= n_digits-3) //indice do caracter da string > que a qtde de caracteres da string - 3?
				{
					character=0;   //zera o indice de caracter da string
				}
			}
		}
}

//*************************************************************************
//Função de conversão do número decimal em string
//**************************************************************************
void Decimal_Number_Display(const double value)
{
	dtostrf(value,4,CASAS_DECIMAIS,string); //converte o valor decimal em string
	//sprintf(string,"%.2f",value);
	Data data;                  //Instancia struct Data
	String_Parse(string,&data,NO_STRING); //funcao para analisar string
	Display_Update(&data,NO_SCROLL);      //funcao para atualizar o display com o valor convertido
}

//*************************************************************************
//Função de conversão do numero inteiro em string
//*************************************************************************

void Integer_Number_Display(const int value)
{
	itoa(value,string,BASE_NUM);  //converte o valor inteiro em string
	//sprintf(string,"%d",value);
	Data data;                   //Instancia da struct Data
	String_Parse(string,&data,NO_STRING);  //funcao para analisar string
	Display_Update(&data,NO_SCROLL);       //funcao para atualizar o display com o valor convertido
}
//*******************************************************************
//Função de uso de string no display
//*******************************************************************

void String_Display(const char *string)
{
	Data data;   //Instancia da struct Data
	String_Parse(string,&data,STRING);   //função para analisar string
	Display_Update(&data,SCROLL);     //funcao para atualizar o display com a string
}

void Clock_Display(const uint16_t value)
{
	itoa(value,string,BASE_NUM);
	Data data;
	String_Parse(string,&data,NO_STRING);
	//data.ponto_position=99;
	data.point_position=2;
	//FLIPBIT(data.ponto_position,7);
	//data.ponto_position^=(1<<7);
	Display_Update(&data,NO_SCROLL);
}
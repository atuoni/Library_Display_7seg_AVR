/*
 * Header da biblioteca de funcoes macro Atmel AVR
 *
 *
 * Created: 29/06/2025 23:46:12
 * Author : Amauri Tuoni
 */


#ifndef AVR_MACROS_H_
#define AVR_MACROS_H_

#pragma message ( "avr_macros.h included" )

#ifndef F_CPU
#define F_CPU     16000000UL
#endif

#define F_50Hz    50UL
#define F_100Hz   100UL
#define F_200Hz   200UL
#define F_500Hz   500UL
#define F_1kHz    1000UL
#define F_5kHz    5000UL
#define F_10kHz   10000UL
#define F_20kHz   20000UL
#define F_40kHz   40000UL
#define F_50kHz   50000UL
#define F_100kHz  100000UL
#define F_200kHz  200000UL
#define F_500kHz  500000UL
#define F_1000kHz 1000000UL
#define F_1Mhz    1000000UL
#define F_62500Hz 62500UL
#define F_7812Hz  7812UL
#define F_976Hz   976UL
#define F_244Hz   244UL
#define F_61Hz    61UL
#define ENABLE  0x01
#define DISABLE 0x00

#define BUSY    2
#define ERROR   1
#define OK      0

#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~(1<<bit))
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |=  (1<<bit))

#define SETBIT(ADDRESS,BIT)   (ADDRESS |=  (1<<BIT))
#define CLEARBIT(ADDRESS,BIT) (ADDRESS &= ~(1<<BIT))
#define FLIPBIT(ADDRESS,BIT)  (ADDRESS ^=  (1<<BIT))
#define CHECKBIT(ADDRESS,BIT) (ADDRESS  &  (1<<BIT))

#endif /* AVR_MACROS_H_ */

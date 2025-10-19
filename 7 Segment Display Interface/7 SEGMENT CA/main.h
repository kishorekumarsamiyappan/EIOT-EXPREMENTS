#include <16F877A.h>
#device ADC=16

#FUSES NOWDT                 	//No Watch Dog Timer
#FUSES PUT                   	//Power Up Timer
#FUSES NOBROWNOUT            	//No brownout reset
#FUSES NOLVP                 	//No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O

#use delay(crystal=4MHz)
#use FIXED_IO( C_outputs=PIN_C7,PIN_C6,PIN_C5,PIN_C4,PIN_C3,PIN_C2,PIN_C1,PIN_C0 )


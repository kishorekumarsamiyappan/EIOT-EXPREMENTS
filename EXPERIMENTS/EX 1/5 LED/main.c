#include <16F877A.h>
#device ADC=16

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES PUT                      //Power Up Timer
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage programming, B3(PIC16) or B5(PIC18) used for I/O

#use delay(crystal=4MHz)
#use FIXED_IO(B_outputs=PIN_B0)

#define LED     PIN_B0
#define SWITCH1  PIN_D0

void main()
{
   set_tris_d(0xFF);  //11111111
   set_tris_b(0xFE); //11111110

   while(TRUE)
   {
      if (input(SWITCH1) == 0)  
         output_low(LED);     
      else
         output_high(LED); 
   }
}


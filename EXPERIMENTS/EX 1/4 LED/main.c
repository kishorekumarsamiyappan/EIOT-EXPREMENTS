#include <16F877A.h>
#device ADC=16

#FUSES NOWDT                    // No Watch Dog Timer
#FUSES PUT                      // Power Up Timer
#FUSES NOBROWNOUT               // No brownout reset
#FUSES NOLVP                    // No low voltage programming

#use delay(crystal=4MHz)
#use FIXED_IO(B_outputs=PIN_B7,PIN_B6,PIN_B5,PIN_B4,PIN_B3,PIN_B2,PIN_B1,PIN_B0)

void main()
{
   while(TRUE)
   {
      output_b(0x55);     // ODD LEDs ON (1010101)
      delay_ms(100);

      output_b(0x00);     // All OFF
      delay_ms(100);

      output_b(0xAA);     // EVEN LEDs ON (10101010)
      delay_ms(100);

      output_b(0x00);     // All OFF
      delay_ms(100);
   }
}


#include <16F877A.h>
#device ADC=16

#FUSES NOWDT                    // No Watch Dog Timer
#FUSES PUT                      // Power Up Timer
#FUSES NOBROWNOUT               // No brownout reset
#FUSES NOLVP                    // No low voltage programming

#use delay(crystal=4MHz)
#use FIXED_IO( C_outputs=PIN_C7,PIN_C6,PIN_C5,PIN_C4,PIN_C3,PIN_C2,PIN_C1,PIN_C0 )

const unsigned int8 segment_code[10] = {
   0xC0, // 0
   0xF9, // 1
   0xA4, // 2
   0xB0, // 3
   0x99, // 4
   0x92, // 5
   0x82, // 6
   0xF8, // 7
   0x80, // 8
   0x90  // 9
};

void main() {
   int i;
   while(TRUE) {
      for(i = 0; i < 10; i++) {
         output_c(segment_code[i]);  // Output digit to 7-segment
         delay_ms(1000);             // Wait 1 second
      }
   }
}


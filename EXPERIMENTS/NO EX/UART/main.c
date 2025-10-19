#include <16F877A.h>
#device ADC=16

#FUSES NOWDT, PUT, NOBROWNOUT, NOLVP
#use delay(crystal=4MHz)
#use rs232(baud=9600, parity=N, xmit=PIN_C6, rcv=PIN_C7, bits=8, stream=PORT1, errors)

int blink_mode = 0;

void main() {
   char c;

   output_low(PIN_B0);   

   while(TRUE) {
      if (kbhit(PORT1)) {      
         c = fgetc(PORT1);      
         if (c == '1') {
            blink_mode = 0;               // stop blinking
            output_high(PIN_B0);   
            printf("LED ON\r\n");
         }
         else if (c == '0') {
            blink_mode = 0;               // stop blinking
            output_low(PIN_B0);    
            printf("LED OFF\r\n");
         }
         else if(c == '2'){
            blink_mode = 1;               // enable blink mode
            printf("LED BLINK MODE\r\n");
         }
         else {
            printf("Undefined Command\r\n");
         }
      }

      // handle blinking if mode is enabled
      if(blink_mode) {
         output_high(PIN_B0);
         delay_ms(100);
         output_low(PIN_B0); 
         delay_ms(100);
      }
   }
}


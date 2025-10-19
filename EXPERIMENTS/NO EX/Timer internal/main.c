#include <16F877A.h>
#device ADC=16
#FUSES NOWDT, PUT, NOBROWNOUT, NOLVP
#use delay(crystal=4MHz)
#define LCD_ENABLE_PIN PIN_B2
#define LCD_RS_PIN PIN_B0
#define LCD_RW_PIN PIN_B1
#define LCD_DATA4 PIN_B4
#define LCD_DATA5 PIN_B5
#define LCD_DATA6 PIN_B6
#define LCD_DATA7 PIN_B7
#include <lcd.c>
#define LED1 PIN_C0
#define LED2 PIN_C1
int seconds = 0, minutes = 0, hours = 0;
#define TMR1_PRELOAD 3036
#INT_TIMER1
void TIMER1_isr() {
   set_timer1(TMR1_PRELOAD); 
   seconds++;
   if (seconds >= 60) {
      seconds = 0;
      minutes++;
      if (minutes >= 60) {
         minutes = 0;
         hours++;
         if (hours >= 24) {
            hours = 0;
         }
      }
   }


   if (seconds % 2 == 1) {       
      output_high(LED1);
      output_low(LED2);
   } else {                      
      output_low(LED1);
      output_high(LED2);
   }
}

void display_time() {
   lcd_gotoxy(1, 1);
   printf(lcd_putc, "Time: %02u:%02u:%02u", hours, minutes, seconds);
}

void main() {
   lcd_init();

   
   output_low(LED1);
   output_low(LED2);

   setup_timer_1(T1_INTERNAL | T1_DIV_BY_8);
   set_timer1(TMR1_PRELOAD);

   enable_interrupts(INT_TIMER1);
   enable_interrupts(GLOBAL);

   while (TRUE) {
      display_time();
      delay_ms(100); 
   }
}


#include <16F877A.h>
#device ADC=16

#FUSES NOWDT                    
#FUSES PUT                      
#FUSES NOBROWNOUT               
#FUSES NOLVP                    

#use delay(crystal=4MHz)

#define LCD_ENABLE_PIN PIN_B0
#define LCD_RS_PIN PIN_B1
#define LCD_RW_PIN PIN_B2
#define LCD_DATA4 PIN_B4
#define LCD_DATA5 PIN_B5
#define LCD_DATA6 PIN_B6
#define LCD_DATA7 PIN_B7

#include <lcd.c>

void main()
{
   char msg[] = "  KONGU ENGINEERING COLLEGE PERUNDURAI  ";
   int i = 0;

   lcd_init();

   while(TRUE)
   {
      for(i = 0; i < 23 ; i++ ) 
      {
         lcd_gotoxy(1, 1); 
         printf(lcd_putc, "%s", msg + i); 
         delay_ms(400);
      }
   }
}


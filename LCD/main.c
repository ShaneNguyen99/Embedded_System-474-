/*#include <stdint.h>
//#include <stdio.h>
#include "addresses.h"
#include "addresses_3.h"
#include "SSD2119.h"
#include "PLL.h"*/
#include "part3.h"

void Timer0_Init(long maxCounterValue);
void ADC_Init_1(void);
void drawCube(short fillColor);

int count = 0;
int temperature;

int main() {
    
    led_main();
       
    #define red   0xD945
    #define green 0x27C2
    #define blue  0x135F
    
    // Section B task 5
    /*Touch_Init();
    LCD_Init();
    drawCube(red);
    int count = 0;
    while (1) {
        if (Touch_ReadZ1() > 1000) {
            while (Touch_ReadZ1() > 1000);
            if (count == 0) {
                drawCube(green);
                count++;
            } else if (count == 1) {
                drawCube(blue);
                count++;
            } else if (count == 2) {
                drawCube(red);
                count = 0;
            }
        }
    }*/
    
    // Section B task 4 - draw a cube (not square) 
    // on the LCD in the center of the screen with a length, width, and depth of 0.6 inches. 
    /*Touch_Init();
    LCD_Init();
    drawCube(red);
    return 0;*/
  
   
    // Section B task 3
    /*Touch_Init();
    LCD_Init();
    while (1) {
       LCD_Goto(0, 0);
       //long coordinates = Touch_GetCoords();
       //long xCoor = ((coordinates & 0xFFFF0000) >> 16); // shift right by 16 so that it's not a large number
       //long yCoor = (coordinates & 0x0000FFFF);
       if (Touch_ReadZ1() > 1000) { // use 1000 as a threshold - Z1 is the pressure on the screen
           long x = Touch_ReadX();
           long y = Touch_ReadY();
           printf("x : %d, y : %d    ", x, y); 
       }
    }
    return 0;*/
    
    /*// Section B task 2
    PLL_Init(24);
    Touch_Init();
    LCD_Init();
    ADC_Init_1();
    while (1) {
        ADCPSSI_1 |= 0x8; 
        temperature = (147.5 - (247.5 * ((float) ADCSSFIFO3_1)) / 4096.0); // internal temperature sensor equation
        // you need to cast ADCSSFIFO3_1 to a float b
      
        printf("Temp in C: %d\n", temperature);
        ADCISC_1 = 0x8;  // clear the ADC flag after each conversion
        
        for (int i = 0; i < 300000; i++);
    }
    return 0;*/
}

/*void drawCube(short fillColor) {
   
   
   LCD_DrawFilledRect(135 + 1, 95 + 1, 70, 70, fillColor);
   LCD_DrawFilledRect(135 + 35 + 1, 95 + 35 + 1, 70, 70, fillColor);  
   
   short startX = 135 + 1;
   short startY = 165 - 1;
   short endX = 135 + 35 - 1;
   short endY = 165 + 35 - 1;
   while ((startX != endX) && (startY != endY)) {
      LCD_DrawLine(startX, startY, endX, endY, fillColor);
      startX++;
      endY--;
   }
   
   startX = 135 + 70 + 1;
   startY = 95 + 1;
   endX = 135 + 70 + 35 - 1;
   endY = 95 + 35 - 1;
   while ((startX != endX) && (startY != endY)) {
      LCD_DrawLine(startX, startY, endX, endY, fillColor);
      startY++;
      endX--;
   }
   
   LCD_DrawRect(135 + 35, 95 + 35, 70, 70, 0xFFFF);
   LCD_DrawRect(135, 95, 70, 70, 0xFFFF);
   LCD_DrawLine(135, 95, 135 + 35, 95 + 35, 0xFFFF);
   LCD_DrawLine(135 + 70, 95, 135 + 35 + 70, 95 + 35, 0xFFFF);
   LCD_DrawLine(135, 95 + 70, 135 + 35, 95 + 35 + 70, 0xFFFF);
   LCD_DrawLine(135 + 70, 95 + 70, 135 + 35 + 70, 95 + 35 + 70, 0xFFFF);
   
   
}

//configures the ADC1 module based on instructions explained in the TM4C123 data sheet
//and lecture 6 slides. 
void ADC_Init_1() { 
    volatile unsigned long delay;
    RCGCADC |= 0x02;                        // page 352 - enable and provide clock to ADC   module 0 in run mode 
    delay = RCGCADC;                        // add a delay since the ADC requires more than one clock cycle
    ADCACTSS_1 &= ~(0x08);                    // choose and disable sample sequencer - page 821 (set bit 3)
    ADCSSCTL3_1 |= 0x08;                      // set bit 3 of ADC CTL (see page  853) - sample the temperature sensor
    ADCSSCTL3_1 |= 0x02;                      // indicate the end of sequence befor initiating a new one
    ADCSSCTL3_1 |= 0x04;                      // set the END0 bit
    EN0 |= (1 << 17);                       // enable the ADC interrupt
    ADCIM_1 |= (1 << 3);                      // mask interrupt for SS3 - set bits 3 (page 825)
    ADCACTSS_1 |= 0x08;                       // enable the sample sequencer SS3 (see page 821)
}*/
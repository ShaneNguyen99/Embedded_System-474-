//*****************************************************************************
//
// freertos_demo.c - Simple FreeRTOS example.
//
// Copyright (c) 2012-2017 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 2.1.4.178 of the EK-TM4C123GXL Firmware Package.
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
//#include <windows.h>

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "led_task.h"
#include "switch_task.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "timerCustom.h"

#include "SSD2119.h"
#include "part3.h"

int counter1 = 0;
int counter2 = 0;
int counter3 = 0;

xTimerHandle timerHndl1Sec;
xTimerHandle timerHndl2Sec;
xTimerHandle timerHndl3Sec;

void drawCube(short fillColor);

#include "addresses.h"
#include "addresses_3.h"

void printChar_bluetooth(char c);
void printString_bluetooth(char * string);
void bluetooth_enable();

void GPIO_PortD_Initialization();
void turn_on_motor();

void Pin_PB6_Init();
void PWM0_Init();

#include "stepper.h"
#define T1ms 16000    // assumes using 16 MHz PIOSC (default setting for clock source)

void turn_motor();

//*****************************************************************************
//
//! \addtogroup example_list
//! <h1>FreeRTOS Example (freertos_demo)</h1>
//!
//! This application demonstrates the use of FreeRTOS on Launchpad.
//!
//! The application blinks the user-selected LED at a user-selected frequency.
//! To select the LED press the left button and to select the frequency press
//! the right button.  The UART outputs the application status at 115,200 baud,
//! 8-n-1 mode.
//!
//! This application utilizes FreeRTOS to perform the tasks in a concurrent
//! fashion.  The following tasks are created:
//!
//! - An LED task, which blinks the user-selected on-board LED at a
//!   user-selected rate (changed via the buttons).
//!
//! - A Switch task, which monitors the buttons pressed and passes the
//!   information to LED task.
//!
//! In addition to the tasks, this application also uses the following FreeRTOS
//! resources:
//!
//! - A Queue to enable information transfer between tasks.
//!
//! - A Semaphore to guard the resource, UART, from access by multiple tasks at
//!   the same time.
//!
//! - A non-blocking FreeRTOS Delay to put the tasks in blocked state when they
//!   have nothing to do.
//!
//! For additional details on FreeRTOS, refer to the FreeRTOS web page at:
//! http://www.freertos.org/
//
//*****************************************************************************

//*****************************************************************************
//
// The mutex that protects concurrent access of UART from multiple tasks.
//
//*****************************************************************************
xSemaphoreHandle g_pUARTSemaphore;

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}

#endif

//*****************************************************************************
//
// This hook is called by FreeRTOS when an stack overflow error is detected.
//
//*****************************************************************************
void
vApplicationStackOverflowHook(xTaskHandle *pxTask, char *pcTaskName)
{
    //
    // This function can not return, so loop forever.  Interrupts are disabled
    // on entry to this function, so no processor interrupts will interrupt
    // this loop.
    //
    while(1)
    {
    }
}

//*****************************************************************************
//
// Configure the UART and its pins.  This must be called before UARTprintf().
//
//*****************************************************************************

/*void
ConfigureUART(void) {
    //
    // Enable the GPIO Peripheral used by the UART.
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Enable UART0
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    //
    // Configure GPIO Pins for UART mode.
    //
    ROM_GPIOPinConfigure(GPIO_PA0_U0RX);
    ROM_GPIOPinConfigure(GPIO_PA1_U0TX);
    ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Use the internal 16MHz oscillator as the UART clock source.
    //
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(0, 115200, 16000000);
}*/

void ConfigureUART(void) {
    //
    // Enable the GPIO Peripheral used by the UART.
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);

    //
    // Enable UART1
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);

    //
    // Configure GPIO Pins for UART mode.
    //
    ROM_GPIOPinConfigure(GPIO_PC4_U1RX);
    ROM_GPIOPinConfigure(GPIO_PC5_U1TX);
    ROM_GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5);

    //
    // Use the internal 16MHz oscillator as the UART clock source.
    //
    UARTClockSourceSet(UART1_BASE, UART_CLOCK_PIOSC);

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(1, 115200, 16000000);
}

//*****************************************************************************
//
// Initialize FreeRTOS and start the initial set of tasks.
//
//*****************************************************************************

#define red    0xD945
#define green  0x0BAA
#define blue   0x135F
#define yellow 0xEFC2
#define magenta 0xB93E
#define pink    0xF936
#define turquoise 0x27DE
#define black    0x0000
             
void playing_screen() {
    LCD_DrawFilledRect(0, 0, 320, 240, black);
    
    LCD_DrawFilledRect(0, 122, 106, 120, yellow); // previous button
    LCD_DrawFilledRect(107, 122, 106, 120, yellow); // pause/resume button
    LCD_DrawFilledRect(214, 122, 106, 120, yellow); // next button
    
    LCD_SetCursor(30, 180);
    printf("Previous");

    LCD_SetCursor(150, 180);
    printf("Pause");
    
    LCD_SetCursor(260, 180);
    printf("Next");
    
    LCD_DrawFilledRect(0, 0, 320, 60, blue); 
    LCD_SetCursor(130, 30);
    printf("Home Page");
    
    LCD_DrawFilledRect(0, 61, 320, 60, magenta);
    LCD_SetCursor(130, 70);
    printf("Now playing: ");
    
    LCD_SetCursor(40, 150);
}


void initial_screen() {
    // Final project
    
    LCD_DrawFilledRect(0, 0, 320, 50, magenta);
    LCD_DrawFilledRect(0, 49, 320, 50, blue);
    LCD_DrawFilledRect(0, 98, 320, 50, red);
    LCD_DrawFilledRect(0, 147, 320, 50, pink);
    LCD_DrawFilledRect(0, 196, 320, 50, turquoise);
    
    LCD_SetTextColor(255, 255, 255);
    
    LCD_SetCursor(50, 25);
    LCD_PrintString("Song #1: \'Survivor\' by Destiny's Child");
    
    LCD_SetCursor(50, 74);
    LCD_PrintString("Song #2: \'thank u, next\' by Ariana Grande");
    
    LCD_SetCursor(50, 123);
    LCD_PrintString("Song #3: \'Hall of Fame\' by The Script");
    
    LCD_SetCursor(50, 172);
    LCD_PrintString("Song #4: \'Demons\' by Imagine Dragons");
    
    LCD_SetCursor(50, 221);
    LCD_PrintString("Song #5: \'Paris\' by The Chainsmokers");;
    
}

void virtual_button_task1(void *p) {
    long x = 0;
    long y = 0;
    
    typedef enum{
       initial_state,
       play_state
    } state;

    state music_state = initial_state;

    int count = 0;
    bool playing = false; // LCD state
    bool touched = false;
    bool back_to_start = false;
    bool music_playing = false; // music currently playing
    bool motor_on = false;
    bool paused = false; // paused button has been pressed
    
    int song_index = 0;
    
    char songs[5][40] = {"\'Survivor\' by Destiny's Child",
                         "\'thank u, next\' by Ariana Grande",
                         "\'Hall of Fame\' by The Script",
                         "\'Demons\' by Imagine Dragons",
                         "\'Paris\' by The Chainsmokers"};
    
    char current_song[40];
    
    while (1) {
      
          if (!playing) {
              if (back_to_start) {
                  initial_screen();
                  back_to_start = false;
              }
              if (Touch_ReadZ1() > 1000) {
                  x = Touch_ReadX();
                  y = Touch_ReadY();
                  while (Touch_ReadZ1() > 1000);
                  playing = true;
                  touched = true;
              }
              //LCD_Goto(0, 0);
              //printf("x : %d, y : %d", x, y);
          }
          
          if (playing) {
            
               if (touched) {
                  playing_screen();
                  LCD_SetCursor(50, 90);
                  if (y > 2300) {;
                      strcpy(current_song, "\'Survivor\' by Destiny\'s Child");
                      printf("Song #1: %s", current_song);
                      song_index = 0;
                     //  GPIO_PORTD_DATA_R = 0x01; // 1 
                   } else if (y > 2100) {
                      strcpy(current_song, "\'thank u, next\' by Ariana Grande");
                      printf("Song #2: %s", current_song);
                      song_index = 1;
                      GPIO_PORTD_DIR_R = 0x02; // 2 
                   } else if (y > 1900) {
                      strcpy(current_song, "\'Hall of Fame\' by The Script");
                      printf("Song #3: %s", current_song);
                      song_index = 2;
                      GPIO_PORTD_DIR_R = 0x03; // 2 
                   } else if (y > 1800) {
                      strcpy(current_song, "\'Demons\' by Imagine Dragons");
                      printf("Song #4: %s", current_song);
                      song_index = 3;
                      GPIO_PORTD_DIR_R = 0x04; // 2 
                   } else if (y > 1600) {
                      strcpy(current_song, "\'Paris\' by The Chainsmokers");
                      printf("Song #5: %s", current_song);
                      song_index = 4;
                      GPIO_PORTD_DIR_R = 0x05; // 2 
                   }
                   
                   // print the song to PuTTy over bluetooth;
                   UARTprintf(current_song);
                   //turn_motor();
                   music_playing = true;
               }
               
               if (Touch_ReadZ1() > 1000) {
                    x = Touch_ReadX();
                    y = Touch_ReadY();
                    while (Touch_ReadZ1() > 1000);
                    
                    if (y >= 2200 && y <= 2600) { // pressing homepage
                         playing = false;
                         back_to_start = true;
                         LCD_Goto(0, 0);
                         printf("x : %d, y : %d", x, y);
                    } else if (x > 1500 && x <= 2000) { // pressing pause/resume button
                        paused = !paused;
                        if (paused) {
                            music_playing = false;
                            LCD_DrawFilledRect(107, 122, 106, 120, green);
                            LCD_SetCursor(150, 180);
                            printf("Resume");
                            UARTprintf("Pause");
                        } else {
                            LCD_DrawFilledRect(107, 122, 106, 120, yellow);
                            LCD_SetCursor(150, 180);
                            printf("Pause");
                            UARTprintf("Resume");
                            music_playing = true;
                        }
                    } else if (x >= 1300 && x <= 1500) { // pressing next button
                        LCD_SetCursor(40, 150);
                        if (song_index == 4) {
                           song_index = 0;
                        } else {
                           song_index++;
                        }
                        strcpy(current_song, songs[song_index]);
                        playing_screen();
                        LCD_SetCursor(50, 90);
                        printf("Song #%d: %s", song_index + 1, current_song);
                        
                        // print new song to PuTTy over bluetooth);
                        UARTprintf(current_song);
                        //turn_motor();
                        music_playing = true;
                        
                    } else if (x > 2000 && x <= 2600) { // pressing previous button
                        if (song_index >= 1 && song_index <= 4) {
                           song_index--;                          
                        } else if (song_index == 0) {
                           song_index = 4;
                        }
                        strcpy(current_song, songs[song_index]);
                        playing_screen();
                        LCD_SetCursor(50, 90);
                        printf("Song #%d: %s", song_index + 1, current_song);
                        UARTprintf(current_song);
                        //turn_motor();
                        music_playing = true;
                    } 
              }
              
              if (music_playing) {
                 turn_motor();
                 /*Stepper_Init();
                 for (int i = 0; i < 100; i++) {
                    Stepper_CW(10 * T1ms);   // output every 10ms
                 }*/
                 //Stepper_CW(10 * T1ms); 
                 //turn_motor();
              }
              
              touched = false;
        }
    }
    
}

void GPIO_PortD_Initialization() {
    SYSCTL_RCGCGPIO_R |= 0x08; // enable Port D GPIO
    GPIO_PORTD_DIR_R |= 0x0F;  // set pins 0-3 for Port D as output
    GPIO_PORTD_DEN_R |= 0x0F;  // enable digital Port D for pins 0 - 3
    GPIO_PORTD_DATA_R &= ~(0x0F);
    
     // 1. Enable Clock to the GPIO Modules (SYSCTL->RCGCGPIO)
    // allow time for clock to stabilize (SYSCTL->PRGPIO)
    
    // 2. Unlock GPIO only PD7, PF0 on TM4C123G; PD7, PE7 on TM4C1294 (GPIOx->LOCK and GPIOx->CR)
    
    // 3. Set Analog Mode Select bits for each Port (GPIOx->AMSEL 0=digital, 1=analog)
    
    // 4. Set Port Control Register for each Port (GPIOx->PCTL, check the PCTL table)
    
    // 5. Set Alternate Function Select bits for each Port (GPIOx->AFSEL 0=regular I/O, 1=PCTL peripheral)
    
    // 6. Set Output pins for each Port (Direction of the Pins: GPIOx->DIR 0=input, 1=output)
 
    // 7. Set PUR bits for internal pull-up, PDR for pull-down reg, ODR for open drain (0: disable, 1=enable)
 
    // 8. Set Digital ENable register on all GPIO pins (GPIOx->DEN 0=disable, 1=enable)
}

void turn_on_motor() {
     GPIO_PORTD_DATA_R = 0xC;         // turn on pins 3 and 2 (others off)
     for (int i = 0; i < 50000000; i++) { };  // delay of 10000
     GPIO_PORTD_DATA_R = 0x6;         // turn on pins 2 and 1 (others off)
     for (int i = 0; i < 50000000; i++) { };  // delay of 10000
     GPIO_PORTD_DATA_R = 0x3;         // turn on pins 1 and 0 (others off)
     for (int i = 0; i < 50000000; i++) { };  // delay of 10000
     GPIO_PORTD_DATA_R = 0x9;         // turn on pins 3 and 0 (others off)
     for (int i = 0; i < 50000000; i++) { };  // delay of 10000
}

void turn_motor() {
   Stepper_Init();
   for (int i = 0; i < 10; i++) {
      Stepper_CW(10 * T1ms);   // output every 10ms
   }
}

int main(void) {
    
    Touch_Init();
    LCD_Init();
    ConfigureUART();
    initial_screen();
    GPIO_PortD_Initialization();
    //Stepper_Init();
    
    xTaskCreate(virtual_button_task1, (signed char*) "tx", 1024, NULL, 4, NULL);
    vTaskStartScheduler();  // Start the scheduler.
    
    return 0;
}

void drawCube(short fillColor) {
   
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



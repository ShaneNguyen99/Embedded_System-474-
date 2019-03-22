#include "tm4c123gh6pm.h"
#include <stdint.h>

#define DELAY 6000000
#define TIMER_FLAG (TIMER0_RIS_R & 0x01)
#define CLEAR_FLAG TIMER0_ICR_R |= 0x01

//int counter = 0; // counter to count the number of seconds

void setUp(void);


void setUpCounter(void);

void GREEN_LED_On(void);

void GREEN_LED_Off(void);
void YELLOW_LED_On(void);

void YELLOW_LED_Off(void);

void RED_LED_On(void);

void RED_LED_Off(void);

unsigned long Switch_Input_Start_Stop(void);

unsigned long Switch_Input_Pes(void);

int wait5Sec(int restart);

void Timer_Handler(void);

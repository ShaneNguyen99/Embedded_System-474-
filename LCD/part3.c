#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "SSD2119.h"

#define DELAY 6000000
#define TIMER_FLAG (TIMER0_RIS_R & 0x01)
#define CLEAR_FLAG TIMER0_ICR_R |= 0x01

int counter = 0; // counter to count the number of seconds

void setUp(void) {  volatile unsigned long delay;
    SYSCTL_RCGC2_R |= 0x00000004; // activate clock for port C
    delay = SYSCTL_RCGC2_R; // allow time for clock to start
    GPIO_PORTC_AMSEL_R &= ~0x70; // disable analog function on PC4, PC5 and PC6
    GPIO_PORTC_PCTL_R &= ~0x0FFF0000; // regular GPIO PC4, PC5, and PC6
    GPIO_PORTC_DIR_R |= 0x10; // set direction to output PC4 - yellow
    GPIO_PORTC_DIR_R |= 0x20; // set direction to output PC5 - red
    GPIO_PORTC_DIR_R |= 0x40; // set direction to output PC6 - green
    GPIO_PORTC_AFSEL_R &= ~0x70; // regular port function PC4, PC5, PC6
    GPIO_PORTC_DEN_R |= 0x70; // enable digital port
}

void setUpCounter(void) {
    SYSCTL_RCGCTIMER_R = SYSCTL_RCGCTIMER_R0; // 1. Enable timer 0 in the RCGCTIMER register
    (*((volatile uint32_t *)0x4003000C)) &= ~(0x00000001); // 2. Disable the timer by assigning 0 to bit 0 of GPTMCTL
    TIMER0_CFG_R = TIMER_CFG_32_BIT_TIMER; // 3. Write the GPTMCFG with a value of 0x00000000 so it run in 32 bit mode
    TIMER0_TAMR_R |= 0x2; //4. Configure TnMRfield in the GPTMTnMR >periodic
    TIMER0_TAMR_R &= ~(0x00000010); //5. Configure the direction of the counter to count down (bit 4 to 0)
    TIMER0_TAILR_R = 0x00F42400; //6. write 16 million to GPTM Timer n Interval Load Register
    TIMER0_IMR_R |= 0x1; //7. GPTM Interrupt Mask Register GPTMIMR:
    NVIC_EN0_R |= (1<<19); // Timer 0A is interrupt number 19 so I should configure the EN0 register 
    (*((volatile uint32_t *)0x4003000C)) |= 0x00000001; // 8. Set the TnENbit in the GPTMCTLregister to enable the timer.
}

void GREEN_LED_On(void) {
    GPIO_PORTC_DATA_R |= 0x40;
}

void GREEN_LED_Off(void) {
    GPIO_PORTC_DATA_R &= ~(0x40);
}

void YELLOW_LED_On(void) {
    GPIO_PORTC_DATA_R |= 0x10;
}

void YELLOW_LED_Off(void) {
    GPIO_PORTC_DATA_R &= ~(0x10);
}

void RED_LED_On(void) {
    GPIO_PORTC_DATA_R |= 0x20;
}

void RED_LED_Off(void) {
    GPIO_PORTC_DATA_R &= ~(0x20);
}

unsigned long Switch_Input(void) {
  if (Touch_ReadZ1() > 1000) {
      counter = 0;
      while ((counter < 2) && (Touch_ReadZ1() > 1000)) {
          if (Touch_ReadZ1() <= 1000) {
              return 0;
          }
      }
      long x = Touch_ReadX();
      long y = Touch_ReadY();
      while ((Touch_ReadZ1() > 1000));
      LCD_Goto(0, 0);
      printf("x : %d, y : %d", x, y); 
      if (x >= 1700) {
          return 2;
      } else if (x < 1700) {
          return 3;
      };
  }
  return 0;
  /*long x;
  long y;
  if (Touch_ReadZ1() > 1000) {
      LCD_Goto(0, 0);
      x = Touch_ReadX();
      y = Touch_ReadY();
      //printf("x : %d, y : %d", x, y);
  }
  return (x >= 50 && x <= 120 && y >= 50 && y <= 120 && (Touch_ReadZ1() > 1000));*/
//   if (/* button is pressed (check z1) and x and y are inside button */ /*GPIO_PORTA_DATA_R & 0x04*/) { // PA2
//       counter = 0;
//       while (counter != 2 && /* button is pressed (check z1) and x and y are inside button*/ ) {}
//       return /* button is pressed (check z1) and x and y are inside button*/
//   }
//   return 0;
//
//    if (GPIO_PORTA_DATA_R & 0x04) { // PA2
//        counter = 0;
//        while (counter != 2 && GPIO_PORTA_DATA_R & 0x04) {
//        }
//        return GPIO_PORTA_DATA_R&0x04;
//    }
//    return 0;
}


int wait5Sec(int restart) {
    counter = 0;
    while (counter < 5) {
        if(Switch_Input() == 2) {
            restart = 0;
            break;
        }
    }
    return restart;
}

void Timer_Handler(void) {
    CLEAR_FLAG;
    counter += 1;
}

#define orange 0xEC85
void drawStartStopButton() {
   LCD_DrawFilledRect(0, 0, 160, 240, orange);
}

#define yellow 0xF786
void drawPedestrianButton() {
   LCD_DrawFilledRect(160, 0, 160, 240, yellow);
}


int led_main () {
    
    Touch_Init();
    LCD_Init();
    
    drawStartStopButton();
    drawPedestrianButton();
    
    /* draw circles for pedestrian and start/stop button here  */
  
    setUp();
    setUpCounter();

    typedef enum{
        redState,
        yellowState,
        greenState
    } state;

    state s = redState;
    int restart = 0;
    while (1) {
        GPIO_PORTC_DATA_R = 0x00; // turnoff

        if (Switch_Input() == 2 || restart) {
            restart = 1;
            s = redState;
            RED_LED_On();
            restart = wait5Sec(restart);
            RED_LED_Off();

            if (restart == 1) {
                s = greenState;
                GREEN_LED_On();
                counter = 0;
                while (counter < 5) {
                    if (Switch_Input() == 3) {
                        s = yellowState;
                        break;
                    }
                    if (Switch_Input() == 2) {
                        restart = 0;
                        break;
                    }
                }
                GREEN_LED_Off();
            }

            if (s == yellowState) {
                YELLOW_LED_On();
                restart = wait5Sec(restart);
                YELLOW_LED_Off();
            }
        }
    }

}
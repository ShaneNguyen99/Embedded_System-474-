// page numbers are in the TM4C123 Data sheet

#define PRI17  (*((volatile unsigned long *) 0xE000E444)) // page 154 - interrupt priorities 
#define PRI4   (*((volatile unsigned long *) 0xE000E410))  // page 152 - interrupt priorities
#define EN0 (*((volatile unsigned long *) 0xE000E100)) // page 142
#define GPTMIMR_TIMER_0 (*((volatile unsigned long *) 0x40030018)) // page 745 - general purpose timer interrupt mask

#define GPTMIMR_TIMER_1 (*((volatile unsigned long *) 0x40031018)) // page 745 - general purpose timer interrupt mask

// memory addresses for GPTM (General-Purpose Timer Module) registers - Timer 0
#define RCGCTIMER_TIMER_0        (*((volatile unsigned long *) 0x400FE604)) // page 338 - base: 0x400F.E000, offset: 0x604  
#define GPTMCTL_TIMER_0          (*((volatile unsigned long *) 0x4003000C))  // page 737 - base for Timer 0: 0x4003.0000, offset: 0x00C
#define GPTMCFG_TIMER_0          (*((volatile unsigned long *) 0x40030000))  // page 727 - base for Timer 0: 0x4003.0000, offset: 0x000
#define GPTMTAMR_TIMER_0         (*((volatile unsigned long *) 0x40030004))  // page 729 -  base for Timer 0: 0x4003.0000, offset: 0x000
#define GPTMTAILR_TIMER_0        (*((volatile unsigned long *) 0x40030028)) // page 756 - base for Timer 0: 0x4003.0000, offset: 0x028
#define GPTMRIS_TIMER_0         (*((volatile unsigned long *) 0x4003001C)) // page 748 - base for Timer 0: 0x4003.0000, offset: 0x01C 
#define GPTMICR_TIMER_0         (*((volatile unsigned long *) 0x40030024)) // page 754 - base for Timer 0:  0x4003.0000, offset: 0x024
#define GPTMIMR_TIMER_0        (*((volatile unsigned long *) 0x40030018)) // page 745 - base for Timer 0: 0x4003.0000, offset: 0x018 

// memory addresses for GPTM (General-Purpose Timer Module) registers - Timer 1
#define RCGCTIMER_TIMER_1        (*((volatile unsigned long *) 0x400FE604)) // page 338 - base: 0x400F.E000, offset: 0x604  
#define GPTMCTL_TIMER_1          (*((volatile unsigned long *) 0x4003100C)) // page 737 - offset: 0x00C
#define GPTMCFG_TIMER_1          (*((volatile unsigned long *) 0x40031000)) // page 727 -  offset: 0x000
#define GPTMTAMR_TIMER_1         (*((volatile unsigned long *) 0x40031004))  // page 729 - offset: 0x000
#define GPTMTAILR_TIMER_1        (*((volatile unsigned long *) 0x40031028)) // page 756 - offset: 0x028
#define GPTMRIS_TIMER_1          (*((volatile unsigned long *) 0x4003101C)) // page 748 -  offset: 0x01C 
#define GPTMICR_TIMER_1          (*((volatile unsigned long *) 0x40031024)) // page 754 - offset: 0x024
#define GPTMIMR_TIMER_1          (*((volatile unsigned long *) 0x40031018)) // page 745 - offset: 0x018   

#define GPIO_PORTF_IS_R  (*((volatile unsigned long *) 0x40025404))  // page 664 - base for Port F: 0x4002.5000, offset: 0x404 
#define GPIO_PORTF_IBE_R (*((volatile unsigned long *) 0x40025408)) // page 665 - base for Port F: 0x4002.5000, offset: 0x408
#define GPIO_PORTF_IEV_R (*((volatile unsigned long *) 0x4002540C)) // page 666 - base for Port F: 0x4002.5000, offset: 0x40C 
#define GPIO_PORTF_ICR_R (*((volatile unsigned long *) 0x4002541C)) // page 670 - base for Port F: 0x4002.5000, offset: 0x41C
#define GPIO_PORTF_IM_R  (*((volatile unsigned long *) 0x40025410)) // page 667 - base for Port F: 0x4002.5000, offset: 0x410 

#define RED 0x02
#define BLUE 0x04
#define GREEN 0x08
#define OFF 0x00    // none of the LEDs are on
#define BLUE_GREEN 0x0C
#define RED_BLUE 0x06
#define RED_GREEN 0x0A
#define ALL_ON 0x0E  // white 

#define SYSCTL_RCGCUART_R    (*((volatile unsigned long *) 0x400FE618))  // page 340 - enable Port F GPIO

#define SYSCTL_RCGC2_R    (*((volatile unsigned long *) 0x400FE608))  // page 340 - enable Port F GPIO
#define GPIO_PORTF_DIR_R  (*((volatile unsigned long *) 0x40025400))  // page 663 - set Port F as output
#define GPIO_PORTF_DEN_R  (*((volatile unsigned long *) 0x4002551C))  // page 683 - enable port F as being digital
#define GPIO_PORTF_DATA_R (*((volatile unsigned long *) 0x400253FC))  // page 662 - clear all of port and turn on an LED

#define GPIO_PORTF_SW1_EN 0x10
#define GPIO_PORTF_SW2_EN 0x01
#define ALL_BITS 0x1F

#define GPIOLOCK_PORTF_R (*((volatile unsigned long *) 0x40025520)) // page 684
#define GPIOCR_PORTF_R   (*((volatile unsigned long *) 0x40025524)) // page 685
#define GPIOPUR_PORTF_R  (*((volatile unsigned long *) 0x40025510)) // page 678

//#define GPIO_PORTA_AMSEL_R  (*((volatile unsigned long *) 0x40004528)) // page 687
//#define GPIO_PORTA_PCTL_R   (*((volatile unsigned long *) 0x4000452C))  // page 689
//#define GPIO_PORTA_DIR_R    (*((volatile unsigned long *) 0x40004400)) // page 663
//#define GPIO_PORTA_AFSEL_R  (*((volatile unsigned long *) 0x40004420)) // page 672
//#define GPIO_PORTA_DEN_R    (*((volatile unsigned long *) 0x4000451C))  // page 683
//#define GPIO_PORTA_DATA_R   (*((volatile unsigned long *) 0x400043FC)) // page 662
//#define GPIO_PORTA_PDR_R    (*((volatile unsigned long *) 0x40004514)) // page 680

#define PA5 (*((volatile unsigned long *) 0x40004080))




// page numbers are in the TM4C123 Data sheet

#define PRI17  (*((volatile unsigned long *) 0xE000E444)) // page 154 - interrupt priorities 
#define PRI4   (*((volatile unsigned long *) 0xE000E410))  // page 152 - interrupt priorities

#define GPTMIMR_TIMER_0 (*((volatile unsigned long *) 0x40030018)) // page 745 - general purpose timer interrupt mask
#define EN0             (*((volatile unsigned long *) 0xE000E100)) // page 142
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

#define RED 0x02
#define BLUE 0x04
#define GREEN 0x08
#define OFF 0x00    // none of the LEDs are on
#define BLUE_GREEN 0x0C
#define RED_BLUE 0x06
#define RED_GREEN 0x0A
#define ALL_ON 0x0E  // white 

#define GPIO_PORTF_SW1_EN 0x10
#define GPIO_PORTF_SW2_EN 0x01
#define ALL_BITS 0x1F

#define GPIOLOCK_PORTF_R (*((volatile unsigned long *) 0x40025520)) // page 684
#define GPIOCR_PORTF_R   (*((volatile unsigned long *) 0x40025524)) // page 685
#define GPIOPUR_PORTF_R  (*((volatile unsigned long *) 0x40025510)) // page 678

#define PA5 (*((volatile unsigned long *) 0x40004080))




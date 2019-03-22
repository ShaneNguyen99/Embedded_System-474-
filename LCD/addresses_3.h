// addresses for bluetooth
//#define RCGCUART_1      (*((volatile unsigned long *) 0x400FE618)) // page 344
#define GPIO_PORTB_DR2R (*((volatile unsigned long *) 0x40005500)) // page 673 - for Port B
#define GPIO_PORTB_SLR  (*((volatile unsigned long *) 0x40005518)) // page 681 - for Port B
#define UART1_CTL       (*((volatile unsigned long *) 0x4000D030)) // page 918 - for UART1
#define UART1_IBRD      (*((volatile unsigned long *) 0x4000D024)) // page 914 - for UART1
#define UART1_FBRD      (*((volatile unsigned long *) 0x4000D028)) // page 915 - for UART1
#define UART1_LCRH      (*((volatile unsigned long *) 0x4000D02C)) // page 916
#define UART1_CC        (*((volatile unsigned long *) 0x4000DFC8)) // page 939 - for UART1
#define UART1_DR        (*((volatile unsigned char *) 0x4000D000)) // page 906 - for UART1
#define UART1_FLAG      (*((volatile unsigned long *) 0x4000D018)) // page 911 - for UART1
#define GPIO_PORTB_AFSEL_R  (*((volatile unsigned long *) 0x40005420)) // page 672
#define GPIO_PORTB_PCTL_R   (*((volatile unsigned long *) 0x4000552C))  // page 689
#define GPIO_PORTB_DEN_R    (*((volatile unsigned long *) 0x4000551C))  // page 683

// addresses for enabling and initializing the UART
#define RCGCUART        (*((volatile unsigned long *) 0x400FE618)) // page 344
#define GPIO_PORTA_DR2R (*((volatile unsigned long *) 0x40004500)) // page 673 - for Port A
#define GPIO_PORTA_SLR  (*((volatile unsigned long *) 0x40004518)) // page 681 - for Port A
#define UART0_CTL       (*((volatile unsigned long *) 0x4000C030)) // page 918 - for UART0
#define UART0_IBRD      (*((volatile unsigned long *) 0x4000C024)) // page 914 - for UART0
#define UART0_FBRD      (*((volatile unsigned long *) 0x4000C028)) // page 915 - for UART0
#define UART0_LCRH      (*((volatile unsigned long *) 0x4000C02C)) // page 916
#define UART0_CC        (*((volatile unsigned long *) 0x4000CFC8)) // page 939 - for UART0
#define UART0_DR        (*((volatile unsigned long *) 0x4000C000)) // page 906 - for UART0
#define UART0_FLAG      (*((volatile unsigned long *) 0x4000C018)) // page 911 - for UART0

// PLL configuration
#define RCC2       (*((volatile unsigned long *) 0x400FE070))  // page 260
#define RIS        (*((volatile unsigned long *) 0x400FE050))  // page 244
#define RCC        (*((volatile unsigned long *) 0x400FE060))  // page 254
#define ADCSSFIFO3 (*((volatile unsigned long *) 0x400380A8))  // page 860
#define MISC       (*((volatile unsigned long *) 0x400FE058))  // page 249

// ADC1 configuration
#define ADCACTSS_1   (*((volatile unsigned long *) 0x40039000)) // page 821
#define ADCEMUX_1    (*((volatile unsigned long *) 0x40039014)) // page 833
#define ADCSSCTL3_1    (*((volatile unsigned long *) 0x400390A4)) // page 876
#define ADCIM_1      (*((volatile unsigned long *) 0x40039008)) // page 825
#define ADCACTSS_1   (*((volatile unsigned long *) 0x40039000)) // page 821
#define ADCPSSI_1    (*((volatile unsigned long *) 0x40039028)) // page 845
#define ADCISC_1    (*((volatile unsigned long *) 0x4003900C)) // page 828
#define ADCSSFIFO3_1 (*((volatile unsigned long *) 0x400390A8))  // page 860

// ADC configuration
#define ADCDCISC   (*((volatile unsigned long *) 0x40038034)) // page 352
#define RCGCADC    (*((volatile unsigned long *) 0x400FE638)) // page 352
#define ADCACTSS   (*((volatile unsigned long *) 0x40038000)) // page 821
#define ADCEMUX  (*((volatile unsigned long *) 0x40038014)) // page 833
#define ADCSSCTL_0 (*((volatile unsigned long *) 0x40038044)) // page 853
#define ADCIM      (*((volatile unsigned long *) 0x40038008)) // page 825
#define ADCPSSI    (*((volatile unsigned long *) 0x40038028)) // page 845
#define ADCISC     (*((volatile unsigned long *) 0x4003800C)) // page 828
#define ADCSSCTL3  (*((volatile unsigned long *) 0x400380A4)) // page 876
#define ADCSSMUX3  (*((volatile unsigned long *) 0x400380A0)) // page 875
#define ADCSSPRI   (*((volatile unsigned long *) 0x40038020)) // page 841
#define RCGC0      (*((volatile unsigned long *) 0x400FE100)) // page 457
#define PRI4       (*((volatile unsigned long *) 0xE000E410)) // page 457

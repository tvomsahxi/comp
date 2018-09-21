#include "rpi_lib/rpi.h"
#define MMIO_BASE 0x3F000000

#define AUX_ENABLE      ((volatile unsigned int*)(MMIO_BASE+0x00215004))
#define AUX_MU_IO       ((volatile unsigned int*)(MMIO_BASE+0x00215040))
#define AUX_MU_IER      ((volatile unsigned int*)(MMIO_BASE+0x00215044))
#define AUX_MU_IIR      ((volatile unsigned int*)(MMIO_BASE+0x00215048))
#define AUX_MU_LCR      ((volatile unsigned int*)(MMIO_BASE+0x0021504C))
#define AUX_MU_MCR      ((volatile unsigned int*)(MMIO_BASE+0x00215050))
#define AUX_MU_LSR      ((volatile unsigned int*)(MMIO_BASE+0x00215054))
#define AUX_MU_MSR      ((volatile unsigned int*)(MMIO_BASE+0x00215058))
#define AUX_MU_SCRATCH  ((volatile unsigned int*)(MMIO_BASE+0x0021505C))
#define AUX_MU_CNTL     ((volatile unsigned int*)(MMIO_BASE+0x00215060))
#define AUX_MU_STAT     ((volatile unsigned int*)(MMIO_BASE+0x00215064))
#define AUX_MU_BAUD     ((volatile unsigned int*)(MMIO_BASE+0x00215068))

/**
 * Set baud rate and characteristics (115200 8N1) and map to GPIO
 */
void uart_init()
{
    register unsigned int r;
    
    /* initialize UART */
    *AUX_ENABLE |=1;       // enable UART1, AUX mini uart
    *AUX_MU_IER = 0;
    *AUX_MU_CNTL = 0;
    *AUX_MU_LCR = 3;       // 8 bits
    *AUX_MU_MCR = 0;
    *AUX_MU_IER = 0;
    *AUX_MU_IIR = 0xc6;    // disable interrupts
    *AUX_MU_BAUD = 270;    // 115200 baud


	pinMode(14,INPUT_OFF);
	pinMode(15,INPUT_OFF);
	pinMode(14,ALT5);
	pinMode(15,ALT5);

    /* map UART1 to GPIO pins */
 /*  r=*GPFSEL1;
    r&=~((7<<12)|(7<<15)); // gpio14, gpio15
    r|=(2<<12)|(2<<15);    // alt5
    *GPFSEL1 = r;
    *GPPUD = 0;            // enable pins 14 and 15
    r=150; while(r--) { asm volatile("nop"); }
    *GPPUDCLK0 = (1<<14)|(1<<15);
    r=150; while(r--) { asm volatile("nop"); }
    *GPPUDCLK0 = 0;        // flush GPIO setup*/
    *AUX_MU_CNTL = 3;      // enable Tx, Rx
}

/**
 * Send a character
 */
void uart_send(unsigned int c) {
    /* wait until we can send */
    do{asm volatile("nop");}while(!(*AUX_MU_LSR&0x20));
    /* write the character to the buffer */
    *AUX_MU_IO=c;
}

/**
 * Receive a character
 */
char uart_getc() {
    char r;
    /* wait until something is in the buffer */
    do{asm volatile("nop");}while(!(*AUX_MU_LSR&0x01));
    /* read it and return */
    r=(char)(*AUX_MU_IO);
    /* convert carrige return to newline */
    return r=='\r'?'\n':r;
}

/**
 * Display a string
 */
void uart_puts(char *s) {
    while(*s) {
        /* convert newline to carrige return + newline */
        if(*s=='\n')
            uart_send('\r');
        uart_send(*s++);
    }
}

void uart_hex(unsigned int d){
	unsigned int n;
	int c;
	for(c=28;c>=0;c-=4){
		n=(d>>c)&0xF;

	n+=n>9?0x37:0x30;
	uart_send(n);
	}
}

unsigned int get_reg0_value(void){
	unsigned int r;
	__asm__ volatile(
		"mov %[Rd],r0"
		:[Rd] "=r"(r)
	);
	return r;
}
unsigned int get_reg1_value(void){ 
        unsigned int r;
        __asm__ volatile(
                "mov %[Rd],r1"
                :[Rd] "=r"(r)
        );
        return r;
}
unsigned int get_reg2_value(void){ 
        unsigned int r;
        __asm__ volatile(
                "mov %[Rd],r2"
                :[Rd] "=r"(r)
        );
        return r;
}
unsigned int get_reg3_value(void){ 
        unsigned int r;
        __asm__ volatile(
                "mov %[Rd],r3"
                :[Rd] "=r"(r)
        );
        return r;
}
unsigned int get_reg4_value(void){ 
        unsigned int r;
        __asm__ volatile(
                "mov %[Rd],r4"
                :[Rd] "=r"(r)
        );
        return r;
}
unsigned int get_reg5_value(void){ 
        unsigned int r;
        __asm__ volatile(
                "mov %[Rd],r5"
                :[Rd] "=r"(r)
        );
        return r;
}
unsigned int get_reg6_value(void){ 
        unsigned int r;
        __asm__ volatile(
                "mov %[Rd],r6"
                :[Rd] "=r"(r)
        );
        return r;
}
unsigned int get_reg7_value(void){ 
        unsigned int r;
        __asm__ volatile(
                "mov %[Rd],r7"
                :[Rd] "=r"(r)
        );
        return r;
}
unsigned int get_reg8_value(void){ 
        unsigned int r;
        __asm__ volatile(
                "mov %[Rd],r8"
                :[Rd] "=r"(r)
        );
        return r;
}
unsigned int get_reg9_value(void){ 
        unsigned int r;
        __asm__ volatile(
                "mov %[Rd],r9"
                :[Rd] "=r"(r)
        );
        return r;
}
unsigned int get_reg10_value(void){ 
        unsigned int r;
        __asm__ volatile(
                "mov %[Rd],r10"
                :[Rd] "=r"(r)
        );
        return r;
}
unsigned int get_reg11_value(void){ 
        unsigned int r;
        __asm__ volatile(
                "mov %[Rd],r11"
                :[Rd] "=r"(r)
        );
        return r;
}
unsigned int get_reg12_value(void){ 
        unsigned int r;
        __asm__ volatile(
                "mov %[Rd],r12"
                :[Rd] "=r"(r)
        );
        return r;
}
unsigned int get_reg13_value(void){ 
        unsigned int r;
        __asm__ volatile(
                "mov %[Rd],r13"
                :[Rd] "=r"(r)
        );
        return r;
}
unsigned int get_reg14_value(void){ 
        unsigned int r;
        __asm__ volatile(
                "mov %[Rd],r14"
                :[Rd] "=r"(r)
        );
        return r;
}
unsigned int get_reg15_value(void){ 
        unsigned int r;
        __asm__ volatile(
                "mov %[Rd],r15"
                :[Rd] "=r"(r)
        );
        return r;
}

unsigned int  get_spr_value(void){
	unsigned int r;
	__asm__ volatile(
		"MRS %[Rd], CPSR"
		:[Rd] "=r"(r)
	);
	return r;

}


int main(void){
	
	uart_init();
    
    // say hello
 	uart_puts("Hello World!\n");
	delay(3000);
	uart_puts("r0 :");
	uart_hex(get_reg0_value());
	uart_puts("\n");
	uart_puts("r1 :");
        uart_hex(get_reg1_value());
        uart_puts("\n");
	uart_puts("r2 :");
        uart_hex(get_reg2_value());
        uart_puts("\n");
	uart_puts("r3 :");
        uart_hex(get_reg3_value());
        uart_puts("\n");
	uart_puts("r4 :");
        uart_hex(get_reg4_value());
        uart_puts("\n");
	uart_puts("r5 :");
        uart_hex(get_reg5_value());
        uart_puts("\n");
	uart_puts("r6 :");
        uart_hex(get_reg6_value());
        uart_puts("\n");
	uart_puts("r7 :");
        uart_hex(get_reg7_value());
        uart_puts("\n");
	uart_puts("r8 :");
        uart_hex(get_reg8_value());
        uart_puts("\n");
	uart_puts("r9 :");
        uart_hex(get_reg9_value());
        uart_puts("\n");
	uart_puts("r8 :");
        uart_hex(get_reg8_value());
        uart_puts("\n");
	uart_puts("r9 :");
        uart_hex(get_reg9_value());
        uart_puts("\n");
	uart_puts("r10 :");
        uart_hex(get_reg10_value());
        uart_puts("\n");
	uart_puts("r11 :");
        uart_hex(get_reg11_value());
        uart_puts("\n");
	uart_puts("r12 :");
        uart_hex(get_reg12_value());
        uart_puts("\n");
	uart_puts("r13 (sp):");
        uart_hex(get_reg13_value());
        uart_puts("\n");
	uart_puts("r14 (lr):");
        uart_hex(get_reg14_value());
        uart_puts("\n");
	uart_puts("r15 (pc):");
        uart_hex(get_reg15_value());
        uart_puts("\n");
	
	uart_puts("cpsr :");
	uart_hex(get_spr_value()); 
/*	while(1){
		while (*/  
    // echo everything back
    	while(1) {
        	uart_send(uart_getc());
	}		
	
	return 0;
}

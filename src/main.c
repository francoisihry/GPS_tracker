/*******************************************************************************
                        SERIAL COMMUNICATION ATM8

    This source code introduces you to the working of the USART Module
    available in ATMEGA 8 @8MHz system clock.

    This code does the task of preparing a menu driven user interface on
    hyperterminal using the USART Module.

    Here the USART Module is configured to operate in the Asychronous
    mode. With a Frame format of 8-bit Data with 1 stop bit and no parity
    bit the baud rate is fixed for 9600 bps.

***********************************ELECDUDE.COM*********************************/


#define F_CPU 8000000UL            //Define the MPU operating frequency
#define FOSC 8000000UL

#include <avr/io.h>                //Header file for AVR device specific I/O Definitions.
#include <avr/interrupt.h>            //Header file for incorportaing interrupt handling faclity (not used here).
#include <util/delay.h>                //Header file for incorporating delay routines.
#include <avr/pgmspace.h>            //Header file for incorporating Program space string utilities.
#include <stdlib.h>                //ISO Standard library of C functions and macros.
#include "usart.h"                //Defines C functions for accessing USART Module.


#define BIT(x)            (1 << (x))    //Set a particular bit mask
#define CHECKBIT(x,b)     (x&b)        //Checks bit status
#define SETBIT(x,b)     x|=b;        //Sets the particular bit
#define CLEARBIT(x,b)     x&=~b;        //Sets the particular bit
#define TOGGLEBIT(x,b)     x^=b;        //Toggles the particular bit

void WaitMs(unsigned int ms);

int main()
{
    unsigned int ch;

    uart_init(9600);        //Initialise the USART Module with the given Baudrate and
                                                            //Frame format.

    while(1)   //Enter into a uncoditional while loop..
        {
            /*ch=uart_getc();
            uart_puts("\n\n\t\t");
            uart_putc('<');cd /
            uart_putc(ch);
            uart_putc('>');*/
    		uart_puts("Hello pd\n");
            WaitMs(1000);
        }

    return 0;
}


void WaitMs(unsigned int ms)    //Generate a delay of ms milli second.
{
    unsigned int i;

    for(i=0;i<=ms/10;i++)
    {
        _delay_ms(10);
    }
}




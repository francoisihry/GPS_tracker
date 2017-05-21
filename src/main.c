#include <stdlib.h>
# include <avr/io.h>
#include <util/delay.h>
# include <avr/interrupt.h>
#include "gps.h"

# define USART_BAUDRATE 9600
# define BAUD_PRESCALE (((( F_CPU / 16) + ( USART_BAUDRATE / 2) ) / ( USART_BAUDRATE ) ) - 1)
#define TRUE 1
#define FALSE 0

typedef enum state {
	NOT_SECURED, GEO_SECURED, ALARM
} State;

void set_state(State);
void uart_init();
void uart_transmit_string(char string[]);
void uart_transmit_char(unsigned char data);
Coordonate get_position();
Coordonate get_fixed_position();
void read_command(char* cmd);

int has_moved();


volatile unsigned char command_ready, new_position=FALSE;
unsigned char data_in[50];
int data_count;

Coordonate received_new_position;
// received commands:
ISR( USART_RXC_vect) {
	command_ready = FALSE;
	// Get data from the USART in register
	data_in[data_count] = UDR;

	if (data_in[data_count] == '\r') {

		data_in[data_count] = '\0';
		//uart_transmit_string(data_in);
		// Reset to 0, ready to go again
		//uart_transmit_string("\nchecking command : \"");
		//uart_transmit_string(data_in);
		//uart_transmit_string("\" \n");
		read_command(data_in);
		data_count = 0;
		// si la commande est une notif de sms alors on le recupere et on l'interprete
	} else {
		data_count++;
	}
}

void read_command(char* cmd)
{
	//uart_transmit_string("checking command : ");
	//uart_transmit_string(cmd);
	if (strstr(cmd, "+CGNSINF:") != NULL) {
		//uart_transmit_string("received position !");
		read_coordonate(&received_new_position, cmd);
		new_position = TRUE;
	}
}

Coordonate get_position()
{
	uart_transmit_string("AT+CGNSINF\n");
	while(!new_position);
	new_position = FALSE;
	return received_new_position;
}

Coordonate get_fixed_position()
{
	return get_position();
}

state = NOT_SECURED;
last_state = NOT_SECURED;
Coordonate fixed_position, position;

int main(void) {
	uart_init();

	DDRB |= 0x01;    //Frame format.
	for (;;) // Loop forever
			{
		switch (state) {
		case NOT_SECURED:
			// switch led verte on
			PORTB |= (1 << PB0);
			_delay_ms(500);
			// switch led verte off
			PORTB &= ~(1 << PB0);
			set_state(GEO_SECURED); // turn LED off on next round
			break;
		case GEO_SECURED:
			// switch led bleu on
			PORTB |= (1 << PB1);
			if (last_state != GEO_SECURED){
				uart_transmit_string("AT+CGNSPWR=1\n");
				_delay_ms(3000);
				fixed_position = get_fixed_position();
				uart_transmit_string("fixed latitude = ");
				uart_transmit_string(fixed_position.latitude);
				uart_transmit_string("\n fixed longitude = ");
								uart_transmit_string(fixed_position.longitude);
			}
			_delay_ms(500);
			position = get_fixed_position();
			uart_transmit_string("\n current latitude = ");
			uart_transmit_string(position.latitude);
			uart_transmit_string("\n current longitude = ");
			uart_transmit_string(position.longitude);
			if (has_moved())
					set_state(ALARM);
			else
				set_state(GEO_SECURED);
			break;
		case ALARM:
			// switch led rouge on
			PORTB |= (1 << PB2);
			_delay_ms(500);
			// switch led rouge off
			PORTB &= ~(1 << PB2);
			set_state(NOT_SECURED);
			break;
		}
	}

}


int has_moved()
{
	return FALSE;
}
void set_state(State new_state){
	last_state = state;
	state = new_state;
}

void uart_init() {
	UCSRB = (1 << RXEN) | (1 << TXEN);
	// Turn on the transmission and reception circuitry
	UCSRC = (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1); // Use 8 - bit character sizes
	UBRRH = ( BAUD_PRESCALE >> 8); // Load upper 8 - bits of the baud rate value into the high byte of the UBRR register
	UBRRL = BAUD_PRESCALE; // Load lower 8 - bits of the baud rate value into the low byte of the UBRR register
	UCSRB |= (1 << RXCIE); // Enable the USART Recieve Complete interrupt ( USART_RXC )
	sei(); // Enable the Global Interrupt Enable flag so that interrupts can be processed

}

void uart_transmit_char(unsigned char data) {
	while (!(UCSRA & (1 << UDRE)))
		;
	UDR = data;
}

void uart_transmit_string(char string[]) {
	int i = 0;
	while (string[i] > 0)
		uart_transmit_char(string[i++]);
}


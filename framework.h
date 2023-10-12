#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>    
#include <avr/power.h>    
#include <avr/sleep.h>  
#include <avr/pgmspace.h>   
#define delay(time)	_delay_ms(time);
#define interruptOn() sei();
#define interruptOff() cli();
#define A0 14
#define A1 15
#define A2 16
#define A3 17
#define A4 18
#define A5 19

enum m {
	OUTPUT, 
	INPUT
};
enum s {
	HIGH, 
	LOW
};


void pinMode(uint8_t pin, uint8_t m){
    if (( pin < 8 ) && (m == 0)){ 
       DDRD |= (1 << pin); 
	}else if (( pin < 8 ) && (m == 1)){ 
       DDRD &= ~(1 << pin); 
    }else if (( pin < 14 ) && (m == 0)){
       DDRB |= (1 << (pin - 8));  
	}else if (( pin<14 ) && (m == 1)){
       DDRB &= ~(1 << (pin - 8));  
	}
}
void digitalWrite(uint8_t pin,uint8_t s){ 
	if (( pin < 8 ) && (s == 1)){ 
       PORTD &= ~(1 << pin); 
	}else if (( pin < 8 ) && (s == 0)){ 
       PORTD |= (1 << pin); 
	}else if (( pin < 14 ) && (s == 0)){  
       PORTB |= (1 << pin-8); 
	}else if (( pin < 14 ) && (s == 1)){ 
       PORTB &= ~(1 << pin-8); 
    }
}
uint8_t digitalRead(uint8_t pin){
	if (pin < 8)
		return ((PIND & (1<<pin)) >> pin); 
	else if (pin < 14)
		return ((PINB & (1<<(pin-8))) >> (pin-8)); 
}

void serialInit(uint16_t baud){
	uint8_t _ubr = (16000000/16/baud-1); 
	UCSR0B |= (1<<RXEN0)  | (1<<TXEN0) | (1<<RXCIE0);
	UCSR0C |= (1<<UCSZ00) | (1<<UCSZ01);
	UBRR0H  = (_ubr >> 8);
	UBRR0L  = _ubr;
}
void serialWrite(uint8_t data){
	UDR0 = data;
	while( ( UCSR0A & ( 1 << UDRE0 ) ) == 0 ){}
}
void serialPrintStr(char *text){
	while(*text){
		serialWrite(*text++);
	}
}
void serialPrintInt(uint16_t value){
	const char buffer[6];                       
    itoa(value, buffer, 10);             
	serialPrintStr(buffer);    
}


void adcInit(){
	
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); 
    ADMUX |= (1 << REFS0); 
    ADCSRA |= (1 << ADEN); 
}
uint16_t analogRead(uint8_t channel){
	
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F); 
    ADCSRA |= (1 << ADSC); 
    while(ADCSRA & (1 << ADSC)); 
    return ADC;
}


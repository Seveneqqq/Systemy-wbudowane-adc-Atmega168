#define ENABLE_BASIC
#define ENABLE_SERIAL
#define ENABLE_ADC
#include "framework.h"

int main(void) {
    pinMode(13, OUTPUT);
	serialInit(9600);
	adcInit();
	
    while (1) {		
		uint16_t ADCval = analogRead(0);	
		uint16_t ADCv = ((ADCval*5)/1024)*100; // TODO:
		uint16_t ADCval2 = analogRead(1);
		uint16_t ADCv2 = ((ADCval*5.0)/1024)*100; // TODO:

		serialPrintStr("ADC: ");
		serialPrintInt(ADCval);
		serialPrintStr(" Napiecie: ");
		serialPrintInt(ADCv / 100);
		serialPrintStr(".");
		serialPrintInt(ADCv % 100);
		serialPrintStr("\n");
		serialPrintStr("ADC2: ");
		serialPrintStr("\n");
		serialPrintInt(ADCval2);
		serialPrintStr(" Napiecie2: ");
		serialPrintInt(ADCv2 / 100);
		serialPrintStr(".");
		serialPrintInt(ADCv2 % 100);
		serialPrintStr("\n");
		

		if(ADCval<ADCval2){
		digitalWrite(13, HIGH);
        }
		else{
        digitalWrite(13, LOW);
		}
    }

    return 0;
}

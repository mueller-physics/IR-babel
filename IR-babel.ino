#include <Arduino.h>
#define IRSND_IR_FREQUENCY          38000
#define IRSND_OUTPUT_PIN 6
#define IRMP_INPUT_PIN 8
//#define DECODE_RC5
#define USE_ONE_TIMER_FOR_IRMP_AND_IRSND


#include <irmpSelectMain15Protocols.h>
#include <irsndSelectMain15Protocols.h>
#include <irsnd.c.h>
#include <irmp.c.h>

IRMP_DATA irsnd_data;
IRMP_DATA irmp_data;

void setup() {
    // put your setup code here, to run once:
    Serial.begin(19200);
 //   pinMode(8, INPUT);
    irmp_init();
    irsnd_init();
    irmp_irsnd_LEDFeedback(true); 
}



void loop() {
    

    irsnd_data.protocol = IRMP_NEC_PROTOCOL;
    irsnd_data.address = 0xff00;
    irsnd_data.flags = 0;

    if (irmp_get_data(&irmp_data)) {

	Serial.println( irmp_data.address );
	Serial.println( irmp_data.command );
	Serial.println( "---" );


	if ( irmp_data.address == 0x0001 ) {
	    switch (irmp_data.command) {

		case 0x10:
		    Serial.println(" vol UP");
		    irsnd_data.command = 0x19;		
		    irsnd_send_data(&irsnd_data, true);
		    delay(100);
		    break;

		case 0x11:
		    Serial.println(" vol DN");
		    irsnd_data.command = 0x1c;		
		    irsnd_send_data(&irsnd_data, true);
		    delay(100);
		    break;

		case 0x0d:
		    Serial.println(" vol mute");
		    irsnd_data.command = 0xb8;		
		    irsnd_send_data(&irsnd_data, true);
		    delay(100);
		    break;

	    }
	}

    }

}

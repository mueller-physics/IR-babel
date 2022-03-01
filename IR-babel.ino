#include <Arduino.h>


#define IRSND_IR_FREQUENCY          38000

#define IRSND_OUTPUT_PIN 4
#define IRMP_INPUT_PIN 2
#define IRMP_FEEDBACK_LED_PIN 13

#define USE_ONE_TIMER_FOR_IRMP_AND_IRSND
#define IRSND_SUPPORT_NEC_PROTOCOL 1

#include <irmpSelectMain15Protocols.h>
//#include <irsndSelectMain15Protocols.h>
#include <irmp.hpp>
#include <irsnd.hpp>

IRMP_DATA irsnd_data;
IRMP_DATA irmp_data;

uint8_t mute_count;

void setup() {
    // put your setup code here, to run once:
	Serial.begin(115200);
    irmp_init();
    irsnd_init();
    irmp_irsnd_LEDFeedback(true); 

	Serial.println(F("IR babel ready"));

	mute_count=0;
}


void loop() {
    

    irsnd_data.protocol = IRMP_NEC_PROTOCOL;
    irsnd_data.address = 0xff00;
    irsnd_data.flags = 0;

    if (irmp_get_data(&irmp_data)) {

	Serial.print(F("0x"));
	Serial.println( irmp_data.address, HEX );
	Serial.print(F("0x"));
	Serial.println( irmp_data.command, HEX );
	Serial.println( "---" );


	if ( irmp_data.address == 0x0001 ) {
	    
		switch (irmp_data.command) {
		
		case 0x10:
		    Serial.println(F(" vol UP"));
		    irsnd_data.command = 0x19;		
		    irsnd_send_data(&irsnd_data, true);
		    delay(100);
			mute_count=0;
		    break;

		case 0x11:
		    Serial.println(F(" vol DN"));
		    irsnd_data.command = 0x1c;		
		    irsnd_send_data(&irsnd_data, true);
		    delay(100);
			mute_count=0;
		    break;

		case 0x0d:
			//Serial.print("mute: ");
			//Serial.println(mute_count);
			if (mute_count++<2) {
				// pressing mute once or twice just sends a mute command
		    	Serial.println(F(" vol mute"));
		    	irsnd_data.command = 0x47;		
			    irsnd_send_data(&irsnd_data, true);
		    	delay(100);
			} else {
				// pressing mute three times sends 'power' followed by 'select optical input'
		    	Serial.println(F(" vol mute 3x --> power + optical input"));
		    	irsnd_data.command = 0x45;		
			    irsnd_send_data(&irsnd_data, true); // send the 'power' command
				// especially if set to 'bluetooth', there needs to be some delay 
				// before the soundbar accepts an input switch command
		    	delay(2500);						
				irsnd_data.command = 0x40;	// switch to optical (see readme for command list)
			    irsnd_send_data(&irsnd_data, true);
		    	delay(200);
				mute_count=0;
			}
		    break;

	    }
	}

}

}

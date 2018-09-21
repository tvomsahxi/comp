#include "rpi.h"

void rpi_init(void){
	clearBss();

	init_gpio();

	pinMode(16,OUTPUT);
	digitalWrite(16,LOW);
}

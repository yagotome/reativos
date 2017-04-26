#include "xtea.c.h"

#define LED 13
#define BUT_PIN 2

void setup () {
    pinMode(LED, OUTPUT);
    pinMode(BUT_PIN, INPUT);
    Serial.begin(9600);
}
 
uint32_t key[] = { 1, 2, 3, 4};
uint32_t v[]   = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
int ini, fim, len = 10;

void loop () {

    static int led = 0;
    digitalWrite(LED, led = !led);
    int but;
    ini = 0;
    fim = 2;
    
    unsigned long t1 = micros();

    int i;
    for(i = ini; i < fim; i++) {
	
		but = digitalRead(BUT_PIN);
		if(but == LOW) {
			digitalWrite(LED, HIGH);
			while(1);
		}
	
		uint32_t new_v[] = {v[ini], v[ini + 1]};

      /*Serial.print("antes: ");
        Serial.print(new_v[0]);
        Serial.print(" ");
        Serial.println(new_v[1]);*/
        
		encipher(32, new_v, key);
      
	  /*Serial.print("durante: ");
        Serial.print(new_v[0]);
        Serial.print(" ");
        Serial.println(new_v[1]);*/
		
		decipher(32, new_v, key);

      /*Serial.print("depois: ");
        Serial.print(new_v[0]);
        Serial.print(" ");
        Serial.println(new_v[1]);*/
  
		ini = fim;
		fim += 2;
      
		if(fim > len) {
			break;
		}
    }

    unsigned long t2 = micros();
    Serial.println(t2-t1);
}
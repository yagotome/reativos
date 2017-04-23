//  _ ___ _______     ___ ___ ___  ___ _   _ ___ _____ ___ 
// / |_  )__ /   \   / __|_ _| _ \/ __| | | |_ _|_   _/ __| 
// | |/ / |_ \ |) | | (__ | ||   / (__| |_| || |  | | \__ \ 
// |_/___|___/___/   \___|___|_|_\\___|\___/|___| |_| |___/ 
// 
// The Unnamed Circuit
// 
// Made by Lucas Alves
// License: CC-BY-SA 3.0
// Downloaded from: https://circuits.io/circuits/4729211-the-unnamed-circuit

#define LED_PIN 13
#define BUT1_PIN 2 //acelera
#define BUT2_PIN 3 //desacelera

unsigned long old = 0;
unsigned long int countBut1 = 0;
unsigned long int countBut2 = 0;
bool pressedBut1 = false; //variável que controla um aumento de velocidade a cada aperto no botão 1
bool pressedBut2 = false; //variável que controla um aumento de velocidade a cada aperto no botão 2
int state = 0;
int velocidade = 1000;

void setup() {
	pinMode(LED_PIN, OUTPUT);
	pinMode(BUT1_PIN, INPUT);
  	pinMode(BUT2_PIN, INPUT);
}

void loop() {
  
  	unsigned long int now = millis();
  
  	if(now >= old + velocidade) {
      	old = now;
      	state = !state;
      	digitalWrite(LED_PIN, state);
    }
  
	int but1 = digitalRead(BUT1_PIN);
  
  	if(but1) {
      	countBut1 = millis();
      	if(countBut2 != 0 && countBut1-countBut2 < 500) {
        	digitalWrite(LED_PIN, LOW);
          	while(1);
      	}
      	if(velocidade > 100 && !pressedBut1) {
        	velocidade-=100;     //acelerando antes de soltar o botão
          	pressedBut1 = true;
      	}
  	}
	else {
		pressedBut1 = false;
  	}
  
  	int but2 = digitalRead(BUT2_PIN);
  	
  	if(but2) {
      	countBut2 = millis();
      	if(countBut1 != 0 && countBut2-countBut1 < 500) {
        	digitalWrite(LED_PIN, LOW);
          	while(1);
      	}
      	if(velocidade < 1000 && !pressedBut2) {
        	velocidade+=100;     //desacelerando antes de soltar o botão
          	pressedBut2 = true;
      	}
  	}
  	else {
    	pressedBut2 = false;  
    }
}

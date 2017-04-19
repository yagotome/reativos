// set pin numbers:
const int buttonPin[2] = {2, 4};     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin
const int buttonCount = 2;

// variables will change:
int buttonState[2];         // variable for reading the pushbutton status
int lastButtonState[2];         // variable for reading the pushbutton status
int delayTime = 1000;
unsigned long currentTime;
unsigned long buttonPressedTime = -1;
unsigned long blinkState = 0;

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin[0], INPUT);
  pinMode(buttonPin[1], INPUT);
  Serial.begin(115200);
}

bool pressed(int ind) {
  return buttonState[ind] == LOW && lastButtonState[ind] == HIGH;
}

bool released(int ind) {
  return buttonState[ind] == HIGH && lastButtonState[ind] == LOW;
}

void loop() {
  int i;
  for(i=0; i<buttonCount; ++i) {
    // read the states of the pushbutton values:
    buttonState[i] = digitalRead(buttonPin[i]);
  }

  if (pressed(0))  { //Faster
        delayTime = max(delayTime-100, 51);
        currentTime = millis();
        if (abs(currentTime - buttonPressedTime) <= 500) {
            Serial.println("Opa parou");
            digitalWrite(LED_BUILTIN, HIGH);
            while(1);
        }
        buttonPressedTime = currentTime;
  } else if (released(0)) {
        buttonPressedTime = 0;
  }

  if (pressed(1))  { //Slower
        delayTime = min(delayTime+100, 2000);
        currentTime = millis();
        if (abs(currentTime - buttonPressedTime) <= 500) {
            Serial.println("Opa parou 2");
            digitalWrite(LED_BUILTIN, HIGH);
            while(1);
        }
        buttonPressedTime = currentTime;
  } else if (released(1)) {
        buttonPressedTime = 0;
  }
  
    
  blinkState = (millis() / delayTime) % 2;
  digitalWrite(LED_BUILTIN, blinkState);   // turn the LED on/off

  for(i=0; i<buttonCount; ++i) {
    // read the states of the pushbutton values:
    lastButtonState[i] = buttonState[i];
  }
}

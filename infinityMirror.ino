  #include <Stepper.h>
#include <FastLED.h>

// pin on the arduino which is connected to the led strips
#define NUM_STRIP_LEDS 163
#define NUM_KNIFE_LEDS 13
#define STRIP_PIN 6
#define KNIFE_PIN 7

int redNum = 0;

CRGB strip[NUM_STRIP_LEDS];
CRGB knife[NUM_KNIFE_LEDS];

const int stepsPerRevolution = 100;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);
int stepCount = 0;  // number of steps the motor has taken

void bloodNumManagement(int bloodNum){
  if (bloodNum > 13) {
    redNum = 0;
  }
}

void flashLeds(){
  normalLeds(redNum);
  for(int i=0; i<NUM_STRIP_LEDS; i++) {
    strip[i] = CRGB::Black;
  }
  FastLED.show();
  redNum++;
  delay(100);
}

void normalLeds(int bloodNum){
  for(int i=0; i<NUM_STRIP_LEDS; i++) {
    strip[i] = CRGB::Red;
  }
  runningBlood(bloodNum);
  bloodNumManagement(bloodNum);
  FastLED.show();
  delay(100);
}

void runningBlood(int bloodNum){
  for(int i=0; i<NUM_KNIFE_LEDS; i++) {
    knife[i] = CRGB::White;
    if (i == bloodNum) {
      knife[i] = CRGB::Red;
    }
  }
}

void totalFlash(int seconds) {
  int flashTime = 0;
  while (flashTime < seconds) {
    flashLeds();

    flashTime++;
  }
}

void setup() {
  //Serial.begin(9600);   
  FastLED.addLeds<NEOPIXEL, STRIP_PIN>(strip, NUM_STRIP_LEDS);
  FastLED.addLeds<NEOPIXEL, KNIFE_PIN>(knife, NUM_KNIFE_LEDS);
  pinMode(5, OUTPUT); 
  digitalWrite(5,HIGH);
  totalFlash(50); // 5 per second
}

void loop() {
  normalLeds(redNum);
  redNum++;
  bloodNumManagement(redNum);
  
}

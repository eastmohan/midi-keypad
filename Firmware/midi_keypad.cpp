#include "USB.h"
#include "USBMIDI.h"
#include <FastLED.h>

USBMIDI USBMIDIClass;

const int keyPins[7] = {1, 2, 3, 4, 5, 6, 7};
const byte midiNotes[7] = {60, 62, 64, 65, 67, 69, 71}; 

const int ENC_A = 44;     
const int ENC_B = 43;    
const int ENC_SW = 8;    

#define LED_PIN 9
#define NUM_LEDS 8
CRGB leds[NUM_LEDS];

volatile int encoderValue = 64; 
int lastStateA;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 5;

bool lastKeyState[7] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};

void setup() {
  USB.begin();
  USBMIDIClass.begin();

  for (int i = 0; i < 7; i++) {
    pinMode(keyPins[i], INPUT_PULLUP);
  }

  pinMode(ENC_A, INPUT_PULLUP);
  pinMode(ENC_B, INPUT_PULLUP);
  pinMode(ENC_SW, INPUT_PULLUP);
  lastStateA = digitalRead(ENC_A);

  FastLED.addLeds<SK6812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50); 
}

void loop() {
  readKeys();
  readEncoder();
  updateLEDs();
}

void readKeys() {
  for (int i = 0; i < 7; i++) {
    bool currentState = digitalRead(keyPins[i]);
    
    if (currentState != lastKeyState[i]) {
      delay(debounceDelay);
      currentState = digitalRead(keyPins[i]);
      
      if (currentState != lastKeyState[i]) {
        lastKeyState[i] = currentState;
        
        if (currentState == LOW) {
         
          USBMIDIClass.noteOn(0, midiNotes[i], 127);
          leds[i] = CRGB::Cyan; 
        } else {
          USBMIDIClass.noteOff(0, midiNotes[i], 0);
          leds[i] = CRGB::Black;
        }
      }
    }
  }
}

void readEncoder() {
  int currentStateA = digitalRead(ENC_A);
  
  if (currentStateA != lastStateA && currentStateA == HIGH) {
   
    if (digitalRead(ENC_B) != currentStateA) {
      encoderValue = min(127, encoderValue + 4);
    } else {
      encoderValue = max(0, encoderValue - 4);
    }
    

    USBMIDIClass.controlChange(0, 7, encoderValue);
  }
  lastStateA = currentStateA;

  
  if (digitalRead(ENC_SW) == LOW) {
    encoderValue = 64;
    USBMIDIClass.controlChange(0, 7, encoderValue);
    delay(200); 
  }
}

void updateLEDs() {

  static uint8_t hue = 0;
  
  for (int i = 0; i < NUM_LEDS; i++) {
   
    if (digitalRead(keyPins[min(i, 6)]) == HIGH) {
      leds[i] = CHSV(hue + (i * 20), 255, 60);
    }
  }
  
  FastLED.show();
  hue++;
  delay(15);
}
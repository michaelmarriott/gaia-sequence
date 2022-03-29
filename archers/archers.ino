#include "FastLED.h"                                          // FastLED library.
//SECEFIC VARIBALES
#define NUM_LEDS_PER_STRIP 1300
#define NUM_STRIPS 8

struct CRGB leds[NUM_STRIPS * NUM_LEDS_PER_STRIP];

int sequence = 1; // What sequence to start playing?
int loopCounter = 0; // ALWAYS RESET TO 0 WHEN SEQUENCE CHANGES

void setup() {
  // put your setup code here, to run once:
 delay(100);//Safe Gaurd
 LEDS.addLeds<NEOPIXEL, NUM_STRIPS>(leds, NUM_LEDS_PER_STRIP);
}

void loop() {
  // put your main code here, to run repeatedly:
  EVERY_N_MILLIS_I(thisTimer, beginDelay) {
    SequenceSchedule();
    loopCounter = loopCounter + 1;
  }
}

// Sequence schedule
void SequenceSchedule() {
  switch (sequence) {
    case 1:
      // SEQUENCE
      if (loopCounter > 10000) {
          sequence = sequence + 1;
          loopCounter = 0;
      }
    break;
    default:
      sequence = 1;
      loopCounter = 0;
      break;
  }
}



///ADD SEQUNECES HERE

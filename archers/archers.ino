#include "FastLED.h" // FastLED library.

//GLOBAL VARIBALES
#define NUM_LEDS_PER_STRIP 450
#define NUM_STRIPS 8
#define NUM_LEDS NUM_LEDS_PER_STRIP * NUM_STRIPS

struct CRGB leds[NUM_LEDS];
CRGB listOfColors[14]; //List of predefined colors

int sequence = 1; // What sequence to start playing?
int loopCounter = 0; // ALWAYS RESET TO 0 WHEN SEQUENCE CHANGES
bool isStarted = true;
int beginDelay = 200;
int loopDelay = 10;
int BRIGHTNESS = 210;

void setup() {
  delay(100);//Safe Gaurd
   
  // put your setup code here, to run once:
  LEDS.addLeds<WS2811_PORTD, NUM_STRIPS>(leds, NUM_LEDS_PER_STRIP);
  LEDS.setBrightness(BRIGHTNESS);
  SetListOfColors(listOfColors);
  FastLED.setMaxPowerInVoltsAndMilliamps(5,60000);
  Serial.setTimeout(50);
  Serial.flush();
}

void loop() {
  
  // put your main code here, to run repeatedly:
  EVERY_N_MILLIS_I(thisTimer,beginDelay) {
      thisTimer.setPeriod(loopDelay); 
    SequenceSchedule();
    loopCounter += 1;
  }

  // EVERY_N_MILLISECONDS(100) {
 //   SequenceSchedule();
//    loopCounter += 1;
//  }

  int startChar = Serial.read();
  SerialRead(startChar);
}

// Sequence schedule
void SequenceSchedule() {
  Serial.print("-sequence:");
  Serial.print(sequence);
  Serial.print("-loopCounter:");
  Serial.println(loopCounter);
  switch (sequence) {
    case 1:
      // SEQUENCE
      OscialateComplexSequenceWrapper(loopCounter);
      if (loopCounter > 100) {
        nextSequence();
      }
      break;
    case 2:
      ColorWipeRainSequenceWrapper();
      if (loopCounter > 10) {
        nextSequence();
      }
      break;
    case 3:
      MatrixWrapper(loopCounter);
      loopDelay = 100;
      if (loopCounter > 3) {
        nextSequence();
      }
      break;
    case 4:
      PacificaSequenceWrapper();
      loopDelay = 200;
      if (loopCounter > 10000) {
        nextSequence();
      }
      break;
    case 5:
      LavaSequenceWrapper();
      loopDelay = 200;
      if (loopCounter > 1000) {
        nextSequence();
      }
      break;
    case 6:
      FireballsWrapper();
      loopDelay = 200;
      if (loopCounter > 1000) {
        nextSequence();
      }
      break;    
    default:
      sequence = 1;
      loopCounter = 0;
      break;
  }
}

//TODO : Top archs btoom archers SPIN opposite directions

void nextSequence(){
    sequence += 1;
    loopCounter = 0;
}

// Listen to incoming commands to sync
void SerialRead(int startChar) {
  if (startChar == '{') {
    String result = Serial.readStringUntil('}');
    char  nextCmnd = result.substring(0, 1)[0];
    int cmndValue = (result.substring(1, 4)).toInt();
    switch (nextCmnd) {
      case 'S':
        sequence = cmndValue;
        break;
      case 'B':
        BRIGHTNESS = cmndValue;
        LEDS.setBrightness(BRIGHTNESS);
        break;
      case 'D':
        loopDelay = cmndValue;
        break;
      default:
        break;
    }

  } else if (startChar == '%') {
    sequence += 1;
    String result = Serial.readStringUntil('\n');
  } else  if (startChar == '?') {
    Serial.print(0);
    Serial.write(',');
    Serial.print(0);
    Serial.println();
    isStarted = true;
  }
}

int ChangeColorNumber = 0;


CRGB RandomColor(uint8_t minR, uint8_t maxR, uint8_t minG, uint8_t maxG , uint8_t minB , uint8_t maxB) {
  CRGB randomColor = CRGB(random8(minR, maxR), random8(minG, maxG), random8(minB, maxB));
  return randomColor;
}

int Increment(int value, int minValue, int maxValue, int increaseBy) {
  int result = value + increaseBy;
  if (result > maxValue) {
    return minValue;
  }
  if (result < minValue) {
    return minValue;
  }
  return result;
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
CRGB Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return CRGB(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  else if (WheelPos < 170) {
    WheelPos -= 85;
    return CRGB(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  else {
    WheelPos -= 170;
    return CRGB(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}

CRGB ChangeColor() {
  ChangeColorNumber = ChangeColorNumber + 1;
  if (ChangeColorNumber > 13) {
    ChangeColorNumber = 0;
  }
  return listOfColors[ChangeColorNumber];
}

void SetListOfColors(CRGB listOfColors[14]) {
  listOfColors[0] = CRGB(162, 58, 136);
  listOfColors[1] = CRGB(87, 210, 95);
  listOfColors[2] = CRGB(219, 30, 90);
  listOfColors[3] = CRGB(204, 126, 189);
  listOfColors[4] = CRGB(56, 58, 136);
  listOfColors[5] = CRGB(212, 58, 136);
  listOfColors[6] = CRGB(162, 21, 136);
  listOfColors[7] = CRGB(162, 58, 181);
  listOfColors[8] = CRGB(162, 123, 136);
  listOfColors[9] = CRGB(215, 58, 136);
  listOfColors[10] = CRGB(162, 4, 136);
  listOfColors[11] = CRGB(162, 58, 109);
  listOfColors[12] = CRGB(162, 179, 136);
  listOfColors[13] = CRGB(28, 58, 136);
}



uint16_t XY (uint8_t x, uint8_t y) {
   Serial.println(x);
  return (y * NUM_LEDS_PER_STRIP + x);
}


uint16_t XYs (int x, int y) {
   Serial.println(x);
  return (y * NUM_LEDS_PER_STRIP + x);
}

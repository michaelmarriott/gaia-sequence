#include "FastLED.h" // FastLED library.

//GLOBAL VARIBALES
#define NUM_LEDS_PER_STRIP 1300
#define NUM_STRIPS 8
#define NUM_LEDS NUM_LEDS_PER_STRIP * NUM_STRIPS

struct CRGB leds[NUM_LEDS];

int sequence = 1; // What sequence to start playing?
int loopCounter = 0; // ALWAYS RESET TO 0 WHEN SEQUENCE CHANGES
bool isStarted = true;
int beginDelay = 200;
int loopDelay = 100;

void setup() {
  // put your setup code here, to run once:
  delay(100);//Safe Gaurd
  LEDS.addLeds<NEOPIXEL, NUM_STRIPS>(leds, NUM_LEDS_PER_STRIP);
  LEDS.setBrightness(210);
  // limit my draw to 50A at 5v of power draw
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 50000);
  Serial.setTimeout(50);
  Serial.flush();
  while ( Serial.available() ) Serial.read();
}

void loop() {
  // put your main code here, to run repeatedly:
  EVERY_N_MILLIS_I(loopDelay, beginDelay) {
    SequenceSchedule();
    loopCounter = loopCounter + 1;
  }

  int startChar = Serial.read();
  SerialRead(startChar);
}

// Sequence schedule
void SequenceSchedule() {
  switch (sequence) {
    case 1:
      // SEQUENCE
      if (loopCounter > 10000) {
        sequence = sequence + 1;
        loopCounter = 0;
        OscialateComplexSequenceWrapper(loopCounter);
      }
      break;
    case 2:
      if (loopCounter > 1000) {
        ColorWipeRainSequenceWrapper();
        break;
      }
    case 3:
      if (loopCounter > 1000) {
        MatrixWrapper();
        break;
      }
    case 4:
      if (loopCounter > 1000) {
        MatrixWrapper();
        break;
      }
    default:
      sequence = 1;
      loopCounter = 0;
      break;
  }
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
        LEDS.setBrightness(cmndValue);
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
CRGB listOfColors[14]; //List of predefined colors

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

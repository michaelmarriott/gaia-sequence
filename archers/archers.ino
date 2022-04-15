#include "FastLED.h" // FastLED library.
//GLOBAL VARIBALES
#define NUM_LEDS_PER_STRIP 450
#define NUM_LEDS_PER_STRIP_SPLIT 120
#define NUM_STRIPS 8
#define NUM_LEDS NUM_LEDS_PER_STRIP * NUM_STRIPS
int ledPin = 13; // Set the pin to digital I/O 13
String previousResult = "";
struct CRGB leds[NUM_LEDS];
CRGB listOfColors[14]; //List of predefined colors

int sequence = 4; // What sequence to start playing?
int loopCounter = 0; // ALWAYS RESET TO 0 WHEN SEQUENCE CHANGES
bool isStarted = true;
int beginDelay = 200;
int loopDelay = 10;
int loopDelayMulti = 10;
int BRIGHTNESS = 255;
bool debug = false;

int ChangeColorNumber = 0;

void setup() {
  delay(100);//Safe Gaurd
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  // put your setup code here, to run once:
  LEDS.addLeds<WS2811_PORTD, NUM_STRIPS>(leds, NUM_LEDS_PER_STRIP);
  LEDS.setBrightness(BRIGHTNESS);
  SetListOfColors(listOfColors);
 // FastLED.setMaxPowerInVoltsAndMilliamps(5, 60000);
  Serial.setTimeout(50);
  Serial.flush();
  writeTeensy();
}

void loop() {

  // put your main code here, to run repeatedly:
   EVERY_N_MILLIS_I(thisTimer,beginDelay) {
      thisTimer.setPeriod(loopDelay);
      SequenceSchedule();
     loopCounter += 1;
  }
  if (Serial.available()) {
    int startChar = Serial.read();
    SerialRead(startChar);
  }
 /// EVERY_N_MILLISECONDS(100) {
  //   SequenceSchedule();
 //   loopCounter += 1;
 // }

}


// Listen to incoming commands to sync
void SerialRead(int startChar) {
  if (startChar == '{') {
    String result = Serial.readStringUntil('}');

    if (previousResult != result) {
      previousResult = result;

      //000 000 000
      if (result.length() > 3) {
        blink();
        int nextSequence = (result.substring(0, 3).toInt());
        int nextBrightness = (result.substring(4, 7).toInt());
        int nextSpeed = (result.substring(8, 11).toInt());

        if (nextSequence != sequence) {
          loopCounter = 0;
          sequence = nextSequence;
        }
        if (nextBrightness != 0) {
          LEDS.setBrightness(nextBrightness);
        }
        if (nextSpeed != 0) {
          loopDelayMulti = nextSpeed;
        }
       
      }
    }
  } else if (startChar == '%') {
    sequence += 1;
    String result = Serial.readStringUntil('\n');
  } else  if (startChar == '?') {
    writeTeensy();
    isStarted = true;
  }
}

void writeTeensy() {
  Serial.print(0); Serial.write(','); Serial.print(0); Serial.write(','); Serial.print(0); Serial.write(','); Serial.print(0); Serial.write(','); Serial.print(0); Serial.write(','); Serial.print(0); Serial.write(',');
  Serial.print(0); Serial.write(','); Serial.print(0); Serial.write(','); Serial.print(0); Serial.write(','); Serial.print(0); Serial.write(','); Serial.print(0); Serial.write(','); Serial.print(0);
  Serial.println();
}

void blink() {
  digitalWrite(ledPin, HIGH); // turn the LED on
  delay(100); // Wait 10 milliseconds for next reading
  digitalWrite(ledPin, LOW); // otherwise turn it off
}

// Sequence schedule
void SequenceSchedule() {
  if (debug) {
    //  Serial.print("-sequence:");
    // Serial.print(sequence);
    //  Serial.print("-loopCounter:");
    //  Serial.println(loopCounter);
  }
  switch (sequence) {
    case 1:
      // SEQUENCE
      OscialateComplexSequenceWrapper(loopCounter);
      if (loopCounter > 1000) {
        nextSequence();
      }
      break;
    case 2:
      ColorWipeRainSequenceWrapper();
      if (loopCounter > 2) {
        nextSequence();
      }
      break;
    case 3:
      MatrixWrapper(loopCounter);
      loopDelay = 10*loopDelayMulti;
      if (loopCounter > 300) {
        nextSequence();
      }
      break;
    case 4:
      PacificaSequenceWrapper();
      loopDelay = 20*loopDelayMulti;
      if (loopCounter > 10000) {
        nextSequence();
      }
      break;
    case 5:
      LavaSequenceWrapper();
      loopDelay = 20*loopDelayMulti;
      if (loopCounter > 1000) {
        nextSequence();
      }
      break;
    case 6:
      FireballsWrapper();
      loopDelay = 20*loopDelayMulti;
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

void nextSequence() {
  sequence += 1;
  loopCounter = 0;
}



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
  return (y * NUM_LEDS_PER_STRIP + x);
}


uint16_t XYs (int x, int y) {
  return (y * NUM_LEDS_PER_STRIP + x);
}

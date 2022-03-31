
//OSCILATE COMPLEX
#define NUM_LEDS_OF_SPLITS 5
int osc_sizeOfStrip = 0;

CRGB colorOC[NUM_STRIPS * NUM_LEDS_OF_SPLITS]; //OSCILATECOMPLEX
int rdms[NUM_STRIPS * NUM_LEDS_OF_SPLITS][3]; //OSCILATECOMPLEX

void OscialateComplexSequenceWrapper(int loopCounter) {
  if (loopCounter == 1 ) {
    Serial.println("OscialateComplex");
    // CRGB wcolor = CRGB::WhiteSmoke;
    int middle = NUM_LEDS_PER_STRIP / 2;
    for (int x = 0; x < NUM_STRIPS; x++) {
      for (int y = 0; y < NUM_LEDS_PER_STRIP; y++) {
        leds[(x * NUM_LEDS_PER_STRIP) + (y)] = CRGB::Black;
      }
    }
    FastLED.show(); // display this frame

    osc_sizeOfStrip = Increment(osc_sizeOfStrip, middle - 10, middle - 1, 2);
    for (int s = 0; s < NUM_STRIPS; s++) {
      rdms[s][0] = osc_sizeOfStrip; //Size
      rdms[s][1] = 0;//COUNTER
      rdms[s][2] = 0;//0 = up, 1 =down;
    }

    //Got Out
    for (int s = 0; s < NUM_STRIPS; s++) {
      colorOC[s] = CRGB(random8(), random8(), random8());
    }
    FastLED.show();
  }

  OscialateComplexSequence(osc_sizeOfStrip);

}

void OscialateComplexSequence(int sizeOfStrip) {
  Serial.println("OscialateComplexSequence");
  int middle = NUM_LEDS_PER_STRIP / 2;
  //  CRGB wcolor = CRGB::WhiteSmoke;
  for (int strip = 0; strip < NUM_STRIPS; strip++) {
    if (rdms[strip][1] <= 0) {// if you get to zero
      rdms[strip][2] = 0; //direction up
      rdms[strip][0] = Increment(sizeOfStrip, 2, middle - 1, 5); //size
      colorOC[strip] = CRGB(random8(), random8(), random8());
    }
    else if (rdms[strip][1] >= rdms[strip][0]) {// counter greater than size
      rdms[strip][2] = 1; //switch direction down
    }

    if (rdms[strip][2] == 0) {// if direction up
      rdms[strip][1] = rdms[strip][1] + 1; //count up
    }
    else {
      rdms[strip][1] = rdms[strip][1] - 1; //count down
    }

    //leds[(strip * NUM_LEDS_PER_STRIP) + (middle - rdms[strip][1])] = wcolor;
    //leds[(strip * NUM_LEDS_PER_STRIP) + (middle + rdms[strip][1])] = wcolor;

  }

  //delay(colorSpeed);
  for (int strip = 0; strip < NUM_STRIPS; strip++) {
    // Serial.println(rdms[strip][1]);
    leds[(strip * NUM_LEDS_PER_STRIP) + (middle - rdms[strip][1])] = colorOC[strip];
    leds[(strip * NUM_LEDS_PER_STRIP) + (middle + rdms[strip][1])] = colorOC[strip];
  }
  FastLED.show();
}

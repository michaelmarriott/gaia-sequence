
//OSCILATE COMPLEX


CRGB colorOC[NUM_STRIPS]; //OSCILATECOMPLEX
int rdms[NUM_STRIPS][3]; //OSCILATECOMPLEX
int osc_middle = 0;
void OscialateComplexSequenceWrapper(int loopCounter) {
  if (loopCounter == 0 ) {
    int sizeOfStrip = 0;
    osc_middle = NUM_LEDS_PER_STRIP / 2;
    for (int x = 0; x < NUM_STRIPS; x++) {
      for (int y = 0; y < NUM_LEDS_PER_STRIP; y++) {
        leds[(x * NUM_LEDS_PER_STRIP) + (y)] = CRGB(25,5,2);
      }
    }
    
    FastLED.show(); // display this frame
    sizeOfStrip = Increment(sizeOfStrip, osc_middle - 6, osc_middle - 1, 2);
    for (int s = 0; s < NUM_STRIPS; s++) {
      rdms[s][0] = sizeOfStrip; //Size
      rdms[s][1] = 0;//COUNTER
      rdms[s][2] = 0;//0 = up, 1 =down;
    }

    //Got Out
    for (int s = 0; s < NUM_STRIPS; s++) {
      colorOC[s] = CRGB(random8(), random8(), random8());
    }
    FastLED.show();
  }
  OscialateComplexSequence(osc_middle, 10);
}

void OscialateComplexSequence(int middle, int minimun) {
  for (int strip = 0; strip < NUM_STRIPS; strip++) {
    if (rdms[strip][1] <= 0) {// if you get to zero
      rdms[strip][2] = 0; //direction up
      rdms[strip][0] = random16(minimun, middle - 2);
      colorOC[strip] = CRGB(random8(), random8(), random8());
    }
    else if (rdms[strip][1] >= rdms[strip][0]) {// counter greater than size
      rdms[strip][2] = 1; //switch direction down
      colorOC[strip] = CRGB(random8(), random8(), random8());
    }

    if (rdms[strip][2] == 0) {// if direction up
      rdms[strip][1] += 1; //count up
    }
    else {
      rdms[strip][1] -= 1; //count down
    }
  }
//up-674down674
//up-156down1056
//up106down1694
//up640down2060
//up1222down2378
//up1742down2758
//up2192down3208
//up2672down3628

 // delay(colorSpeed);
  
  for (int strip = 0; strip < NUM_STRIPS; strip++) {
    Serial.print("middle");
   Serial.print(middle);
  Serial.print("down");
   Serial.println(rdms[strip][1]);
    leds[(strip * NUM_LEDS_PER_STRIP) + (middle - rdms[strip][1])] = colorOC[strip];
    leds[(strip * NUM_LEDS_PER_STRIP) + (middle + rdms[strip][1])] = colorOC[strip];
  }

  FastLED.show();
}

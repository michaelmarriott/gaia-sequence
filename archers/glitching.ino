int GLITCH_STRIP = 0;
int DELAY_BETWEEN_GLICHES_MIN = 1000;
int DELAY_BETWEEN_GLICHES_MAX = 5000;
int GLITCH_LOOPS_MIN = 50;
int GLITCH_LOOPS_MAX = 200;
int GLITCH_INTERNAL_DELAY_MIN = 0;
int GLITCH_INTERNAL_DELAY_MAX = 50;

int glitch_array0[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,21,22,23,24,25,26,27.28,29,30,31,32,33,34,35 };
int glitch_array1[] = {138, 139, 137, 136, 135, 134, 133, 132, 131, 130,140,141,142,143,144,145,146,147,148,149,150, 51,52,53,54,55,56,57,58,59,60,61};
int glitch_array2[] = {125, 126, 127, 128, 129, 124, 123, 122, 121, 120, 119,36,37,38,39,40,41,42,43,45,44,46,47,48,49,50};
int glitch_array3[] = {115, 116, 117, 118, 119, 114, 113, 112, 111, 110, 109, 108, 107, 106, 105, 104, 103, 102, 101, 100, 99, 98, 87,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85 };

int arrSizes[4] = {sizeof(glitch_array0) / sizeof(glitch_array0[0]), sizeof(glitch_array1) / sizeof(glitch_array1[0]), sizeof(glitch_array2) / sizeof(glitch_array2[0]), sizeof(glitch_array3) / sizeof(glitch_array3[0]) };


void GlitchSequenceWrapper(){
  randomGlitchSequence();
}

void randomGlitchSequence() {
  int randomGlitch = random8(0, 4);
 // Serial.println(randomGlitch);
  int * randomArr = getGlitchRandomArray(randomGlitch);
  int sizeOf = arrSizes[randomGlitch];
  doArrayGlitchSeqence(randomArr, sizeOf);

  int delayBetweenGlitches = random(DELAY_BETWEEN_GLICHES_MIN, DELAY_BETWEEN_GLICHES_MAX);
  delay(delayBetweenGlitches);
}


void doArrayGlitchSeqence(int* randomArr, int sizeOf) {
  //Serial.println("doArrayGlitchSeqence");

  CRGB color = ChangeColor();
  int loops = random8(GLITCH_LOOPS_MIN, GLITCH_LOOPS_MAX);
  for (int a = 0; a < loops; a++) {
    for (int y = 0; y < NUM_STRIPS; y++) {
      for (int x = 0; x < sizeOf; x++) {
       // Serial.println((y * NUM_STRIPS) + randomArr[x]);
        leds[(y * NUM_LEDS_PER_STRIP) + randomArr[x]] = color;
      }
    }
    FastLED.show();
    for (int y = 0; y < NUM_STRIPS; y++) {
      for (int x = 0; x < sizeOf; x++) {
        leds[(y * NUM_LEDS_PER_STRIP) + randomArr[x]] = CRGB::Black;
      }
    }
    FastLED.show();
    int delays = random8(GLITCH_INTERNAL_DELAY_MIN, GLITCH_INTERNAL_DELAY_MAX);
    delay(delays);
  }

}

int* getGlitchRandomArray(int intArr) {
  //Serial.println(intArr);
  switch (intArr) {
    case 0:
      return glitch_array0;
      break;
    case 1:
      return glitch_array1;
      break;
    case 2:
      return glitch_array2;
      break;
    case 3:
      return glitch_array3;
      break;
    default:
      return glitch_array3;
      break;
  }

}

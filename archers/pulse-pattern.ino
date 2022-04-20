void DoAllColorsSequenceWrapper() {
  DoAllColorsSequence(0, 245, 80, 150);
  FastLED.show();
}

int pulse_hue=0;
int pulse_sat = 100;
int pulse_bright = 200;
int pulse_bounceDirection =0;

void DoAllColorsSequence(int minHue, int maxHue, int minSat, int maxSat) {
  if (pulse_bounceDirection == 0) {
    pulse_bright++;
    if (pulse_bright >= 250) {
      pulse_bounceDirection = 1;
    }
  }
  if (pulse_bounceDirection == 1) {
    pulse_bright--;
    if (pulse_bright <= 50) {
      pulse_hue = Increment(pulse_hue, minHue, maxHue, 42);
      pulse_sat = Increment(pulse_sat, minSat, maxSat, 12);
      pulse_bounceDirection = 0;
    }
  }
  
  for (int x = 0; x < NUM_STRIPS; x++) {
    for (int y = 0; y < NUM_LEDS_PER_STRIP; y++) {
      int tempBright = sin8(pulse_bright + y);
      if (tempBright < 50) {
        tempBright = 50;
      }
      leds[(x * NUM_LEDS_PER_STRIP) + (y)] = CHSV(pulse_hue, pulse_sat, tempBright);
    }
  }

}

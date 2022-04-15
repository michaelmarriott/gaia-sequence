
int CWR_LENGTH_VARIABLE = 5;

int cwr_trailMax = 0;
int cwr_apart = 0;
int cwr_amountofaparts = 0;
int cwr_i = 0;
bool cwr_allowReverse = true;
int cwr_delay = 20;

//ColorWipe Rain Sequence
void ColorWipeRainSequenceWrapper() {
  // Serial.println("ColorWipeRainWrapper");
  ColorWipeRainSequence(ChangeColor(), cwr_allowReverse, cwr_delay);
}


void ColorWipeRainSequence(CRGB color, bool allowReverse, uint8_t wait) {
  // Serial.println("ColorWipeRainSequence");
  int reverse = 0;
  if (allowReverse) {
    cwr_i = Increment(cwr_i, 16, 30, 5);
    if (cwr_i % 2 == 0) {
      reverse = NUM_LEDS_PER_STRIP - 1;
    }
  }

  int colorWipeSpeed = wait;

  cwr_trailMax = Increment(cwr_trailMax, 4 * CWR_LENGTH_VARIABLE, 12 * CWR_LENGTH_VARIABLE, 3);
  cwr_apart = Increment(cwr_apart, 6 * CWR_LENGTH_VARIABLE, 20 * CWR_LENGTH_VARIABLE, 4);
  cwr_amountofaparts = Increment(cwr_amountofaparts, 5 * CWR_LENGTH_VARIABLE, 25 * CWR_LENGTH_VARIABLE, 6);

  for (int i = (0 - (cwr_trailMax)); i < NUM_LEDS_PER_STRIP + cwr_trailMax + (cwr_apart * cwr_amountofaparts); i++) {
    for (int strip = 0; strip < NUM_STRIPS; strip++) {
      for (int t = 0; t < cwr_trailMax; t++) {
        if (i - t > 0 && i - t < NUM_LEDS_PER_STRIP) {
          leds[(strip * NUM_LEDS_PER_STRIP) + abs(reverse - (i - t))] = color;
          leds[(strip * NUM_LEDS_PER_STRIP) + abs(reverse - (i - t))].fadeToBlackBy(t * (int)(256 / cwr_trailMax));
        }
        for (int a = 1; a < cwr_amountofaparts; a++) {
          int icwr_apart = ((i - t) - (cwr_apart * a));
          if (icwr_apart > 0 && (icwr_apart) < NUM_LEDS_PER_STRIP) {
            leds[(strip * NUM_LEDS_PER_STRIP) + abs(reverse - icwr_apart)] = color;
            leds[(strip * NUM_LEDS_PER_STRIP) + abs(reverse - icwr_apart)].fadeToBlackBy(t * (int)(256 / cwr_trailMax));
          }
        }
      }
    }
    FastLED.show();
    //delay(colorWipeSpeed);
    for (int strip = 0; strip < NUM_STRIPS; strip++) {
      for (int t = 0; t < cwr_trailMax; t++) {
        if (i - t > 0 && i - t < NUM_LEDS_PER_STRIP) {
          leds[(strip * NUM_LEDS_PER_STRIP) + abs(reverse - (i - t))].fadeToBlackBy(210);
        }
        for (int a = 1; a < cwr_amountofaparts; a++) {
          int icwr_apart = ((i - t) - (cwr_apart * a));
          if (icwr_apart > 0 && (icwr_apart) < NUM_LEDS_PER_STRIP) {
            leds[(strip * NUM_LEDS_PER_STRIP) + abs(reverse - 0)].fadeToBlackBy(250);
            leds[(strip * NUM_LEDS_PER_STRIP) + abs(reverse - icwr_apart)].fadeToBlackBy(210);
          }
        }
      }
    }
  }
}

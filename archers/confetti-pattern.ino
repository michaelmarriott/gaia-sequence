

void ConfettiWrapper() {
  Confetti();
  FastLED.show();
}

// random colored speckles that blink in and fade smoothly
void Confetti()
{
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV(gHue + random8(64), 200, 255);
}

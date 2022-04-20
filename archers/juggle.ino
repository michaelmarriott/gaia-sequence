

void JuggleWrapper() {
  Juggle();
  FastLED.show();
}

 // eight colored dots, weaving in and out of sync with each other
void Juggle() {
  fadeToBlackBy( leds, NUM_LEDS, 40);
  byte dothue = 0;
  CRGB color = CRGB(random8(10,255),random8(2,120),random8(10,255));
  for( int i = 0; i < 40; i++) {
    leds[beatsin16( i+1, 0, NUM_LEDS-1 )] |= color;
    dothue += 32;
  }
}

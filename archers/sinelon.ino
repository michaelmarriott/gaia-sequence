
  // a colored dot sweeping back and forth, with fading trails
  
void SinelonWrapper() {
  Sinelon();
  FastLED.show();
}

void Sinelon()
{
  int sat = random8(20,60);
  fadeToBlackBy( leds, NUM_LEDS, 1);
  int pos = beatsin16( 3650, 0, NUM_LEDS-1 );
  leds[pos] += CHSV( gHue, sat, 255);
}

uint16_t lava_brightnessScale = 150;
uint16_t lava_indexScale = 100;

CRGBPalette16  lavaPalette = CRGBPalette16(
  CRGB::DarkRed,  CRGB::Maroon,   CRGB::DarkRed,  CRGB::Maroon,
  CRGB::DarkRed,  CRGB::Maroon,   CRGB::DarkRed,  CRGB::DarkRed,
  CRGB::DarkRed,  CRGB::DarkRed,  CRGB::Red,      CRGB::Orange,
  CRGB::White,    CRGB::Orange,   CRGB::Red,      CRGB::DarkRed
);

void LavaWrapper(){
    for (int i = 0; i < NUM_LEDS; i++) {
    uint8_t brightness = inoise8(i * lava_brightnessScale, millis() / 5);
    uint8_t index = inoise8(i * lava_indexScale, millis() /10);
    leds[i] = ColorFromPalette(lavaPalette, index, brightness);
    //leds[i] = CHSV(0, 255, brightness);
  }
}

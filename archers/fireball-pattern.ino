void FireballsWrapper(){
  uint8_t bx1 = beatsin8(15, 0, NUM_LEDS_PER_STRIP - 1, 0, 0);
  uint8_t by1 = beatsin8(18, 0, NUM_STRIPS - 1, 0, 0);
  uint8_t bx2 = beatsin8(28, 0, NUM_LEDS_PER_STRIP - 1, 0, 32);
  uint8_t by2 = beatsin8(23, 0, NUM_STRIPS - 1, 0, 32);
  uint8_t bx3 = beatsin8(30, 0, NUM_LEDS_PER_STRIP - 1, 0, 64);
  uint8_t by3 = beatsin8(24, 0, NUM_STRIPS - 1, 0, 64);
  uint8_t bx4 = beatsin8(17, 0, NUM_LEDS_PER_STRIP - 1, 0, 128);
  uint8_t by4 = beatsin8(25, 0, NUM_STRIPS - 1, 0, 128);
  uint8_t bx5 = beatsin8(19, 0, NUM_LEDS_PER_STRIP - 1, 0, 170);
  uint8_t by5 = beatsin8(21, 0, NUM_STRIPS - 1, 0, 170);

  for (int i = 0; i < NUM_LEDS_PER_STRIP; i++)    {
    for (int j = 0; j < NUM_STRIPS; j++) {

      byte  sum =  dist(i, j, bx1, by1);
      sum = qadd8(sum, dist(i, j, bx2, by2));
      sum = qadd8(sum, dist(i, j, bx3, by3));
      sum = qadd8(sum, dist(i, j, bx4, by4));
      sum = qadd8(sum, dist(i, j, bx5, by5));

      leds[XYs(i, j)] =  ColorFromPalette(HeatColors_p, sum + 220, BRIGHTNESS);
    }
  }

  blur2d(leds, NUM_LEDS_PER_STRIP, NUM_STRIPS, 32 );
}

byte dist (uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)  {
  int a = y2 - y1;
  int b = x2 - x1;
  a *= a;
  b *= b;
  byte dist = 220 / sqrt16(a + b);
  return dist;
}

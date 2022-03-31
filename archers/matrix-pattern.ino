//EVERY_N_MILLISECONDS(100)

void MatrixWrapper(int loopCounter){
   if (loopCounter == 1) {
    MatrixInit();
   }
   MatrixUpdate();
   FastLED.show();
   MatrixChange();
}

void MatrixChange () {
  matrix_hue = Increment(matrix_hue, 0, 255, 1);
  matrix_sat = Increment(matrix_sat, 100, 220, 1);
  matrix_color =  CHSV(matrix_hue, matrix_sat, BRIGHTNESS);

  int rand1 = random16 (NUM_LEDS);
  int rand2 = random16 (NUM_LEDS);
  if ((matrix_rain[rand1] == 1) && (matrix_rain[rand2] == 0) )   //simple get two random dot 1 and 0 and swap it,
  {
    matrix_rain[rand1] = 0;  //this will not change total number of dots
    matrix_rain[rand2] = 1;
  }
} 

void MatrixInit() {
  //init array of dots. run once
  for (int i = 0; i < NUM_LEDS; i++) {
    if (random8(10) == 0) {
      matrix_rain[i] = 1;  //random8(20) number of dots. decrease for more dots
    }
    else {
      matrix_rain[i] = 0;
    }
  }
} 

void MatrixUpdate() {

  for (byte i = 0; i < NUM_COLS; i++) {

    for (byte j = 0; j < NUM_ROWS; j++) {
      byte layer = matrix_rain[XY(i, ((j + matrix_speed + random8(3) + NUM_ROWS) % NUM_ROWS))];
      //fake scroll based on shift coordinate
      // random8(2) // add glitchy look
      if (layer) {
        leds[XY((NUM_COLS - 1) - i, (NUM_ROWS - 1) - j)] = matrix_color;
      }
    }
  }

  matrix_speed ++;
  fadeToBlackBy(leds, NUM_LEDS, 40);
  blurRows(leds, NUM_COLS, NUM_ROWS, 16);      //if you want
} 

uint16_t XY (uint8_t x, uint8_t y) {
  return (y * NUM_COLS + x);
}

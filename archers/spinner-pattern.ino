int spin_top = 0;
int spin_bottom = 0;
CRGB spin_top_colour = RandomColor(40, 140, 40, 140, 40, 240);
CRGB spin_bottom_colour = RandomColor(40, 250, 40, 140, 40, 140);

int r1 = spin_top_colour.r/1.2;
int g1 = spin_top_colour.g/1.2;
int b1 = spin_top_colour.b/1.2;
CRGB spin_top_colour_fade = CRGB(r1,g1,b1);

int r2 = spin_bottom_colour.r/1.2;
int g2 = spin_bottom_colour.g/1.2;
int b2 = spin_bottom_colour.b/1.2;
CRGB spin_bottom_colour_fade  = CRGB(r2,g2,b2);

void spinnerPattern(){
 for(int x = 0; x < NUM_STRIPS; x++) {
    if(showIt(spin_top, x, 5)){
      for(int i = NUM_LEDS_PER_STRIP_SPLIT; i < NUM_LEDS_PER_STRIP; i++) {
        leds[x][i] = spin_top_colour;
      }
    }else{
       for(int i = NUM_LEDS_PER_STRIP_SPLIT; i < NUM_LEDS_PER_STRIP; i++) {
        leds[x][i] = spin_top_colour_fade;
      }
    }
  }
  for(int x = NUM_STRIPS-1; x >= 0; x--) {
    // This inner loop will go over each led in the current strip, one at a time
    if(showIt(spin_bottom,x,3)){//} {
      for(int i = 0; i < NUM_LEDS_PER_STRIP_SPLIT; i++) {
        leds[x][i] = spin_bottom_colour;
      }
    } else {
       for(int i = 0; i < NUM_LEDS_PER_STRIP_SPLIT; i++) {
        leds[x][i] = spin_bottom_colour_fade;
      }
    }
  }
  spin_top = spin_top + 1;
  spin_bottom = spin_bottom - 1;
  if(spin_top >= NUM_STRIPS){
    spin_top = 0;
  }
  if(spin_bottom < 0){
    spin_bottom = NUM_STRIPS-1;
  }
}

bool showIt(int row, int position, int amount){
  bool isShow = false;
  if(amount >= 2){
    isShow = position == row || position == row - 1  || (row == 0 && position == NUM_STRIPS-1);
  }
  if(!isShow && amount >= 3){
    isShow = position == row - 2 || (row == 0 && position == NUM_STRIPS-2) || (row == 1 && position == NUM_STRIPS-1);
  }
  if(!isShow && amount >= 4){
    isShow = position == row - 3 || (row == 0 && position == NUM_STRIPS-3) || (row == 2 && position == NUM_STRIPS-1);
  }
  if(!isShow && amount >= 5){
    isShow = position == row - 4 || (row == 0 && position == NUM_STRIPS-4) || (row == 3 && position == NUM_STRIPS-1);
  }
  return isShow;
}

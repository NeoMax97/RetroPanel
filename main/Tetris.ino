#include <Tetris.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_GFX.h>
#include <NewPing.h>

#define PIN 4
/**
#define UP 7
#define NEUT 8
#define DOWN 9
**/
// These two pins are used for the Distance Sensor.
#define ECHO 5
#define TRIG 10

/**
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(16, 16, PIN, 
                            NEO_MATRIX_TOP + NEO_MATRIX_LEFT +
                            NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
                            NEO_RGB         + NEO_KHZ800);
**/
Tetris tetris = Tetris(&matrix, 6, 17);
NewPing sensor(TRIG, ECHO, 200);


long time_out = 0;
long time_out2 = 0;

void readyTetris() {
  // put your setup code here, to run once:
  matrix.begin();
  matrix.setBrightness(5);
  matrix.clear();
  tetris = Tetris(&matrix, 6, 17);
  tetris.setup_wall();
  tetris.setup_bag();
  tetris.generate();
  tetris.set_next();
  tetris.show_piece();
  time_out = 0;
  time_out2 = 0;
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
}

void runTetris() {
  // put your main code here, to run repeatedly:
  if (time_out2 < millis()){
      // tetris.move_side(7, 8, 9);
      tetris.move_side(sensor.ping_cm(), 8);
      tetris.show_piece();
      tetris.show_occupied();
      tetris.rotate(7, 9);
      time_out2 = millis() + 250;
    }
  if (time_out < millis()){
    tetris.move_down();
    tetris.show_score(10, 11);
    if (tetris.check_over()){
      game_over();
    }
    time_out = millis() + 1000;
  }

}

void game_over(){
  boolean end = true;
  while(end){
    tetris.show_end();
    if (!digitalRead(8)){
      end = false;
      setup();
    }
  }
}


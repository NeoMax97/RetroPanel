/**
#define UP 7
#define NEUT 8
#define DOWN 9
**/
#include <Adafruit_NeoPixel.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_GFX.h>

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(16, 16, 4, 
                            NEO_MATRIX_TOP + NEO_MATRIX_LEFT +
                            NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
                            NEO_RGB         + NEO_KHZ800);

long to = 0;
boolean started = false;
boolean pong_selected = false;
boolean tetris_selected = false;

void setup() {
  // put your setup code here, to run once:
  matrix.begin();
  matrix.setBrightness(5);
  matrix.clear();
  show_menu();
  to = 0;
  started = false;
  pong_selected = false;
  tetris_selected = false;
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (to < millis()){
    if (!started){
      if (!digitalRead(9)){
        started = true;
        pong_selected = false;
        tetris_selected = true;
        readyTetris();
        // runTetris();
      }
      if (!digitalRead(7)){
        started = true;
        tetris_selected = false;
        pong_selected = true;
        readyPong();
        // runPong();
      }
    }
    if (started){
      if (pong_selected){
        runPong();
      }else{
        runTetris();
      }
    }
    to = millis() + 100;
  }
  // end of loop
}

void show_menu(){
  // Draw Tetris blocks
  matrix.drawPixel(4, 0, matrix.Color(0, 128, 128));
  matrix.drawPixel(5, 0, matrix.Color(0, 128, 128));
  matrix.drawPixel(5, 1, matrix.Color(0, 128, 128));
  matrix.drawPixel(5, 2, matrix.Color(0, 128, 128));
  matrix.drawPixel(3, 7, matrix.Color(225, 0, 0));
  matrix.drawPixel(4, 7, matrix.Color(225, 0, 0));
  matrix.drawPixel(4, 8, matrix.Color(225, 0, 0));
  matrix.drawPixel(5, 8, matrix.Color(225, 0, 0));
  
  // Draw the paddles
  for (int i = 10; i < 14; i++){
    matrix.drawPixel(i, 0, matrix.Color(0, 225, 0));
    matrix.drawPixel(i, 15, matrix.Color(0, 225, 0));
  }
  // Draw the ball
  matrix.drawPixel(14, 4, matrix.Color(125, 0, 0));
  matrix.drawPixel(15, 5, matrix.Color(125, 0, 0));
  matrix.drawPixel(14, 6, matrix.Color(175, 0, 0));
  matrix.drawPixel(13, 7, matrix.Color(225, 0, 0));
  // Draw the line
  for (int i = 0; i < 16; i++){
    matrix.drawPixel(7, i, matrix.Color(0, 225, 0));
    matrix.drawPixel(8, i, matrix.Color(0, 225, 0));
  }

  matrix.show();
}


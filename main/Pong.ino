#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <Paddle.h>
#include <Ball.h>
#include <NewPing.h>

// #include <Adafruit_SSD1306.h>

#define PIN 4
/**
#define UP 7
#define NEUT 8
#define DOWN 9
**/
// These two pins are for the Distance Sensor
#define ECHO 5  // Input
#define TRIG 10 // Output

// Adafruit_SSD1306 lcd(-1); // create display object

/**
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(16, 16, PIN, 
                            NEO_MATRIX_TOP + NEO_MATRIX_LEFT +
                            NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
                            NEO_RGB         + NEO_KHZ800);
**/
Paddle player = Paddle(false, &matrix);
Paddle cpu = Paddle(true, &matrix);
Ball ball = Ball(&matrix);
long timeout = 0;
long timeout2 = 0;

NewPing sonar(TRIG, ECHO, 200);

void readyPong() {
  // put your set7code here, to run once:
  matrix.begin();
  matrix.setBrightness(5);
  matrix.clear();
  timeout = 0;
  timeout2 = 0;
  player = Paddle(false, &matrix);
  cpu = Paddle(true, &matrix);
  ball = Ball(&matrix);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  // pinMode(TRIG, OUTPUT);
  // pinMode(ECHO, INPUT);
  // Serial.begin(9600);
  // lcd.begin(SSD1306_SWITCHCAPVCC, 0x3C);
//  lcd.clearDisplay();
//  lcd.setTextColor(WHITE);
//  lcd.setTextSize(2);
//  lcd.display();
}

void runPong() {
  // put your main code here, to run repeatedly:
    if (timeout < millis()){
      matrix.clear();
      player.show_paddle();
      cpu.show_paddle();
      if (!ball.isSetup()){
        ball.setup_move(7, 8, 9);
      }
      // ball.move();
      // ball.check_collision(player, cpu);
      int pos = ball.getY();
      if (pos == 0 || pos == 15){
        game_over(pos);
      }else{
        player.move(sonar.ping_cm());
        if ((ball.getY() % 2 == 0) && ball.getY() >= 8 && ball.getGrady() > 0){
          cpu.move(ball.getEnd());
        }
//        lcd.clearDisplay();
//        lcd.setCursor(0, 0);
//        lcd.print(sonar.ping_cm());
//        lcd.display();
        // Serial.write(sonar.ping_cm());
        ball.move();
        ball.check_collision(player, cpu);
      }
      timeout = millis() + 100;
    }
}

void show_score(int score){
  for(int i = 6; i < 15; i++){
    for (int j = 12; j < 14; j++){
      matrix.drawPixel(i, j, matrix.Color(0, 0, 0));
    }
  }
  if(score/10 > 0){
    for (int i = 0; i < score/10; i++){
      matrix.drawPixel(6+i, 2, matrix.Color(255, 0, 255));
    }
  }
  for (int i = 0; i < score%10; i++){
    if (i <= 5){
      matrix.drawPixel(6+i, 2+1, matrix.Color(255, 255, 0));
    }else{
      matrix.drawPixel(6+i, 2+2, matrix.Color(255, 255, 0));
    }
  }
}

void game_over(int pos){
  boolean pressed = false;
  show_score(ball.get_score());
  if (pos == 0){
    for (int i = 6; i < 10; i++){
      for (int j = 6; j < 10; j++){
        matrix.drawPixel(i, j, matrix.Color(0, 255, 0));
        matrix.show();
      }
    }
  }else{
    for (int i = 6; i < 10; i++){
      for (int j = 6; j < 10; j++){
        matrix.drawPixel(i, j, matrix.Color(255, 0, 0));
        matrix.show();
      }
    }
  }
  
  while(!pressed){
      if (timeout < millis()){
        if (!digitalRead(8)){
          pressed = true;
          setup();
        }
        timeout = millis() + 100;
      }
  }
}

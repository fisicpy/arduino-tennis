#include <GyverOLED.h>
GyverOLED<SSD1306_128x64> oled(0x3C);

byte BallX = 4, BallY = 11;
int BallSpeedX = 1, BallSpeedY = 1;
byte PlayerX = 64, PlayerScore = 0;
#define BallSize 4
#define PlayerSpeed 3
#define PlayerSize 20
#define btn_right_pin 9
#define btn_left_pin 10

void setup() {
  oled.init();
  Wire.setClock(400000L);
  pinMode(btn_right_pin, INPUT_PULLUP);
  pinMode(btn_left_pin, INPUT_PULLUP);
}

void loop() {
  while(true) {
    oled.clear();
    bool btn_right_read = !digitalRead(btn_right_pin);
    bool btn_left_read = !digitalRead(btn_left_pin);
    
    BallX = constrain(BallX + BallSpeedX, 1, 127);
    BallY = constrain(BallY + BallSpeedY, 10, 62);
    
    if (BallX >= 127 - BallSize || BallX == 1) BallSpeedX = -BallSpeedX;
    if (BallY >= 62 - BallSize || BallY == 10) BallSpeedY = -BallSpeedY;
  
    if (btn_right_read == 1) PlayerX = constrain(PlayerX + PlayerSpeed, 3, 125 - PlayerSize);
    if (btn_left_read == 1) PlayerX = constrain(PlayerX - PlayerSpeed, 3, 125 - PlayerSize);
  
    if (PlayerScore == 100) {
      oled.clear();
      oled.setScale(2);
      oled.setCursorXY(17, 10);
      oled.print(F("YOU WIN!"));
      oled.update();
      PlayerScore = 0;
      delay(800);
      BallX = 4, BallY = 11;
      BallSpeedX = 1;
      BallSpeedY = 1;
      PlayerX = 64;
      PlayerScore = 0;
      continue;
    }
    
    if (PlayerX - 5 < BallX & BallX < PlayerX + 24 & BallY == 55) {
        BallSpeedX = BallSpeedX;
        BallSpeedY = -BallSpeedY;
        PlayerScore++;
        if (PlayerScore == 20){
          if (BallSpeedX < 0) {
            BallSpeedX--;
          } else {
            BallSpeedX++;
          }
          if (BallSpeedY < 0) {
            BallSpeedY--;
          } else {
            BallSpeedY++;
          }
        }
        if (PlayerScore == 80){
          if (BallSpeedX < 0) {
            BallSpeedX--;
          } else {
            BallSpeedX++;
          }
          if (BallSpeedY < 0) {
            BallSpeedY--;
          } else {
            BallSpeedY++;
          }
        }
    }
    
    if (BallY > 57) {
      oled.clear();
      oled.setScale(2);
      oled.setCursorXY(17, 10);
      oled.print(F("YOU LOSE!"));
      oled.update();
      PlayerScore = 0;
      delay(800);
      BallX = 4, BallY = 11;
      BallSpeedX = 1;
      BallSpeedY = 1;
      PlayerX = 64;
      PlayerScore = 0;
      continue;
    }
  
    oled.home();
    oled.setScale(1);
    oled.print(F("score: "));
    oled.print(PlayerScore);
    oled.print(F(" speed: "));
    oled.print(abs(BallSpeedX));
    oled.line(0, 10, 127, 10);
    oled.line(0, 63, 127, 63);
    oled.line(0, 10, 0, 127);
    oled.line(127, 10, 127, 63);
    oled.rect(BallX, BallY, BallX + BallSize, BallY + BallSize);
    oled.rect(PlayerX, 59, PlayerX + PlayerSize, 60);
    
    oled.update();
  }
}

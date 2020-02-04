#include <LedControl.h>

int LEDR = 12;
int LEDG = 13;
int ObstaclePin = 11;
// int ObstaclePin2 = 7;
int DIN = 8;
int CS =  9;
int CLK = 10;

int Obstacle = HIGH;
int Obstacle2 = HIGH;



byte zero[8] = {0x00,0x3C,0x24,0x24,0x24,0x24,0x24,0x3C};
byte un[8] = {0x00,0x08,0x18,0x28,0x08,0x08,0x08,0x08};
byte deux[8] = {0x00,0x3C,0x04,0x04,0x3C,0x20,0x20,0x3C};
byte trois[8] = {0x00,0x3C,0x04,0x04,0x1C,0x04,0x04,0x3C};
byte quatre[8] = {0x00,0x24,0x24,0x24,0x3C,0x04,0x04,0x04};
byte cinq[8] = {0x00,0x3C,0x20,0x20,0x3C,0x04,0x04,0x3C};
byte six[8] = {0x00,0x3C,0x20,0x20,0x3C,0x24,0x24,0x3C};
byte sept[8] = {0x00,0x3C,0x04,0x04,0x04,0x04,0x04,0x04};
byte huit[8] = {0x00,0x3C,0x24,0x24,0x3C,0x24,0x24,0x3C};
byte neuf[8] = {0x00,0x3C,0x24,0x24,0x3C,0x04,0x04,0x3C};
byte dix[8] = {0x00,0x2F,0x69,0xA9,0x29,0x29,0x29,0x2F};


LedControl lc=LedControl(DIN,CLK,CS,0);

int score = 0;
int state = 0;

void setup(){
  lc.shutdown(0,false);       //The MAX72XX is in power-saving mode on startup
  lc.setIntensity(0,1);      // Set the brightness to maximum value
  lc.clearDisplay(0);         // and clear the display
 
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(ObstaclePin, INPUT);
  //pinMode(ObstaclePin2, INPUT);

  
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop(){  
  Obstacle = digitalRead(ObstaclePin);
  // Obstacle2 = digitalRead(ObstaclePin2);

  if (Obstacle == LOW){
    Serial.println("Attention un Obstacle");
    digitalWrite(LEDR, HIGH);
    digitalWrite(LEDG, LOW);
     if (state == 0){
        score ++;
        state = 1;
        if(score > 10){
          score = 0;
        }
     } else {
          state = 1;
     }
  } else {
    Serial.println("clear");
    digitalWrite(LEDR, LOW);
    digitalWrite(LEDG, HIGH);
    state = 0;
  }
  

  printByte(convertScore(score));
}

void printByte(byte character [])
{
  int i = 0;
  for(i=0;i<8;i++)
  {
    lc.setRow(0,i,character[i]);
  }
}

byte *convertScore(int score){
  switch (score) {
  case 0:
      return zero;
    break;
  case 1:
    return un;
    break;
  case 2:
    return deux;
    break;
    case 3:
    return trois;
    break;
    case 4:
    return quatre;
    break;
    case 5:
    return cinq;
    break;
    case 6:
    return six;
    break;
    case 7:
    return sept;
    break;
    case 8:
    return huit;
    case 9:
    return neuf;
    break;
    case 10:
    return dix;
    break;
  default:
    return zero;
    break;
  }
}

#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h>

int LB = 4;
int RB = 5;
volatile bool direction = 0;
volatile bool buttonFlag = 0;
int currentPin = 0;
bool endgame = 0;
bool endgameSongPlayed = 0;
int buttonPressed = 0;

AsyncDelay cooldown;
AsyncDelay sensorCooldown;


int volume = 0;

int pinState[10][2]{
  {0,0},
  {1,0},
  {2,0},
  {3,0},
  {4,0},
  {5,0},
  {6,0},
  {7,0},
  {8,0},
  {9,0},
};

int winSong[12][2]{
  {261.63,100},
  {261.63,100},
  {261.63,100},
  {261.63,300},
  {329.63,100},
  {329.63,100},
  {329.63,100},
  {329.63,300},
  {392,100},
  {392,100},
  {392,100},
  {523.25,600},
};

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
  attachInterrupt(digitalPinToInterrupt(LB), ButtonL, RISING);
  attachInterrupt(digitalPinToInterrupt(RB), ButtonR, RISING);
  cooldown.start(500, AsyncDelay::MILLIS);
  sensorCooldown.start(1000, AsyncDelay::MILLIS);
}

void loop() {
  while(endgame == 0){
    if(sensorCooldown.isExpired()){
      volume = CircuitPlayground.mic.soundPressureLevel(1000);
      volume = map(volume, 0, 1023, 0, 150);
      sensorCooldown.repeat();
    }
    puzzleclockwise(volume, pinState);
  }
  if(endgame == 1 && endgameSongPlayed == 0){
    playPhrase(winSong, 12);
    CircuitPlayground.clearPixels();
    endgameSongPlayed = 1;
  }
}

void puzzleclockwise(int volume, int pinState[][2]){
  for(int j = 0; j < 10; j++){
    int currentPin = pinState[j][0];
    int currentPinState = pinState[j][1];
    Serial.println(currentPin);
    Serial.println(currentPinState);
    Serial.println(buttonFlag);
    CircuitPlayground.setPixelColor(currentPin, 255, 0, 0);//set color

    if(buttonFlag == 1){
      if(cooldown.isExpired()){
        buttonPressed = 1;
        buttonFlag = 0;
        cooldown.repeat();
      }else{
        buttonFlag = 0;
      }
    }

    if(buttonPressed){   
      currentPinState = !currentPinState;
      buttonPressed = 0;
      if(currentPinState == 0){
        CircuitPlayground.playTone(207.65,50);
      }
      if(currentPinState == 1){
        CircuitPlayground.playTone(329.63,50);
      }
    }

    pinState[j][1] = currentPinState; //change the state (problem?)

    delay(50+volume);//light up for this long

    if(currentPinState == 0){ //check if the light is in closed state or open state and react
      CircuitPlayground.setPixelColor(currentPin, 0, 0, 0);
    }
    else{
      CircuitPlayground.setPixelColor(currentPin, 255, 255, 255);
    }

    delay(50+volume);
  }
}

void ButtonL(){
  direction = !direction;
}

void ButtonR(){
  buttonFlag= 1;
}

void playPhrase(int a[][2], int size)
{
    // Step through 2D array, setting 
    for(int i = 0; i < size; i++) // Calculate how many rows are in the array using: sizeof(song) / sizeof(song[0])
    {
      CircuitPlayground.playTone(a[i][0], a[i][1]);
      Serial.println(a[i][0]);
      delay(1);
    }
}
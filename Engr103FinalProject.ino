#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h>

//set up the button
int RB = 5;
volatile bool buttonFlag = 0;

int currentPin = 0; //used to tell where the scanning LED is at
bool endgame = 0; //check if the game has ended
bool endgameSongPlayed = 0; //check if the endgame animation/song is finished
int count = 0; //use to check the pin state of each pins
int accumulatedScore = 0; //check if all pins are turned on

AsyncDelay cooldown; //the cooldown between each press of the button
AsyncDelay sensorCooldown; //check the sensor after this interval

int volume = 0;

int pinState[10][2]{ //the storage space for the state of each pin. {pin number, pin state(on/off)}
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

int winSong[12][2]{ //the music played when the game ends
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

void setup(){
  Serial.begin(9600);
  CircuitPlayground.begin();
  attachInterrupt(digitalPinToInterrupt(RB), ButtonR, RISING); //set up interrupt for right button
  cooldown.start(1300, AsyncDelay::MILLIS); //start the timers
  sensorCooldown.start(100, AsyncDelay::MILLIS);
}

void loop(){
  if(sensorCooldown.isExpired()){ //detect and map the volume
    volume = CircuitPlayground.soundSensor(); 
    volume = map(volume, -1023, 1023, 0, 200); 
    sensorCooldown.repeat();
  }
  
  if(endgame == 0){ //if the game is still going, let the game keep going
    puzzleclockwise(volume, pinState);
  }

  if(endgame == 1 && endgameSongPlayed == 0){ //if the game has ended and endgame song hasn't been played, play it and game over
    playPhrase(winSong, 12);
    CircuitPlayground.clearPixels();
    endgameSongPlayed = 1;
  }

  accumulatedScore = 0; //count the score by checking the pinState array. store the score in accumulated Score
  for(int i = 0; i < 10; i++){
    count = pinState[i][1];
    accumulatedScore = accumulatedScore + count;
  }


  if(accumulatedScore == 10){ //if all 10 LEDs are turned on, set endgame signal
    endgame = 1;
  }

  //Serial.println(accumulatedScore); //testing line
}

void puzzleclockwise(int volume, int pinState[][2]){ //main game function
  for(int j = 0; j < 10; j++){ //run through all 10 LEDs by reading the Pin number in PinState array
    int currentPin = pinState[j][0];
    int currentPinState = pinState[j][1]; //use a variable to store the pinState temporarily
    CircuitPlayground.setPixelColor(currentPin, 255, 0, 0); //set color

    if(buttonFlag == 1){ //when button is off cooldown and pressed, check if the player turned the light on or off
      if(cooldown.isExpired()){ 
        currentPinState = !currentPinState;
          if(currentPinState == 0){ //turned it off: play failure sound
            CircuitPlayground.playTone(107.65,25);
          }
          if(currentPinState == 1){ //turned it on: play success sound
            CircuitPlayground.playTone(329.63,25);
          }
        cooldown.repeat();
        buttonFlag = 0;
      }
    }

    /*if(!cooldown.isExpired()){ //test if the cooldown works
      Serial.println("yes");
    }
    if(cooldown.isExpired()){
      Serial.println("no");
    }*/

    pinState[j][1] = currentPinState; //change the state of the pin in the storage array

    delay(20 + volume); //light up for this long

    if(currentPinState == 0){ //check if the light is in closed state or open state right now and set it to the corresponding color
      CircuitPlayground.setPixelColor(currentPin, 0, 0, 0);
    }
    else{
      CircuitPlayground.setPixelColor(currentPin, 255, 255, 255);
    }

    delay(20 + volume);

    //Serial.println(currentPin); //test lines
    //Serial.println(currentPinState);
    //Serial.println(buttonFlag);
    Serial.println(volume);
  }
}

void ButtonR(){ //ISR for button
  buttonFlag= 1;
}

void playPhrase(int a[][2], int size){ // Step through 2D array and play {note, duration}
  for(int i = 0; i < size; i++){
    CircuitPlayground.playTone(a[i][0], a[i][1]); 
    Serial.println(a[i][0]);
    delay(1);
  }
}
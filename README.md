# ENGR103Final

# Author
  Gordon Shum
  
# What it does
  Normally, all the LED will be closed. Each LED will start popping out as red in one direction quickly. Pressing the right button will turn on the LED that’s red. The speed of the lights is very quick, but the player can scream and slow down the LED. If the right button is pressed mistakenly when the LED is already on, it will turn back off.

The goal is to turn all the LEDs on. When all the LEDs are turned on, a winning tune will play.

# Inputs and Outputs
Input: 

Button right: when pressed, turn off the current LED, or turn it back on if it’s off

Sound: use a sound sensor to detect the sound of the user screaming. Map it from 0 to 1023 to a range of 0 to 500. The louder the sound, the slower the LED flows. 


Output:

The LED getting turned on and off

A sound will be played if the LED is successfully turned on, another sound will be played if the LED get mistakenly turned back off

A tune will be played if the LED is all turned off


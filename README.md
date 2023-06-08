# ENGR103Final

# Author
  Gordon Shum
  
# What it does
  Normally, all the LED will be closed. A red dot will scan through the LEDs in one direction quickly. Pressing the right button will turn on the LED that the red scanner is on. The speed of the lights is very quick, but the player can scream and make noises to slow down the LED. If the right button is pressed mistakenly when the LED is already on, it will turn back off.
  There is also a cooldown for the button which avoids player press non stop and win too easily. 

The goal is to turn all the LEDs on. When all the LEDs are turned on, a winning tune will play.

# Instruction


# Inputs and Outputs
Input: 

Button right: when pressed, turn off the current LED, or turn it back on if it’s off

Sound: use a sound sensor to detect the sound of the user screaming. Map it from -1023 to 1023 to a range of 0 to 200. The louder the sound, the slower the LED flows. 


Output:

The LED getting turned on and off

A sound will be played if the LED is successfully turned on, another sound will be played if the LED get mistakenly turned back off

A tune will be played if the LED is all turned off


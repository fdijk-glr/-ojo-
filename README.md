

# ¡ojo!



Hi! I'm ¡ojo!, your animatronic companion. 





# Programming guide



I, ¡ojo!, run on a XIAO esp32c3 microcontroller which can be programmed to do what you want. I have 2 servo motors to controll my eyeball and eyelids. With my LED i can express emotions and moods.



## Getting things ready



First we need to install the Arduino IDE and setup the board manager. To be able to find the board we need to add the following link to the Additional board URLs in the preferences.

```

https:jihulab.comesp-mirrorespressifarduino-esp32.git

```

Once my board can be found we can install my controller in the Board manager. Search for esp32 by Expressif systems. 

Or follow the official setup guide below

https:wiki.seeedstudio.comXIAO_ESP32C3_Getting_Started 



**Be carefull my code wont work with the newest version, so we install version 2.0.17**





The code in the ojo folder is prepared to make programming my actions easier. It uses 2 libraries, one customised  included and one needs to be installed.

In the Library manager, install the Adafruit Neopixel library (latest version).

After this install i am ready to perform my first show!



## Using the code

You only need to work in the .ino file. Which is the main program that uses everything else. Here we have 2 basic blocks of code. The setup() is run at the startup of the controller and can be used once. The loop() will be repeated until you turn me off.



Inside the loop() is where the magic happens. This is the place to create fun animations. The provided code contains a couple of lines to help you start. And moves the animations to the CustomAnimations() function.



The CumstomAnimations() function has a state switch. This makes it possible to go from animation to animation.



## Eye functions

Most function to program my moves have multiple variants. So you can customize the animation a little bit. You can replace the values inside the brackets ***(...)*** to change the values of the function.

### eye.moveEye(...)

moveEye moves my eyeball left or right to the value that is given. 

```

eye.moveEye(side){

&nbsp;	moves at maximum speed

}

eye.moveEye(side, time){

&nbsp;	moves over time in ms

}

```



| Left| Center | Right|

| ----------- | ----------- | ----------- |

| 0| 500 | 1000|

### eye.openEye(...)

openEye opens my eyelids to the value that is given. 

```

eye.openEye(spread){

&nbsp;	opens at maximum speed

}

eye.openEye(spread, time){

&nbsp;	opens over time in ms

}

```



| Open| Center | Closed|

| ----------- | ----------- | ----------- |

| 0| 500 | 1000|

### eye.setEye(...)

setEye moves my eyeball left or right **and** opens my eyelids to the values that are given. 

```

eye.setEye(side){

&nbsp;	moves and opens at maximum speed

}

eye.setEye(side, time){

&nbsp;	moves and opens over time in ms

}

```



| Left| Center | Right|

| ----------- | ----------- | ----------- |

| 0| 500 | 1000|



| Open| Center | Closed|

| ----------- | ----------- | ----------- |

| 0| 500 | 1000|




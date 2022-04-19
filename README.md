# THEIF DETECTOR


## 1 – Embedded System Proposal
>input

* active/deactive button is at PA0
* Buzzer mute button is at PA1
* PIR sensor at pin PA3

>output

* Buzzer attach to pin PB3
* Run mode indication led attach to PB1
* Alert led attach to PB0

>function

* Run Mode/Idle Mode is activate and de-activate by pressing active/deactive button
* At RunMode
	* when human detect PIR sensor send high signal to microcontroller for 5 second and alert led and buzzer will start toggle for 500ms
	* you can adjust the PIR sensor alert timing by adjusting the potentiometer on PIR sensor attached.
	* when alert is activate by pressing mute button it will silent the buzzer and alert indicate by alert led only
* At IdleMode
	* do nothing and turn off all the sensor and led 
	
## 2 – Hardware Design

### list of Hardware Used 
* stm32f103c8(bluepill)[pinout:https://circuitdigest.com/microcontroller-projects/getting-started-with-stm32-blue-pill-development-board-stm32f103c8-using-arduino-ide]
* PIR sensor (datasheet:https://components101.com/sites/default/files/component_datasheet/HC%20SR501%20PIR%20Sensor%20Datasheet.pdf)
* buzzer (https://components101.com/misc/buzzer-pinout-working-datasheet) 
* resistors 
* push button 
* leds
* Transistor

## 3 – Embedded Code Implementation and Architecture

>	In the coding side we use traditional super-loop coding style in which activate/deactivate button is attached to hardware interrupt and remaining buzzer mute button and sensor signal reading In polling. 

>We have a list of individual task in our software system such as
	--Getting status of activate/deactivate button 
	--Getting status of buzzerMute button 
	--Getting motion sensor status 

>	We set priority highest to activate/deactivate button and give them a hardware interrupt when it pressed system goes to run mode and when it pressed it again system get back to idle mode but there is a constraint we did not entertain button debouncing because in interrupt routine timer won’t work so delay is not possible.

>All  the C++ source code is for handling the system is written by us with name as main.c
	As we earlier discuss the issue for button debouncing in activate button is not entertaining we improve our system by using timer routing master ticking input monitoring system for debouncing issue so we can set 100ms master tick and count for how many tick button is pressed and set debounce accordingly, we didn’t use and deep sleep mode  because we want to stay live our module so it capture every live thief moment.

## 4 – Evaluation
> Our working implementation is successfully worked fine but sometime motion sensor take false reading as we use the cheaper module 
> so this one is not that accurate rest our system is working great for future amendment button debouncing 
> may entertatin and we can add relay and connected light or some bigger alert buzzer as well.
s # gangasanim-coursework
# ThiefDetector-

// Username = gangasanim
// SID = 11442727



#include <Arduino.h>

//defines
#define Activate_pin     PA0
#define MuteButton_pin   PA1
#define MotionSensor_pin PA3
#define Runled_pin       PB1
#define Alertled_pin     PB0
#define Buzzer_pin       PB3

#define Alert_interval 500 //500 ms


//protyping 
bool read_mute_button();
void ISR();
void Alert();


//global variable
bool activate_state = false;
bool buzzer_active = true;
unsigned long preTime = 0;

void setup() {
  // initialize digital IO PIN
  pinMode(Runled_pin, OUTPUT);
  pinMode(Alertled_pin, OUTPUT);
  pinMode(Buzzer_pin, OUTPUT);
  
  pinMode(MotionSensor_pin, INPUT_PULLUP);
  pinMode(Activate_pin, INPUT_PULLUP);
  pinMode(MuteButton_pin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(Activate_pin), ISR, CHANGE );

}

// the loop function runs over and over again forever
void loop() {
  
 
  while(activate_state){
      digitalWrite (Runled_pin, HIGH);   //turn on Runled to indicate system is in running mode
      bool humanDetect = digitalRead(MotionSensor_pin);
      
      if(humanDetect ==  true){
        Alert();
      } 
  }

  //turn off all the device at normal state 
  digitalWrite (Runled_pin, LOW); //turn off Runled 
  digitalWrite(Alertled_pin,LOW); //turn off Alertled_pin 
  digitalWrite(Buzzer_pin,LOW);   //turn off Buzzer_pin 
  
}


void ISR() {
  if(!digitalRead(Activate_pin)){
    activate_state = !activate_state;
  }
}


void Alert(){
  unsigned long PostTime;
  int i = 0; //for complete on/off
  while(i!=2){// when ever 1 complete state of on and off done it get out of the loop
    PostTime= millis();
    if((PostTime - preTime)>Alert_interval){ // toggle led and buzzer pin on alert_interval
      preTime = PostTime;
      
      if(i==0){
        digitalWrite(Alertled_pin, HIGH);       // turn on the AlertLED 
        if(buzzer_active){//buzzer only work when it is in activate mode
          digitalWrite(Buzzer_pin, HIGH);         // turn on the Buzzer on  
        }
      }

      if(i==1){
        digitalWrite(Alertled_pin, LOW);       // turn Off the AlertLED 
        if(buzzer_active){//buzzer only work when it is in activate mode
          digitalWrite(Buzzer_pin, LOW);         // turn off the Buzzer on  
        }
      }
      
      i++; 
    }

    if(read_mute_button()){
        buzzer_active = !buzzer_active;
        digitalWrite(Buzzer_pin, LOW);         // initialize to low state
    }
  }
}


bool read_mute_button(){
  bool dirty = false;
  dirty = !digitalRead(MuteButton_pin);

  if(dirty){
    delay(200); //delay for debouncing check
    dirty = !digitalRead(MuteButton_pin); 
    return dirty;
  }
  
  return false;
}

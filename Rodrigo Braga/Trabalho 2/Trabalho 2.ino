//  _ ___ _______     ___ ___ ___  ___ _   _ ___ _____ ___ 
// / |_  )__ /   \   / __|_ _| _ \/ __| | | |_ _|_   _/ __| 
// | |/ / |_ \ |) | | (__ | ||   / (__| |_| || |  | | \__ \ 
// |_/___|___/___/   \___|___|_|_\\___|\___/|___| |_| |___/ 
// 
// The Unnamed Circuit
// 
// Made by rbs758 rbs758
// License: CC-BY-SA 3.0
// Downloaded from: https://circuits.io/circuits/4723703-the-unnamed-circuit

// Button 1 - Reduce speed
// Button 2 - Increase speed
int button1 = 2;
int button2 = 3;

int button1pressed;
int button2pressed;

unsigned long button1time;
unsigned long button2time;

int led = 13 ;
int ledState;

unsigned long time;
unsigned long blinkTime;
int bothButtonPressedTime;


void setup() {  
  pinMode (button1 , INPUT );
  pinMode (button2 , INPUT );
  
  pinMode (led , OUTPUT );
  
  button1pressed = 0;
  button2pressed = 0;
  
  button1time = millis();
  button2time = millis();
  
  ledState = 1;
  
  time = millis();
  blinkTime = 1000;
  bothButtonPressedTime = 0;
  
  Serial.begin(9600); 
}

void loop () {
  	int button1value = !digitalRead(button1);
  	int button2value = !digitalRead(button2);
    if(button1pressed==1){
      	if(button1value==0){
          Serial.print("Button 1 unpressed\n");
          	button1pressed = 0;
          	bothButtonPressedTime = 0;
          	button1time = millis();
      	}
    }else if(button1pressed==0){
    	if(button1value==1 && button1time+200<millis()){
            Serial.print("Button 1 pressed\n");
            blinkTime-=100;
            button1pressed = 1;
          	button1time = 0;
    	}
    }
  	
  	if(button2pressed==1){
      	if(button2value==0){
          Serial.print("Button 2 unpressed\n");
          	button2pressed = 0;
          	bothButtonPressedTime = 0;
          	button2time = millis();
      	}
    }else if(button2pressed==0){
    	if(button2value==1 && button2time+200<millis()){
            Serial.print("Button 2 pressed\n");
            blinkTime+=100;
            button2pressed = 1;
          	button2time = 0;\
    	}
    }
  	if(button1pressed==1 && button2pressed==1){
      	if(bothButtonPressedTime==0){
          	Serial.print("Both pressed, first time\n");
  			bothButtonPressedTime=millis();
      	}
        if(bothButtonPressedTime+500<=millis()){
          	Serial.print("Led Stopped\n");
        	while(1);
        }
    }
  
  	//blink the led
	if(time+blinkTime<=millis()){
      ledState=!ledState;
      time=millis();
      digitalWrite(led, ledState);
    }
}

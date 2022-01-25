#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>

//for OLEd Screen
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64 
#define OLED_RESET -1
Adafruit_SSD1306 display(OLED_RESET);

//input for iR sensor
int irPin=7;
int irPin2=8;
int count=0;
boolean state1 = true;
boolean state2 = true;
boolean insideIr = false;
boolean outsideIr=false;
boolean isPeopleExiting=false;
int i=1;




void setup() {
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  Serial.begin(9600);
  pinMode(irPin, INPUT);
  pinMode(irPin2, INPUT);
}

void process() {
  //process of two IR sensor for count and discount
  //For count process from IR1 to IR2
  if (!digitalRead(irPin) && i==1 && state1){
     outsideIr=true;
     delay(10);
     i++;
     state1 = false;
  }

   if (!digitalRead(irPin2) && i==2 &&   state2){
     outsideIr=true;
     delay(10);
     i = 1 ;
     count++;
     Serial.println("Student inside the room \n");
     Serial.println(count);
     
     state2 = false;
  }

  //for discount process from IR2 to IR1
  if (!digitalRead(irPin2) && i==1 && state2 ){
     outsideIr=true;
     delay(10);
     i = 2 ;
     state2 = false;
  }

  if (!digitalRead(irPin) && i==2 && state1 ){
     outsideIr=true;
     delay(10);
     count--;
       Serial.print("Student inside the room \n");
       Serial.println(count);
     i = 1;
     state1 = false;
  }  
  if (digitalRead(irPin)){
     state1 = true;
    }

     if (digitalRead(irPin2)){
     state2 = true;
     }
}
  



//process for display in 0.96 OLED screen
void OLED_display(){
  display.clearDisplay();
  display.setTextColor(WHITE, BLACK);
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print(count);
  display.display();

}


void loop(){
  process();
  OLED_display();
}

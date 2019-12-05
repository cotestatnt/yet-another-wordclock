//#define DEBUG 1
#ifdef DEBUG
  #define Print(x) Serial.print(x)
  #define Println(x) Serial.println(x)
  #define serialBegin(x) Serial.begin(x)
#else
  #define Print(x)
  #define Println(x)
  #define SerialBegin(x)
#endif

#include <Adafruit_NeoPixel.h>    //https://github.com/adafruit/Adafruit_NeoPixel
#include <RTClib.h>  

#define BUTTON 12
#define LONG          1500   // Tempo "pressione tasto lunga" (Programmazione ON-OFF)
#define MEDIUM        700    // Tempo "pressione tasto media" (Switch tra i parametri in programmazione) 
#define SHORT         100    // Tempo "pressione tasto breve" (Modifica dei parametri)

#define SONO_LE_ORE true
RTC_DS3231 rtc;

//RTC_Millis rtc;

#define LEDS_COUNT 144
#define LEDS_SIDE 12
boolean led_matrix[LEDS_COUNT];  
uint8_t plusMinutes = 0;
uint8_t hour, minute, second, day, month;
uint16_t year;

#define PIXELS_DATA_PIN 6
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(LEDS_COUNT, PIXELS_DATA_PIN, NEO_GRB + NEO_KHZ800);
uint32_t colorOn = pixels.Color(200,150,150);
uint32_t colorOff = pixels.Color(0,0,0);


enum timeUnit {HOUR, MINS, SECS, DAY, MONTH, YEAR};
uint8_t timeUnitIndex;

uint32_t updateTime, pressTime;
bool adjustTime = false;

#include "data_array.h"
#include "led_matrix.h"
#include "led_driver.h"


void setup() {
  pinMode(BUTTON, INPUT_PULLUP);

  SerialBegin(115200);  
  Println("Start WordClock");
  pixels.begin();
  // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one.
  for(int i=0; i<LEDS_COUNT; i++) { // For each pixel...
    pixels.setPixelColor(i, pixels.Color(127, 127,127));
    pixels.show();   // Send the updated pixel colors to the hardware.
    delay(20); // Pause before next pass through loop
  }

  //testAll();
  

  if (! rtc.begin()) {
    Println(F("Couldn't find RTC"));    
  }

  if (rtc.lostPower()) {
    Println(F("RTC lost power, lets set the time!"));  
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

}


void loop() {
  pressTime = millis();
  readButton();

  if(millis() - updateTime > 1000){
    updateTime = millis();  

    if(!adjustTime) {
      DateTime now = rtc.now();
      hour = now.hour();
      minute = now.minute();
      second = now.second();
      day = now.day();
      month = now.month();
      year = now.year();
      setTimeMatrix(hour, minute, second);
      //setTimeMatrix(23, 45, 00);
      display();
    } 
    else    {
      showUnitTime();
    }
     

  }
 
}


void readButton(){
  if(digitalRead(BUTTON) == HIGH){
    delay(SHORT);
    static uint8_t pressType = 0;
    uint32_t pTime;
    while(digitalRead(BUTTON) == HIGH){    
      pTime = millis() - pressTime;
      if(pTime > SHORT  && pTime <= MEDIUM)
        pressType = 1;
      else if (pTime > MEDIUM && pTime <= LONG) {
        reset();
        display();
        pressType = 2;  
      }
       
      else if (pTime > LONG){
        reset();
        display();
        pressType = 3; 
        break;
      }
    }
    switch(pressType){
      case 0: break;
      case 1: shortClick();  break;
      case 2: mediumClick();  break;
      case 3: longClick(); break;
    }
  }  
}

void shortClick(){
  //Serial.println("Short Click");   
  delay(SHORT);
  if(adjustTime){    
    switch (timeUnitIndex) {
      case HOUR: 
        hour = (hour + 1) % 24;
        Print("hours: "); Println(hour);
        break;
      case MINS: 
        minute = (minute + 1) % 60;      
        Print("minutes: "); Println(minute);
        break;
      case SECS: 
        second = (second + 1) % 60;
        Print("seconds: "); Println(second);
        break;
      case DAY: 
        day = (day + 1) % 31;
        Print("day: ");  Println(day);
        break;
      case MONTH: 
        month = (month + 1) % 12;    
        Print("month: "); Println(month);
        break;
      case YEAR:           
        year++;      
        Print("year: "); Println(year);
        break;
    }
    showUnitTime();
  }
}

void mediumClick(){
  //Serial.println("Medium Click");  
  if(adjustTime){  
    timeUnitIndex = (timeUnitIndex + 1)% 6;
    reset();
    display();
  }
}

void longClick(){  
  adjustTime = !adjustTime;
  if(adjustTime){
    Println("Start adjust time");  
    timeUnitIndex = HOUR;
    DateTime now = rtc.now();
    hour = now.hour();
    minute = now.minute();
    second = now.second();
    day = now.day();
    month = now.month();    
    year = 2019;  // Built in november 2019
    reset();
    showUnitTime();    
  }
  else {
    reset();
    display(); 
    Println("Stop adjust time");  
    rtc.adjust(DateTime(year, month, day, hour, minute, second));
  }
  delay(2000);
}


void showUnitTime(){
  switch (timeUnitIndex) {
    case HOUR: 
      setNumberMatrix(hour);
      break;
    case MINS: 
      setNumberMatrix(minute);
      break;
    case SECS: 
      setNumberMatrix(second);
      break;
    case DAY: 
      setNumberMatrix(day);
      break;
    case MONTH: 
      setNumberMatrix(month);
      break;
    case YEAR:           
      setNumberMatrix(year - 2000);      
      break;
  }
  display();
}


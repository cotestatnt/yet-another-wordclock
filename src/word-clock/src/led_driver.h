
void updateLED(int index, boolean isOn) {
  if (isOn) 
    pixels.setPixelColor(index, colorOn); 
  else 
    pixels.setPixelColor(index, colorOff); 
  
}

// Our LEDs matrix is built with an Z pattern, 
// and the LEDs index order follows the following scheme:
// 
// > 0  1  2  3  4  5  6  7  8  9  10 11
//   23 22 21 20 19 18 17 16 15 14 13 12
//   24 25 26 27 28 29 30 31 32 33 34 35
//
// So we need to invert the column order in alternate rows from our logic matrix
void updateLEDs() {
  for (uint8_t i=0; i<LEDS_COUNT; i++) {
    uint8_t row = i / LEDS_SIDE;
    uint8_t ledId;
    if (row % 2 == 0) {
      // -->
      ledId = i;
    } else {
      // <--
      ledId = (row + 1) * LEDS_SIDE - (i - row * LEDS_SIDE) - 1;
    }
    updateLED(ledId, led_matrix[i]);  
  }
}

void logMatrix() {
  for (uint8_t i=0; i<LEDS_COUNT; i++) {
    Print(led_matrix[i] ? "X" : "_"); 
    Print(" ");
    if ((i % LEDS_SIDE) == (LEDS_SIDE-1)) {
      Println();
    }
  }
  Println();
}

void display() {    
  //logMatrix();    
  updateLEDs();
    
  //pixels.setBrightness(ambientBrightness * 255);
  pixels.setBrightness(60);
  pixels.show();    
}






void testAll(){
  reset();
  display();
  delay(1000);
  setTimeMatrix(0, 45, 00);
  display();
  delay(2000);
  setTimeMatrix(1, 15, 00);
  display();
  delay(2000);
  setTimeMatrix(1, 45, 00);
  display();
  delay(2000);
  setTimeMatrix(2, 15, 00);
  display();
  delay(2000);
  setTimeMatrix(2, 45, 00);
  display();
  delay(2000);
  setTimeMatrix(3, 15, 00);
  display();
  delay(2000);
  setTimeMatrix(3, 45, 00);
  display();
  delay(2000);
  setTimeMatrix(4, 15, 00);
  display();
  delay(2000);
  setTimeMatrix(4, 45, 00);
  display();
  delay(2000);
  setTimeMatrix(5, 15, 00);
  display();
  delay(2000);
  setTimeMatrix(5, 45, 00);
  display();
  delay(2000);
   setTimeMatrix(6, 15, 00);
  display();
  delay(2000);
  setTimeMatrix(6, 45, 00);
  display();
  delay(2000);
   setTimeMatrix(7, 15, 00);
  display();
  delay(2000);
  setTimeMatrix(7, 45, 00);
  display();
  delay(2000);
   setTimeMatrix(8, 15, 00);
  display();
  delay(2000);
  setTimeMatrix(8, 45, 00);
  display();
  delay(2000);
  setTimeMatrix(9, 15, 00);
  display();
  delay(2000);
  setTimeMatrix(9, 45, 00);
  display();
  delay(2000);
  setTimeMatrix(10, 15, 00);
  display();
  delay(2000);
  setTimeMatrix(10, 45, 00);
  display();
  delay(2000);
   setTimeMatrix(11, 15, 00);
  display();
  delay(2000);
  setTimeMatrix(11, 45, 00);
  display();
  delay(2000);
   setTimeMatrix(12, 15, 00);
  display();
  delay(2000);
  setTimeMatrix(12, 45, 00);
  display();
  delay(2000);
  setTimeMatrix(13, 15, 00);
  display();
  delay(2000);
  setTimeMatrix(13, 45, 00);
  display();
  delay(2000);
  setTimeMatrix(14, 15, 00);
  display();
  delay(2000);
  setTimeMatrix(14, 45, 00);
  display();
  delay(2000);
  setTimeMatrix(15, 15, 00);
  display();
  delay(2000);
  setTimeMatrix(15, 45, 00);
  display();
  delay(2000);
  setTimeMatrix(16, 15, 00);
  display();  
  delay(2000);
  setTimeMatrix(16, 45, 00);
  display();
  delay(2000);
  setTimeMatrix(17, 15, 00);
  display();
  delay(2000);
  setTimeMatrix(17, 45, 00);
  display();
  delay(2000);
  setTimeMatrix(18, 15, 00);
  display();
  delay(2000);
  setTimeMatrix(18, 45, 00);
  display();
  delay(2000);
  setTimeMatrix(19, 15, 00);
  display();
  delay(2000);
  setTimeMatrix(19, 45, 00);
  display();
  delay(2000);
   setTimeMatrix(20, 15, 00);
  display();
  delay(2000);
  setTimeMatrix(20, 45, 00);
  display();
  delay(2000);
  setTimeMatrix(21, 15, 00);
  display();
  delay(2000);
  setTimeMatrix(21, 45, 00);
  display();
  delay(2000);
   setTimeMatrix(22, 15, 00);
  display();
  delay(2000);
  setTimeMatrix(22, 45, 00);
  display();
  delay(2000);
  setTimeMatrix(23, 15, 00);
  display();
  delay(2000);
  setTimeMatrix(23, 45, 00);
  display();
  delay(2000);
  setTimeMatrix(0, 15, 00);
  display();
  delay(2000);
  setTimeMatrix(0, 45, 00);
  display();
  delay(2000);
  
}

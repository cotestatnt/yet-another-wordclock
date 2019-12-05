void combine(const uint8_t text[3]){
  uint8_t row = pgm_read_byte_near(text);
  uint8_t col = pgm_read_byte_near(text + 1);
  uint8_t len = pgm_read_byte_near(text + 2);  
  for(uint8_t i=0; i<len; i++)
    led_matrix[row*LEDS_SIDE + col + i] = true;

  if (plusMinutes != 5 && plusMinutes > 0){
    for(uint8_t i=0; i< plusMinutes; i++)
      led_matrix[140+i] = true;
  }
}

void reset() {
  for (uint8_t i=0; i<LEDS_COUNT; i++) {
    led_matrix[i] = false;
  }
}

void addPrefix(uint8_t hour, uint8_t minutes) {
  uint8_t displayedHour = hour;
  if (minutes >= 35) 
    displayedHour++;
  displayedHour = displayedHour%12;

  if ((displayedHour == 1 ) || (displayedHour == 12) || (displayedHour == 0 )) {
    combine(E_);  
  } else {
    combine(SONO); 
    combine(LE);  
    if(SONO_LE_ORE)
      combine(ORE);  
  }
}

void addHours(uint8_t hour, uint8_t minutes) {
  uint8_t displayedHour = hour;
  if (minutes >= 35) 
    displayedHour++;
  if (displayedHour == 1 || displayedHour == 13) combine(L_UNA);
  else if (displayedHour == 2 || displayedHour == 14 ) combine(DUE);
  else if (displayedHour == 3 || displayedHour == 15) combine(TRE);
  else if (displayedHour == 4 || displayedHour == 16) combine(QUATTRO);
  else if (displayedHour == 5 || displayedHour == 17) combine(CINQUE);
  else if (displayedHour == 6 || displayedHour == 18) combine(SEI);
  else if (displayedHour == 7 || displayedHour == 19) combine(SETTE);
  else if (displayedHour == 8 || displayedHour == 20) combine(OTTO);
  else if (displayedHour == 9 || displayedHour == 21) combine(NOVE);
  else if (displayedHour == 10 || displayedHour == 22) combine(DIECI);
  else if (displayedHour == 11 || displayedHour == 23) combine(UNDICI);
  else if (displayedHour == 12) combine(MEZZOGIORNO);
  else if (displayedHour == 24 || displayedHour == 0  ) combine(MEZZANOTTE);
}

void addSeparator(uint8_t minutes) {
  if (minutes < 5) 
    return;  
  if (minutes < 35) 
    combine(E);
  else 
    combine(MENO);  
}

void addMinutes(uint8_t minutes) {
  if (minutes < 5) {
    return;
  }
  if (minutes < 10 || minutes >= 55) {  
    combine(M_CINQUE);  
  }
  else if (minutes < 15 || minutes >= 50) {  
    combine(M_DIECI);  
  }
  else if (minutes < 20 || minutes >= 45) {
    combine(UN);
    combine(QUARTO);
  }
  else if (minutes < 25 || minutes >= 40) {
    combine(VENTI);
  }
  else if (minutes < 30 || minutes >= 35) {
    combine(VENTI);
    combine(M_CINQUE);    
  }
  else {
    combine(E);
    combine(MEZZA);  
  }

  plusMinutes = 5 - ((60 - minutes) % 5);
}

String getPrefix(uint8_t h, uint8_t m){
  uint8_t displayedHour = h;
  String txt = "";
  if (m >= 35) 
    displayedHour++;
  displayedHour = displayedHour%12;

  if (displayedHour == 1 ) 
    txt += "E' l'" ;
  else if (displayedHour == 12 || displayedHour == 0 ) 
    txt += "E' " ;
  else {
    txt += "Sono le ";    
    if(SONO_LE_ORE)
      txt += "ore ";
  }
  return txt;
}

String getHour(uint8_t h, uint8_t m) {
  uint8_t displayedHour = h;
  String txt = "";
  if (m >= 35) 
    displayedHour++;
  if (displayedHour == 24 || displayedHour == 0 ) txt = "mezzanotte";
  else if (displayedHour == 1 || displayedHour == 13) txt = "una";
  else if (displayedHour == 2 || displayedHour == 14) txt = "due";
  else if (displayedHour == 3 || displayedHour == 15) txt = "tre";
  else if (displayedHour == 4 || displayedHour == 16) txt = "quattro";
  else if (displayedHour == 5 || displayedHour == 17) txt = "cinque";
  else if (displayedHour == 6 || displayedHour == 18) txt = "sei";
  else if (displayedHour == 7 || displayedHour == 19) txt = "sette";
  else if (displayedHour == 8 || displayedHour == 20) txt = "otto";
  else if (displayedHour == 9 || displayedHour == 21) txt = "nove";
  else if (displayedHour == 10 || displayedHour == 22) txt = "dieci";
  else if (displayedHour == 11 || displayedHour == 23) txt = "undici";
  else if (displayedHour == 12) txt = "mezzogiorno";
  return txt;
}

String getSeparator(uint8_t minutes) {
  if (minutes < 5) {
      return "";
  }
  if (minutes < 35) {
      return " e ";
  }
  return " meno ";
}

String getMinutes(uint8_t minutes) {
  String res;
  if (minutes < 5) {
    res = "";
  }
  else if (minutes < 10 || minutes >= 55) {
    res += "cinque";
  }
  else if (minutes < 15 || minutes >= 50) {
    res += "dieci";  
  }
  else if (minutes < 20 || minutes >= 45) {
    res += "un quarto";
  }
  else if (minutes < 25 || minutes >= 40) {
    res += "venti";
  }
  else if (minutes < 30 || minutes >= 35) {
    res += "venticinque";;    
  }
  else {
    res += "mezza";  
  }

  return res;
}

void setTimeMatrix(uint8_t h, uint8_t m, uint8_t s) {  
  reset();
  addPrefix(h, m);
  addHours(h, m);  
  addSeparator(m);
  addMinutes(m);

// Serial logging
  
  Print(F("Time: ")); Print(h);  Print(F(":")); 
  if(m < 10) Print("0");  
  Print(m);  Print(F(":")); 
  if(s <10) Print("0");  Print(s);
  Println(); 
  String timeString;
  timeString += getPrefix(h, m);
  timeString += getHour(h, m);
  timeString += getSeparator(m);
  timeString += getMinutes(m);  
  Print(timeString);  
  Print(" (+"); Print(plusMinutes); Println(") ");
  

}


void combineNumber( uint8_t row, uint8_t col, uint16_t number){
  #define O_SIDE 3
  #define V_SIDE 5
  uint8_t bit_index = 0;
  uint8_t ccol, crow;

  crow = row;
  for(uint8_t n=0; n<V_SIDE; n++){    
    ccol = col;
    for(uint8_t j=0; j<O_SIDE; j++){      
      led_matrix[crow*LEDS_SIDE + ccol] = bitRead(number, bit_index);
      bit_index++;
     // Print(crow); Print("-"); Print(ccol); Print(" ");
      ccol++;
    }
    // Println();
    crow++;
  }
}



void setNumberMatrix(uint8_t number){
  #define ten_row 5
  #define ten_col 2
  #define unit_row 5
  #define unit_col 6
  uint8_t unit, ten;

  ten = (number / 10) % 10;
  unit = number - (ten*10);

  reset();
  combineNumber(ten_row, ten_col, NUMBERS[ten]);
  combineNumber(unit_row, unit_col, NUMBERS[unit]);
  switch (timeUnitIndex) {
    case HOUR:   
      plusMinutes = 0;        
      combine(ORE);        
      break;
    case MINS: 
      plusMinutes = 1;      
      break;
    case SECS: 
      plusMinutes = 2;
      break;
    case DAY: 
      plusMinutes = 3;
      break;
    case MONTH: 
      plusMinutes = 4;
      break;
    case YEAR:               
      break;
  }   
  combine(_NULL);
}
const uint8_t _NULL[] PROGMEM =    {0, 0, 0};
const uint8_t SONO[] PROGMEM =     {0, 0, 4};      // row, col, lengt
const uint8_t E_[] PROGMEM =       {0, 4, 1};
#ifdef SONO_LE_ORE
    const uint8_t LE[] PROGMEM =       {0, 5, 2};
#else
    const uint8_t LE[] PROGMEM =       {1, 4, 2};
#endif
const uint8_t ORE[] PROGMEM =      {0, 8, 3};

const uint8_t L_UNA[] PROGMEM =    {1, 0, 4};
const uint8_t DUE[] PROGMEM =      {1, 7, 3};
const uint8_t TRE[] PROGMEM =      {2, 0, 3};
const uint8_t QUATTRO[] PROGMEM =  {7, 0, 7};
const uint8_t CINQUE[] PROGMEM =   {4, 5, 6};
const uint8_t SEI[] PROGMEM =      {7, 9, 3};
const uint8_t SETTE[] PROGMEM =    {4, 0, 5};
const uint8_t OTTO[] PROGMEM =     {2, 7, 4};
const uint8_t NOVE[] PROGMEM =     {2, 3, 4};
const uint8_t DIECI[] PROGMEM =    {6, 7, 5};
const uint8_t UNDICI[] PROGMEM =   {6, 0, 6};
const uint8_t MEZZOGIORNO[] PROGMEM =  {3, 0, 11};
const uint8_t MEZZANOTTE[] PROGMEM =   {5, 2, 10};

const uint8_t E[] PROGMEM =          {8, 1, 1};
const uint8_t MENO[] PROGMEM =       {8, 0, 4};
const uint8_t UN[] PROGMEM =         {9, 3, 2};
const uint8_t QUARTO[] PROGMEM =     {9, 6, 6};
const uint8_t VENTI[] PROGMEM =      {10, 0, 5};
const uint8_t M_DIECI[] PROGMEM =    {11, 0, 5};
const uint8_t M_CINQUE[] PROGMEM =   {10, 5, 6};
const uint8_t MEZZA[] PROGMEM =      {8, 7, 5};


/* Numbers 3x5, position is relative to weigth (1, 10)

1:  -   #   -   2:  #   #   #   etc..
    -   #   -       -   -   #
    -   #   -       #   #   #
    -   #   -       #   -   -
    -   #   -       #   #   #

*/
const uint16_t _ZERO =       0b0111101101101111;
const uint16_t _UNO =        0b0010010010010010;
const uint16_t _DUE =        0b0111001111100111;
const uint16_t _TRE =        0b0111100110100111;
const uint16_t _QUATTRO =    0b0100100111010100;
const uint16_t _CINQUE =     0b0111100111001111;
const uint16_t _SEI =        0b0111101111001111;
const uint16_t _SETTE =      0b0010010010100111;
const uint16_t _OTTO =       0b0111101111101111;
const uint16_t _NOVE =       0b0111100111101111;
const uint16_t NUMBERS[] {_ZERO, _UNO, _DUE, _TRE, _QUATTRO, _CINQUE, _SEI, _SETTE, _OTTO, _NOVE};


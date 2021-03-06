#include <YAMorseRx.h>
YAMorseRx MORSE = YAMorseRx();

// the prosign 'as'  will be decoded as 'EB'
// the prosign 'bk'  will be decoded as 'BK'
// the prosign 'sk'  will be decoded as 'SK'
// the prosign 'sos' will be decoded as 'V7'
// the prosign 'kn'  will be decoded as 'TP'
//
// you can transmit any prosign writing them using lowcase letters.
// For example you can transmit the arbitrary prosign 'fhks' (..-.....-.-...)
// and it will be decoded as 'IBFB' (..-.....-.-...) that is the same sequence
// of signs.

#define dotLength 24    // ms (values from 6ms to 6500ms are allowed)
#define pinRx      2    // you can use any pin

void setup() {
  MORSE.mm_setup(dotLength,pinRx,0,0);
  Serial.begin(57600);
}

void loop() {
  uint8_t buf[8];
  uint8_t buflen = 0;

  MORSE.mm_checkRxPinStatus();
  MORSE.mm_refresh();

  if (MORSE.mm_have_message()){
    MORSE.mm_get_message(buf, &buflen);
    if (buflen>1){                    // prosigns
      Serial.print("(");
      for (uint8_t n=buflen;n>0;n--){ // (!) please read chars in reverse order (!)
        Serial.print(char(buf[n-1])); // (!) from the buffer (!)
      }
      Serial.print(")");
    } else {
      Serial.print(char(buf[0]));     // chars A-Z or 0-9
    }
  }
}

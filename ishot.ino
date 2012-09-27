#include <OneWire.h>

OneWire ds(4);  // on pin 4

void setup(void) {
  // initialize inputs/outputs
  // start serial port
  Serial.begin(9600);
}

void loop(void) {
  byte i;
  byte present = 0;
  byte data[12];
  byte addr[8];

  if ( !ds.search(addr)) {
      Serial.print("");
      ds.reset_search();
      return;
  }

  Serial.print("R=");
  for( i = 8; i>0 ; i--) {
    Serial.print(addr[i],HEX);
    Serial.print(" ");
  }
  Serial.print("Device found: 0x");
  Serial.println(addr[0],HEX);

  ds.reset();
  ds.select(addr);
  ds.write(0x44,1);         // start conversion, with parasite power on at the end

  delay(750);     // maybe 750ms is enough, maybe not

  present = ds.reset();

}

/*

  layout for wiring hardware
  
            5 v
             | <---- red
             |
          {resistor} 4.7 k.ohms
      gr       |
             *      +--------------+
  uc pin *---+------|iButton Reader|
           ^     ^  +--------------+
           |     |      |  blue
      yellow     green  -
                        V
                      ground
*/

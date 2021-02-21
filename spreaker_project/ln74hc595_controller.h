//////////////////////// controller of shift register LN74HC595 //////////////////////////////////


// PIN for shift register for LEDs
#define PIN_SRCLR A0  // pin A0 Arduino Nano Every // pin 16 75HC595
#define PIN_OE A1     // pin A1 Arduino Nano Every // pin 13 75HC595
#define PIN_SRCLK A2  // pin A2 Arduino Nano Every // pin 11 75HC595
#define PIN_RCLK A3   // pin A3 Arduino Nano Every // pin 12 75HC595
#define PIN_SER A4    // pin A4 Arduino Nano Every // pin 14 75HC595

#define show74HC595Console false

int numOfRegisterPins ;

void initPin74hc595(){
  pinMode(PIN_SER, OUTPUT);
  pinMode(PIN_OE, OUTPUT);
  pinMode(PIN_RCLK, OUTPUT);
  pinMode(PIN_SRCLK, OUTPUT);
  pinMode(PIN_SRCLR, OUTPUT);

  digitalWrite(PIN_OE, LOW);
  digitalWrite(PIN_SRCLR, HIGH);
}

// set value recorded in array "registers" and display on the end
void writeRegisters(int numOfLed, bool registers[], int time){
  // Until LOW modification will not be apply
  digitalWrite(PIN_RCLK, LOW);

  // loop for aplly all value for each pin 74hc595
  for (int i = numOfLed -1 ; i >= 0; i--)
  {

    //need to be low for change column soon
    digitalWrite(PIN_SRCLK, LOW);

    // catch value insinde array registers
    int val = registers[i];

    if (show74HC595Console) Serial.print(val);

    //apply the value to a pin of 74hc595
    digitalWrite(PIN_SER, val);
    //colonne suivante
    // next column
    digitalWrite(PIN_SRCLK, HIGH);
  }
  if (show74HC595Console) Serial.println("");

  // apply value to all pin of 74hc595
  digitalWrite(PIN_RCLK, HIGH);

  delay(time);

}

//set all register pins to LOW
void clearRegisters(int numOfLed){
  bool registers[numOfLed] = { false };
    
  for (int i = numOfLed - 1; i >= 0; i--){
    registers[i] = LOW;

    //apply the value to a pin of 74hc595
    digitalWrite(PIN_SER, registers[i]);
    //colonne suivante
    // next column
    digitalWrite(PIN_SRCLK, HIGH);

  }
  writeRegisters(numOfLed, registers, 50);
}

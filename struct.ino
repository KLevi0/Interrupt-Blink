

typedef struct led {
  const uint8_t pin;  // Pinout
  const uint8_t max;  // 1/Hz
  uint8_t counter;
} LED;

//Array
LED leds[] = {
  { 9, 16, 0 },  //RED
  { 8, 30, 0 },  //GREEN
  { 7, 66, 0 },  //BLUE
};


ISR(PCINT2_vect) {
  for (int i = 0; i < (sizeof(leds) / sizeof(led)) - 1; i++) {
    if (leds[i].counter <= leds[i].max) {
      leds[i].counter = leds[i].counter + 1;
    } else {
      leds[i].counter = 0;
      digitalToggle(leds[i].pin);
    }
  }
}


void setup() {
  // put your setup code here, to run once:
  // Serial.begin(115200);
  pinMode(2, INPUT);
  PCMSK2 |= bit(PCINT18);                 // A0
  PCIFR |= bit(PCIF2);                    // clear interrupts
  PCICR |= bit(digitalPinToPCICRbit(2));  // enable pin change interrupts for Analog pins

  for (int i = 0; i < sizeof(leds); i++) {
    pinMode(leds[i].pin, OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}

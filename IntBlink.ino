unsigned long total = 0;

typedef struct led {
  const uint8_t pin;  // Pinout
  const uint8_t max;  // 1/Hz
} LED;

//Array
LED leds[3] = {
  { 9, 16 },   //RED
  { 8, 100 },  //GREEN
  { 7, 66 },   //BLUE
};


ISR(PCINT2_vect) {
  total++;
  for (int i = 0; i < (sizeof(leds) / 2); i++) {
    if (!(total % leds[i].max)) {
      digitalToggle(leds[i].pin);
    }
  }
}


void setup() {
  // put your setup code here, to run once:
  pinMode(2, INPUT);
  PCMSK2 |= bit(PCINT18);                 // D2
  PCIFR |= bit(PCIF2);                    // clear interrupts
  PCICR |= bit(digitalPinToPCICRbit(2));  // enable pin change interrupts for Analog pins

  for (int i = 0; i < sizeof(leds); i++) {
    pinMode(leds[i].pin, OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}

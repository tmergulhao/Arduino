// IO

int outputPort = 11; // ~
int buttonPort = 12;
int gaugerPort = A5;

// LOGICS

void setup() {
  pinMode(outputPort, OUTPUT);
  pinMode(buttonPort,INPUT);
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  static int persistentButtonInput = LOW;
  static bool state = false;
  int gaugerInput = analogRead(gaugerPort);
  int buttonInput = digitalRead(buttonPort);

  if (buttonInput == HIGH && persistentButtonInput == LOW) {
  	state = !state;
    delay(10);
  }

  persistentButtonInput = buttonInput;

  if (itsTime(10)) { // in milliseconds
    if (state) {
      fadeTo(gaugerInput);
    } else {
      fadeTo(0);
    }
  }

}

bool itsTime (long int interval) {
  static unsigned long previousTime = 0;
  unsigned long time = millis();
  if (time - previousTime > interval) {
    previousTime = time;
    return true;
  }
  return false;
}

void fadeTo (int gaugerInput) {
  static int analogOutput = 0;

  if (analogOutput - gaugerInput > 0) {
    analogOutput--;
  } else if (analogOutput - gaugerInput < 0) {
    analogOutput++;
  }

  analogWrite(outputPort, map(analogOutput, 0, 1023, 0, 255));
}

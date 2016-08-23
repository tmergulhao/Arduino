// IO

int outputPort = 11; // ~
int buttonPort = 12;
int gaugerPort = A5;

// LOGICS

int buttonInput = LOW, persistentButtonInput = LOW;
bool state = false;

void setup() {
  pinMode(outputPort, OUTPUT);
  pinMode(buttonPort,INPUT);
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  int gaugerInput = analogRead(gaugerPort);
  int buttonInput = digitalRead(buttonPort);

  if (buttonInput == HIGH && persistentButtonInput == LOW) {
  	state = !state;
    delay(10);
  }

  persistentButtonInput = buttonInput;

  // digitalWrite(outputPort, state ? HIGH : LOW);
  // analogWrite(outputPort, state ? 255 * sensorValue / 1023 : 0); // 0 .. 255
  fadeTo(state, gaugerInput);

  delay(5); // wait 1/4 of a secong
}

//int analogOutput = 0;

void fadeTo (int state, int gaugerInput) {
  static int analogOutput = 0;

  int errorMargin = analogOutput - gaugerInput;

  if (state) {
  	if (errorMargin > 0) {
      analogOutput--;
    } else if (errorMargin < 0) {
      analogOutput++;
    }
  } else {
    if (analogOutput > 0) {
      analogOutput--;
    }
  }

  analogWrite(outputPort, analogOutput * 255 / 1023);
}

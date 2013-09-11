const int button = 3;
const long debounce = 50;

char b;
int previousState = 0;
int state = 0;
long lastBounce = 0;
long lastSent = 0;
String buffer;

void setup() {
  pinMode(button, INPUT);
}

void loop() {
  while (Serial.available()) {
    b = Serial.read();

    buffer += b;

    if (b == '\n') {
      if (buffer == "READ\n") lastSent = 0;

      buffer = "";
    }
  }

  state = digitalRead(button);

  if (state != previousState) {
    lastBounce = millis();
  }

  if (lastBounce > lastSent && (millis() - lastBounce) > debounce) {
    if (state == HIGH) {
      Serial.println("UP");
    } else {
      Serial.println("DOWN");
    }

    lastSent = millis();
  }

  previousState = state;
}

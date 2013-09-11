const int button = 3;
const long debounce = 50;

long lastBounce = 0;
long lastSent = 0;
int state = 0;
int previousState = 0;

void setup() {
  pinMode(button, INPUT);
}

void loop() {
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

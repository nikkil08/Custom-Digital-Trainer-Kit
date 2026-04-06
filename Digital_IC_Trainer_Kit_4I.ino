const int ledPins[] = {11, 10, 9, 8}; 

void setup() {
  Serial.begin(9600);
  
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }
  
  Serial.println("Digital IC Trainer kit Version 1.1");
  Serial.println("Commands: 'test' for auto-cycle, or enter 4-bit BCD");
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    if (input == "test") {
      runAutoTest();
    } 
    else if (input.length() == 4) {
      applyBits(input);
    } else {
      Serial.println("Invalid Input");
    }
  }
}

void applyBits(String bits) {
  for (int i = 0; i < 4; i++) {
    if (bits[i] == '1') {
      digitalWrite(ledPins[i], HIGH);
    } else {
      digitalWrite(ledPins[i], LOW);
    }
  }
  Serial.print("Output: ");
  Serial.println(bits);
}

void runAutoTest() {
  Serial.println("Starting Auto-Test (0-15)...");
  for (int i = 0; i < 16; i++) {
    String binary = "";
    for (int j = 3; j >= 0; j--) {
      int bit = (i >> j) & 1;
      binary += String(bit);
      digitalWrite(ledPins[3-j], bit);
    }
    Serial.print("Testing: ");
    Serial.println(binary);
    delay(1000); 
  }
  Serial.println("Test Complete.");
}
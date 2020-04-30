#include <Arduino.h>
#include <BleKeyboard.h>

BleKeyboard bleKeyboard;

const int switchPin = 32;
const int ledPin = 27;

int currentState = 0;
int beforeState = 0;

boolean isOn = false;

void setup()
{
  Serial.begin(9600);
  pinMode(switchPin, INPUT);
  pinMode(ledPin, OUTPUT);

  bleKeyboard.begin();
}

boolean isChange(int current, int before)
{
  return (current != before) && (current == 1);
}

void loop()
{
  currentState = digitalRead(switchPin);

  if (isChange(currentState, beforeState))
  {
    Serial.println("Change!!!");

    isOn = !isOn;
    digitalWrite(ledPin, isOn);

    if(bleKeyboard.isConnected()) {
      Serial.println("Send!!!");

      bleKeyboard.press(KEY_LEFT_ALT);
      bleKeyboard.press(0x61);
      delay(100);
      bleKeyboard.releaseAll();
      
      Serial.println("Send Complete!!!");
    }
  }

  beforeState = currentState;

  delay(100);
}
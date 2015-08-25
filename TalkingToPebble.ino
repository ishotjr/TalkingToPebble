#include <ArduinoPebbleSerial.h>

// The buffer for transferring data
static uint8_t s_data_buffer[256];

// 0x1hhh = experimental
// see http://developer.getpebble.com/guides/hardware/smartstrap-protocol/#generic-service-profile
static const uint16_t s_service_ids[] = {(uint16_t)0x1001};
static const uint16_t s_attr_ids[] = {(uint16_t)0x1001};

int serialPin = 8;  // for software serial
int ledPin = 13;    // Uno LED

void setup() {
  
  // initialize software serial
  ArduinoPebbleSerial::begin_software(serialPin, s_data_buffer, sizeof(s_data_buffer), Baud57600, s_service_ids, 1);  
  
  // initialize LED pin as output
  pinMode(ledPin, OUTPUT);  
}

void loop() {
  
  // check once per second (hack)
  delay(900);
  // blip LED even if not connected to show we're alive
  digitalWrite(ledPin, HIGH);
  delay(100);
  
  // light LED if connected
  if(ArduinoPebbleSerial::is_connected()) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

}

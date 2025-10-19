#include "BluetoothSerial.h"
String device_name = "ESP32-BT-PANDA";
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Port Profile for Bluetooth is not available or not enabled.
#endif
BluetoothSerial SerialBT;

#define LED_PIN 2   // LED on D2 (GPIO2)
void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);  // Start with LED OFF

  Serial.begin(9600);
  SerialBT.begin(device_name);
  Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str());
  SerialBT.println("ESP32 Bluetooth LED Control Ready!");
}

void loop() {
  if (SerialBT.available()) {
    char incoming = SerialBT.read();   // Read Bluetooth data

    if (incoming == 'h' || incoming == 'H') {
      digitalWrite(LED_PIN, HIGH);
      Serial.println("LED ON");
      SerialBT.println("LED is now ON ✅");
    }
    else if (incoming == 'l' || incoming == 'L') {
      digitalWrite(LED_PIN, LOW);
      Serial.println("LED OFF");
      SerialBT.println("LED is now OFF ❌");
    }
  }

  // Optional: forward Serial <-> BT
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }

  delay(20);
}
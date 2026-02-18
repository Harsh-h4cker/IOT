#define THINGER_SERIAL_DEBUG

#include "DHT.h"

#include <ThingerESP8266.h>
#include "arduino_secrets.h"

#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN,DHTTYPE);


ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

void setup() {
  // open serial for monitoring
  Serial.begin(115200);
  dht.begin();

  // set builtin led as output
  pinMode(LED_BUILTIN, OUTPUT);

  // add WiFi credentials
  thing.add_wifi(SSID, SSID_PASSWORD);
  thing["dht"] >> [](pson &out)
  {
    float t = dht.readTemperature();
    float h = dht.readHumidity();
    
    out["Tempreture"] = t;
    out["Humidity"] = h;
  };
  // digital pin control example (i.e. turning on/off a light, a relay, configuring a parameter, etc)
  thing["led"] << digitalPin(LED_BUILTIN);

  // resource output example (i.e. reading a sensor value)
  //thing["millis"] >> outputValue(millis());

  // more details at http://docs.thinger.io/arduino/
}

void loop() {
  thing.handle();
}
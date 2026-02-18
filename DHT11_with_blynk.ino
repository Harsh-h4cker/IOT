#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE  DHT11
#define BLYNK_TEMPLATE_ID "TMPL3MeZFPKg4"
#define BLYNK_TEMPLATE_NAME "LED CONTROLED"
#define BLYNK_AUTH_TOKEN "NrkySRQ8pNH9yBh8Sy_M11AoH9Dm7uo5"

#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "GSP-STUDENT";
char pass[] = "65@Ssr#b5";

BlynkTimer timer;
DHT dht(DHTPIN,DHTTYPE);
// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
BLYNK_WRITE(V0) //lamp
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  if (pinValue == 0)
  {
    digitalWrite(2, HIGH);
  }
  else
  {
    digitalWrite(2, LOW);
  }
  // process received value
}

BLYNK_WRITE(V1) //fan
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  if (pinValue == 0)
  {
    digitalWrite(16, HIGH);
  }
  else
  {
    digitalWrite(16, LOW);
  }
  // process received value
}


void sensor_data()
{
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  if(isnan(t)||isnan(h))
  {
    Serial.println("failed to read sensor");
  } 
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V2, t);
  Blynk.virtualWrite(V3, h);
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  dht.begin();
  pinMode(2, OUTPUT);
  pinMode(16, OUTPUT);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
  timer.setInterval(1000L, sensor_data);
}

void loop()
{
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
}
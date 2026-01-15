#define BLYNK_TEMPLATE_ID "TMPL3MeZFPKg4"
#define BLYNK_TEMPLATE_NAME "LED CONTROLED"
#define BLYNK_AUTH_TOKEN "PdW9r6GQC_0EZ08E7JiydHaD3qk4HErQ"


/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "GSP-STUDENT";
char pass[] = "65@Ssr#b5";

// This function will be called every time Slider Widget
// in Blynk app writes values to the Virtual Pin V1
BLYNK_WRITE(V0)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  if(pinValue == 0)
  {
    digitalWrite(2, LOW);
  }
  else 
  {
    digitalWrite(2, HIGH);
  }
  // process received value
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);
}

void loop()
{
  Blynk.run();
}
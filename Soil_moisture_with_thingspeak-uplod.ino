#include <Ticker.h>

#define TS_ENABLE_SSL // For HTTPS SSL connection

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include "secrets.h"
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros

char ssid[] = SECRET_SSID;   // your network SSID (name) 
char pass[] = SECRET_PASS;   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClientSecure  client;
Ticker ticker;
unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

// Initialize our values
float soil_moiture;
float sm_precentage;
int pump = 2; //pump is on GPIO 2
int pump_status;
boolean Timer_reached;


void send_data()
{
  Timer_reached=true;
}

// Fingerprint check, make sure that the certificate has not expired.
const char * fingerprint = NULL; // use SECRET_SHA1_FINGERPRINT for fingerprint check

void setup() {
  Serial.begin(115200);  // Initialize serial
  pinMode(pump,OUTPUT);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo native USB port only
  }
  
  WiFi.mode(WIFI_STA); 

  if(fingerprint!=NULL){
    client.setFingerprint(fingerprint);
  }
  else{
    client.setInsecure(); // To perform a simple SSL Encryption
  }
  
  ThingSpeak.begin(client);  // Initialize ThingSpeak
   // Connect or reconnect to WiFi
   if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED)
    {
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }
  Timer_reached = false;
  ticker.attach(15,send_data);
}

void loop() {

 soil_moiture = analogRead(A0);
sm_precentage = map(soil_moiture,0,1023,100,0);

if (sm_precentage <=30)
{
  digitalWrite(pump, LOW);
  Serial.println("soil dry");
  pump_status = 1;
}
else if (sm_precentage > 31 && sm_precentage < 40)
{
   digitalWrite(pump, LOW);
   Serial.println("Soil moisture is optimum");
   pump_status = 1;
}
else if (sm_precentage >= 40)
{
  digitalWrite(pump, HIGH);
  Serial.println("soil moisture is wet");
  pump_status = 0;
}

Serial.print("Soil Moisture= ");
Serial.println(soil_moiture);
Serial.print("Soil Moisture % = ");
Serial.print(sm_precentage);
Serial.println("%");

if(Timer_reached)
 {
  // set the fields with the values
  ThingSpeak.setField(1, sm_precentage);
  ThingSpeak.setField(2, pump_status);


  
  // write to the ThingSpeak channel
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
   Timer_reached =false;
 }
  delay(15000); // Wait 15 seconds to update the channel again
}

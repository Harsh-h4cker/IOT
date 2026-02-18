// DHT data
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE  DHT11
#define BLYNK_TEMPLATE_ID "TMPL3MeZFPKg4"
#define BLYNK_TEMPLATE_NAME "LED CONTROLED"
#define BLYNK_AUTH_TOKEN "NrkySRQ8pNH9yBh8Sy_M11AoH9Dm7uo5"

#define BLYNK_PRINT Serial
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

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
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println("HARSH");
  display.println("YADUWANSHI");
  display.display();
  delay(2000);


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
  // DHT data
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
  
  // Wait for display
  delay(500);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();
}


void loop()
{
 Blynk.run();
 timer.run(); 

}
int trig = 21;
int echo = 20;
float time, cm, inches;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial3.begin(115200);
  Serial.println("Serial Monitor Setup.....");
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  sendToESP("AT+RST", 2000);
  sendToESP("AT+CWMODE=1", 1000);
  sendToESP("AT+CWJAP=\"GSP-STAFF\",\"55r@G5b#\"",8000);
  delay(2000);
  Serial.println("ESP8266 ready");
  sendToESP("AT+CIFSR",2000);

}

void loop() {
  digitalWrite(trig, LOW);
  delayMicroseconds(5);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  time = pulseIn(echo, HIGH);
  cm = 0.0343 * (time/2);  // distance in CM Speed is 0.0343 cm/usec
  inches = cm/2.54;
 

  sendToESP("AT+CIPMUX=0", 2000);
  sendToESP("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80", 1000);
 
 String data = "GET /update?api_key=8RFKQCLTALG3O6N9&field1=" + String(cm)+ "&field2="+ String(inches)
                +"HTTP/1.1\r\nHost: api.thingspeak.com\r\nConnections: close\r\n\r\n"; 

  sendToESP("AT+CIPSEND="+String(data.length()),2000);
  
  sendToESP(data,5000);
  //sendToESP("AT+CIPCLOSE",2000);
  //sendToESP("AT+CIPCLOSE",2000);
  delay(15000);
}

void sendToESP(String command, int delayTime)
{
  Serial3.println(command);
  delay(delayTime);
  while(Serial3.available())
  {
    Serial.write(Serial3.read());  // show response on SM
  }
}
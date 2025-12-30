void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial3.begin(115200);
Serial.println("AT command egin....");
sendtoESP("AT",1000);
sendtoESP("AT+RST",1000);
sendtoESP("AT+CWMODE=1",1000);
sendtoESP("AT+CWJAP=\"GSP-STAFF\",\"55r@G5b#\"",5000);
}

void loop() {
  // put your main code here, to run repeatedly:
int a=random(0,100);
int b=random(200,500);
sendtoESP("AT+CIFSR",2000);
sendtoESP("AT+CIPMUX=0",2000);
sendtoESP("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80",1000);

String url = "GET /update?api_key=TEXNCPTGE11J48VK&field1=" +String(a)+"&field2=" + String(b)+ "HTTP/1.1\r\nHOST:api.thingsspeak.com\r\nConnection: close\r\n\r\n";
int l = url.length(); 
sendtoESP("AT+CIPSEND="+String(l),2000);
sendtoESP(url,5000);
//sendtoESP("AT+CIPCLOSE",2000);
//sendtoESP("AT+CIPCLOSE",2000);

delay(15000);
}


void sendtoESP(String cmd, int delayTime)
{
  Serial3.println(cmd);

  delay(delayTime); 
  while(Serial3.available())
  {
    Serial.write(Serial3.read()) ;  // responds frome ESP
  }
}
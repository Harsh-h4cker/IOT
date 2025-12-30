void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial3.begin(115200);
sendtoESP("AT+RST",2000);
sendtoESP("AT+CWMODE=1",1000);
sendtoESP("AT+CWJAP=\"GSP-STAFF\",\"55r@G5b#\"", 5000);
sendtoESP("AT+CIFSR",2000);
sendtoESP("AT+CIPMUX=1",2000);
sendtoESP("AT+CIPSERVER=1,80",5000);
sendtoESP("AT+CIPSEND=0,30",2000);
}

void loop() {
  int a= random(100-500);
  String data = "Random number =" +String(a);
  // put your main code here, to run repeatedly:
  int connectionID;
  if(Serial3.available())
  {
    if(Serial3.find("+IPD"))
    {
      connectionID= Serial3.read()-48;
      String send = "AT+CIPSEND=" + String(connectionID)+data.length();
      sendtoESP(send,2000);
      sendtoESP(String(a),1000);
      sendtoESP("AT+CIPCLOSE="+ String(connectionID),1000);


     //sendtoESP("AT+CIPSEND=String (connectionID)data.length,30" ,3000);
    }
  } 

//sendtoESP("Hello,Welcome to IOT CLass",3000);
//sendtoESP("AT+CIPCLOSE=0",1000);
//sendtoESP("AT+CIPSERVER=0",2000);
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
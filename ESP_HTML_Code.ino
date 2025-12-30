void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial3.begin(115200);
sendtoESP("AT+RST",2000);
sendtoESP("AT+CWMODE=1",1000);
sendtoESP("AT+CWJAP=\"GSP-STAFF\",\"55r@G5b#\"", 8000);
sendtoESP("AT+CIFSR",2000);
sendtoESP("AT+CIPMUX=1",2000);
sendtoESP("AT+CIPSERVER=1,80",5000);
}

void loop() {
  // put your main code here, to run repeatedly:
  int a = random(100,500);
String data = "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Connection: close\r\n\r\n"
        "<!DOCTYPE html>"
        "<html>"
        "<head>"
        "<meta http-equiv='refresh' content='15'>"
        "<title>GSP_BPL</title>"


        "<style>"
        "body{font-family:Arial;text-align:center;margin-top:50px;}"
        "h1{font-size:32px;color:#EB3B6B;}"
        "p{font-size:24px;color:#1547EB;}"
        "</style>"




        "</head>"
        "<body>"
        "<h1> IoT Lab Data</h1>"
        "<p> Sesnsor value <b>"+String(a)+"</b></p>"
        "<p>This page will auto refresh every 10 sec</p>" 
        "<body>"
        "</html>";

int connectionID;
if (Serial3.available())
{
  if(Serial3.find("+IPD,"))
  {
    connectionID = Serial3.read()+1;
    Serial.print("connectionID: ");
    Serial.print(connectionID);
    Serial.println("Data String length");
    Serial.println(data.length());

    String send = "AT+CIPSEND=" + String(connectionID) + ","+String(data.length());
    //sendToESP("AT+CIPSEND=0,5");
    sendtoESP(send, 2000);
    sendtoESP(data, 2000);
    sendtoESP("AT+CIPCLOSE="+String(connectionID),1000);

  }
}
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
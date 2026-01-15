const int Temppin=A6;
const int Humpin=A7;


void setup() {

  // put your setup code here, to run once:
Serial.begin(9600);
Serial3.begin(115200);
sendtoESP("AT+RST",  2000);
sendtoESP("AT+CWMODE=1", 1000);
sendtoESP("AT+CWJAP=\"GSP-STAFF\",\"55r@G5b#\"", 8000);
sendtoESP("AT+CIFSR" ,2000);
sendtoESP("AT+CIPMUX=1", 5000);
sendtoESP("AT+CIPSERVER=1,80" , 5000);


}

void loop() {
  // put your main code here, to run repeatedly:
float tempearture=temp();
float humidity=Hum();

//Serial.print("Tempearture :");
//Serial.print(tempearture);
//Serial.println("°c");

//Serial.print("Relative Humidity :");
//Serial.print(humidity);
//Serial.println("%RH");
//Serial.println("*****");
//delay(1000);

float Tempearture = temp();
float Humidity = Hum();
String data = "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Connection: close\r\n\r\n"
        "<!DOCTYPE html>"
        "<html>"
        "<head>"
        "<meta http-equiv='refresh' content= '15'>"
        "<title>GSP BHOPAL</title>"
        "<style>"
        "body{font-family:Times New Roman;text-align:center;margin-top:50px;}"
        "h1{font-size:32px;color:#1D03FF}"
        "p{font-size:24px;color:#C90202}"
        "p1{font-size:20px;color:#0795E8}"
        "p2{font-size:20px;color:#00A80E}"
        "</style>"
        "</head>"
        "<body>"
        "<h1> IoT Lab Data</h1>"
        "<p> Tempearture =<b>"+String(Tempearture)+"</b> &deg;C </p>"
        "<p1> Humidity =<b>"+String(Humidity)+"%RH<b></p>"
        "<p2> This page will auto refresh every 15 sec</p1>"
        "</body>"
        "</html>";
int connectionID;
if (Serial3.available()) 
{
  if (Serial3.find("+IPD,")) 
  {
    connectionID = Serial3.read()-'0';
    Serial.print("connection ID: ");
    Serial.println(connectionID);
    Serial.print("Data String length =");
    Serial.println(data.length());

    String send = "AT+CIPSEND="+ String(connectionID) +","+ String(data.length())+"\r\n";
    
    sendtoESP(send, 2000);
    sendtoESP(data, 1000);
    sendtoESP("AT+CIPCLOSE="+ String(connectionID), 1000);
  }
}
}


float temp()
{ 
  float sumTemp = 0;
  for (int i=0; i<10;i++)
  {
  int t =analogRead(Temppin);
  float Temp_voltage=(t)*(5.0/1023);
  float Temp = (2*Temp_voltage -0.5)*100;
  
  sumTemp += Temp;
  delay(50);
  }
  return(sumTemp/10);
}

float Hum()
{
float sumHum = 0;
  for (int i=0; i<10;i++)
  {
  int h =analogRead(Humpin);
  float Hum_voltage= (h)*(5.0/1023);
  float Humi = ((2*Hum_voltage /5.0) -0.16) /0.0062;
  
  sumHum += Humi;
  delay(50);
  }
  return(sumHum/10);
}

void sendtoESP(String cmd,int delayTime)
{
  Serial3.println(cmd);
  delay(delayTime);
  while(Serial3.available())
  {
    Serial.write(Serial3.read()); //response from ESP
  }
}
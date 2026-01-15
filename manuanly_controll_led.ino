int led = 0;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);  //Serial monitor 
pinMode(6,OUTPUT); 
pinMode(12,INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
int button_satus;
button_satus = digitalRead(12);
Serial.print("Button satus :");
Serial.println(button_satus);
if(button_satus == 0) 
{
  led=~led;
  digitalWrite(6,led);
}
delay(999);
}

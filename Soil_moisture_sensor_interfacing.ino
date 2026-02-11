float soil_moiture;
float sm_precentage;
int pump = 2; //pump is on GPIO 2

void setup() {
  // put your setup code here, to run once:
 Serial.begin(115200);
 pinMode(pump,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
soil_moiture = analogRead(A0);
sm_precentage = map(soil_moiture,0,1023,100,0);

Serial.print("Soil Moisture= ");
Serial.println(soil_moiture);
Serial.print("Soil Moisture % = ");
Serial.print(sm_precentage);
Serial.println("%");
delay(1000);

}
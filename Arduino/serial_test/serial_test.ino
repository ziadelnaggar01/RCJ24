void setup() {
Serial3.begin(9600);
Serial.begin(9600);
}

void loop() {
Serial3.println("Hi");
delay(1000);
if(Serial3.available() > 0)
{
  String data = Serial3.readStringUntil('\n');
  Serial.println(data);
}
}

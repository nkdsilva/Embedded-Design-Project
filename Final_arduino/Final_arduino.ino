#include <SoftwareSerial.h>

SoftwareSerial mySerial(9, 5);//tx, rx

void setup() {
  Serial.begin(9600);
  pinMode(10,INPUT);//receiver-mega
  pinMode(7,OUTPUT);//LED
  digitalWrite(7, LOW);

  mySerial.begin(9600);
  delay(1000);
  Serial.println("Preparing to send SMS");
  digitalWrite(7, LOW);

  if ((digitalRead(10))== HIGH)//check arduino pin 10 is high
  {
    digitalWrite(7, HIGH);
    // Serial.println("Done");
    SendMessage();
    Serial.println("Message sent");
  }

  else
  {
    Serial.println("Message received");
  }
}

void loop(){
}

void SendMessage()
{
  Serial.println("Sending Message Detected");
  mySerial.println("AT+CMGF=1"); //Sets the GSM Module in Text Mode
  delay(1000); // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+94702343888\"\r"); // Replace x with mobile number +94
  delay(1000);
  mySerial.println("Someone trying to open the door");// The SMS text you want to send
  delay(100);
  mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}

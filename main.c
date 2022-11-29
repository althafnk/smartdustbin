#include <SoftwareSerial.h> // library for serial communication
#include <Servo.h> // library for servo motor rotating
Servo myservo; // servo motor object
SoftwareSerial gsmSerial(2, 3); // rx,tx // new object for gsm module with rxpin=3 and txpin=2(arduino board)
int pos = 0; // angle of servo motor
//************LID OPENING ULTRASONIC SENSOR PINS **********
#define trigPin1 10
#define echoPin1 11
//************GARBAGE MONITORING ULTRASONIC SENSOR PINS ******
#define trigPin2 5
#define echoPin2 6
long duration1,duration2;
int cnt=0;
float distance1,distance2;
void setup()
{
myservo.attach(9); // attach pin of servo motor
pinMode(trigPin1, OUTPUT);
pinMode(echoPin1, INPUT);
myservo.write(pos);
pinMode(LED_BUILTIN, OUTPUT);
pinMode(trigPin2, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin2, INPUT); // Sets the echoPin as an Input
gsmSerial.begin(9600); // Setting the baud rate of GSM Module
Serial.begin(9600); // Setting the baud rate of Serial Monitor (Arduino)
delay(1000);
Serial.println("Preparing to send SMS");
}
void loop()

{
Serial.begin(9600);
digitalWrite(trigPin1, LOW);
delayMicroseconds(2);
digitalWrite(trigPin1, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin1, LOW);
duration1 = pulseIn(echoPin1, HIGH);
distance1 = 0.034*(duration1/2);
if (distance1 < 20) {
digitalWrite(LED_BUILTIN,HIGH);
myservo.write(180);
delay(5000); // wait for 5s before the bin closes.
myservo.write(pos);
digitalWrite(LED_BUILTIN,LOW);
}
if(cnt<1) {
Sendmessage(); // Function call
delay(300);
}
if(check()>10) {
cnt=0; }
}
void Sendmessage() {
digitalWrite(trigPin2, LOW);
delayMicroseconds(2);
digitalWrite(trigPin2, HIGH);

delayMicroseconds(10);
digitalWrite(trigPin2, LOW);
duration2 = pulseIn(echoPin2, HIGH);
delay(500);
distance2 = 0.034*(duration2/2);
Serial.println(distance2);
if (distance2 < 10)
{
digitalWrite(LED_BUILTIN,LOW);
Serial.println("Setting the GSM in text mode");
gsmSerial.println("AT+CPIN?");
gsmSerial.println("AT+CMGF=1\r");
delay(2000);
Serial.println("Sending SMS to the desired phone number!");
gsmSerial.println("AT+CMGS=\"+918129525926\"\r");
// Replace x with mobile number
delay(2000);
gsmSerial.println("BIN FULL!!!!Ready to collect"); // SMS Text
delay(200);
gsmSerial.println((char)26); // ASCII code of CTRL+Z
delay(2000);
cnt=2;
}
}
int check()
{
digitalWrite(trigPin2, LOW);
delayMicroseconds(2);
digitalWrite(trigPin2, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin2, LOW);
duration2 = pulseIn(echoPin2, HIGH);
delay(500);
distance2 = 0.034*(duration2/2);
return distance2;
}

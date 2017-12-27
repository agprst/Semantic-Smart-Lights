//ULTRASONIC
#include "RestClient.h"

const int trigPin = 12;
const int echoPin = 14;
long duration;
int distance;
String payload;
char wew[200];
String response;

RestClient client = RestClient("192.168.43.81", 4567);

//Setup
void setup() {
  Serial.begin(115200);
  Serial.println("connect to WiFi network");
  client.begin("Redmi", "wewe1234");
  Serial.println("Setup!");

  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  delay(100);
  digitalWrite(2, LOW);
  delay(100);
  digitalWrite(2, HIGH);
  delay(100);
  digitalWrite(2, LOW);
  delay(100);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

}

void loop() {
  
  payload = "{\"sensorId\":\"Ultrasonik2314\",\"quantitykind\":\"distance\",\"unit\":\"centimeter\",\"Deployment\":\"Ruang Garasi\",\"metadataValue\": \"" + String(sensorSensing()) + "\" }";
  payload.toCharArray(wew, 200);
  response = "";
  int statusCode = client.post("/sensor", wew, &response);
  Serial.print("Status code from server: ");
  Serial.println(statusCode);
  Serial.print("Response body from server: ");
  Serial.println(response);
  Serial.println(sensorSensing());
  delay(1000);


}

int sensorSensing () {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.println(distance);
  return distance;
}


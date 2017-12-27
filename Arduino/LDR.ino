
#include "RestClient.h"

const int sensorPin = A0;
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


}

void loop() {
  
  payload = "{\"sensorId\":\"Ldr4132\",\"quantitykind\":\"luminosity\",\"unit\":\"lumen\",\"Deployment\":\"Ruang Garasi\",\"metadataValue\": \"" + String(analogRead(sensorPin)) + "\" }";
  payload.toCharArray(wew, 200);
  response = "";
  int statusCode = client.post("/sensor", wew, &response);
  Serial.print("Status code from server: ");
  Serial.println(statusCode);
  Serial.print("Response body from server: ");
  Serial.println(response);
  Serial.println(analogRead(sensorPin));
  delay(5000);

}




#include "RestClient.h"

int relayPin = 16; 
RestClient client = RestClient("192.168.43.81", 4567);

//Setup
void setup() {
  Serial.begin(115200);
  Serial.println("connect to WiFi network");
  client.begin("Redmi", "wewe1234");
  Serial.println("Setup!");

  pinMode(relayPin, OUTPUT);

}
String payload;
char wew[120];
String response;
void loop(){
  payload = "{\"actuatorId\":\"Relay8742\",\"effect\":\"light\",\"Deployment\":\"Ruang Garasi Area 1\",\"value\":\"OFF\" }";
  payload.toCharArray(wew, 120);
  response = "";
  int statusCode = client.post("/actuator", wew, &response);
  Serial.print("Status code from server: ");
  Serial.println(statusCode);
  Serial.print("Response body from server: ");
  Serial.println(response);
  if(response.indexOf("ON") > 0){
    digitalWrite(relayPin, HIGH);
  }else{
    digitalWrite(relayPin, LOW);
  }
delay(500);
}

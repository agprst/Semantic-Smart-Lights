
#include "RestClient.h"
int calibrationTime = 30;        

long unsigned int lowIn;         

long unsigned int pause = 5000;  

boolean lockLow = true;
boolean takeLowTime;  
String payload;
char payloadChar[200];
String response;

int pirPin = 14;    //the digital pin connected to the PIR sensor's output
int ledPin = 13;

RestClient client = RestClient("192.168.43.81", 4567);

//Setup
void setup() {
  Serial.begin(115200);
  Serial.println("connect to WiFi network");
  client.begin("Redmi", "wewe1234");
  Serial.println("Setup!");

  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(pirPin, LOW);

}


void loop() {
  if(digitalRead(pirPin) == HIGH){
       digitalWrite(ledPin, HIGH);   //the led visualizes the sensors output pin state
       if(lockLow){  
         lockLow = false;            
         Serial.println("---");
         Serial.print("motion detected at ");
         Serial.print(millis()/1000);
         Serial.println(" sec");
         sendData("Detected");
         delay(50);
         }         
         takeLowTime = true;
       }

     if(digitalRead(pirPin) == LOW){
       digitalWrite(ledPin, LOW);

       if(takeLowTime){
        lowIn = millis();
        takeLowTime = false;
        }
       if(!lockLow && millis() - lowIn > pause){  
           lockLow = true;                        
           Serial.print("motion ended at ");
           Serial.print((millis() - pause)/1000);
           Serial.println(" sec");
           sendData("NotDetected");
           delay(50);
           }
       } 
}

void sendData (String data) {
  payload = "{\"sensorId\":\"Pir5421\",\"quantitykind\":\"motion\",\"unit\":\"TrueFalse\",\"Deployment\":\"Ruang Garasi Area 1\",\"metadataValue\": \"" + data + "\" }";
  payload.toCharArray(payloadChar, 200);
  response = "";
  int statusCode = client.post("/sensor", payloadChar, &response);
  Serial.print("Status code from server: ");
  Serial.println(statusCode);
  Serial.print("Response body from server: ");
  Serial.println(response);
}


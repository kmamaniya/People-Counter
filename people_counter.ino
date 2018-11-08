#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
 
const char* ssid = "NYU Gold Street";
const char* password = "goldstreetspace";

void connectWifi(){
    while (WiFi.status() != WL_CONNECTED) {
 
    delay(1000);
    Serial.print("Connecting..");
 
  }
}
 
void setup () {
 
  Serial.begin(115200);
  pinMode(2,INPUT);
  pinMode(5, OUTPUT);
  digitalWrite(2,LOW);
  WiFi.begin(ssid, password);
  connectWifi();
}


void push(){
  
      HTTPClient http;  //Declare an object of class HTTPClient
      http.begin("http://api.pushingbox.com/pushingbox?devid=v1902992F1D22F82");  //Specify request destination
      int httpCode = http.GET();                                                                  //Send the request 
      http.end();   //Close connection 
}
 
void loop() {
  
  digitalWrite(2,LOW);
  int buttonState = digitalRead(2);
  if(buttonState==HIGH){
    digitalWrite(5, HIGH);   // Turn the LED on (Note that LOW is the voltage level
    delay(20);
  }
  // but actually the LED is on; this is because
  // it is active low on the ESP-01)
  else{
        digitalWrite(5, LOW);   // Turn the LED on (Note that LOW is the voltage level
        delay(20);
        if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
            push();
        }
        else{
            connectWifi();
            push();
        } 
     }
}

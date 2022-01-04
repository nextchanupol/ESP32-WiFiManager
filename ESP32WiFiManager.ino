#include <WiFi.h>
#include <WiFiManager.h>
#include <Ticker.h>
Ticker ticker;

#define LED  2
#define SW1  34

void tick(){
  digitalWrite(LED,!digitalRead(LED));
}

void configModeCallback(WiFiManager *myWiFiManager){
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  Serial.println(myWiFiManager->getConfigPortalSSID());
  ticker.attach(0.2, tick);
}

void Wifi_Reset_begin(){
  if(digitalRead(SW1) == LOW) {
    Serial.println("Wifi Reset? Pls. waiting 3S..");
    delay(3000);
    if (digitalRead(SW1) == LOW) {
      delay(10);
      while (digitalRead(SW1) == LOW){
        digitalWrite(LED, HIGH);
        delay(10);
      }
      Serial.println("WiFi Reset Settings....OK!.");
      WiFiManager wm;
      wm.resetSettings(); 
      ESP.restart();  
    }
  }
  
  
}

void setup() {
  pinMode(LED,OUTPUT);
  pinMode(SW1, INPUT_PULLUP);
  
  Serial.begin(9600);  

  ticker.attach(1,tick);
  
  WiFiManager wm;
  wm.setAPCallback(configModeCallback);
  if( !wm.autoConnect("WiFI_ABC_AP") ){
    Serial.println("failed to connect and hit timeout");
    ESP.restart();
    delay(1000);   
  }
  
  ticker.detach();
  digitalWrite(LED, LOW);
  
  delay(100);
  Serial.println("");
  Serial.println("connected...already..WiFi :)");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
 
}

void loop() {
  Wifi_Reset_begin();
  
  delay(1000);
}

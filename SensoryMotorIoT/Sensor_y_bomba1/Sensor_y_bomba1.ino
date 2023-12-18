#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h> //usar si es protocolo http
//#include <WiFiClientSecure.h> //usar si es protocolo https
#define WIFI_SSID "iPhone de Camilo" //Nombre red wifi
#define WIFI_PASSWORD "camilo2023" //Pass red wifi
#include "ThingSpeak.h" 
#define SECRET_CH_ID 2380517     // replace 0000000 with your channel number
#define SECRET_WRITE_APIKEY "DCWZL0XSRF7LGE53"   // replace XYZ with your channel write API Key
#define SECRET_READ_APIKEY_COUNTER "KAXUPO64WYNMEFL2"
#define SECRET_CH_ID_WEATHER_STATION 2380517

// Weather station channel details
unsigned long weatherStationChannelNumber = SECRET_CH_ID_WEATHER_STATION;
unsigned int temperatureFieldNumber = 2;

// Counting channel details
unsigned long counterChannelNumber = SECRET_CH_ID;
const char * myCounterReadAPIKey = SECRET_READ_APIKEY_COUNTER;



unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;
//WiFiClientSecure client;
WiFiClient client;
int sensor = A0;

unsigned int bomba = D4;

int in1 = D4;
int inicio_bomba = millis();
int inicio_sensor = millis();

void setup() {
  pinMode(sensor, INPUT);

  pinMode(bomba,OUTPUT);
  Serial.begin(9600);


  // Conectar a la red WiFi
  Serial.println();
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("Direccion IP: ");
  Serial.println(WiFi.localIP());
  //Desde aca incorpora tus sentencias
  if (WiFi.status() == WL_CONNECTED) {
     
    HTTPClient https;  //Declare an object of class HTTPClient
    //client.setInsecure(); // Ignore SSL certificate errors
  }
  ThingSpeak.begin(client);
}

void loop() {
  if (millis()-inicio_sensor>12000){
    int valor = analogRead(sensor);
    Serial.println(valor);
    int x = ThingSpeak.writeField(myChannelNumber, 1, valor, myWriteAPIKey);
    if(x == 200){
      Serial.println("Channel update successful.");
    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }
    inicio_sensor = millis();
  }
  


  if (millis()-inicio_bomba>3000){
    int statusCode = 0;
  
  // Read in field 4 of the public channel recording the temperature
    int valor_bomba = ThingSpeak.readIntField(weatherStationChannelNumber, temperatureFieldNumber);  

    // Check the status of the read operation to see if it was successful
    statusCode = ThingSpeak.getLastReadStatus();
    if(statusCode == 200){
      if (valor_bomba == 0){
        Serial.println("hola");
        digitalWrite(in1 , LOW);
      }else if(valor_bomba == 1){
        digitalWrite(in1 , HIGH);
      }
      Serial.println("Temperature at MathWorks HQ: " + String(valor_bomba) + " deg F");
      }else{
        Serial.println("Problem reading channel. HTTP error code " + String(statusCode)); 
      }
    inicio_bomba = millis();
  }
}

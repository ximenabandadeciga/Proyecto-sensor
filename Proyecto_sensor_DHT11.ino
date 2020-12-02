//PROYECTO DE SENSOR DE TEMPERATURA 
#include <WiFi.h>
#include <WebServer.h>
#include "DHT.h" //Biblioteca del sensor 
 
#define DHTTYPE DHT11   // Sensor DHT 11

 
const char* ssid = "F2C835";  // El nombre de mi red
const char* password = "L21503736411324";  // Mi clave de wifi
 
WebServer server(80);
 
// El Sensor DHT
uint8_t DHTPin = 4; //Conectar al ping 4 de datos (DATA) del sensor
 
// Inicializar sensor DHT.
DHT dht(DHTPin, DHTTYPE);                
 
float Temperature;// Variable de temperatura
float Humidity;
 
void setup() {
  Serial.begin(115200);
  delay(100);
 
  pinMode(DHTPin, INPUT);
 
  dht.begin();              
 
  Serial.println("Connecting to ");
  Serial.println(ssid);
 
  //conecta a la red wi-fi local
  WiFi.begin(ssid, password);
 
  //comprobar si el dispositivo wi-fi está conectado a la red wi-fi
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());
 
  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);
 
  server.begin();
  Serial.println("HTTP server started");
 
}
void loop() {
 
  server.handleClient();
 
}
 
void handle_OnConnect() {
 
 Temperature = dht.readTemperature(); // Retorna los valores de la temperatura
  Humidity = dht.readHumidity(); // Retorna los valores de la humedad
  server.send(200, "text/html", SendHTML(Temperature,Humidity)); 
}
 
void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}
 
String SendHTML(float Temperaturestat,float Humiditystat){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>Sensor de temperatura y humedad</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";
  ptr +="p {font-size: 24px;color: #444444;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<div id=\"webpage\">\n";
  ptr +="<h1>UNIVERSIDAD POLITECNICA DE JUVENTINO ROSAS</h1>\n";
  ptr +="<h1>Sensor de temperatura y humedad</h1>\n";
 
  
 
  ptr +="<p><img src='termometro.png'align='left'>Temperatura:";
  ptr +=(int)Temperaturestat;
  ptr +="°C</p>";
  ptr +="<p><img src='humedad.png'align='left'>Humedad: ";
  ptr +=(int)Humiditystat;
  ptr +="%</p>";
 
  ptr +="</div>\n";
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}

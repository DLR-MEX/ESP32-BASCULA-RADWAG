#include <WiFi.h>

const char* ssid = "Totalplay-15A7";
const char* password = "SPACE2022!";

//const uint16_t port = 23;
//const char * host = "192.168.100.35";
WiFiServer wifiServer(8899);

String c;
 char buffer[20];  // Selecciona un tamaño suficientemente grande para el búfer



bool Connected = 0;
void setup() {
wifiServer.close();
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  WiFi.mode(WIFI_STA);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("...");
  }

  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());
  wifiServer.begin();
  
}

void loop() {
  
    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("...");
  }
  WiFiClient client = wifiServer.available();
  //client.stop();


  if (client) {
   Serial.println("Client Conectado");
      double randomValue = 1 + static_cast<double>(random()) / RAND_MAX * (1500 - 1);
      Connected = 0; // Variable de Desconexion
      while (client.available() > 0) {
        c = client.readString();
        Serial.print(c);
        if (c == "Z\r\n") {
          //client.write("Hola Mundo");
          client.write("Z D\r\n");
        }
        if (c == "T\r\n") {
          client.write("T A\r\n");
          client.write("T D\r\n");
        }
        if (c == "OT\r\n") {
          client.write("OT      48.9  kg\r\n");
        }
        if (c == "S\r\n") {
          client.write("S A\r\n");
              // Especifica un ancho mínimo de campo de 5 para el número en la cadena formateada
          sprintf(buffer, "S    +%9d kg\r\n",  randomValue);
          delay(4000);
          client.write(buffer);
           //sprintf(cadena + 15 - valorAleatorio, "%d", valorAleatorio);
          Serial.println(buffer);
        }
        //client.write(c);
      }
      delay(1000);
      client.stop();
    }
  }
 


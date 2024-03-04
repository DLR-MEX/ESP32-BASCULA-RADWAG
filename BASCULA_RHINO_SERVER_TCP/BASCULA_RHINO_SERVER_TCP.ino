#include <WiFi.h>

#include <SoftwareSerial.h>
#define RXPin 17  // Serial Receive pin
#define TXPin 16  // Serial Transmit pin
String option;




SoftwareSerial RS485Serial(RXPin, TXPin);  // RX, TX
 
const char* ssid = "INVITADOS";
const char* password =  "MXHOTELESMX";
 
//const uint16_t port = 23;
//const char * host = "192.168.100.35";
WiFiServer wifiServer(8899);
String c;


void setup()
{
 
  Serial.begin(115200);

RS485Serial.begin(9600, SWSERIAL_8N1);  // set the data rate
RS485Serial.setTimeout(50);
 
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("...");
  }
 
  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());
  wifiServer.begin();
}

void loop() {

  WiFiClient client = wifiServer.available();

  if (client) {

    while (client.connected()) {
        if(RS485Serial.available()) {
           option = RS485Serial.readString();
           client.println(option);
            Serial.println(option);
           }

      while (client.available()>0) {
        c = client.readString();
        Serial.print(c);
        if(c == "P\r\n")
        {
          RS485Serial.print("P\r\n"); 
          //client.write("Z D\r\n");
        }
        if(c == "T\r\n")
        {
          client.write("T A\r\n");
          //client.write("T D\r\n");
        }
        if(c == "OT\r\n")
        {
          client.write("OT      48.9  kg\r\n");
        }
        if(c == "S\r\n")
        {
          client.write("S A\r\n");
          delay(4000);
          client.write("S     +     48.9 kg\r\n");
        }
        //client.write(c);
      }

    }

    client.stop();
    Serial.println("Client disconnected");

  }
}


#include <SoftwareSerial.h>
#define RXPin 16  // Serial Receive pin
#define TXPin 17 // Serial Transmit pin
String option;

 char buffer[20];  


SoftwareSerial RS485Serial(RXPin, TXPin);  // RX, TX
//SoftwareSerial Serial(17, 18);  
void setup() {
Serial.begin(115200);
RS485Serial.begin(9600, SWSERIAL_8N1);  // set the data rate
RS485Serial.setTimeout(50);
 
 
}
 
void loop() {
  
    //leemos la opcion enviada
    if(RS485Serial.available() > 0 ) {
    option = RS485Serial.readString();
    double randomValue = 1 + static_cast<double>(random()) / RAND_MAX * (1500 - 1);
    Serial.println(option);
    if (option == "T\r\n") {
      Serial.println("Send data!");
      RS485Serial.print("T A\r\n"); 
      delay(5000);                                  // Send message
      RS485Serial.print("T D\r\n");
       
      //delay(100);
    }
    if (option == "OT\r\n") {
      Serial.println("Send data!");
      RS485Serial.print("OT      48.9  kg\r\n");                                   // Send message
    }
    if (option == "S\r\n") {
      Serial.println("Send data!");
      RS485Serial.print("S A\r\n");
      delay(2000);
    double randomValue = 1 + static_cast<double>(random()) / RAND_MAX * (1500 - 1);
    sprintf(buffer, "S    +%9.2f kg\r\n",  randomValue);
    RS485Serial.print(buffer);
           //sprintf(cadena + 15 - valorAleatorio, "%d", valorAleatorio);
    Serial.println(buffer);
      
    }
     
    }
 }
  
  
  



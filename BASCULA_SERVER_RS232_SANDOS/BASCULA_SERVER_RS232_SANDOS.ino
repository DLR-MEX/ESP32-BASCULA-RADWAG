
#include <SoftwareSerial.h>
#define RXPin 17  // Serial Receive pin
#define TXPin 16  // Serial Transmit pin
String option;




SoftwareSerial RS485Serial(RXPin, TXPin);  // RX, TX
void setup() {
Serial.begin(115200);
RS485Serial.begin(9600, SWSERIAL_8N1);  // set the data rate
RS485Serial.setTimeout(50);
 
 
}
 
void loop() {
    //leemos la opcion enviada
    if(RS485Serial.available() > 0 ) {
    option = RS485Serial.readString();
    if(option == "P\r\n"){
    Serial.println(option);
    Serial.println("Send data!");
    RS485Serial.print(random(14,500));
    RS485Serial.print("Kg");
    }
    }
  
  
  delay(100);
   
 }
  

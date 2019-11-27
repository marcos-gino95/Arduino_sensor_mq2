#include "RF24.h"
RF24 myRadio (7, 8);
byte addresses[][6] = {"0", "1","2"};

const int LED =4;
const int BOTON = 2;
int val=0;
int state1 = 0;
int old_val = 0;
const int MQ_PIN = 5;
const int MQ_DELAY = 500;


struct package
{
  int led1= 0;
  int led2 = 0;
  bool state = 0;
  };
 typedef struct package Package;
 Package data;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BOTON, INPUT);
  Serial.begin(115200);
//  delay(100);
  myRadio.begin();
  myRadio.setChannel(115);
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate(RF24_250KBPS);
  myRadio.openReadingPipe(1, addresses[0]);
  myRadio.openWritingPipe(addresses[0]);

}

void loop() {
     
  myRadio.stopListening();
  data.state= digitalRead(MQ_PIN);
 
  if (!data.state)
  {
    Serial.println("Deteccion");
    digitalWrite(LED,HIGH);
    myRadio.write(&data, sizeof(data));
    
  }
  else
  {
    Serial.println("No detectado");
//    digitalWrite(LED,LOW);
  }
  
  //delay(MQ_DELAY);

  val= digitalRead(BOTON); // lee el estado del Boton
  if ((val == HIGH) && (old_val == LOW)){
  data.led1=1-data.led1;
  myRadio.write(&data, sizeof(data));

  delay(10);
  }
  
  old_val = val; // valor del antiguo estado
  if (data.led1==1){
  digitalWrite(LED, LOW); // enciende el LED
  }
//  else{
//  digitalWrite(LED,LOW); // apagar el LED
 
//  }
  delay(10);   


  
  myRadio.startListening();  

  if(myRadio.available())
  {
    
    while(myRadio.available())
    {
      myRadio.read(&data, sizeof(data));
    }
    Serial.print("reading");
    
//    Serial.println(data.led2);
    //Serial.print("\n");
    if(data.led2 ==1){
      digitalWrite(LED, LOW);
    }
//    else{
  //       digitalWrite(LED, LOW);
         
    //  }
  //Serial.println(data.led2);
  }
 delay(10);   


 }

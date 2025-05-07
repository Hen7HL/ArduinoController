//Receiver setup

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


//receiver Setup ==============================
#define CE_PIN   7
#define CSN_PIN 8

const byte thisSlaveAddress[5] = {'R','x','A','A','A'};
RF24 radio(CE_PIN, CSN_PIN);

bool newData = false;

//set up data struct with the same amount of data as in the sender struct
struct Controls{
  int one;
  int two;
  
};

//initialize struct
Controls controls;

//=======================================

void setup() {
    //debug
    Serial.begin(9600);
    Serial.println("Car receiver Starting");

    //setup receiver NRF24L01
    radio.begin();
    radio.setDataRate( RF24_250KBPS );
    radio.openReadingPipe(1, thisSlaveAddress);
    radio.startListening();
}

//Main loop======================================

void loop() {
    getData();
    showData();
}

//Read data function ===================================
void getData() {
    if (radio.available()) {
        radio.read(&controls, sizeof(controls));
        newData = true;
    }
 
}
//show data function ===================================
//changie if youwant to do something with the data
void showData() {
    if (newData == true) {
        Serial.print("Data received ");
        Serial.print(controls.one);
        Serial.print(" ");
        Serial.println(controls.two);
        newData = false;
    }
    
}

//Code for the controller/sender

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//set up radio
#define CE_PIN   7
#define CSN_PIN 8

const byte slaveAddress[5] = {'R','x','A','A','A'};
RF24 radio(CE_PIN, CSN_PIN); // Create a Radio

//set analog input pins
const int pin1 = A0;
const int pin2 = A4;
//add as many as you have

//set up data struct with as much data as you want to send
struct Controls {
  int one = 0;
  int two = 0;
};

//initialize struct
Controls controls;


//set up send frequency
unsigned long currentMillis;
unsigned long prevMillis;
unsigned long txIntervalMillis = 50; // send once per 50 ms


void setup() {
    
    Serial.begin(9600);
    Serial.println("SimpleTx Starting");

    radio.begin();
    radio.setDataRate( RF24_250KBPS );
    radio.setRetries(3,5); // delay, count 
    radio.openWritingPipe(slaveAddress);
}

//====================
//main loop
void loop() {
    currentMillis = millis();
    if (currentMillis - prevMillis >= txIntervalMillis) {
        send();
        prevMillis = millis();
    }
    
}

//====================

void send() {
    //read in data
    controls.one = analogRead(pin1);
    controls.two = analogRead(pin2);

    //send data
    bool rslt = radio.write(&controls, sizeof(controls));

    //debug
    Serial.print("Data Sent ");
    Serial.print(controls.one);
    Serial.print(" ");
    Serial.print(controls.two);
    if (rslt) {
        Serial.print("  Ack");
    }
    else {
        Serial.print("  Ack failed");
    }
    
}


#include "Wire.h" //allows communication over i2c devices
#define LI 3 // Digital pin for solenoid valve 2
#define LR 4 // Digital pin for solenoid valve 3
#define RI 5 // Digital pin for solenoid valve 4
#define RR 6 // Digital pin for solenoid valve 5
#define LO 7 // Digital pin for solenoid valve 6
#define RO 8 // Digital pin for solenoid valve 7

//#include "LiquidCrystal_I2C.h" //allows interfacing with LCD screens

const int pressureInput1 = A1; //select the analog input pin for the pressure transducer
const int pressureInput2 = A2; //select the analog input pin for the pressure transducer
const int pressureInput3 = A3; //select the analog input pin for the pressure transducer
const int pressureZero = 102.4; //analog reading of pressure transducer at 0psi
const int pressureMax = 921.6; //analog reading of pressure transducer at 100psi
const int pressuretransducermaxPSI = 100; //psi value of transducer being used
const int baudRate = 9600; //constant integer to set the baud rate for serial monitor
const int sensorreadDelay = 250; //constant integer to set the sensor read delay in milliseconds

float pressureValue = 0; //variable to store the value coming from the pressure transducer

bool start=1;
void setup() //setup routine, runs once when system turned on or reset
{
  Serial.begin(baudRate); //initializes serial communication at set baud rate bits per second
//  lcd.begin(); //initializes the LCD screen
  Wire.begin();
  
  pinMode(LO, OUTPUT);
  pinMode(LI, OUTPUT);
  pinMode(LR, OUTPUT);
  pinMode(RO, OUTPUT);
  pinMode(RI, OUTPUT);
  pinMode(RR, OUTPUT);

}

void loop() //loop routine runs over and over again forever
{
  pressureValue1 = analogRead(pressureInput1); //reads value from input pin and assigns to variable
  pressureValue1 = ((pressureValue-pressureZero)*pressuretransducermaxPSI)/(pressureMax-pressureZero); //conversion equation to convert analog reading to psi
  pressureValue2 = analogRead(pressureInput2); //reads value from input pin and assigns to variable
  pressureValue2 = ((pressureValue-pressureZero)*pressuretransducermaxPSI)/(pressureMax-pressureZero); //conversion equation to convert analog reading to psi
  pressureValue3 = analogRead(pressureInput3); //reads value from input pin and assigns to variable
  pressureValue3 = ((pressureValue-pressureZero)*pressuretransducermaxPSI)/(pressureMax-pressureZero); //conversion equation to convert analog reading to psi
  Serial.print(pressureValue, 1); //prints value from previous line to serial

  if(start){
    while(pressureValue1<65){
      digitalWrite(LI,HIGH);
      digitalWrite(LO,LOW);
      digitalWrite(LL,LOW);
      digitalWrite(RI,LOW);
      digitalWrite(RR,LOW);
      digitalWrite(RO,LOW);
      delay(sensorreadDelay);
      pressureValue1 = analogRead(pressureInput1); //reads value from input pin and assigns to variable
      pressureValue1 = ((pressureValue-pressureZero)*pressuretransducermaxPSI)/(pressureMax-pressureZero);
    }
    start=0;
  }

  digitalWrite(LI,LOW);
  digitalWrite(LR,HIGH);

  pressureValue2 = analogRead(pressureInput2); //reads value from input pin and assigns to variable
  pressureValue2 = ((pressureValue-pressureZero)*pressuretransducermaxPSI)/(pressureMax-pressureZero);
  while(pressureValue2<65){
    if(pressureValue1<55){
      digitalWrite(LR,LOW);
      digitalWrite(LO,HIGH);
      digitalWrite(LI,LOW);
    }
    else if(pressureValue1<45){
      digitalWrite(LO,LOW);
      digitalWrite(LI,LOW);
      digitalWrite(LR,LOW);
    }
    digitalWrite(RI,HIGH);
    digitalWrite(RO,LOW);
    digitalWrite(RR,LOW);
    delay(sensorreadDelay);
    pressureValue1 = analogRead(pressureInput1); //reads value from input pin and assigns to variable
    pressureValue1 = ((pressureValue-pressureZero)*pressuretransducermaxPSI)/(pressureMax-pressureZero);
    pressureValue2 = analogRead(pressureInput2); //reads value from input pin and assigns to variable
    pressureValue2 = ((pressureValue-pressureZero)*pressuretransducermaxPSI)/(pressureMax-pressureZero);
  }
  digitalWrite(RI,LOW);
  digitalWrite(RR,HIGH);
  digitalWrite(RO,LOW);
  # ASSUMING PRESSUREVALUE1<45
  while(pressureValue1<65){
    if(pressureValue2<55){
      digitalWrite(RR,LOW);
      digitalWrite(RO,HIGH);
    }
    else if(pressureValue2<45){
      digitalWrite(RI,LOW);
      digitalWrite(RR,LOW);
      digitalWrite(RO,LOW);
    }
    digitalWrite(LI,HIGH);
    digitalWrite(LO,LOW);
    digitalWrite(LR,LOW);
    delay(sensorreadDelay);
    pressureValue1 = analogRead(pressureInput1); //reads value from input pin and assigns to variable
    pressureValue1 = ((pressureValue-pressureZero)*pressuretransducermaxPSI)/(pressureMax-pressureZero);
    pressureValue2 = analogRead(pressureInput2); //reads value from input pin and assigns to variable
    pressureValue2 = ((pressureValue-pressureZero)*pressuretransducermaxPSI)/(pressureMax-pressureZero);
  }
  delay(sensorreadDelay); //delay in milliseconds between read values
}
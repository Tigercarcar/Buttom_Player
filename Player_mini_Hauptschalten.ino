#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);
const byte LED = 13;
const byte SW = 3;
const byte SWN = 4;
const byte SWP = 5;
const byte SWU = 6;
const byte SWD = 7;

int Light = 0;


void setup()
{
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);

  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.volume(20);  //Set volume value. From 0 to 30
  myDFPlayer.play(1);  //Play the first mp3
///////////////////////////////////////////////////////////////////////////////////////////////////////////
  pinMode(LED,OUTPUT);
  pinMode(SW,INPUT);
  pinMode(SWN,INPUT);
  pinMode(SWP,INPUT);
  pinMode(SWU,INPUT);
  pinMode(SWD,INPUT);

}

void loop()
{ int n = digitalRead(SW);
 if (Light == 0)
 {
 if (n == HIGH)
 {
 delay(500); 
 digitalWrite(13, HIGH);
 myDFPlayer.pause();  //pause the mp3 from the start
  delay(1000);
 Light++; //markieren Led laufen
 }
 }
 else 
 {
 if (n == HIGH)
 {
 delay(500); 
 digitalWrite(13, LOW);
  myDFPlayer.start();  //start the mp3 from the pause
  delay(1000);
 Light--; //markieren Led laufen
 }
 } //wenn led leuchtet, stopt das mp3. wenn led nicht leuchtet, spielt das mp3


if(digitalRead(SWN) == HIGH)
{myDFPlayer.next();  
myDFPlayer.next();  //Wenn es nur zwei mal "next" gibt, dann es next mp3 spielt
  delay(1000);
  Serial.println(myDFPlayer.readCurrentFileNumber()); //read current play file number
}

if(digitalRead(SWP) == HIGH)
{  myDFPlayer.previous();
   myDFPlayer.previous(); //Wenn es nur zwei mal "previous" gibt, dann es previous mp3 spielt
  delay(1000);
  Serial.println(myDFPlayer.readCurrentFileNumber()); //read current play file number
}
if(digitalRead(SWU) == HIGH)
{ myDFPlayer.volumeUp(); //Volume Up
 Serial.println(myDFPlayer.readVolume()); //read current volume
}
if(digitalRead(SWD) == HIGH)
{ myDFPlayer.volumeDown(); //Volume Down
 Serial.println(myDFPlayer.readVolume()); //read current volume
}

 
 if (myDFPlayer.available()) {
    printDetail(myDFPlayer.readType(), myDFPlayer.read()); //Print the detail message from DFPlayer to handle different errors and states.
  }
}

void printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}

/*
  Main Central Jean Paul Fermaint 12/01
  Updated and synchronized with all files
*/

#include <ArduinoBLE.h>
#include <RocketCentralFlightBLE.h>

#define DEBUG true

#define MAXSIZE 200
#define DATAROWS 1000
#define DATACOLS 9

#define STATE_NONE  0
#define STATE_READY 1
#define STATE_ARMING 2
#define STATE_ARMED 3
#define STATE_LAUNCH 4
#define STATE_LANDED 5

const int ledPin = LED_BUILTIN;
// variables for button
const int buttonPin = 2;
int oldButtonState = LOW;
int FlightState;

struct dataRow{
  unsigned long timeMs;
  short int data[DATACOLS];
};

union FltData {
  byte byteData[sizeof(struct dataRow)*DATAROWS];
  struct dataRow row[DATAROWS];
} flight;

//union FltData {
//  byte byteData[DATAROWS*DATACOLS*sizeof(short int)];
//  short int dataRows[DATAROWS][DATACOLS];
//} flight;

RocketCentralFlightBLE rktCtrl;

void setup() {
  Serial.begin(115200);
  if (DEBUG) while (!Serial);

  // configure the button pin as input
  pinMode(buttonPin, INPUT);
  // set LED pin to output mode
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  rktCtrl.setupRocketBLE();
  FlightState = STATE_NONE;
}

void loop() {
  static bool rocketCommsReady = false;
  static bool startTransmission = false;
  char msgbuffer[80];
  int totalBytesRead;

  switch (FlightState) {
    case STATE_NONE:
      break;
    case STATE_READY:
      break;
    case STATE_ARMING:
      rktCtrl.armRocket();
      FlightState = STATE_ARMED;
      return;
    case STATE_ARMED:
      // Something transitions from ARMED to LAUNCH
      // pressing launch button?
      break;
      
    case STATE_LAUNCH:
      rktCtrl.launchRocket();
      FlightState = STATE_LANDED;
      return;
      
    case STATE_LANDED:
      break;
  }

  if (!rktCtrl.rocketConnectedBLE()) {
    rocketCommsReady = false;
  }
  
  if (!rocketCommsReady) {
    if (rktCtrl.connectBLE()) {
      rocketCommsReady = rktCtrl.discoverRocket();
      sprintf(msgbuffer, "Rocket discovered: %d", rocketCommsReady);
      Serial.println(msgbuffer);
    } else {
      rocketCommsReady = false;
    }
  }

  // read the button pin
  int buttonState = digitalRead(buttonPin);

  if (oldButtonState != buttonState) {
    // button changed
    oldButtonState = buttonState;
    
    if (buttonState) {
      Serial.println("button pressed");
      startTransmission = true;
      digitalWrite(ledPin, HIGH);

      if (rktCtrl.rocketConnectedBLE()) {
        // button is pressed, write 0x01 to turn the LED on
        rktCtrl.setLedCharacteristic((byte)0x01);
      }
      else // Disconnected, try again
        return;
        
    } else {
      Serial.println("button released");
      if (rktCtrl.rocketConnectedBLE()) {
        // button is released, write 0x00 to turn the LED off
        rktCtrl.setLedCharacteristic((byte)0x00);
      }
    }
  }
  
  if (startTransmission) {
    Serial.println("Check for data");
    if (rktCtrl.rocketHasData()) {
      Serial.println("Rocket has data");
      if (rktCtrl.receiveRocketData((byte*)flight.byteData, sizeof(flight.byteData), &totalBytesRead)) {
        sprintf(msgbuffer, "Bytes %d, rows %d", totalBytesRead, totalBytesRead / (sizeof(struct dataRow)*DATAROWS));
        Serial.println(msgbuffer);
        for (int inx = 0; inx < sizeof(flight.byteData); inx++){
//          sprintf(msgbuffer,"Accelaration: %d Gyro: %d,%d,%d Magneto: %d,%d,%d Altitude: %d Time: %d",
          sprintf(msgbuffer,"%d %d %d %d %d %d %d %d %d",
          flight.row[inx].data[0],flight.row[inx].data[1],flight.row[inx].data[2],
          flight.row[inx].data[3],flight.row[inx].data[4],flight.row[inx].data[5],
          flight.row[inx].data[6],flight.row[inx].data[7],flight.row[inx].timeMs);
          
          Serial.print(msgbuffer);
          Serial.println();
      }
        Serial.println();
        digitalWrite(ledPin, LOW);
        startTransmission = false;
      } else {
        Serial.println("Data Transfer failed");
      }
    }
  }
}

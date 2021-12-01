/*
  Saved on 11/27 by Jean Paul Fermaint
  Updated and synchronized with all files
 */
#include <ArduinoBLE.h>
#include <Arduino_LPS22HB.h>
#include <Arduino_LSM9DS1.h>

#include <stdio.h>
#include <RocketFlightBLE.h>
#define DEBUG false

#define MAXBLESIZE 200
#define DATASIZE 960
#define DATAROWS 1000
#define DATACOLS 9


const int ledPin = LED_BUILTIN;
const int buttonPin = 2;
int oldButtonState = 0;


union FltData {
  byte byteData[DATAROWS*DATACOLS*sizeof(short int)];
  short int dataRows[DATAROWS][DATACOLS];
} flight;

RocketFlightBLE rktFlt;

//state actions
#define STATE_BOOT 0
#define STATE_NONE 1
#define STATE_ARM 2
#define STATE_RUN 3
#define STATE_STOPPING 4
#define STATE_DONE 5

// Global variables
float groundPressurekPa;
int16_t AcX,AcY,AcZ,GyX,GyY,GyZ,MaX,MaY,MaZ;
int inx;
int state = STATE_NONE;
bool stateChange = false;
int gravityAcc;
int period = 1;
unsigned long time_now = 0;



struct AMS{
  float AcX,AcY,AcZ,GyX,GyY,GyZ,MaX,MaY,MaZ;
}d;

void setup() {
  inx = -1;
  if (DEBUG) {
    Serial.begin(115200);
    while (!Serial);
    Serial.println("Serial Started");
  }

  if (!IMU.begin()){
    Serial.println("Failed to initialize IMU");
    while(1);
    }
  if (!BARO.begin()){
    Serial.println("Failed to initialize BARO");
    while(1);
  }

  // set LED pin to output mode
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin,LOW);
  pinMode(buttonPin, INPUT);


  if (!rktFlt.setupBLE()) {
     if (DEBUG) {
      Serial.println("setup fail");
     }
    while(true);
  }
 

  groundPressurekPa = BARO.readPressure(); // Get ground pressure sometime before launch
}

class AverageValue
{
  private:
    int count = 0;
    long valueSum = 0;
  
  public:
    AverageValue() {
      Reset();
    }
    void Reset() {
      count = 0;
      valueSum = 0;
    }
    void AddValue(long value) {
      valueSum += value;
      count++;
    }
    
    long GetAverage() {
      int average = valueSum / count;
      Reset();
      return average;
    }
};
int getGravityVector() {
  long sumX, sumY, sumZ;
  
  sumX = 0;
  sumY = 0;
  sumZ = 0;
  for (int x = 0; x < 16; x++) {
    sumX += d.AcX;
    sumY += d.AcY;
    sumZ += d.AcZ;
  }

  // use all 3 axis to avoid orientation errors
  gravityAcc = sqrt( pow((sumX/16),2) + pow((sumY/16),2) + pow((sumZ/16),2) );
}

AverageValue altitudeValues;
AverageValue xAccValues;
AverageValue yAccValues;
AverageValue zAccValues;

void loop() {
//  bool armStart;
//  long altitudeValue;
//  int AccSum;
//  int timerId;
//
//  //State actions
//  switch(state)
//
//  {
//    case STATE_NONE:
//      if (stateChange){
//        state= STATE_ARM;
//        stateChange=false;
//        Serial.println(F("ARM"));
//        stateChange=false;
//        gravityAcc = getGravityVector();
//        armStart=true;
//    }
//      break;
//
//    case STATE_ARM:
//      if (armStart){
//      }
//      apogee=false;
//
//      GetLSM9DS1();
//
//      if (ComputeAcc(d.AcX, d.AcY, d.AcZ) > gravityAcc * 1.25) // launch
//        stateChange = true;
//      
//
//      if (stateChange) {
//        state = STATE_RUN;
//        stateChange = false;
//        Serial.println();
//        Serial.println(F("Launch"));
//        startTime = millis();
//        timerId = timer.every(PERIOD, WriteData, (void*)0);
//        stateChange = false;
//      }
//      break;
//
//    case STATE_RUN:
//      if (stateChange){
//        state = STATE_STOPPING;
//        stateChange = false;
//        Serial.println();
//        Serial.println(F("Land"));
//        stateChange = false;
//        
//      }
//       if (BARO)
//      {
//        altitudeValues.AddValue(GetAltitude());
//      }
//
//      if(IMU)
//      {
//        GetLSM9DS1();
//        xAccValues.AddValue(d.AcX);
//        yAccValues.AddValue(d.AcY);
//        zAccValues.AddValue(d.AcZ);
//        AccSum = ComputeAcc(d.AcX, d.AcY, d.AcZ);
//      }
//      // In free fall?
//      if (AccSum < gravityAcc * 0.25)
//      {
//        apogee = true;
//        apogeeTime = millis();
//        // Release chute
//        myservo.write(90);
//      }
//
//      // Landed?
//      if (altitudeValue < 100 && (AccSum < gravityAcc * 1.1) &&
//          apogee && (millis() - apogeeTime > 100))
//        stateChange = true;
//        
////      Serial.print(P);
////      Serial.print(" ");
////      Serial.println(altitudeValue);
//      break;
//
//    case STATE_STOPPING:
//      Serial.println(F("done."));
//      timer.cancel();
//      apogee = false;
//      state = STATE_DONE;
//      break;
//
//    case STATE_DONE:
//      if (stateChange)
//        state = STATE_NONE;
//      stateChange = false;
//      break;
//  }

  static bool buttonState = false;
  static bool ledStatus = LOW;

float Alt = GetAltitude();
Serial.println(Alt);

    time_now = millis();
    if (Alt>1){ // while altitude is higher than 1 and time_now is higher than millis StoreData
      digitalWrite(ledPin, HIGH);
      ledStatus = HIGH;
        StoreData();
        while(millis()<time_now+period){ 
        }
      }    
    else { // flip the status of led
      ledStatus = LOW;
      digitalWrite(ledPin,ledStatus);
      }
    Serial.println("Data collected");

  static bool getDataFlag = false;
  // when flight done, this flag is set
  getDataFlag = true;
    if (DEBUG) {
      Serial.println("Data ready set");
     }
  
  // MUST test for connected in loop().  
  // This allows characteristic discovery by other devices.
      if (rktFlt.connectedBLE()) {
        if (getDataFlag) {
          rktFlt.setHasData(true);
          if (rktFlt.transferBLE(flight.byteData, DATASIZE)) {
            getDataFlag = false;
            rktFlt.setHasData(false);
    }
  }
        }
    else {
       if (DEBUG) {
        Serial.println("Not connected");
       }
    }
}

struct AMS GetLSM9DS1(){
  float x,y,z;
  float a,b,c;
  float g,h,s;
  
  IMU.readAcceleration(x,y,z);
  d.AcX=x;
  d.AcY=y;
  d.AcZ=z;

  IMU.readGyroscope(a, b, c);
  d.GyX=a;
  d.GyY=b;
  d.GyZ=c;

  IMU.readMagneticField(g,h,s);
  d.MaX=g;
  d.MaY=h;
  d.MaZ=s;

 delay(5);

 return d;
}
void PrintData(float altitude){
  
  Serial.print("AcX = "); Serial.println(d.AcX);
  Serial.print(" | AcY = "); Serial.println(d.AcY);
  Serial.print(" | AcZ = "); Serial.println(d.AcZ);
  Serial.print(" | GyX = "); Serial.println(d.GyX);
  Serial.print(" | GyY = "); Serial.println(d.GyY);
  Serial.print(" | GyZ = "); Serial.println(d.GyZ);
  Serial.print(" | MaX = "); Serial.println(d.MaX);
  Serial.print(" | MaY = "); Serial.println(d.MaY);
  Serial.print(" | MaZ = "); Serial.println(d.MaZ);
  
  Serial.print("Altitude according to kPa is = ");
  Serial.print(altitude);
  Serial.println(" m");
  Serial.println();
  return;
}

float GetAltitude(){
  float pressure = BARO.readPressure();
  return 44330 * (1 - pow(pressure / groundPressurekPa, 0.1903));
}

int ComputeAcc(int Xacc,int Yacc,int Zacc){
  return sqrt(Xacc * Xacc + Yacc * Yacc + Zacc * Zacc);
}

void StoreData(){
  char buffer[80];
  if (inx>999){
    return;
  }
  GetLSM9DS1();
  float alt = GetAltitude();
  float totalAcc = ComputeAcc(d.AcX,d.AcY,d.AcZ);

  inx++;
  flight.dataRows[inx][0]=totalAcc*100;
  flight.dataRows[inx][1]=d.GyX*100;
  flight.dataRows[inx][2]=d.GyY*100;
  flight.dataRows[inx][3]=d.GyZ*100;
  flight.dataRows[inx][4]=d.MaX*100;
  flight.dataRows[inx][5]=d.MaY*100;
  flight.dataRows[inx][6]=d.MaZ*100;
  flight.dataRows[inx][7]=alt*100;
  flight.dataRows[inx][8]=millis();

  sprintf(buffer, "Accelaration: %d Gyro: %d,%d,%d Magneto: %d,%d,%d Altitude: %d Time: %d",
  flight.dataRows[inx][0],flight.dataRows[inx][1],flight.dataRows[inx][2],
  flight.dataRows[inx][3],flight.dataRows[inx][4],flight.dataRows[inx][5],
  flight.dataRows[inx][6],flight.dataRows[inx][7],flight.dataRows[inx][8]);
  Serial.println(buffer);
  
  for (int i=0;i<100;i++){
    Serial.print("Flight Data: ");
    Serial.print(i+1);
    Serial.print("--- ");
    for (int j=0;j<9;j++){
      Serial.print(flight.dataRows[i][j]);
      Serial.print(" ");
         
    }
  Serial.println();
  }
}



// Check for switch on
// Input:   button pin value
// Output:  state of switch: true or false
//
bool switchOn(int buttonPin)
{
  static bool buttonToggle = false;
  static bool buttonResult = false;
  static int currentButtonReading;      // the current reading from the input pin
  static int lastButtonReading = LOW;   // the previous reading from the input pin

  // the following variables are unsigned longs because the time, measured in
  // milliseconds, will quickly become a bigger number than can be stored in an int.
  static unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
  static unsigned long debounceDelay = 25;    // the debounce time; increase if the output flickers
  char buffer[32];

  buttonResult = false;
  
  // Debounce logic.  Not needed for state machine?  Only need single detection.
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonReading) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != currentButtonReading) {
      currentButtonReading = reading;

      // only toggle the LED if the new button state is HIGH
      if (currentButtonReading == HIGH && !buttonToggle) 
      {
        buttonToggle = true;
        buttonResult = true;
      }
      if (currentButtonReading == LOW)
      {
        buttonToggle = false;
      }
    }
  }
  lastButtonReading = reading;
    
  return buttonResult;
}

#include <SPI.h>          //Library for using SPI Communication 
#include <mcp2515.h>      //Library for using CAN Communication

struct can_frame canMsg1;
struct can_frame canMsg2;
struct can_frame canMsg3;
struct can_frame canMsg4;
struct can_frame canMsg5;
struct can_frame canMsg6;

MCP2515 mcp2515(10); // chip select pin 10

String feedback ;
String readString;
String command_Main;
String command_Dir;
String command_Time;

float rotate_Time;

float time_init = 0.00;
float time_last = 0.00;
float time_current = 0.00;
float time_set = 0;

#define pulse 2
#define pulse_2 3
#define motor_R 4
#define motor_L 5
#define motor_speed 6

bool status_Rotate_1 = false;
bool status_Cook_1 = false;

void rotate() {
  digitalWrite(pulse, LOW);
  delay(4.885208);
  digitalWrite(pulse, HIGH);
  delay(1.212792);
  digitalWrite(pulse, LOW);
  delayMicroseconds(494.125);
  digitalWrite(pulse, HIGH);
  delayMicroseconds(480.458);
  digitalWrite(pulse, LOW);
  delay(1.225417);
  digitalWrite(pulse, HIGH);
  delay(1.212417);
  digitalWrite(pulse, LOW);
  delayMicroseconds(494.583);
  digitalWrite(pulse, HIGH);
  delayMicroseconds(481.5);
  digitalWrite(pulse, LOW);
  delay(1.224458);
  digitalWrite(pulse, HIGH);
  delayMicroseconds(480.708);
  digitalWrite(pulse, LOW);
  delay(1.226);
  digitalWrite(pulse, HIGH);
  delay(1.212375);
  digitalWrite(pulse, LOW);
  delayMicroseconds(493.792);
  digitalWrite(pulse, HIGH);
  delay(1.211958);
  digitalWrite(pulse, LOW);
  delayMicroseconds(493.667);
  digitalWrite(pulse, HIGH);

  delay(1.212542);
  digitalWrite(pulse, LOW);

  delayMicroseconds(493.75);
  digitalWrite(pulse, HIGH);

  delay(1.211292);
  digitalWrite(pulse, LOW);

  delayMicroseconds(494.125);
  digitalWrite(pulse, HIGH);
  delayMicroseconds(480.917);
  digitalWrite(pulse, LOW);
  delay(1.225292);
  digitalWrite(pulse, HIGH);
  delay(1.212833);
  digitalWrite(pulse, LOW);
  delayMicroseconds(493.458);
  digitalWrite(pulse, HIGH);
  delay(1.212375);
  digitalWrite(pulse, LOW);

  delayMicroseconds(494.292);
  digitalWrite(pulse, HIGH);
  delay(1.212125);
  digitalWrite(pulse, LOW);
  delayMicroseconds(495.042);
  digitalWrite(pulse, HIGH);

  delayMicroseconds(480.042);
  digitalWrite(pulse, LOW);
  delay(1.22525);
  digitalWrite(pulse, HIGH);
  delayMicroseconds(481.208);
  digitalWrite(pulse, LOW);
  delay(1.225083);
  digitalWrite(pulse, HIGH);
  delay(1.212333);
  digitalWrite(pulse, LOW);
  delayMicroseconds(493.625);
  digitalWrite(pulse, HIGH);
  delay(1.212458);
  digitalWrite(pulse, LOW);
  delayMicroseconds(493.958);
  digitalWrite(pulse, HIGH);
  delayMicroseconds(480.625);
  digitalWrite(pulse, LOW);
  delay(1.22425);
  digitalWrite(pulse, HIGH);
  delay(1.212417);
  digitalWrite(pulse, LOW);
  delayMicroseconds(494.125);
  digitalWrite(pulse, HIGH);
  delay(1.212042);
  digitalWrite(pulse, LOW);
  delayMicroseconds(494.542);
  digitalWrite(pulse, HIGH);
  delay(1.212167);
  digitalWrite(pulse, LOW);
  delayMicroseconds(493.75);
  digitalWrite(pulse, HIGH);
  delay(1.212583);
  digitalWrite(pulse, LOW);
  delayMicroseconds(494.417);
  digitalWrite(pulse, HIGH);
  delay(1.212208);
  digitalWrite(pulse, LOW);
  delayMicroseconds(494.625);
  digitalWrite(pulse, HIGH);
  delayMicroseconds(480.167);
  digitalWrite(pulse, LOW);
  delay(1.221125);
  digitalWrite(pulse, HIGH);
  delay(7.790958);
}

void On() {
  digitalWrite(pulse, LOW);
  delay(4.889958);
  digitalWrite(pulse, HIGH);
  delayMicroseconds(480.875);
  digitalWrite(pulse, LOW);
  delay(1.22525);
  digitalWrite(pulse, HIGH);
  delayMicroseconds(481.333);
  digitalWrite(pulse, LOW);
  delay(1.225917);
  digitalWrite(pulse, HIGH);
  delayMicroseconds(480.958);
  digitalWrite(pulse, LOW);
  delay(1.226042);
  digitalWrite(pulse, HIGH);
  delayMicroseconds(481.708);
  digitalWrite(pulse, LOW);
  delay(1.226375);
  digitalWrite(pulse, HIGH);
  delayMicroseconds(481.208);
  digitalWrite(pulse, LOW);
  delay(1.22675);
  digitalWrite(pulse, HIGH);
  delayMicroseconds(480.625);
  digitalWrite(pulse, LOW);
  delay(1.226);
  digitalWrite(pulse, HIGH);
  delay(1.213625);
  digitalWrite(pulse, LOW);
  delayMicroseconds(494.708);
  digitalWrite(pulse, HIGH);
  delayMicroseconds(481);
  digitalWrite(pulse, LOW);
  delay(1.225375);
  digitalWrite(pulse, HIGH);
  delay(1.213417);
  digitalWrite(pulse, LOW);
  delayMicroseconds(494.708);
  digitalWrite(pulse, HIGH);
  delayMicroseconds(481.083);
  digitalWrite(pulse, LOW);
  delay(1.226);
  digitalWrite(pulse, HIGH);
  delayMicroseconds(481.625);
  digitalWrite(pulse, LOW);
  delay(1.22625);
  digitalWrite(pulse, HIGH);
  delayMicroseconds(480.417);
  digitalWrite(pulse, LOW);
  delay(1.226667);
  digitalWrite(pulse, HIGH);
  delayMicroseconds(480.042);
  digitalWrite(pulse, LOW);
  delay(1.226375);
  digitalWrite(pulse, HIGH);
  delayMicroseconds(481.708);
  digitalWrite(pulse, LOW);
  delay(1.226083);
  digitalWrite(pulse, HIGH);
  delayMicroseconds(480.958);
  digitalWrite(pulse, LOW);
  delay(1.225917);
  digitalWrite(pulse, HIGH);
  delay(1.213708);
  digitalWrite(pulse, LOW);
  delayMicroseconds(494.792);
  digitalWrite(pulse, HIGH);
  delayMicroseconds(481.083);
  digitalWrite(pulse, LOW);
  delay(1.225292);
  digitalWrite(pulse, HIGH);
  delay(1.213625);
  digitalWrite(pulse, LOW);
  delayMicroseconds(494.125);
  digitalWrite(pulse, HIGH);
  delay(1.213542);
  digitalWrite(pulse, LOW);
  delayMicroseconds(494.167);
  digitalWrite(pulse, HIGH);
  delay(1.212583);
  digitalWrite(pulse, LOW);
  delayMicroseconds(494.292);
  digitalWrite(pulse, HIGH);
  delay(1.2135);
  digitalWrite(pulse, LOW);
  delayMicroseconds(494.042);
  digitalWrite(pulse, HIGH);
  delay(1.212875);
  digitalWrite(pulse, LOW);
  delayMicroseconds(494.125);
  digitalWrite(pulse, HIGH);
  delayMicroseconds(481.417);
  digitalWrite(pulse, LOW);
  delay(1.226);
  digitalWrite(pulse, HIGH);
  delayMicroseconds(481.208);
  digitalWrite(pulse, LOW);
  delay(1.221417);
  digitalWrite(pulse, HIGH);
  delay(7.79825);

}

void read_data() {

  while (readString.length() < 10 ) {
    if (mcp2515.readMessage(&canMsg2) == MCP2515::ERROR_OK )
    {

      if (canMsg2.can_id == 0xBB  ) {
        delay(3);
        char c = canMsg2.data[0];
        readString += c;
        Serial.println(readString);
      }
    }
  }
  //RO1+001000N
  //CO1+001000N
  if (readString.length() > 0) {

    command_Main = readString.substring(0, 3);
    command_Dir  = readString.substring(3, 4);  // PO1+,PU1-
    command_Time = readString.substring(4, 10); // 005000 = 5 sec
  }
  if (command_Main == "RO1")
  {
    Serial.println("debug rotate");
    rotate_Time = command_Time.toInt();
    time_init = millis();
    status_Rotate_1 = true ;
  }
  if (command_Main == "CO1")
  {
    Serial.println("debug Cook");
    rotate_Time = command_Time.toInt();
    time_init = millis();
    status_Cook_1 = true ;
  }

  readString = "";
}

void Cooking_1 () {
  while (status_Cook_1 == true ) {
    time_last = millis();
    time_current = abs(time_last - time_init);

    rotate();
    delay(rotate_Time);
    On();
    Serial.println(time_current);

    if (time_current >= rotate_Time) {
      On();
      Serial.println(time_current);
      status_Cook_1 = false ;
    }
  }
}

void Motor_1 () {
  while (status_Rotate_1 == true) {
    time_last = millis();
    time_current = abs(time_last - time_init);
    Serial.println(rotate_Time);

    if (command_Dir == "+") {
      digitalWrite(motor_L, LOW);
      digitalWrite(motor_R, HIGH);
      analogWrite(motor_speed, 255);
      Serial.println("Debug +");

    }
    else if (command_Dir == "-") {
      digitalWrite(motor_L, HIGH);
      digitalWrite(motor_R, LOW);
      analogWrite(motor_speed, 255);
      Serial.println("Debug -");
    }

    /* else {
       digitalWrite(motor_L, LOW);
       digitalWrite(motor_R, LOW);
       analogWrite(motor_speed, 0);
      }*/
    if ( time_current >= rotate_Time) {

      digitalWrite(motor_L, LOW);
      digitalWrite(motor_R, LOW);
      analogWrite(motor_speed, 0);
      status_Rotate_1 = false ;
      Serial.println(time_current);
    }
  }
}
/// on to stop rotate/reset
void setup() {
  pinMode(pulse, OUTPUT);
  pinMode(pulse_2, OUTPUT);
  pinMode(motor_L, OUTPUT);
  pinMode(motor_R, OUTPUT);
  pinMode(motor_speed, OUTPUT);

  Serial.begin(9600);
  SPI.begin();               //Begins SPI communication

  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS, MCP_8MHZ); //Sets CAN at speed 500KBPS and Clock 8MHz
  mcp2515.setNormalMode();

  canMsg1.can_id  = 0xAA;
  canMsg1.can_dlc = 8;

  canMsg2.can_id  = 0xBB;
  canMsg2.can_dlc = 8;

  canMsg3.can_id  = 0xCC;
  canMsg3.can_dlc = 8;

  canMsg4.can_id  = 0xDD;
  canMsg4.can_dlc = 8;

  canMsg5.can_id  = 0xEE;
  canMsg5.can_dlc = 8;

  canMsg6.can_id  = 0xFF;
  canMsg6.can_dlc = 8;
  /*
    for ( int i = 0 ; i < 50 ; i++) {
      Off();
    }

    for ( int i = 0 ; i < 50 ; i++) {
      puff();
    }

    for ( int i = 0 ; i < 2000 ; i++) {
      stopRotate();
    }
    On();*/


}

void loop() {
  read_data();
  Motor_1();
  Cooking_1();


}

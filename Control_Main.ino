#include <SPI.h>          //Library for using SPI Communication 
#include <mcp2515.h>      //Library for using CAN Communication

struct can_frame canMsg1;
struct can_frame canMsg2;
struct can_frame canMsg3;
struct can_frame canMsg4;
struct can_frame canMsg5;
struct can_frame canMsg6;

MCP2515 mcp2515(53); // chip select pin 10

String feedback ;
String readString;
String command_Main;
String command_Dir;
String command_Time;

bool status_powder_0 = false;
bool status_powder_1 = false;
bool status_powder_2 = false;
bool status_powder_3 = false;
bool status_powder_4 = false;
bool status_powder_5 = false;
bool status_powder_6 = false;
bool status_powder_7 = false;
bool status_powder_8 = false;
bool status_powder_9 = false;

bool status_pump_0 = false;
bool status_pump_1 = false;
bool status_pump_2 = false;
bool status_pump_3 = false;
bool status_pump_4 = false;
bool status_pump_5 = false;
bool status_pump_6 = false;
bool status_pump_7 = false;
bool status_pump_8 = false;
bool status_pump_9 = false;

#define powder_Relay_0  22
#define powder_Relay_1  23
#define powder_Relay_2  24
#define powder_Relay_3  25
#define powder_Relay_4  26
#define powder_Relay_5  27
#define powder_Relay_6  28
#define powder_Relay_7  29
#define powder_Relay_8  30
#define powder_Relay_9  31


float time_powder_0 = 0 ;
float time_powder_1 = 0 ;
float time_powder_2 = 0 ;
float time_powder_3 = 0 ;
float time_powder_4 = 0 ;
float time_powder_5 = 0 ;
float time_powder_6 = 0 ;
float time_powder_7 = 0 ;
float time_powder_8 = 0 ;
float time_powder_9 = 0 ;

float time_pump_0 = 0 ;
float time_pump_1 = 0 ;
float time_pump_2 = 0 ;
float time_pump_3 = 0 ;
float time_pump_4 = 0 ;
float time_pump_5 = 0 ;
float time_pump_6 = 0 ;
float time_pump_7 = 0 ;
float time_pump_8 = 0 ;
float time_pump_9 = 0 ;


int pump_R_0 ;
int pump_L_0 ;
#define pump_R_1 32
#define pump_L_1 33
#define pump_R_2 34
#define pump_L_2 35
#define pump_R_3 36
#define pump_L_3 37
#define pump_R_4 38
#define pump_L_4 39
#define pump_R_5 40
#define pump_L_5 41
#define pump_R_6 42
#define pump_L_6 43
#define pump_R_7 44
#define pump_L_7 45
#define pump_R_8 46
#define pump_L_8 47
#define pump_R_9 48
#define pump_L_9 49

float time_init = 0.00;
float time_last = 0.00;
float time_current = 0.00;
float time_set = 0;


void read_data() {
  //POT+001000N
  while (Serial.available()) {
    delay(3);
    char c = Serial.read();
    if ((c != '\r') && (c != '\n')) {
      readString += c;
    }
    else if (c == '\n') {
      Serial.println(readString);
      command_Main = readString.substring(0, 3);  // PO1,PU1
      command_Dir  = readString.substring(3, 4);  // PO1+,PU1-
      command_Time = readString.substring(4, 10); // 005000 = 5 sec

      if ((command_Main == "PO0")) {
        time_powder_0  = command_Time.toInt();
        time_init = millis();
        status_powder_0 = true ;
      }

      if ((command_Main == "PO1")) {
        time_powder_1  = command_Time.toInt();
        time_init = millis();
        status_powder_1 = true ;
      }
      if ((command_Main == "PO2")) {
        time_powder_2  = command_Time.toInt();
        time_init = millis();
        status_powder_2 = true ;
      }
      if ((command_Main == "PO3")) {
        time_powder_3  = command_Time.toInt();
        time_init = millis();
        status_powder_3 = true ;
      }
      if ((command_Main == "PO4")) {
        time_powder_4  = command_Time.toInt();
        time_init = millis();
        status_powder_4 = true ;
      }
      if ((command_Main == "PO5")) {
        time_powder_5  = command_Time.toInt();
        time_init = millis();
        status_powder_5 = true ;
      }
      if ((command_Main == "PO6")) {
        time_powder_6  = command_Time.toInt();
        time_init = millis();
        status_powder_6 = true ;
      }
      if ((command_Main == "PO7")) {
        time_powder_7  = command_Time.toInt();
        time_init = millis();
        status_powder_7 = true ;
      }
      if ((command_Main == "PO8")) {
        time_powder_8  = command_Time.toInt();
        time_init = millis();
        status_powder_8 = true ;
      }
      if ((command_Main == "PO9")) {
        time_powder_9  = command_Time.toInt();
        time_init = millis();
        status_powder_9 = true ;
      }

      if ((command_Main == "PU0")) {
        time_pump_0  = command_Time.toInt();
        time_init = millis();
        status_pump_0 = true ;
      }
      if ((command_Main == "PU1")) {
        time_pump_1  = command_Time.toInt();
        time_init = millis();
        status_pump_1 = true ;
      }
      if ((command_Main == "PU2")) {
        time_pump_2  = command_Time.toInt();
        time_init = millis();
        status_pump_2 = true ;
      }
      if ((command_Main == "PU3")) {
        time_pump_3  = command_Time.toInt();
        time_init = millis();
        status_pump_3 = true ;
      }
      if ((command_Main == "PU4")) {
        time_pump_4  = command_Time.toInt();
        time_init = millis();
        status_pump_4 = true ;
      }
      if ((command_Main == "PU5")) {
        time_pump_5  = command_Time.toInt();
        time_init = millis();
        status_pump_5 = true ;
      }
      if ((command_Main == "PU6")) {
        time_pump_6  = command_Time.toInt();
        time_init = millis();
        status_pump_6 = true ;
      }
      if ((command_Main == "PU7")) {
        time_pump_7  = command_Time.toInt();
        time_init = millis();
        status_pump_7 = true ;
      }
      if ((command_Main == "PU8")) {
        time_pump_8  = command_Time.toInt();
        time_init = millis();
        status_pump_8 = true ;
      }
      if ((command_Main == "PU9")) {
        time_pump_9  = command_Time.toInt();
        time_init = millis();
        status_pump_9 = true ;
      }
      /*  if (command_Main == "POT") {
          Serial.println(command_Main);
          for (int i = 0 ; i < readString.length() ; i ++) {
            delay(3);
            canMsg2.data[0] = readString[i];
            canMsg3.data[0] = readString[i];
            canMsg4.data[0] = readString[i];
            mcp2515.sendMessage(&canMsg2);
            mcp2515.sendMessage(&canMsg3);
            mcp2515.sendMessage(&canMsg4);
          }
        }*/
      //   readString = "";
    }
  }
}

void Powder() {                                 // LOW level trigger
  while (status_powder_0 == true) {
    time_last = millis();
    time_current = abs(time_last - time_init);
    digitalWrite(powder_Relay_0, LOW);

    if (time_current >= time_powder_0) {
      digitalWrite(powder_Relay_0, HIGH);
      Serial.println(time_current);
      status_powder_0 = false;
    }
  }
  while (status_powder_1 == true) {
    time_last = millis();
    time_current = abs(time_last - time_init);
    digitalWrite(powder_Relay_1, LOW);

    if (time_current >= time_powder_1) {
      digitalWrite(powder_Relay_1, HIGH);
      Serial.println(time_current);

      status_powder_1 = false;
    }
  }
  while (status_powder_2 == true) {
    time_last = millis();
    time_current = abs(time_last - time_init);
    digitalWrite(powder_Relay_2, LOW);

    if (time_current >= time_powder_2) {
      digitalWrite(powder_Relay_2, HIGH);
      status_powder_2 = false;
    }
  }
  while (status_powder_3 == true) {
    time_last = millis();
    time_current = abs(time_last - time_init);
    digitalWrite(powder_Relay_3, LOW);

    if (time_current >= time_powder_3) {
      digitalWrite(powder_Relay_3, HIGH);
      status_powder_3 = false;
    }
  }
  while (status_powder_4 == true) {
    time_last = millis();
    time_current = abs(time_last - time_init);
    digitalWrite(powder_Relay_4, LOW);

    if (time_current >= time_powder_4) {
      digitalWrite(powder_Relay_4, HIGH);
      status_powder_4 = false;
    }
  }
  while (status_powder_5 == true) {
    time_last = millis();
    time_current = abs(time_last - time_init);
    digitalWrite(powder_Relay_5, LOW);

    if (time_current >= time_powder_5) {
      digitalWrite(powder_Relay_5, HIGH);
      status_powder_5 = false;
    }
  }
  while (status_powder_6 == true) {
    time_last = millis();
    time_current = abs(time_last - time_init);
    digitalWrite(powder_Relay_6, LOW);

    if (time_current >= time_powder_6) {
      digitalWrite(powder_Relay_6, HIGH);
      status_powder_6 = false;
    }
  }
  while (status_powder_7 == true) {
    time_last = millis();
    time_current = abs(time_last - time_init);
    digitalWrite(powder_Relay_7, LOW);

    if (time_current >= time_powder_7) {
      digitalWrite(powder_Relay_7, HIGH);
      status_powder_7 = false;
    }
  }
  while (status_powder_8 == true) {
    time_last = millis();
    time_current = abs(time_last - time_init);
    digitalWrite(powder_Relay_8, LOW);

    if (time_current >= time_powder_8) {
      digitalWrite(powder_Relay_8, HIGH);
      status_powder_8 = false;
    }
  }
  while (status_powder_9 == true) {
    time_last = millis();
    time_current = abs(time_last - time_init);
    digitalWrite(powder_Relay_9, LOW);

    if (time_current >= time_powder_9) {
      digitalWrite(powder_Relay_9, HIGH);
      status_powder_9 = false;
    }
  }
}

void Fluid() {
  while (status_pump_0 == true) {
    time_last = millis();
    time_current = abs(time_last - time_init);

    digitalWrite(pump_R_0 , LOW);
    digitalWrite(pump_L_0 , HIGH);

    if ( time_current >= time_pump_0) {
      digitalWrite(pump_R_0 , LOW);
      digitalWrite(pump_L_0 , LOW);
      Serial.println(time_current);
      status_pump_0 = false;
    }
  }

  while (status_pump_1 == true) {
    time_last = millis();
    time_current = abs(time_last - time_init);

    digitalWrite(pump_R_1, LOW);
    digitalWrite(pump_L_1, HIGH);

    if ( time_current >= time_pump_1) {
      digitalWrite(pump_R_1 , LOW);
      digitalWrite(pump_L_1 , LOW);
      Serial.println(time_current);
      status_pump_1 = false;
    }
  }
  while (status_pump_2 == true) {
    time_last = millis();
    time_current = abs(time_last - time_init);

    digitalWrite(pump_R_2, LOW);
    digitalWrite(pump_L_2, HIGH);

    if ( time_current >= time_pump_2) {
      digitalWrite(pump_R_2 , LOW);
      digitalWrite(pump_L_2 , LOW);
      Serial.println(time_current);
      status_pump_2 = false;
    }
  }
  while (status_pump_3 == true) {
    time_last = millis();
    time_current = abs(time_last - time_init);

    digitalWrite(pump_R_3, LOW);
    digitalWrite(pump_L_3, HIGH);

    if ( time_current >= time_pump_3) {
      digitalWrite(pump_R_3 , LOW);
      digitalWrite(pump_L_3 , LOW);
      Serial.println(time_current);
      status_pump_3 = false;
    }
  }
  while (status_pump_4 == true) {
    time_last = millis();
    time_current = abs(time_last - time_init);

    digitalWrite(pump_R_4, LOW);
    digitalWrite(pump_L_4, HIGH);

    if ( time_current >= time_pump_4) {
      digitalWrite(pump_R_4 , LOW);
      digitalWrite(pump_L_4 , LOW);
      Serial.println(time_current);
      status_pump_4 = false;
    }
  }
  while (status_pump_5 == true) {
    time_last = millis();
    time_current = abs(time_last - time_init);

    digitalWrite(pump_R_5, LOW);
    digitalWrite(pump_L_5, HIGH);

    if ( time_current >= time_pump_5) {
      digitalWrite(pump_R_5 , LOW);
      digitalWrite(pump_L_5 , LOW);
      Serial.println(time_current);
      status_pump_5 = false;
    }
  }
  while (status_pump_6 == true) {
    time_last = millis();
    time_current = abs(time_last - time_init);

    digitalWrite(pump_R_6, LOW);
    digitalWrite(pump_L_6, HIGH);

    if ( time_current >= time_pump_6) {
      digitalWrite(pump_R_6 , LOW);
      digitalWrite(pump_L_6 , LOW);
      Serial.println(time_current);
      status_pump_6 = false;
    }
  }
  while (status_pump_7 == true) {
    time_last = millis();
    time_current = abs(time_last - time_init);

    digitalWrite(pump_R_7, LOW);
    digitalWrite(pump_L_7, HIGH);

    if ( time_current >= time_pump_7) {
      digitalWrite(pump_R_7 , LOW);
      digitalWrite(pump_L_7 , LOW);
      Serial.println(time_current);
      status_pump_7 = false;
    }
  }
  while (status_pump_8 == true) {
    time_last = millis();
    time_current = abs(time_last - time_init);

    digitalWrite(pump_R_8, LOW);
    digitalWrite(pump_L_8, HIGH);

    if ( time_current >= time_pump_8) {
      digitalWrite(pump_R_8 , LOW);
      digitalWrite(pump_L_8 , LOW);
      Serial.println(time_current);
      status_pump_8 = false;
    }
  }
  while (status_pump_9 == true) {
    time_last = millis();
    time_current = abs(time_last - time_init);

    digitalWrite(pump_R_9, LOW);
    digitalWrite(pump_L_9, HIGH);

    if ( time_current >= time_pump_9) {
      digitalWrite(pump_R_9 , LOW);
      digitalWrite(pump_L_9 , LOW);
      Serial.println(time_current);
      status_pump_9 = false;
    }
  }
}

void Canbus_Send_Data() {

  if (readString.length() > 0) {
    if (command_Main == "POT") {
      Serial.println(command_Main);
      Serial.println(readString.length());
      for (int i = 0 ; i < readString.length() ; i ++) {
        delay(3);
        canMsg2.data[0] = readString[i];
        canMsg3.data[0] = readString[i];
        canMsg4.data[0] = readString[i];
        mcp2515.sendMessage(&canMsg2);
        mcp2515.sendMessage(&canMsg3);
        mcp2515.sendMessage(&canMsg4);
      }
    }
    if (command_Main == "VER") {
      Serial.println(command_Main);
      Serial.println(readString.length());
      for (int i = 0 ; i < readString.length() ; i ++) {
        delay(3);
        canMsg2.data[0] = readString[i];
        canMsg3.data[0] = readString[i];
        canMsg4.data[0] = readString[i];
        mcp2515.sendMessage(&canMsg2);
        mcp2515.sendMessage(&canMsg3);
        mcp2515.sendMessage(&canMsg4);
      }
    }
    if (command_Main == "HOR") {
      Serial.println(command_Main);
      Serial.println(readString.length());
      for (int i = 0 ; i < readString.length() ; i ++) {
        delay(3);
        canMsg2.data[0] = readString[i];
        canMsg3.data[0] = readString[i];
        canMsg4.data[0] = readString[i];
        mcp2515.sendMessage(&canMsg2);
        mcp2515.sendMessage(&canMsg3);
        mcp2515.sendMessage(&canMsg4);
      }
    }
    if (command_Main == "RO1") {
      Serial.println(command_Main);
      Serial.println(readString.length());
      for (int i = 0 ; i < readString.length() ; i ++) {
        delay(3);
        canMsg2.data[0] = readString[i];
        canMsg3.data[0] = readString[i];
        canMsg4.data[0] = readString[i];
        mcp2515.sendMessage(&canMsg2);
        mcp2515.sendMessage(&canMsg3);
        mcp2515.sendMessage(&canMsg4);
      }
    }
    if (command_Main == "CO1") {
      Serial.println(command_Main);
      Serial.println(readString.length());
      for (int i = 0 ; i < readString.length() ; i ++) {
        delay(3);
        canMsg2.data[0] = readString[i];
        canMsg3.data[0] = readString[i];
        canMsg4.data[0] = readString[i];
        mcp2515.sendMessage(&canMsg2);
        mcp2515.sendMessage(&canMsg3);
        mcp2515.sendMessage(&canMsg4);
      }
    }
  }

  //readString = "";
}


void setup() {

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

  pinMode(powder_Relay_0, OUTPUT);
  pinMode(powder_Relay_1, OUTPUT);
  pinMode(powder_Relay_2, OUTPUT);
  pinMode(powder_Relay_3, OUTPUT);
  pinMode(powder_Relay_4, OUTPUT);
  pinMode(powder_Relay_5, OUTPUT);
  pinMode(powder_Relay_6, OUTPUT);
  pinMode(powder_Relay_7, OUTPUT);
  pinMode(powder_Relay_8, OUTPUT);
  pinMode(powder_Relay_9, OUTPUT);

  pinMode(pump_R_0, OUTPUT);
  pinMode(pump_L_0, OUTPUT);
  pinMode(pump_L_1, OUTPUT);
  pinMode(pump_R_1, OUTPUT);
  pinMode(pump_L_2, OUTPUT);
  pinMode(pump_R_2, OUTPUT);
  pinMode(pump_L_3, OUTPUT);
  pinMode(pump_R_3, OUTPUT);
  pinMode(pump_L_4, OUTPUT);
  pinMode(pump_R_4, OUTPUT);
  pinMode(pump_L_5, OUTPUT);
  pinMode(pump_R_5, OUTPUT);
  pinMode(pump_L_6, OUTPUT);
  pinMode(pump_R_6, OUTPUT);
  pinMode(pump_L_7, OUTPUT);
  pinMode(pump_R_7, OUTPUT);
  pinMode(pump_L_8, OUTPUT);
  pinMode(pump_R_8, OUTPUT);
  pinMode(pump_L_9, OUTPUT);
  pinMode(pump_R_9, OUTPUT);

  digitalWrite(powder_Relay_0, HIGH);
  digitalWrite(powder_Relay_1, HIGH);
  digitalWrite(powder_Relay_2, HIGH);
  digitalWrite(powder_Relay_3, HIGH);
  digitalWrite(powder_Relay_4, HIGH);
  digitalWrite(powder_Relay_5, HIGH);
  digitalWrite(powder_Relay_6, HIGH);
  digitalWrite(powder_Relay_7, HIGH);
  digitalWrite(powder_Relay_8, HIGH);
  digitalWrite(powder_Relay_9, HIGH);

}

void loop() {
  read_data();
  Canbus_Send_Data();
  Powder();
  Fluid();
  readString = "";

}

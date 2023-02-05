#include <SPI.h>          //Library for using SPI Communication 
#include <mcp2515.h>      //Library for using CAN Communication

struct can_frame canMsg1;
struct can_frame canMsg2;
struct can_frame canMsg3;
struct can_frame canMsg4;
struct can_frame canMsg5;
struct can_frame canMsg6;

MCP2515 mcp2515(53); // chip select pin 10

String feedback     ;
String readString   ;
String command_Main ;
String command_Dir  ;
String command_Step ;
String command_Stop ;

int limit_switch = 22 ;
bool state_top  ;

int step_Ver_1 = 2 ;
int step_Ver_2 = 3 ;
int step_Hor_1 = 4 ;
int step_Pot_1 = 12;

int dir_Ver_1 = 5 ;
int dir_Ver_2 = 6 ;
int dir_Hor_1 = 7 ;
int dir_Pot_1 = 13;

#define EN_VER_1 8
#define EN_VER_2 9
#define EN_HOR_1 10
#define EN_POT_1 11

bool status_Pot   = false ;
bool status_Hor   = false ;
bool status_Ver   = false ;
bool status_Stop  = false ;

int step_Con = 0;

void read_data() {

  while (readString.length() < 10 ) {
    // while (readString != '\n') {
    if (mcp2515.readMessage(&canMsg4) == MCP2515::ERROR_OK )
    {

      if (canMsg4.can_id == 0xDD  ) {
        //delay(3);
        char c = canMsg4.data[0];
        readString += c;
        Serial.println(readString);
      }
    }
  }
  //POT+001000N
  //HOR+001000N
  //VER+001000N
  if (readString.length() > 0) {

    command_Main = readString.substring(0, 3);
    command_Dir  = readString.substring(3, 4);  // PO1+,PU1-
    command_Step = readString.substring(4, 10); // 005000 = 5 sec
    command_Stop = readString.substring(0, 4);  // STOP
  }
  if (command_Main == "POT")
  {
    Serial.println("debug pot");
    step_Con = command_Step.toInt();
    status_Pot = true ;
  }
  if (command_Main == "VER")
  {
    step_Con = command_Step.toInt();
    status_Ver = true ;
  }
  if (command_Main == "HOR")
  {
    step_Con = command_Step.toInt();
    status_Hor = true ;
  }
  if (command_Stop == "STOP")
  {
    status_Stop = true ;
  }
  readString = "";
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

  pinMode(step_Ver_1, OUTPUT);
  pinMode(step_Ver_2, OUTPUT);
  pinMode(step_Hor_1, OUTPUT);
  pinMode(step_Pot_1, OUTPUT);
  pinMode(dir_Ver_1, OUTPUT);
  pinMode(dir_Ver_2, OUTPUT);
  pinMode(dir_Hor_1, OUTPUT);
  pinMode(dir_Pot_1, OUTPUT);

  pinMode (EN_VER_1, OUTPUT);
  pinMode (EN_VER_2, OUTPUT);
  pinMode (EN_HOR_1, OUTPUT);
  pinMode (EN_POT_1, OUTPUT);
  digitalWrite (EN_VER_1, HIGH); // stop work
  digitalWrite (EN_VER_2, HIGH);
  digitalWrite (EN_HOR_1, HIGH);
  digitalWrite (EN_POT_1, HIGH);

  pinMode(limit_switch, INPUT_PULLUP);


}

void Control_Vertical() {
  state_top = digitalRead(limit_switch);

  if (status_Ver == true) {
    digitalWrite (EN_VER_1, LOW);
    digitalWrite (EN_VER_2, LOW);
    Serial.println("status_VER");
    if (command_Dir == "+") {
      digitalWrite(dir_Ver_1, LOW);
      digitalWrite(dir_Ver_2, LOW);
    }
    else if (command_Dir == "-") {
      digitalWrite(dir_Ver_1, HIGH);
      digitalWrite(dir_Ver_2, HIGH);
    }
    for (int i = 0; i <= step_Con ; i++) {
      digitalWrite(step_Ver_1, HIGH);
      digitalWrite(step_Ver_2, HIGH);
      //delay(1);
      digitalWrite(step_Ver_1, LOW);
      digitalWrite(step_Ver_2, LOW);

      delayMicroseconds(1500);
      /*  state_top = digitalRead(limit_switch);
        Serial.println(state_top);


        if (state_top == 1) {
          status_Ver = false ;
          Serial.println("Stop Vertical");
          break;
        }*/
    }
    digitalWrite (EN_VER_1, HIGH);
    digitalWrite (EN_VER_2, HIGH);
    status_Ver = false ;
  }
}
////////////////////////////////////////////////////////////
void Control_Horizontal() {
  if (status_Hor == true) {
    digitalWrite (EN_HOR_1, LOW);
    delay(5);
    if (command_Dir == "+") {
      digitalWrite(dir_Hor_1, LOW);
      Serial.println("+++++");
    }
    else if (command_Dir == "-") {
      digitalWrite(dir_Hor_1, HIGH);
      Serial.println("----");
    }
    for (int i = 0; i < step_Con; i++) {
      digitalWrite(step_Hor_1, HIGH);
      //delay(2);
      //delayMicroseconds(1000);
      digitalWrite(step_Hor_1, LOW);
      delay(1);
      //delayMicroseconds(2000);

      /*  state_top = digitalRead(limit_switch);
        Serial.println(state_top);


        if (state_top == 1) {
          status_Ver = false ;
          Serial.println("Stop Vertical");
          break;
        }*/
    }
    digitalWrite (EN_HOR_1, HIGH);
    status_Hor = false ;
  }
}
//////////////////////////////////////////////////////////////////////

void Control_Pot() {
  if (status_Pot == true) {
    digitalWrite (EN_POT_1, LOW);
    Serial.println("POT555");
    if (command_Dir == "+") {
      Serial.println("++++");
      digitalWrite(dir_Pot_1, LOW);
    }
    else if (command_Dir == "-") {
      digitalWrite(dir_Pot_1, HIGH);
    }

    for (int i = 0; i < step_Con; i++) {
      digitalWrite(step_Pot_1, HIGH);
      delayMicroseconds(1000);          //1000
      digitalWrite(step_Pot_1, LOW);
      delayMicroseconds(1000);          //1000
    }
    digitalWrite (EN_POT_1, HIGH);
    status_Pot = false ;

  }
  canMsg4.data[0] = ' ';

}

void loop() {
  read_data();
  Control_Vertical();
  Control_Horizontal();
  Control_Pot();
  readString = "";
}

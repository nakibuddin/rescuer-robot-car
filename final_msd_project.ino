#include "DHT.h"
#include <Keypad.h>
#include <LiquidCrystal.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'7','8','9','/'},
  {'4','5','6','*'},
  {'1','2','3','-'},
  {'c','0','=','+'}
};
byte rowPins[ROWS] = {18,19,20,21}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {22,23,24,25}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

const int rs = 13, e = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, e, d4, d5, d6, d7);

#define DHTPIN 3
#define DHTTYPE DHT22       // DHT22 sensor is used
DHT dht(DHTPIN, DHTTYPE);   // Initialize DHT library


int a=0, b=0, c=0, x=0, y=0, z=0, m=0, n=0, spd=1020, val=0, max_=0, min_=0, otv=0, L=4;
int ldr=A0;
int lm35=A3;
int lm35_value=0;
int car_light=0;
int buzz=53;
int water_sensor=36;
int gas_sensor=52;
int fire_sensor=50;
int warning_led=35;
int warning_led2=37;
int ldr_value = 0;
int torch=49;




const int f_echoPin = 47; // Echo Pin of Ultrasonic Sensor
const int f_trigerPin = 46;
const int b_echoPin = 45;
const int b_trigerPin = 44;

int front_left_led=17;
int front_right_led=34;
int back_left_led=32;
int back_right_led=33;

int Fornt_LeftMotorForward = 7;
int Fornt_LeftMotorReverse = 6; 

int Fornt_RightMotorForward = 5;
int Fornt_RightMotorReverse = 4; 


int Back_LeftMotorForward = 27;
int Back_LeftMotorReverse = 28; 

int Back_RightMotorForward = 29;
int Back_RightMotorReverse = 30;

int pump_motor_forward=48;
int pump_motor_reverse=51;
  
void setup()
{
  //Serial.begin(9600);
  //lcd.setCursor(11, 1);
  //lcd.clear();
  //delay(1500);
  //lcd.blink();
  //lcd.cursor();
  //lcd.noCursor();
  //lcd.noBlink();
  
  lcd.begin(20, 4);
  dht.begin();

  lcd.setCursor(3,0); lcd.print("WELCOME TO OUR");
  lcd.setCursor(6,1); lcd.print("PROJECT");
  lcd.setCursor(1,3); lcd.print("RESCUER ROBOT CAR");
  delay(1000);
  
  lcd.clear();
  lcd.setCursor(4,0); lcd.print("INSTRUCTION"); 
  lcd.setCursor(0,1); lcd.print("7 FOR FORWARD");
  lcd.setCursor(0,2); lcd.print("8 FOR BACKWARD");
  lcd.setCursor(0,3); lcd.print("4FOR LEFT 5FOR RIGHT");
  delay(700);
  lcd.clear();
  lcd.setCursor(1,1); lcd.print("PRESS 0 FOR MORE"); 
  lcd.setCursor(4,2); lcd.print("INSTRUCTION");
  delay(500);
  lcd.clear(); 
  lcd.setCursor(4,0); lcd.print("INSTRUCTION"); 
  lcd.setCursor(0,1); lcd.print("7 FOR FORWARD");
  lcd.setCursor(0,2); lcd.print("8 FOR BACKWARD");
  lcd.setCursor(0,3); lcd.print("4FOR LEFT 5FOR RIGHT");
  
  
  pinMode(Fornt_LeftMotorForward, OUTPUT);  
  pinMode(Fornt_LeftMotorReverse, OUTPUT);  
  pinMode(Fornt_RightMotorForward, OUTPUT);  
  pinMode(Fornt_RightMotorReverse, OUTPUT); 

  pinMode(Back_LeftMotorForward, OUTPUT);  
  pinMode(Back_LeftMotorReverse, OUTPUT);  
  pinMode(Back_RightMotorForward, OUTPUT);  
  pinMode(Back_RightMotorReverse, OUTPUT);
  
  pinMode(pump_motor_forward, OUTPUT);  
  pinMode(pump_motor_reverse, OUTPUT);

  pinMode(front_left_led, OUTPUT);
  pinMode(front_right_led, OUTPUT);
  pinMode(back_left_led, OUTPUT);
  pinMode(back_right_led, OUTPUT);

  pinMode(buzz, OUTPUT);
  pinMode(warning_led, OUTPUT);
  pinMode(warning_led2, OUTPUT); 
  pinMode(torch, OUTPUT);
  
  pinMode(gas_sensor, INPUT);
  pinMode(fire_sensor, INPUT);
  pinMode(water_sensor, INPUT);     

  pinMode(f_trigerPin, OUTPUT);
  pinMode(f_echoPin, INPUT);
  pinMode(b_trigerPin, OUTPUT);
  pinMode(b_echoPin, INPUT);   
  delay(50);
}

long f_duration, f_cm;
long b_duration, b_cm;
int i=0, f_ultra=0, f_running=0, f_soon=0;
int j=0, b_ultra=0, b_running=0, b_soon=0;

double RH;
double Temp;

void loop() {    
  char key = customKeypad.getKey();

  //tone(buzz,1000);
  //delay(2000);
  
  /*
  if (key=='*' && a==0){
    lcd.clear();
    lcd.print(key);
    
    a=1;
  }
  else if(key=='1' && a==1 && b==0) 
  {
    lcd.print(key);
    b=1; 
  }
  else if(key=='4'&& b==1 && c==0) 
  {
    lcd.print(key);
    c=1; 
  }
  else if(a==0 || b==0 || c==0)
  {
    //lcd.clear();
    //lcd.setCursor(0,2);
    //lcd.print("WRONG PASSWORD");  
    a=0;
    b=0;
    c=0;
    goto end ;
  } */
    
  
  ldr_value= analogRead(ldr);                                   //detect enought light or not
  if(ldr_value<100)
    digitalWrite(torch,HIGH);
  else
    digitalWrite(torch,LOW);
  
  //Serial.println("Intensity of the LDR is =");
  //Serial.println(value);
  //delay(500);
  

  if(digitalRead(gas_sensor)==HIGH && y==0)                        //detect present of gas
  {
    lcd.clear();
    lcd.setCursor(7,1); lcd.print("WARNING");
    lcd.setCursor(3,2); lcd.print("GAS IS DETECTED");            
    tone(buzz,1000);     
    y=1;
  }
  else if(digitalRead(gas_sensor)==LOW && y==1)
  {
    lcd.clear();
    lcd.setCursor(4,0); lcd.print("INSTRUCTION"); 
    lcd.setCursor(0,1); lcd.print("7 FOR FORWARD");
    lcd.setCursor(0,2); lcd.print("8 FOR BACKWARD");
    lcd.setCursor(0,3); lcd.print("4FOR LEFT 5FOR RIGHT");     
    noTone(buzz);    
    y=0;
  }
  if(y==1)
  {
    digitalWrite(warning_led,HIGH);
    delay(20);
    digitalWrite(warning_led,0);    
    delay(10);     
  }

  if(digitalRead(fire_sensor)==HIGH && z==0)                              //detect present of fire
  {
    lcd.clear();
    lcd.setCursor(7,1); lcd.print("WARNING");
    lcd.setCursor(2,2); lcd.print("Flame IS DETECTED");            
    tone(buzz,1000);     
    z=1;
  }
  else if(digitalRead(fire_sensor)==LOW && z==1)
  {
    lcd.clear();
    lcd.setCursor(4,0); lcd.print("INSTRUCTION"); 
    lcd.setCursor(0,1); lcd.print("7 FOR FORWARD");
    lcd.setCursor(0,2); lcd.print("8 FOR BACKWARD");
    lcd.setCursor(0,3); lcd.print("4FOR LEFT 5FOR RIGHT");   
    noTone(buzz);    
    z=0;
  }
  if(z==1)
  {
    digitalWrite(warning_led,HIGH);
    delay(20);
    digitalWrite(warning_led,0);    
    delay(10);     
  }

  /*if(digitalRead(gas_sensor)==HIGH && digitalRead(fire_sensor)==HIGH)
  {
    digitalWrite(warning_led2,HIGH);
    delay(20);
    digitalWrite(warning_led2,0);    
    delay(10);     
  } */
  
  if(digitalRead(water_sensor)==LOW && m==0)                          //detect water tank empty or not
  {
    lcd.clear();
    lcd.setCursor(6,1); lcd.print("WARNING");
    lcd.setCursor(0,2); lcd.print("WATAR TANK IS EMPTY");
    digitalWrite(pump_motor_forward, LOW); 
    digitalWrite(pump_motor_reverse, LOW);          
    tone(buzz,1000);    
    for(m=0;m<20;m++)
    {
      digitalWrite(warning_led,HIGH);
      delay(20);
      digitalWrite(warning_led,0);    
      delay(10);      
    }
    m=1;
    lcd.clear();
    lcd.setCursor(4,0); lcd.print("INSTRUCTION"); 
    lcd.setCursor(0,1); lcd.print("7 FOR FORWARD");
    lcd.setCursor(0,2); lcd.print("8 FOR BACKWARD");
    lcd.setCursor(0,3); lcd.print("4FOR LEFT 5FOR RIGHT");   
    noTone(buzz);     
  }
  else if(digitalRead(water_sensor)==HIGH && m==1)
  {
    m=0;
    lcd.clear();
    lcd.setCursor(4,0); lcd.print("INSTRUCTION"); 
    lcd.setCursor(0,1); lcd.print("7 FOR FORWARD");
    lcd.setCursor(0,2); lcd.print("8 FOR BACKWARD");
    lcd.setCursor(0,3); lcd.print("4FOR LEFT 5FOR RIGHT"); 
  }
  
  



  digitalWrite(f_trigerPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(f_trigerPin, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(f_trigerPin, LOW);
  
  f_duration = pulseIn(f_echoPin, HIGH);  // return microsecond  
  f_cm = f_duration / 29 / 2;
  
  if(f_cm<200 && i==0 && f_running==1)                                      //detect obstacle from front
  {
    lcd.clear();    
    lcd.setCursor(0,1); lcd.print("REMOVE OBSTACLE FROM");
    lcd.setCursor(7,2); lcd.print("FRONT");    
    
    digitalWrite(Fornt_LeftMotorForward, LOW); 
    digitalWrite(Fornt_LeftMotorReverse, LOW);
    digitalWrite(Fornt_RightMotorForward, LOW); 
    digitalWrite(Fornt_RightMotorReverse, LOW);
    
    digitalWrite(Back_LeftMotorForward, LOW); 
    digitalWrite(Back_LeftMotorReverse, LOW);
    digitalWrite(Back_RightMotorForward, LOW); 
    digitalWrite(Back_RightMotorReverse, LOW); 
    x=0;
    digitalWrite(front_left_led,0);
    digitalWrite(front_right_led,0);     
    //digitalWrite(back_left_led,0);
    //digitalWrite(back_right_led,0); 
    i=1;
    f_ultra=1;
    f_soon=0;
  }
  else if(f_cm>200 && i==1)
  { 
    f_ultra=0;
    if(f_soon==0)
      key='7';
    i=0;
  }

  digitalWrite(b_trigerPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(b_trigerPin, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(b_trigerPin, LOW);
  
  b_duration = pulseIn(b_echoPin, HIGH);  // return microsecond
  b_cm = b_duration / 29 / 2;

  //lcd.clear();
  //lcd.setCursor(7,2); lcd.print(b_cm);   
  
  if(b_cm<200 && j==0 && b_running==1)                          //detect obstacle from back
  {
    lcd.clear();    
    lcd.setCursor(0,1); lcd.print("REMOVE OBSTACLE FROM");
    lcd.setCursor(7,2); lcd.print("BACK");    
    
    digitalWrite(Fornt_LeftMotorForward, LOW); 
    digitalWrite(Fornt_LeftMotorReverse, LOW);
    digitalWrite(Fornt_RightMotorForward, LOW); 
    digitalWrite(Fornt_RightMotorReverse, LOW);
    
    digitalWrite(Back_LeftMotorForward, LOW); 
    digitalWrite(Back_LeftMotorReverse, LOW);
    digitalWrite(Back_RightMotorForward, LOW); 
    digitalWrite(Back_RightMotorReverse, LOW); 
    x=0;
    digitalWrite(back_left_led,0);
    digitalWrite(back_right_led,0);     
    //digitalWrite(back_left_led,0);
    //digitalWrite(back_right_led,0); 
    j=1;
    b_ultra=1;
    b_soon=0;
  }
  else if(b_cm>200 && j==1)
  { 
    b_ultra=0;
    if(b_soon==0)
      key='8';
    j=0;
  }

  val = map(spd, 0, 1020, 0, 255); 
  
  if (key=='7' && f_ultra==0)                                   //car move Forward
  {      
    lcd.clear();
    lcd.setCursor(3,0); lcd.print("CAR IS MOVING");
    lcd.setCursor(6,1); lcd.print("FORWARD");
    lcd.setCursor(2,3); lcd.print("PRESS C FOR STOP"); 
    analogWrite(Fornt_LeftMotorForward, val); 
    digitalWrite(Fornt_LeftMotorReverse, LOW);
    analogWrite(Fornt_RightMotorForward, val); 
    digitalWrite(Fornt_RightMotorReverse, LOW);
    
    analogWrite(Back_LeftMotorForward, val); 
    digitalWrite(Back_LeftMotorReverse, LOW);
    analogWrite(Back_RightMotorForward, val); 
    digitalWrite(Back_RightMotorReverse, LOW); 
    x=3;
    digitalWrite(back_left_led,0);
    digitalWrite(back_right_led,0);
    b_soon=1;
    b_running=0;
    
    f_running=1;
  }
  else if(key=='7' && f_ultra==1)                               //remove obstacle then car move Forward
  {
    lcd.clear();    
    lcd.setCursor(0,1); lcd.print("REMOVE OBSTACLE FROM");
    lcd.setCursor(7,2); lcd.print("FRONT");
    digitalWrite(Fornt_LeftMotorForward, LOW); 
    digitalWrite(Fornt_LeftMotorReverse, LOW);
    digitalWrite(Fornt_RightMotorForward, LOW); 
    digitalWrite(Fornt_RightMotorReverse, LOW);
    
    digitalWrite(Back_LeftMotorForward, LOW); 
    digitalWrite(Back_LeftMotorReverse, LOW);
    digitalWrite(Back_RightMotorForward, LOW); 
    digitalWrite(Back_RightMotorReverse, LOW); 
    b_soon=1;
    b_running=0;
    
    f_soon=0; 
  }



  
  else if (key=='8' && b_ultra==0)                               //car move Backward
  {
    lcd.clear();
    lcd.setCursor(3,0); lcd.print("CAR IS MOVING");
    lcd.setCursor(6,1); lcd.print("BACKWARD");
    lcd.setCursor(2,3); lcd.print("PRESS C FOR STOP"); 
    digitalWrite(Fornt_LeftMotorForward, LOW); 
    analogWrite(Fornt_LeftMotorReverse, val);
    digitalWrite(Fornt_RightMotorForward, LOW); 
    analogWrite(Fornt_RightMotorReverse, val);
    
    digitalWrite(Back_LeftMotorForward, LOW); 
    analogWrite(Back_LeftMotorReverse, val);
    digitalWrite(Back_RightMotorForward, LOW); 
    analogWrite(Back_RightMotorReverse, val);
    x=4;
    digitalWrite(front_left_led,0);
    digitalWrite(front_right_led,0); 
    f_soon=1;
    f_running=0;
       
    b_running=1;    
  } 
  else if(key=='8' && b_ultra==1)                            // remove obstacle then car move Backward
  {
    lcd.clear();    
    lcd.setCursor(0,1); lcd.print("REMOVE OBSTACLE FROM");
    lcd.setCursor(7,2); lcd.print("BACK");
    digitalWrite(Fornt_LeftMotorForward, LOW); 
    digitalWrite(Fornt_LeftMotorReverse, LOW);
    digitalWrite(Fornt_RightMotorForward, LOW); 
    digitalWrite(Fornt_RightMotorReverse, LOW);
    
    digitalWrite(Back_LeftMotorForward, LOW); 
    digitalWrite(Back_LeftMotorReverse, LOW);
    digitalWrite(Back_RightMotorForward, LOW); 
    digitalWrite(Back_RightMotorReverse, LOW); 
    f_soon=1;
    f_running=0;
    
    b_soon=0; 
  }



  
  else if (key=='4')                                         // car turning Left
  {
    lcd.clear();
    lcd.setCursor(3,0); lcd.print("CAR IS TURNING");
    lcd.setCursor(7,1); lcd.print("LEFT");
    lcd.setCursor(2,3); lcd.print("PRESS C FOR STOP"); 
    digitalWrite(Fornt_LeftMotorForward, LOW); 
    digitalWrite(Fornt_LeftMotorReverse, LOW);
    digitalWrite(Fornt_RightMotorForward, HIGH); 
    digitalWrite(Fornt_RightMotorReverse, LOW);
    
    digitalWrite(Back_LeftMotorForward, LOW); 
    digitalWrite(Back_LeftMotorReverse, LOW);
    analogWrite(Back_RightMotorForward, spd); 
    digitalWrite(Back_RightMotorReverse, LOW);  
    x=1;
    digitalWrite(front_right_led,0);
    digitalWrite(back_right_led,0);
    f_soon=1;
    f_running=0;
    b_soon=1;
    b_running=0;
  }
  else if (key=='5')                                             // car turning Right
  {
    lcd.clear();
    lcd.setCursor(3,0); lcd.print("CAR IS TURNING");
    lcd.setCursor(7,1); lcd.print("RIGHT");
    lcd.setCursor(2,3); lcd.print("PRESS C FOR STOP"); 
    digitalWrite(Fornt_LeftMotorForward, HIGH); 
    digitalWrite(Fornt_LeftMotorReverse, LOW);
    digitalWrite(Fornt_RightMotorForward, LOW); 
    digitalWrite(Fornt_RightMotorReverse, LOW);
    
    analogWrite(Back_LeftMotorForward, spd); 
    digitalWrite(Back_LeftMotorReverse, LOW);
    digitalWrite(Back_RightMotorForward, LOW); 
    digitalWrite(Back_RightMotorReverse, LOW);  
    x=2;
    digitalWrite(front_left_led,0);
    digitalWrite(back_left_led,0);
    f_soon=1;
    f_running=0;
    b_soon=1;
    b_running=0;
  }
  else if (key=='c')                                               // car Stop
  {
    lcd.clear();
    lcd.setCursor(4,0); lcd.print("INSTRUCTION"); 
    lcd.setCursor(0,1); lcd.print("7 FOR FORWARD");
    lcd.setCursor(0,2); lcd.print("8 FOR BACKWARD");
    lcd.setCursor(0,3); lcd.print("4FOR LEFT 5FOR RIGHT");
    digitalWrite(Fornt_LeftMotorForward, LOW); 
    digitalWrite(Fornt_LeftMotorReverse, LOW);
    digitalWrite(Fornt_RightMotorForward, LOW); 
    digitalWrite(Fornt_RightMotorReverse, LOW);
    
    digitalWrite(Back_LeftMotorForward, LOW); 
    digitalWrite(Back_LeftMotorReverse, LOW);
    digitalWrite(Back_RightMotorForward, LOW); 
    digitalWrite(Back_RightMotorReverse, LOW); 
    x=0;
    digitalWrite(front_left_led,0);
    digitalWrite(front_right_led,0);     
    digitalWrite(back_left_led,0);
    digitalWrite(back_right_led,0); 
    f_soon=1;
    f_running=0;
    b_soon=1;
    b_running=0;
  }
  else if(key=='/' && car_light==0)                               //car's light activated function
  {
    lcd.clear();
    lcd.setCursor(0,1); lcd.print("CAR'S LIGHT FUNCTION");
    lcd.setCursor(4,2); lcd.print("IS ACTIVATED");
    car_light=1;
  }   
  else if(key=='/' && car_light==1 )                              //car's light deactivated function
  {
    lcd.clear();
    lcd.setCursor(0,1); lcd.print("CAR'S LIGHT FUNCTION");
    lcd.setCursor(3,2); lcd.print("IS DEACTIVATED");    
    car_light=0;
    digitalWrite(front_left_led,0);
    digitalWrite(front_right_led,0);     
    digitalWrite(back_left_led,0);
    digitalWrite(back_right_led,0); 
  }
  else if(key=='1')                                              // show surrundings information
  {
    lcd.clear();
    lcd.setCursor(2,0); lcd.print("SURROUNDINGS I.");
    
    if(digitalRead(fire_sensor)==HIGH){
      lcd.setCursor(0,1); lcd.print("FLAME: PRESENT");}    
    else{
      lcd.setCursor(0,1); lcd.print("FLAME: ABSENT");}
    
    if(digitalRead(gas_sensor)==HIGH){
      lcd.setCursor(0,2); lcd.print("GAS: PRESENT");}
    else{
      lcd.setCursor(0,2); lcd.print("GAS: ABSENT");}

    if(ldr_value<100){
      lcd.setCursor(0,3); lcd.print("LIGHT: NOT ENOUGH");}
    else{
      lcd.setCursor(0,3); lcd.print("LIGHT: ENOUGH");}    
  }
  else if(key=='2')                                           // show surrundings information
  {    
    lcd.clear();
    lcd.setCursor(2,0); lcd.print("SURROUNDINGS I.");
    RH = dht.readHumidity();
    Temp = dht.readTemperature();
    
    lm35_value = analogRead(lm35);
    float milivolts = ( lm35_value/1024.0)*5000; 
    float cel = milivolts/10;   
    
    if(isnan(RH)){
      lcd.setCursor(0,1); lcd.print("HUMIDITY: ERROR");}
    else{
      lcd.setCursor(0,1); lcd.print("HUMIDITY: "); lcd.print(RH);}
    if(isnan(Temp)){
      lcd.setCursor(0,2); lcd.print("Temp: ERROR");  lcd.print("C (DHT)");}
    else{
      lcd.setCursor(0,2); lcd.print("TEMP: "); lcd.print(Temp);  lcd.print("C (DHT)");} 
    lcd.setCursor(0,3); lcd.print("TEMP: "); lcd.print(cel);  lcd.print("C (LM35)");  
  } 
  else if(key=='*' && n==0 && m==0)                                                           //water pump running
  {
    digitalWrite(pump_motor_forward, HIGH); 
    digitalWrite(pump_motor_reverse, LOW); 
    n=1;
    lcd.clear();
    lcd.setCursor(3,1); lcd.print("WATER PUMP IS");
    lcd.setCursor(6,2); lcd.print("RUNNING");
  }
  else if(key=='*' && n==1 )                                    //water pump off
  {
    digitalWrite(pump_motor_forward, LOW); 
    digitalWrite(pump_motor_reverse, LOW);
    n=0;
    lcd.clear();
    lcd.setCursor(4,0); lcd.print("INSTRUCTION"); 
    lcd.setCursor(0,1); lcd.print("7 FOR FORWARD");
    lcd.setCursor(0,2); lcd.print("8 FOR BACKWARD");
    lcd.setCursor(0,3); lcd.print("4FOR LEFT 5FOR RIGHT");
  }
  else if(key=='*' && m==1)                                        //water tank empty
  {
    lcd.clear();
    lcd.setCursor(0,1); lcd.print("FILL THE WATER TANK");
    lcd.setCursor(6,2); lcd.print("FIRST"); 
  }
  else if(key=='0')                                                 //show instruction
  {
    lcd.clear();
    lcd.setCursor(4,0); lcd.print("INSTRUCTION"); 
    lcd.setCursor(0,1); lcd.print("1 FOR SURROUNDINGS I.");
    lcd.setCursor(0,2); lcd.print("2 FOR SURROUNDINGS I.");
    lcd.setCursor(0,3); lcd.print("3 FOR SYSTEM I.");
  }
  else if(key=='=')                                                 //show instruction
  {
    lcd.clear();
    lcd.setCursor(4,0); lcd.print("INSTRUCTION");
    lcd.setCursor(0,1); lcd.print("* FOR WATER PUMP C."); 
    lcd.setCursor(0,2); lcd.print("/ FOR CAR'S LIGHT C.");    
    lcd.setCursor(0,3); lcd.print("+ & - FOR CAR'S B.C.");
  }
  else if(key=='3')
  {
    lcd.clear();
    lcd.setCursor(4,0); lcd.print("SYSTEM INFO.");
    
    if(digitalRead(water_sensor)==HIGH){
      lcd.setCursor(0,2); lcd.print("WATER TANK: FULL");}    
    else{
      lcd.setCursor(0,2); lcd.print("WATER TANK: EMPTY");}
    lcd.setCursor(0,3); lcd.print("CAR'S SPEED LAVEL:");
    lcd.print(L);
        
  }







  if((key=='+' && max_==1) || (key=='+' && otv==0) )                //max speed already exist
  {
    lcd.clear();
    lcd.setCursor(0,1); lcd.print("MAXIMUM SPEED LEVEL");
    lcd.setCursor(3,2); lcd.print("ALREADY EXIXT");
    
  }
  else if(key=='+' && spd<1020)                                      //car's speed up
  {
    
    lcd.clear();
    lcd.setCursor(2,1); lcd.print("CAR'S SPEED UP");
    if(spd==0){
      lcd.setCursor(5,2); lcd.print("LEVEL 1"); L=1;}
    else if(spd==255){
      lcd.setCursor(5,2); lcd.print("LEVEL 2"); L=2;}
    else if(spd==510){
      lcd.setCursor(5,2); lcd.print("LEVEL 3"); L=3;}
    else if(spd==765){
      lcd.setCursor(5,2); lcd.print("LEVEL 4");
      lcd.setCursor(3,3); lcd.print("MAXIMUM LEVEL");
      max_=1;      
      L=4;
      }
    min_=0;  
    spd=spd + 255;
  }

  if(key=='-' && min_==1)                                       //min speed already exist
  {
    lcd.clear();
    lcd.setCursor(0,1); lcd.print("MINIMUM SPEED LEVEL");
    lcd.setCursor(3,2); lcd.print("ALREADY EXIXT");
  }
  else if(key=='-' && spd>=255)                                   //car's speed down
  {
    lcd.clear();
    lcd.setCursor(2,1); lcd.print("CAR'S SPEED DOWN");
    if(spd==1020){
      lcd.setCursor(6,2); lcd.print("LEVEL 3"); L=3;}
    else if(spd==765){
      lcd.setCursor(6,2); lcd.print("LEVEL 2"); L=2;}
    else if(spd==510){
      lcd.setCursor(6,2); lcd.print("LEVEL 1"); L=1;}
    else if(spd==255){
      lcd.setCursor(6,2); lcd.print("LEVEL 0");
      lcd.setCursor(3,3); lcd.print("MINIMUM LEVEL");
      min_=1;
      L=0;
      }
    otv=1; 
    max_=0;  
    spd=spd - 255;
  }

  
  
  
  if(x==1 && car_light==1)                                             //car Turning Left light
  {            
    digitalWrite(front_left_led,0);
    digitalWrite(back_left_led,0);
    delay(5);  
    digitalWrite(front_left_led,HIGH);
    digitalWrite(back_left_led,HIGH);
    delay(5);
  }
  else if(x==2 && car_light==1)                                       //car Turning Right light
  {    
    digitalWrite(front_right_led,0);
    digitalWrite(back_right_led,0);
    delay(5);
    digitalWrite(front_right_led,HIGH);
    digitalWrite(back_right_led,HIGH);
    delay(5);  
  }
  else if(x==3 && car_light==1)                                       //car Moving Forward light
  {   
    digitalWrite(front_left_led,HIGH);
    digitalWrite(front_right_led,HIGH);    
  }
  else if(x==4 && car_light==1)                                       //car Moving Backward light
  {
    digitalWrite(back_left_led,HIGH);
    digitalWrite(back_right_led,HIGH); 
  } 
  
  
  if(key =='9' && x==3 && car_light==1)                                //car Moving Forward led off
  {    
    digitalWrite(front_left_led,0);
    digitalWrite(front_right_led,0);
    x=5;
  }
  else if(key=='9' && x==5 && car_light==1)                            //car Moving Forward led on
  {    
    digitalWrite(front_left_led,1);
    digitalWrite(front_right_led,1);
    x=3;
  }

 
   
  end:
  return;
}

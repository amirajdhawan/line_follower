//PWM Pins Defination
#define MOT1_EN 6
#define MOT2_EN 11

//Digital Pins for Motors
#define MOT1_IN1 3
#define MOT1_IN2 5

#define MOT2_IN1 10
#define MOT2_IN2 9

//Analog Pins for Sensors
#define SENSOR1 A0
#define SENSOR2 A1
#define SENSOR3 A2
#define SENSOR4 A3
#define SENSOR5 A4

int left_sensor_data = 0;
int right_sensor_data = 0;
int center_sensor_data = 0;
int spd = 0;
int spdstr = 255;

void setup(){
  pinMode(MOT1_EN,OUTPUT);
  pinMode(MOT2_EN,OUTPUT);
  pinMode(MOT1_IN1,OUTPUT);
  pinMode(MOT1_IN2,OUTPUT);
  pinMode(MOT2_IN1,OUTPUT);
  pinMode(MOT2_IN2,OUTPUT);
  pinMode(SENSOR1,INPUT);
  pinMode(SENSOR2,INPUT);
  pinMode(SENSOR3,INPUT);
  pinMode(SENSOR4,INPUT);
  pinMode(SENSOR5,INPUT);
  digitalWrite(MOT1_IN1,LOW);
  digitalWrite(MOT1_IN2,HIGH);
  digitalWrite(MOT2_IN1,LOW);
  digitalWrite(MOT2_IN2,HIGH);
  Serial.begin(9600);
}

void loop(){
  
  left_sensor_data = get_sensor_left_data();
  right_sensor_data = get_sensor_right_data();
  center_sensor_data = get_sensor_center_data();
  
  if(left_sensor_data > 375 && right_sensor_data < 375){
    spd = map(left_sensor_data,0,3000,0,255);
    move_left(spd);
  }
  else{
    if(right_sensor_data > 375 && left_sensor_data < 375){
      spd = map(right_sensor_data,0,3000,0,255);
      move_right(spd);
    }
    else{
      if(right_sensor_data > 375 && left_sensor_data > 375){
        move_stop();
      }
      else
        move_straight(spdstr);
    }
  }
  delay(50);
  //Serial.println(sensor_data);
  //delay(1000);
  /*move_straight(255);
  delay(2000);
  move_straight(0);
  delay(1000);
  move_left(255); 
  delay(1000);
  move_straight(255);
  delay(2000);*/
}
int get_sensor_right_data(){
  int data = 0;
  data += analogRead(SENSOR4);
  data += (analogRead(SENSOR5)*2);
  return data;
  
}

int get_sensor_left_data(){
  int data = 0;
  data += analogRead(SENSOR1);
  data += (analogRead(SENSOR2)*2);
  return data;
}

int get_sensor_center_data(){
  int data = 0;
  data += analogRead(SENSOR3);
  return data;

}

void move_straight(int spd){
  analogWrite(MOT1_EN,spd);
  analogWrite(MOT2_EN,spd);
}

void move_left(int spd){
  analogWrite(MOT1_EN,spd);
  analogWrite(MOT2_EN,0);
}

void move_right(int spd){
  analogWrite(MOT1_EN,0);
  analogWrite(MOT2_EN,spd);
}

void move_stop(){
  analogWrite(MOT1_EN,0);
  analogWrite(MOT2_EN,0);
}

#define LEFT 3 
#define RIGHT 2
#define LP 5 //Скорость левого мотора
#define RP 13 //Скорость правого мотора
#define L1 12 //Направление вращения левого мотора
#define L2 4 //Напрвление вращения левого мотора 
#define R1 8 //Напрвление вращения правого мотора
#define R2 10 //Напрвление вращения правого мотора

#define SPEED_PERIOD 200
#define SPEED_PERIOD1 200

int disk = 20;
int time_lengh = 5;
int rad = (90 * disk * 3)/360;
volatile int pulses_l = 0;
volatile int pulses_r = 0;
int speed = 50; 

void counter1( void ){
  pulses_l++;
}

void counter2( void ){
  pulses_r++;
}

void into(){
   static unsigned long time;
  
  if ((millis() - time) >= SPEED_PERIOD){

    time = millis();

  
  int k_l = (pulses_r - pulses_l) * 6;
  int k_r = (pulses_l - pulses_r) * 3;

    Serial.print("\nl = ");
    Serial.print(pulses_l);
    Serial.print("\tr = ");
    Serial.print(pulses_r);

  int speed_l = speed + k_l;
  int speed_r = speed + k_r;

  analogWrite(LP, speed_l);
  analogWrite(RP, speed_r); 
  }
}
void stop(){     
  digitalWrite(L1, LOW);
  digitalWrite(L2, LOW);
  digitalWrite(R1, LOW);
  digitalWrite(R2, LOW);

 delay(500);
}

void turnRobot1(){     
  pulses_r = 0;
  pulses_l = 0;
  digitalWrite(L1, LOW);
  digitalWrite(L2, HIGH);
  digitalWrite(R1, HIGH);
  digitalWrite(R2, LOW);
  while (pulses_r <= (rad) || pulses_l <= (rad)){
     into();
  }

}

void turnRobot2(){     
  pulses_r = 0;
  pulses_l = 0;
  digitalWrite(L1, HIGH);
  digitalWrite(L2, LOW);
  digitalWrite(R1, LOW);
  digitalWrite(R2, HIGH);
  while (pulses_r <= (rad) || pulses_l <= (rad)){
     into();
  }

}

void setup( void ){
  Serial.begin(115200);

  pinMode(LEFT, INPUT);
  pinMode(RIGHT, INPUT);
  pinMode(L1,OUTPUT);
  pinMode(L2,OUTPUT);
  pinMode(R1,OUTPUT);
  pinMode(R2,OUTPUT);
  pinMode(LP,OUTPUT);
  pinMode(RP,OUTPUT);

  attachInterrupt(digitalPinToInterrupt(LEFT), counter1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(RIGHT), counter2, CHANGE);

  // По умолчанию моторы выключены  
  analogWrite(LP, 0);
  analogWrite(RP, 0);

  // Установка направления движения
  digitalWrite(L1,LOW);
  digitalWrite(L2,HIGH);
  digitalWrite(R1,LOW);
  digitalWrite(R2,HIGH);
}
 
void loop( ){
  for (int i = 0; i < 4; i++){
    while (pulses_r <= (disk * time_lengh) || pulses_l <= (disk * time_lengh)){
      into();
    }
    stop();
    turnRobot1();
    stop();

    pulses_r = 0;
    pulses_l = 0;

    digitalWrite(L1,LOW);
    digitalWrite(L2,HIGH);
    digitalWrite(R1,LOW);
    digitalWrite(R2,HIGH);
  }

  for (int j = 0; j < 4; j++){
    while (pulses_r <= (disk * time_lengh) || pulses_l <= (disk * time_lengh)){
      into();
    }
    stop();
    turnRobot2();
    stop();

    pulses_r = 0;
    pulses_l = 0;

    digitalWrite(L1,LOW);
    digitalWrite(L2,HIGH);
    digitalWrite(R1,LOW);
    digitalWrite(R2,HIGH);
  }
}





#define LEFT 3 
#define RIGHT 2
#define LP 5 //Скорость левого мотора
#define RP 13 //Скорость правого мотора
#define L1 12 //Направление вращения левого мотора
#define L2 4 //Напрвление вращения левого мотора 
#define R1 8 //Напрвление вращения правого мотора
#define R2 10 //Напрвление вращения правого мотора

#define HOLES_DISC 20
#define SPEED_PERIOD 200

volatile int pulses_l = 0;
volatile int pulses_r = 0;
int speed = 50;


void counter1( void ){
  pulses_l++;
}

void counter2( void ){
  pulses_r++;
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
 
void loop( void ){
  static unsigned long time;
  
  if ((millis() - time) >= SPEED_PERIOD){
    unsigned long delta_time = millis() - time; 
    time = millis();
  
    Serial.print("\nl = ");
    Serial.print(pulses_l);
    Serial.print("\tr = ");
    Serial.print(pulses_r);

  int k_l = (pulses_r - pulses_l) * 6;
  int k_r = (pulses_l - pulses_r) * 3;

  int speed_l = speed + k_l;
  int speed_r = speed + k_r;

    analogWrite(LP, speed_l);
    analogWrite(RP, speed_r);

    Serial.print("\nsl = ");
    Serial.print(speed + k_l);
    Serial.print("\tsr = ");
    Serial.print(speed + k_r);
  }

 
}
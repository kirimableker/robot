#define LEFT 3 
#define RIGHT 2
#define LP 5 //Скорость левого мотора
#define RP 13 //Скорость правого мотора
#define L1 12 //Направление вращения левого мотора
#define L2 4 //Напрвление вращения левого мотора 
#define R1 8 //Напрвление вращения правого мотора
#define R2 10 //Напрвление вращения правого мотора

#define SPEED_PERIOD 100

const int circle_big_d = 900;  
const int platform_wheels_distante = 118;    
const int wheel_d = 62;
const int tact_one_rmp = 40;
const int circle_small_d = circle_big_d - (platform_wheels_distante * 2);
const int wheel_length = PI * wheel_d; //Длина окружности колеса
const int circle_big_length = PI * circle_big_d;
const int circle_small_length = PI * circle_small_d;
const int circle_big_tact = ((long)tact_one_rmp * (long)circle_big_length)/(long)wheel_length;
const int circle_small_tact = ((long)tact_one_rmp * (long)circle_small_length)/(long)wheel_length;
const float tact_ratio = (float)circle_small_tact/(float)circle_big_tact;
volatile int pulses_l = 0;
volatile int pulses_r = 0;
const int speed_l = 80; 
int speed_r = ((long)speed_l * (long)circle_small_tact)/(long)circle_big_tact;
 
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

    Serial.print("\nl = ");
    Serial.print(pulses_l);
    Serial.print("\tr = ");
    Serial.print(pulses_r);
    Serial.print("\tspeed_l = ");
    Serial.print(speed_l);
    Serial.print("\tspeed_r = ");
    Serial.print(speed_r);


    if (((float)speed_r/(float)speed_l) < (float)tact_ratio){
      if (speed_r < (speed_l * 2)){
        speed_r++; 
      }
    } 
    else if (((float)speed_r/(float)speed_l) > (float)tact_ratio){
      if (speed_r > 0){
        speed_r--; 
      }
    }
    analogWrite(LP, speed_l);
    analogWrite(RP, speed_r);
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
  delay(1000);
  // Установка направления движения
  digitalWrite(L1,LOW);
  digitalWrite(L2,HIGH);
  digitalWrite(R1,LOW);
  digitalWrite(R2,HIGH);

    Serial.print("\nl = ");
    Serial.print(pulses_l);
    Serial.print("\tr = ");
    Serial.print(pulses_r);
    Serial.print("\nsl = ");
    Serial.print(speed_l);
    Serial.print("\tsr = ");
    Serial.print(speed_r);
    Serial.print("\nwheel_length = ");
    Serial.print(wheel_length);
    Serial.print("\tcircle_small_d = ");
    Serial.print(circle_small_d);
    Serial.print("\nscircle_big_length = ");
    Serial.print(circle_big_length);
    Serial.print("\tcircle_small_length = ");
    Serial.print(circle_small_length);
    Serial.print("\ncircle_big_tact = ");
    Serial.print(circle_big_tact);
    Serial.print("\tcircle_small_tact = ");
    Serial.print(circle_small_tact);
    Serial.print("\ntact_ratio = ");
    Serial.print(tact_ratio);
    Serial.print("\tspeed_r = ");
    Serial.print(speed_r);

}
 
void loop( ){
    into();
}





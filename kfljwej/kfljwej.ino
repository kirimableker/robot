#define LEFT 1 
#define RIGHT 2
#define LP 5 //Скорость левого мотора
#define RP 13 //Скорость правого мотора
#define L1 12 //Направление вращения левого мотора
#define L2 4 //Напрвление вращения левого мотора 
#define R1 8 //Напрвление вращения правого мотора
#define R2 10 //Напрвление вращения правого мотора

#define HOLES_DISC 20
#define SPEED_LOG_PERIOD_MS 200

volatile unsigned int pulses1 = 0;
volatile unsigned int pulses2 = 0;
float rpm1;
float rpm2;

unsigned long timeOld = 0;
int speed = 50;

void counter1( void ){
 pulses1++;
}

void counter2( void ){
 pulses2++;
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
  // Установка скорости движения
  analogWrite(LP, speed);
  analogWrite(RP, speed);
}
 
void loop( void ){
  if ((millis() - timeOld) >= SPEED_LOG_PERIOD_MS){
    rpm1 = (float)pulses1 * ((60.0f * 1000.0f) / (float)(HOLES_DISC * SPEED_LOG_PERIOD_MS));
    rpm2 = (float)pulses2 * ((60.0f * 1000.0f) / (float)(HOLES_DISC * SPEED_LOG_PERIOD_MS));
    Serial.print("\nl = ");
    Serial.print(rpm1);
    Serial.print("\tr = ");
    Serial.print(rpm2);
    timeOld = millis();
    pulses1 = 0; // Сбрасываем счетчики импульсов
    pulses2 = 0;
  }
}
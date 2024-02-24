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

volatile int pulses_l = 0;
volatile int pulses_r = 0;
const int speed = 50;

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
  // Установка скорости движения
  analogWrite(LP, speed + 10);
  analogWrite(RP, speed);
}
 
void loop( void ){
  static unsigned long timestamp_rpm_measurement;
  if ((millis() - timestamp_rpm_measurement) >= SPEED_LOG_PERIOD_MS){
    // Храним прошлое значение импульсов
    static int pulses_l_old = 0;
    static int pulses_r_old = 0;
    // Узнаем время, которое прошло с предыдущего измерения RPM
    unsigned long delta_time = millis() - timestamp_rpm_measurement; 
    timestamp_rpm_measurement = millis();

    // Нахождение изменения кол-ва импульсов с прошлого исполнения
    int pulses_l_delta = pulses_l - pulses_l_old;
    int pulses_r_delta = pulses_r - pulses_r_old;
    
    pulses_l_old = pulses_l;
    pulses_r_old = pulses_r;

    // Расчет RPM
    float rpm_l = (float)pulses_l_delta * ((60.0f * 1000.0f) / (float)(HOLES_DISC * delta_time));
    float rpm_r = (float)pulses_r_delta * ((60.0f * 1000.0f) / (float)(HOLES_DISC * delta_time));

    Serial.print("\nl = ");
    Serial.print(rpm_l);
    Serial.print("\tr = ");
    Serial.print(rpm_r);
  }
}
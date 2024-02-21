#define left 1 
#define right 2
#define LP 5 //Скорость левого мотора
#define RP 13 //Скорость правого мотора
#define L1 12 //Направление вращения левого мотора
#define L2 4 //Напрвление вращения левого мотора 
#define R1 8 //Напрвление вращения правого мотора
#define R2 10 //Напрвление вращения правого мотора

volatile unsigned int pulses1;
volatile unsigned int pulses2;
float rpm1;
float rpm2;
unsigned long timeOld;
#define HOLES_DISC 20

int speed = 50;


void counter1()
{
 pulses1++;
}

void counter2()
{
 pulses2++;
}
 
void setup()
{
 Serial.begin(9600);
 pinMode(left, INPUT);
 pinMode(right, INPUT);
 pulses1 = 0;
 pulses2 = 0;
 timeOld = 0;
 attachInterrupt(digitalPinToInterrupt(left), counter1, FALLING);
 attachInterrupt(digitalPinToInterrupt(right), counter2, FALLING);


  digitalWrite(L1,OUTPUT);
  digitalWrite(L2,OUTPUT);
  digitalWrite(R1,OUTPUT);
  digitalWrite(R2,OUTPUT);
  analogWrite(LP, OUTPUT);
  analogWrite(RP, OUTPUT);
}
 
void loop()
{


 if (millis() - timeOld >= 1000)
 {
 detachInterrupt(digitalPinToInterrupt(left));
 rpm1 = (pulses1 * 60) / (HOLES_DISC);
 detachInterrupt(digitalPinToInterrupt(right));
 rpm2 = (pulses2 * 60) / (HOLES_DISC);
 Serial.print("\nl = ");
 Serial.print(rpm1);
 Serial.print("\tr = ");
 Serial.print(rpm2);
 timeOld = millis();
 pulses1 = 0; // Сбрасываем счетчики импульсов
 pulses2 = 0;
 attachInterrupt(digitalPinToInterrupt(left), counter1, FALLING);
 attachInterrupt(digitalPinToInterrupt(right), counter2, FALLING);
 
 }
  digitalWrite(L1,LOW);
  digitalWrite(L2,HIGH);
  digitalWrite(R1,LOW);
  digitalWrite(R2,HIGH);
  analogWrite(LP, speed);
  analogWrite(RP, speed);
}
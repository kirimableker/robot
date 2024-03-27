//#define LEFT 3
//#define RIGHT 2
#define LP 5 //Скорость левого мотора
#define RP 13 //Скорость правого мотора
#define L1 12 //Направление вращения левого мотора
#define L2 4 //Напрвление вращения левого мотора 
#define R1 8 //Напрвление вращения правого мотора
#define R2 10 //Напрвление вращения правого мотора

#define LEFTSENSOR 7
#define RIGHTSENSOR 2
#define CENTERSENSOR 3

#define CENTERBANG 11
#define RIGHTBANG 6
#define RIGHTBANGDIAGONAL 9


int speed = 100;
int turn = 100;

const int turn_90_degree_time_ms = 400;
const int collision_move_time = 800;
const int waid_time_ms = 1000;

void go(){

  analogWrite(LP, speed);
  digitalWrite(L1, LOW);
  digitalWrite(L2, HIGH);
  analogWrite(RP, speed);
  digitalWrite(R1, LOW);
  digitalWrite(R2, HIGH);
}

void stop(){

  analogWrite(LP, 0);
  digitalWrite(L1, LOW);
  digitalWrite(L2, HIGH);
  analogWrite(RP, 0);
  digitalWrite(R1, LOW);
  digitalWrite(R2, HIGH);
}

void fastright(){

  analogWrite(LP, turn);
  digitalWrite(L1, LOW);
  digitalWrite(L2, HIGH);
  analogWrite(RP, turn);
  digitalWrite(R1, HIGH);
  digitalWrite(R2, LOW);
}

void fastleft(){

  analogWrite(LP, turn);
  digitalWrite(L1, HIGH);
  digitalWrite(L2, LOW);
  analogWrite(RP, turn);
  digitalWrite(R1, LOW);
  digitalWrite(R2, HIGH);
}

void slowlyright(){

  analogWrite(LP, speed + 10);
  digitalWrite(L1, LOW);
  digitalWrite(L2, HIGH);
  analogWrite(RP, 0);
  digitalWrite(R1, LOW);
  digitalWrite(R2, LOW);
}

void slowlyleft(){
  
  analogWrite(LP, 0);
  digitalWrite(L1, LOW);
  digitalWrite(L2, LOW);
  analogWrite(RP, speed);
  digitalWrite(R1, LOW);
  digitalWrite(R2, HIGH);
}

void line(){
  byte LEFTS = digitalRead(LEFTSENSOR);
  byte RIGHTS = digitalRead(RIGHTSENSOR);
  byte CENTERS = digitalRead(CENTERSENSOR);
  
  if ((LEFTS==1)&&(CENTERS==0)&&(RIGHTS==1)){
    go();
  }
  else if ((LEFTS==1)&&(CENTERS==1)&&(RIGHTS==1)){
    go();
  }
  else if ((LEFTS==1)&&(CENTERS==1)&&(RIGHTS==0)){
    slowlyright();
  }
  else if ((LEFTS==0)&&(CENTERS==1)&&(RIGHTS==1)){
    slowlyleft();
  }
  else if ((LEFTS==1)&&(CENTERS==0)&&(RIGHTS==0)){
    fastright();
  }
  else if ((LEFTS==0)&&(CENTERS==0)&&(RIGHTS==1)){
    fastleft();
  }
  else if ((LEFTS==0)&&(CENTERS==0)&&(RIGHTS==0)){
    stop();
  }
  else{
    go();
  }  
}

void collision(){
  //bool RIGHTS = digitalRead(RIGHTSENSOR);

  // Повернуть направо 90*
  fastright();
  delay(turn_90_degree_time_ms);
  stop();
  delay(waid_time_ms);

  // Проехать вперед
  go();
  delay(collision_move_time);
  stop();
  delay(waid_time_ms);

  // Повернуть налево 90*
  fastleft();
  delay(turn_90_degree_time_ms);
  stop();
  delay(waid_time_ms);

  // Проехать вперед
  go();
  delay(collision_move_time);
  stop();
  delay(waid_time_ms);

  // Повернуть налево 90*
  fastleft();
  delay(turn_90_degree_time_ms);
  stop();
  delay(waid_time_ms);

  // Проехать вперед
  go();
  delay(collision_move_time);
  stop();
  delay(waid_time_ms);

  fastright();
  delay(turn_90_degree_time_ms);
  stop();
  delay(waid_time_ms);
}

void setup( void ){
  Serial.begin(115200);  

  pinMode(LEFTSENSOR,INPUT);
  pinMode(RIGHTSENSOR,INPUT);
  pinMode(CENTERSENSOR,INPUT);
  //pinMode(LEFT,INPUT);
  //pinMode(RIGHT,INPUT);
  pinMode(CENTERBANG,INPUT);
  pinMode(RIGHTBANG,INPUT);
  pinMode(RIGHTBANGDIAGONAL,INPUT);
  pinMode(L1,OUTPUT);
  pinMode(L2,OUTPUT);
  pinMode(R1,OUTPUT);
  pinMode(R2,OUTPUT);
  pinMode(LP,OUTPUT);
  pinMode(RP,OUTPUT);


  // По умолчанию моторы выключены  
  analogWrite(LP, 0);
  analogWrite(RP, 0);

  // Установка направления движения
  digitalWrite(L1,LOW);
  digitalWrite(L2,HIGH);
  digitalWrite(R1,LOW);
  digitalWrite(R2,HIGH);

  delay(3000);

  collision();
  while(1);
}


 
void loop( ){
  //0-black
  //1-white
  bool CENTERB = digitalRead(CENTERBANG);
  bool RIGHTB = digitalRead(RIGHTBANG);
  bool RIGHTBD = digitalRead(RIGHTBANGDIAGONAL);

  bool LEFTS = digitalRead(LEFTSENSOR);
  bool RIGHTS = digitalRead(RIGHTSENSOR);
  bool CENTERS = digitalRead(CENTERSENSOR);

  if (CENTERB && RIGHTB && RIGHTBD){
    line();
  }else{
    collision();
  }
}




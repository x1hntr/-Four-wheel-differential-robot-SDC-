#include <PS2X_lib.h>
#include <Servo.h>

Servo Servo_1;  
Servo Servo_2;  
PS2X ps2x;


int error = 0;
byte vibrate = 0;
const int MotorA1=52;
const int MotorA2=50;
const int PWMA=9;
const int MotorB1=48;
const int MotorB2=46;
const int PWMB=8;
const int MotorC2=44;
const int MotorC1=42;
const int PWMC=10;
const int MotorD2=40;
const int MotorD1=38;
const int PWMD=11;
int vel=0;
int valy=0;
int valx=0;
int v=250;
int pos=0;
void setup()
{
  //MOTOR A
  pinMode(MotorA1, OUTPUT);
  pinMode(MotorA2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  //MOTOR B
  pinMode(MotorB1, OUTPUT);
  pinMode(MotorB2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  //MOTOR C
  pinMode(MotorC1, OUTPUT);
  pinMode(MotorC2, OUTPUT);
  pinMode(PWMC, OUTPUT);
    //MOTOR D
  pinMode(MotorD1, OUTPUT);
  pinMode(MotorD2, OUTPUT);
  pinMode(PWMD, OUTPUT);
  Serial.begin(9600);
    //SERVOS
  Servo_1.attach(5);  
  Servo_2.attach(6);
  Servo_1.write(pos);
  Servo_2.write(pos); 
  error = ps2x.config_gamepad(4,2,A0,3,true,true);  //(clock, command, attention, data)

  if(error == 0)
  {
    Serial.println("Controlador encontrado y configurado");
  }
  else
  {
    Serial.println("Error, mando no encontrado");
    parar();
  }
 
}

void loop() 
{
   int temp;
  ps2x.read_gamepad(false,vibrate);
  vibrate = ps2x.Analog(PSAB_BLUE);
 valy=ps2x.Analog(PSS_LY), DEC;
    if(valy>=0 && valy<=126){
      vel=map(valy , 0, 126, v, 0);
      adelante();
      Serial.println(vel);
      }
      if(valy>=128 && valy<=255){
      vel=map(valy , 128, 255, 0, v);
      atras();
      Serial.println(vel);
      }
    
  valx=ps2x.Analog(PSS_RX ), DEC;

    if(valx>=0 && valx<=126){
      vel=map(valx , 0, 126, v, 0);
      derecha();
      Serial.println(vel);
      }
      if(valx>=128 && valx<=255){
      vel=map(valx , 128, 255, 0, v);
      izquierda();
      Serial.println(vel);
      }
      if(valx==127 && valy==127){
      parar();
        }
  if(ps2x.Button(PSB_PAD_UP)){
  abrir_jaula();
  }
 if(ps2x.Button(PSB_PAD_DOWN)){
  cerrar_jaula();
   }
 if(ps2x.Button(PSB_PAD_LEFT)){
  abrir_compuerta();
 }
 if(ps2x.Button(PSB_PAD_RIGHT)){
  cerrar_compuerta();
   }
 delay(50);
}
void adelante(){
  digitalWrite(MotorA1, HIGH );
  digitalWrite(MotorA2, LOW);
  analogWrite(PWMA,vel);
   digitalWrite(MotorB1, HIGH);
  digitalWrite(MotorB2, LOW);
  analogWrite(PWMB,vel);
   digitalWrite(MotorC1, HIGH);
  digitalWrite(MotorC2, LOW);
  analogWrite(PWMC,vel);
   digitalWrite(MotorD1, HIGH);
  digitalWrite(MotorD2, LOW);
  analogWrite(PWMD,vel);
}
void atras(){
  digitalWrite(MotorA1, LOW);
  digitalWrite(MotorA2, HIGH);
  analogWrite(PWMA,vel);
   digitalWrite(MotorB1, LOW);
  digitalWrite(MotorB2, HIGH);
  analogWrite(PWMB,vel);
   digitalWrite(MotorC1, LOW);
  digitalWrite(MotorC2, HIGH);
  analogWrite(PWMC,vel);
   digitalWrite(MotorD1, LOW);
  digitalWrite(MotorD2, HIGH);
  analogWrite(PWMD,vel);
}
void derecha(){
  digitalWrite(MotorA1, HIGH);
  digitalWrite(MotorA2, LOW);
  analogWrite(PWMA,vel);
   digitalWrite(MotorB1, HIGH);
  digitalWrite(MotorB2, LOW);
  analogWrite(PWMB,vel);
   digitalWrite(MotorC1, LOW);
  digitalWrite(MotorC2, HIGH);
  analogWrite(PWMC,vel);
   digitalWrite(MotorD1, LOW);
  digitalWrite(MotorD2, HIGH);
  analogWrite(PWMD,vel);
}
void izquierda(){
  digitalWrite(MotorA1, LOW);
  digitalWrite(MotorA2, HIGH);
  analogWrite(PWMA,vel);
   digitalWrite(MotorB1, LOW);
  digitalWrite(MotorB2, HIGH);
  analogWrite(PWMB,vel);
   digitalWrite(MotorC1, HIGH);
  digitalWrite(MotorC2, LOW);
  analogWrite(PWMC,vel);
   digitalWrite(MotorD1, HIGH);
  digitalWrite(MotorD2, LOW);
  analogWrite(PWMD,vel);
}
void parar(){
  digitalWrite(MotorA1, LOW);
  digitalWrite(MotorA2, LOW);
  analogWrite(PWMA,0);
   digitalWrite(MotorB1, LOW);
  digitalWrite(MotorB2, LOW);
  analogWrite(PWMB,0);  
   digitalWrite(MotorC1, LOW);
  digitalWrite(MotorC2, LOW);
  analogWrite(PWMC,0);
   digitalWrite(MotorD1, LOW);
  digitalWrite(MotorD2, LOW);
  analogWrite(PWMD,0);
}
void cerrar_jaula(){
  Servo_2.write(90);
  }
void abrir_jaula(){
  Servo_2.write(0);
  }
void abrir_compuerta(){
  Servo_1.write(90);
  }
void cerrar_compuerta(){
    Servo_1.write(0);
  }

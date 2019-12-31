#define E1 10  // Enable Pin für Motor 1
#define E2 11  // Enable Pin für Motor 2

#define C1 8   // Control Pin 1 für Motor 1
#define C2 9   // Control Pin 2 für Motor 1
#define C3 12  // Control Pin 1 für Motor 2
#define C4 13  // Control Pin 2 für Motor 2
#include<math.h>


float v1,v2,v3,v;

void Read()
{
  float v1_int = analogRead(A0);
   v1 = v1_int *20 /1024;
  float v2_int = analogRead(A1);
  v2 = v2_int *20 /1024;
  float v3_int = analogRead(A2);
   v3 = v3_int *20 /1024;
   //v = v2 - v3/10 ;
   //delay(100);
}


 
void motor_forward()
{                   
  digitalWrite(C1, HIGH);    
  digitalWrite(C2, LOW);
  digitalWrite(C3, HIGH);
  digitalWrite(C4, LOW);
  
  analogWrite(E1,200);  
  analogWrite(E2,200);
  delay(80);
}


void motor_backward()
{                   
  digitalWrite(C1, LOW);    
  digitalWrite(C2, HIGH);
  digitalWrite(C3, LOW);
  digitalWrite(C4, HIGH);

 
  analogWrite(E1,200);  
  analogWrite(E2,200);
  delay(80);
}


void motorStop()
{
  analogWrite(E1,0);  
  analogWrite(E2,0);
  //delay(300);
}



void setup() {
  
  pinMode(E1, OUTPUT);
  pinMode(E2, OUTPUT);
 
  pinMode(C1, OUTPUT);
  pinMode(C2, OUTPUT);
  pinMode(C3, OUTPUT);
  pinMode(C4, OUTPUT);

  Serial.begin(9600);

}

int armCmd_number = 0 ; 
double  u;
double v1_l;
double v1_u;
double v2_l; 
double v2_u;
double  v3_l;
double  v3_u;
double  est_v1;
double est_v2;
double  est_v3;
double  coeff_1 [6]= { -7.58184303e-11,  -1.19400391e-07,   5.03723221e-05,  -5.70858165e-03,  1.73484030e-01,   1.17955871e+01};
double  coeff_2 [6]= { -2.32814936e-09,   8.81378471e-07,  -1.08192605e-04,   4.65879043e-03,  -1.11757825e-03,   9.86481108e+00};
double  coeff_3 [6]= { 2.89053287e-09,  -1.48124027e-06,   2.71111570e-04,  -2.11690111e-02,  5.77557543e-01,   1.50945291e+01};

int buffer_x = 0;

void loop() 
{
  
    
    int x= 0;
    Serial.println("Bitte geben Sie den Drehwinkel ein:");
    
    while(Serial.available()==0){
      
      delay(100);
    }
    
    String tmp_string = Serial.readString();
    int armCmd_number = tmp_string.toInt();
    x = armCmd_number;
  
    

     est_v1 = coeff_1 [0]*pow(x,5)+coeff_1 [1]*pow(x,4)+coeff_1 [2]*pow(x,3)+coeff_1 [3]*pow(x,2)+coeff_1 [4]*pow(x,1)+ coeff_1 [5];


      v1_l = est_v1 - 0.1;
     v1_u = est_v1 + 0.1;

     est_v2 = coeff_2 [0]*pow(x,5)+coeff_2 [1]*pow(x,4)+coeff_2 [2]*pow(x,3)+coeff_2 [3]*pow(x,2)+coeff_2 [4]*pow(x,1)+ coeff_2 [5];

      v2_l = est_v2 - 0.1;
     v2_u = est_v2 + 0.1;
 
    est_v3 = coeff_3 [0]*pow(x,5)+coeff_3 [1]*pow(x,4)+coeff_3 [2]*pow(x,3)+coeff_3 [3]*pow(x,2)+coeff_3 [4]*pow(x,1)+ coeff_3 [5];

      v3_l = est_v3 - 0.1;
     v3_u = est_v3 + 0.1;

   Serial.println(v2_l);
   Serial.println(v3_l);
   Serial.println("Starting");
   
   
if (armCmd_number<=90 )
 {
    if(x>buffer_x)
      {
   while(1)
   {
  
     motor_forward();
     motorStop();
     Read();
     delay(20);
     Serial.print(v2);
     Serial.print(",");
     Serial.println(v3);
       
  
     if(v3 <= v3_l)
     {
      Serial.println("Erfolg!!");
      motorStop();
      buffer_x = armCmd_number ; 
      break;
     }
   } 
  } 
 
   else if(x< buffer_x)
      {
   while(1)
   {
  
     motor_backward();
     motorStop();
     Read();
     delay(20);
     Serial.print(v2);
     Serial.print(",");
     Serial.println(v3);
 
     if(v3 >= v3_u)
     {
      Serial.println("Erfolg!!");
      motorStop();
      buffer_x = armCmd_number ; 
      break;
     }
   }
  }
}






 if(armCmd_number>90 )
 {
       if(x>buffer_x)
      {
   while(1)
   {
  
     motor_forward();
     motorStop();
     Read();
     delay(20);
     Serial.print(v2);
     Serial.print(",");
     Serial.println(v3);

     if(v2 >= v2_l)
     {
      Serial.println("Erfolg!!");
      motorStop();
      buffer_x = armCmd_number ; 
      break;
     }
   } 
  }
 
   if(x< buffer_x)
      {
   while(1)
   {
  
     motor_backward();
     motorStop();
     Read();
     delay(20);
     Serial.print(v2);
     Serial.print(",");
     Serial.println(v3);
   
     if(v2 <= v2_u)
     {
      Serial.println("Erfolg!!");
      motorStop();
      buffer_x = armCmd_number ; 
      break;
     }
   }
 } 

 }
  Serial.print("Drehwinkel ist jetzt ");
  Serial.print(armCmd_number);
  Serial.println(" Grad");



}

#define E1 10  // Enable Pin für Motor 1
#define E2 11  // Enable Pin für Motor 2

#define C1 8   // Control Pin 1 für Motor 1
#define C2 9   // Control Pin 2 für Motor 1
#define C3 12  // Control Pin 1 für Motor 2
#define C4 13  // Control Pin 2 für Motor 2



float v1,v2,v3,v;

void Read()
{
  float v1_int = analogRead(A0);
   v1 = v1_int *20 /1024;
  float v2_int = analogRead(A1);
  v2 = v2_int *20 /1024;
  float v3_int = analogRead(A2);
   v3 = v3_int *20 /1024;
   v = v2 - v3/10 ;
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
  delay(40);
}


/*void motor_backward()
{                   
  digitalWrite(C1, LOW);    
  digitalWrite(C2, HIGH);
  digitalWrite(C3, LOW);
  digitalWrite(C4, HIGH);

 
  analogWrite(E1,200);  
  analogWrite(E2,200);
  float u = armCmd_number/2*75
  delay(u);
}*/


void motorStop()
{
  analogWrite(E1,0);  
  analogWrite(E2,0);
  //delay(20);
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
float u;

void loop() 
{
  if(Serial.available() >0){
  analogWrite(E1,200);  
  analogWrite(E2,200); 
  int i=0;
  while(i<= 180)
  {
   motor_forward(); 
   motorStop();
   //delay(35);
   Read();
   Serial.print(v1);
   Serial.print(",");
   Serial.print(v2);
   Serial.print(",");
   Serial.println(v3);
   //delay(100);
   i= i+1;
   }


  Serial.println("initiating");
  digitalWrite(C1, LOW);    
  digitalWrite(C2, HIGH);
  digitalWrite(C3, LOW);
  digitalWrite(C4, HIGH);
  analogWrite(E1,200);  
  analogWrite(E2,200); 
  delay(8000);
  }
}

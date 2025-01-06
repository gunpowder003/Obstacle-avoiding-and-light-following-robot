int incomingByte ;
 int value;
int PWM_E1 = 6;
int DIR_M1 = 7;
int PWM_E2 = 5;
int DIR_M2 = 4;
int le;
int r;
int s;

// the setup routine runs once when you press reset:
void setup() {
 // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
 s=1;incomingByte=0;
  pinMode(DIR_M1, OUTPUT);
pinMode(DIR_M2, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  
   if (Serial.available() > 0) {
                 // read the incoming byte:
                 incomingByte = Serial.read();

                 // say what you got:
                 Serial.print("I received: ");
                 Serial.println(incomingByte, DEC);
                 if(s==0)s=1;
                 if(s==1)s=0;
         }

  
  if (s==1){
  // read the input on analog pin 0:
  int RLDR = analogRead(A2);int LLDR = analogRead(A3);int RS = analogRead(A0);int LS = analogRead(A1);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float rldr = (RLDR* (5.0 / 1023.0))-.3;float lldr = LLDR * (5.0 / 1023.0);float rs = RS/2;float ls = LS/2;
  // print out the value you read:

  Serial.print(" RLDR ");
  Serial.print(rldr);
  Serial.print(" LLDR ");
  Serial.print(lldr);
   Serial.print(" RS ");
  Serial.print(rs);
  Serial.print(" LS ");
  Serial.print(ls);
  
  le=1;
  r=1;
  value = 100;
 
  
  if(ls<=8)
r=0 ;
  if(rs<=8)
le=0; 


if((le+r)>0)
{if(lldr>=(rldr+.4))
le=0;
if((lldr+.4)<=rldr)
r=0;
  
digitalWrite(DIR_M1,HIGH);            
digitalWrite(DIR_M2, LOW);
analogWrite(PWM_E1, value*le); 
analogWrite(PWM_E2, value*r);
Serial.print(" Foward ");
 if(r==0)
Serial.print(" Right ");
  if(le==0)
Serial.print(" Left "); }

else if((le+r)==0)
{digitalWrite(DIR_M2,HIGH);            
digitalWrite(DIR_M1, LOW);
analogWrite(PWM_E1, value); 
analogWrite(PWM_E2, value-100); 
Serial.print(" Reverse "); 
delay(100);}

delay(100);
  Serial.println("");
  }}

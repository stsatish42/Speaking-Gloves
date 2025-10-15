#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  // sets the interfacing pins


//Soft serial library used to send serial commands on pin 2 instead of regular serial pin.
#include <SoftwareSerial.h>
//Define the Pin Numbers for the sketch.
#define txPin  1
//Create a SoftSerial Objet
SoftwareSerial speakjet = SoftwareSerial(0, txPin);
//The message array contains the command for sounds to be sent in order to inunciate the words "Hello my name is Arduino." Check the SpeakJet Manual for more information
//on producing words
// Set up a memorable token for "Word Pause"
#define WP 6    // 6 is 90ms pause
#define RES  3                    

const int FLEX_PIN[]={A0,A1,A2,A3};
int i;
float angle[5];
int d[5];
const int xPin   = A4;
int x = 0;

// Measure the voltage at 5V and the actual resistance of your
// 47k resistor, and enter them below:
const float VCC = 4.98; // Measured voltage of Ardunio 5V line
const float R_DIV = 47000.0; // Measured resistance of 3.3k resistor

// Upload the code, then try to adjust these values to more
// accurately calculate bend degree.
float STRAIGHT_RESISTANCE[] = {34500,32000,25000,30000}; // resistance when straight
float BEND_RESISTANCE[] = {50000,56000,40000,62000}; // resistance at 90 deg
//char message[] ={20, 96, 21, 114, 22, 88, 23, 5, 147, 159, 194, 134, 140};
void setup() 
{
  lcd.begin(20, 4);  // initializes the 20x4 LCD
  //Configure the pins for the SpeakJet module
  pinMode(txPin, OUTPUT);
  pinMode(RES, OUTPUT);
  //Set up a serial port to talk from Arduino to the SpeakJet module on pin 1.
  speakjet.begin(9600);    
  
  Serial.begin(9600);
  for(i=0;i<4;i++)
  {
  pinMode(FLEX_PIN[i], INPUT);      //CHECK INDEX STARTS FROM 0 OR 1     
  }
}

void loop() 
{
  x = analogRead(xPin);
  Serial.print("x = ");
  Serial.print(x);
  angle[4]=constrain(map(x,347,275,0,90),0,90);
  Serial.print("  angle x = ");
  Serial.println(angle[4]);
  // Read the ADC, and calculate voltage and resistance from it
  for(i=0;i<4;i++)
  {
  int flexADC = analogRead(FLEX_PIN[i]);
  float flexV = flexADC * VCC / 1023.0;
  float flexR = R_DIV * ((VCC / flexV) - 1.0);
  Serial.print("Resistance");
  Serial.print(i);
  Serial.print(":");
  Serial.println(flexR);
  angle[i] = map(flexR, STRAIGHT_RESISTANCE[i], BEND_RESISTANCE[i],
                   0, 90.0);
  Serial.print("Bend");
  Serial.print(i);
  Serial.print(":");
  Serial.println(angle[i]);
  Serial.println();
  
  }

 // Use the calculated resistance to estimate the sensor's
  // bend angle:
  
  delay(500);

for(i=0;i<5;i++)
{
  if(angle[i]<=30)
  d[i]=0;
  else
  d[i]=1;
}


int decimalval=d[0]*1+d[1]*2+d[2]*4+d[3]*8+d[4]*16;
Serial.print("decimalval ");
Serial.println(decimalval);

digitalWrite(RES, LOW);
 delay(100);
 digitalWrite(RES, HIGH);
 delay(1000);
switch(decimalval) 
 {
  case 0:
  { Serial.println("WELCOME");
  lcd.clear();
  lcd.setCursor(0,0);           //sets the cursor at  line 3 column 5
  lcd.print("WELCOME");     // prints WELCOME
  char message[] ={20, 96, 21, 114, 22, 88, 23, 5, 147, 159, 194, 134, 140};
  for(i=0;i<sizeof(message);i++)
  speakjet.print(message[i]);
  break;}
  case 1:{Serial.println("HELLO");
  lcd.clear();
  lcd.setCursor(0,0);           
  lcd.print("HELLO");
  char message[] ={20, 96, 21, 114, 22, 88, 23, 5,183, 159, 146, 164};
  for(i=0;i<sizeof(message);i++)
  speakjet.print(message[i]);
  delay(1000);
  break;}
  case 2:{Serial.println("WHAT IS YOUR NAME");
  lcd.clear();
  lcd.setCursor(0,0);           
  lcd.print("WHAT IS YOUR NAME");
  char message[] ={20, 127, 21, 114, 22, 88, 23, 5, 185, 8, 136, 191, 8, 129, 167, 128, 153, 141, 154, 140};
  for(i=0;i<sizeof(message);i++)
  speakjet.print(message[i]);
  break;}
  case 3:{Serial.println("NEED WATER");
  lcd.clear();
  lcd.setCursor(0,0);           
  lcd.print("NEED WATER");
  char message[] ={20, 127, 21, 114, 22, 88, 23, 5, 141, 8, 128, 176, 147, 136, 191, 7, 151};
  for(i=0;i<sizeof(message);i++)
  speakjet.print(message[i]);
  break;}
  case 4:{Serial.println("NEED HELP");
  lcd.clear();
  lcd.setCursor(0,0);           
  lcd.print("NEED HELP");
  char message[] ={20, 127, 21, 114, 22, 88, 23, 5, 141, 8, 128, 176,WP,WP, 183, 159, 199};
  for(i=0;i<sizeof(message);i++)
  speakjet.print(message[i]);
  break;}
  case 5:{Serial.println("I AM NOT WELL");
  lcd.clear();
  lcd.setCursor(0,0);           
  lcd.print("I AM NOT WELL");
  char message[] ={20, 127, 21, 114, 22, 88, 23, 5, 157, 132, 132, 140, 141, 136, 191, 147, 159};
  for(i=0;i<sizeof(message);i++)
  speakjet.print(message[i]);
  break;}
  case 6:{Serial.println("CALL THE DOCTOR");
  lcd.clear();
  lcd.setCursor(0,0);           
  lcd.print("CALL THE DOCTOR");
  char message[] ={20, 127, 21, 114, 22, 88, 23, 5, 195, 8, 136, 146, 8, 169, 8, 128, 175, 136, 194, 191, 7, 151};
  for(i=0;i<sizeof(message);i++)
  speakjet.print(message[i]);
  break;}
  case 7:{Serial.println("CALL THE POLICE");
  lcd.clear();
  lcd.setCursor(0,0);           
  lcd.print("CALL THE POLICE");
  char message[] ={20, 127, 21, 114, 22, 88, 23, 5, 195, 8, 136, 146, 8, 169, 8, 128, 199, 7, 134, 145, 128, 187};
  for(i=0;i<sizeof(message);i++)
  speakjet.print(message[i]);
  break;}
  case 8:{Serial.println("I NEED SLEEP");
  lcd.clear();
  lcd.setCursor(0,0);           
  lcd.print("I NEED SLEEP");
  char message[] ={20, 127, 21, 114, 22, 88, 23, 5, 157, 141, 8, 128, 176, 187, 7, 145, 8, 128, 199};
  for(i=0;i<sizeof(message);i++)
  speakjet.print(message[i]);
  break;}
  case 9:{Serial.println("I CAN'T TALK");
  lcd.clear();
  lcd.setCursor(0,0);           
  lcd.print("I CAN'T TALK");
  char message[] ={20, 127, 21, 114, 22, 88, 23, 5, 157, 191, 8, 136, 8, 197};
  for(i=0;i<sizeof(message);i++)
  speakjet.print(message[i]);
  break;}
  case 10:{Serial.println("HOW ARE YOU");
  lcd.clear();
  lcd.setCursor(0,0);           
  lcd.print("HOW ARE YOU");
  char message[] ={20, 127, 21, 114, 22, 88, 23, 5, 184, 8, 163, 152, 8, 160};
  for(i=0;i<sizeof(message);i++)
  speakjet.print(message[i]);
  break;}
  case 11:{Serial.println("GIVE ME YOUR NUMBER");
  lcd.clear();
  lcd.setCursor(0,0);           
  lcd.print("GIVE ME YOUR NUMBER");
  char message[] ={20, 127, 21, 114, 22, 88, 23, 5, 8, 178, 8, 129, 7, 166, 140, 128, 128, 128, 153, 141, 134, 140, 18, 171, 148};
  for(i=0;i<sizeof(message);i++)
  speakjet.print(message[i]);
  break;}
  case 12:{Serial.println("NO");
  lcd.clear();
  lcd.setCursor(0,0);           
  lcd.print("NO");
  char message[] ={20, 127, 20, 96, 21, 114, 22, 88, 23, 5, 142, 164};
  for(i=0;i<sizeof(message);i++)
  speakjet.print(message[i]);
  break;}
  case 13:{Serial.println("YES");
  lcd.clear();
  lcd.setCursor(0,0);           
  lcd.print("YES");
  char message[] ={20, 127, 21, 114, 22, 88, 23, 5, 158, 187, 187};
  for(i=0;i<sizeof(message);i++)
  speakjet.print(message[i]);
  break;}
  case 14:{Serial.println("I HAVE SOME WORK");
  lcd.clear();
  lcd.setCursor(0,0);           
  lcd.print("I HAVE SOME WORK");
  char message[] ={20, 127, 21, 114, 22, 88, 23, 5, 157, 183, 8, 132, 166, 8, 187, 134, 140, 147, 151, 8, 196};
  for(i=0;i<sizeof(message);i++)
  speakjet.print(message[i]);
  break;}
  case 15:{Serial.println("LET'S GO OUT");
  lcd.clear();
  lcd.setCursor(0,0);           
  lcd.print("LET'S GO OUT");
  char message[] ={20, 127, 21, 114, 22, 88, 23, 5, 8, 179, 8, 164, 163, 191};
  for(i=0;i<sizeof(message);i++)
  speakjet.print(message[i]);
  break;}
  case 16:{Serial.println("WHERE WERE YOU");
  lcd.clear();
  lcd.setCursor(0,0);           
  lcd.print("WHERE WERE YOU");
  char message[] ={20, 127, 21, 114, 22, 88, 23, 5, 147, 150, 8, 160};
  for(i=0;i<sizeof(message);i++)
  speakjet.print(message[i]);
  break;}
  case 17:{Serial.println("HAD YOUR LUNCH");
  lcd.clear();
  lcd.setCursor(0,0);           
  lcd.print("HAD YOUR LUNCH");
  char message[] ={20, 127, 21, 114, 22, 88, 23, 5, 128, 153, 146, 134, 8, 141, 182};
  for(i=0;i<sizeof(message);i++)
  speakjet.print(message[i]);
  break;}
  case 18:{Serial.println("LET'S HAVE DINNER");
  lcd.clear();
  lcd.setCursor(0,0);           
  lcd.print("LET'S HAVE DINNER");
  char message[] ={20, 127, 21, 114, 22, 88, 23, 5, 183, 8, 132, 166, 174, 129, 141, 7, 151};
  for(i=0;i<sizeof(message);i++)
  speakjet.print(message[i]);
  break;}
  case 19:{Serial.println("I AM FINE");
  lcd.clear();
  lcd.setCursor(0,0);           
  lcd.print("I AM FINE");
  char message[] ={20, 127, 21, 114, 22, 88, 23, 5, 157, 132, 132, 140};
  for(i=0;i<sizeof(message);i++)
  speakjet.print(message[i]);
  break;}
  case 20:{Serial.println("WHERE DO YOU STAY");
  lcd.clear();
  lcd.setCursor(0,0);           
  lcd.print("WHERE DO YOU STAY");
  char message[] ={20, 127, 21, 114, 22, 88, 23, 5, 147, 150, 174, 162, 8, 160, 187, 191, 154, 7, 128};
  for(i=0;i<sizeof(message);i++)
  speakjet.print(message[i]);
  break;}
  case 21:{Serial.println("HOW MUCH DOES IT COST");
  lcd.clear();
  lcd.setCursor(0,0);           
  lcd.print("HOW MUCH DOES IT COST");
  char message[] ={20, 127, 21, 114, 22, 88, 23, 5, 184, 8, 163, 140, 134, 182, 8, 129, 8, 191, 195, 8, 135, 187, 191};
  for(i=0;i<sizeof(message);i++)
  speakjet.print(message[i]);
  break;}
  case 22:{Serial.println("I DIDN'T UNDERSTAND");
  lcd.clear();
  lcd.setCursor(0,0);           
  lcd.print("I DIDN'T UNDERSTAND");
  char message[] ={20, 127, 21, 114, 22, 88, 23, 5, 157, 134, 7, 141, 175, 7, 151, 187, 7, 191, 132, 142, 177};
  for(i=0;i<sizeof(message);i++)
  speakjet.print(message[i]);
  break;}
  case 23:{Serial.println("I WILL CALL YOU LATER");
  lcd.clear();
  lcd.setCursor(0,0);           
  lcd.print("I WILL CALL YOU LATER");
  char message[] ={20, 127, 21, 114, 22, 88, 23, 5, 157, 147, 129, 8, 145, 195, 8, 136, 146, 8, 160};
  for(i=0;i<sizeof(message);i++)
  speakjet.print(message[i]);
  break;}
  case 24:{Serial.println("NICE TO MEET U");
  lcd.clear();
  lcd.setCursor(0,0);           
  lcd.print("NICE TO MEET U");
  char message[] ={20, 127, 21, 114, 22, 88, 23, 5, 8, 191, 162, 8, 160};
  for(i=0;i<sizeof(message);i++)
  speakjet.print(message[i]);
  break;}
  case 25:{Serial.println("THANK YOU");
  lcd.clear();
  lcd.setCursor(0,0);           
  lcd.print("THANK YOU");
  char message[] ={20, 127, 21, 114, 22, 88, 23, 5, 8, 160};
  for(i=0;i<sizeof(message);i++)
  speakjet.print(message[i]);
  break;}
  case 26:{Serial.println("I AM GOING OUT");
  lcd.clear();
  lcd.setCursor(0,0);           
  lcd.print("I AM GOING OUT");
  char message[] ={20, 127, 21, 114, 22, 88, 23, 5, 157, 132, 132, 140, 163, 191};
  for(i=0;i<sizeof(message);i++)
  speakjet.print(message[i]);
  break;}
  case 27:{Serial.println("WHY ARE YOU IN A HURRY");
  lcd.clear();
  lcd.setCursor(0,0);           
  lcd.print("WHY ARE YOU IN A HURRY");
  char message[] ={20, 127, 21, 114, 22, 88, 23, 5, 185, 157, 152, 8, 160, 8, 129, 8, 141, 154, 128, 184, 151, 128};
  for(i=0;i<sizeof(message);i++)
  speakjet.print(message[i]);
  break;}
  case 28:{Serial.println("I WAS WAITING FOR YOU");
  lcd.clear();
  lcd.setCursor(0,0);           
  lcd.print("I WAS WAITING FOR YOU");
  char message[] ={20, 127, 20, 96, 21, 114, 22, 88, 23, 5, 157, 147, 134, 167, 186, 153, 8, 160};
  for(i=0;i<sizeof(message);i++)
  speakjet.print(message[i]);
  break;}
  case 29:{Serial.println("SHOULD WE LEAVE");
  lcd.clear();
  lcd.setCursor(0,0);           
  lcd.print("SHOULD WE LEAVE");
  char message[] ={20, 127, 21, 114, 22, 88, 23, 5, 8, 189, 8, 139, 177, 147, 8, 128, 145, 128, 166};
  for(i=0;i<sizeof(message);i++)
  speakjet.print(message[i]);
  break;}
  case 30:{Serial.println("WHEN ARE WE MEETING NEXT");
  lcd.clear();
  lcd.setCursor(0,0);           
  lcd.print("WHEN ARE WE MEETING NEXT");
  char message[] ={20, 127, 21, 114, 22, 88, 23, 5, 185, 8, 131, 8, 141, 152, 147, 8, 128, 141, 131, 194, 187, 191};
  for(i=0;i<sizeof(message);i++)
  speakjet.print(message[i]);
  break;}
  case 31:{Serial.println("I AM TIRED");
  lcd.clear();
  lcd.setCursor(0,0);           
  lcd.print("I AM TIRED");
  char message[] ={20, 127, 21, 114, 22, 88, 23, 5, 157, 132, 132, 140, 8, 191, 155, 148, 177};
  for(i=0;i<sizeof(message);i++)
  speakjet.print(message[i]);
  break;}
 }
delay(3000);

}
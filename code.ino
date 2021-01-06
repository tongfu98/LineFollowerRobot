#include<Servo.h>

Servo servoLeft;  //attaching servos
Servo servoRight;
int R = 5; //right QTI
int M = 7; //middle QTI
int L = 10; //left QTI


int tL = 0; //setting up left time constant
int tM = 0; //setting up middle time constant
int tR = 0; //setting up right time constant
int t = 400; //qti cutoff
int cond = 0; //set up condition variable for loop
int x2 = 0; //our variable
int c2 = 1; //our condition value
int x1 = 0; //set up variables to receive values from other groups
int x3 = 0;
int x4 = 0;
int x5 = 0;
int c1 = 0; //condition variables to determine when a message has been received from another group
int c3 = 0;
int c4 = 0;
int c5 = 0;
const int interval = 500; //interval variable used to stagger message
unsigned long previousMillis = 0; //variable used to measure interval
int ledState = LOW; //LED pin 11 value
int total = 0; //sets up sum and remainder value
//define frequencies for tone
const int c = 261;
const int d = 294;
const int dSH = 622;
const int dS = dSH / 2;
const int e = 329;
const int f = 349;
const int fSH = 740;
const int fS = fSH / 2;
const int g = 391;
const int gS = 415;
const int a = 440;
const int aS = 455;
const int b = 493;
const int cH = 523;
const int cSH = 554;
const int dH = 587;
const int eH = 659;
const int fH = 698;
const int gH = 784;
const int gSH = 830;
const int aH = 880;
const int bH = 987;

const int buzzerPin = 4; //sets up pin connected to speaker
//defining length of notes for song
const int q = 400;
const int qh = q * 1.5;
const int ha = 2 * q;
const int o = 4 * q;
const int ei = q / 2;
char outgoing = ' ';


//defining pins for xbee
#define Rx 17
#define Tx 16
void setup() {
  Serial.begin(9600); //sets up serial monitor(used to troubleshoot)


  servoLeft.attach(12);                       // Attach left signal to pin 13
  servoRight.attach(13);                     // Attach right signal to pin 12

  delay(500);
  Serial2.begin(9600); //sets up serial for xbee
  delay(500); //delays slow down bot to troubleshoot easier
  pinMode(buzzerPin, OUTPUT); //sets up buzzerpin to write to spaker


}
//This function measures the rc time of the qti sensor to determine whether it is over dark or light ground
long rcTime(int pin) {
  pinMode(pin, OUTPUT); //sets pin to output
  digitalWrite(pin, HIGH); //high voltage to charge capacitor
  delayMicroseconds(230);
  pinMode(pin, INPUT); //switches pin to input
  digitalWrite(pin, LOW); 
  long time = micros(); 
  while
  (digitalRead(pin));
  time = micros() - time; //measures time that has passed
  return time; //returns time when capacitor discharges
}

//Beep Function simplifies tone command and adds delay to properly play notes as a song
void beep(int note, int duration)

{
  //Plays tone on buzzerPin
  tone(buzzerPin, note, duration);
  delay(duration + 10);

}
//main loop where everything happens
void loop() {
  //setting up output pins
  pinMode(3, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(11, OUTPUT);

  //measuring rcTime of each qti, storing each in a variable:
  tL = rcTime(L);
  tM = rcTime(M);
  tR = rcTime(R);

  //Serial prints for troubleshooting:
  //Serial.println("Left");
  //Serial.println(tL);
  //Serial.println("Middle");
  //Serial.println(tM);
  //Serial.println("Right");
  //Serial.println(tR);
  //Serial.println(cond);

  //Main line following code:
  if ((tL < t) && (tM > t) && (tR < t) && (cond == 0)) {
    servoLeft.writeMicroseconds(1550);
    servoRight.writeMicroseconds(1450);
    //straight, only center sees black and outward two see white
  }


  else if ((tL < t) && (tM < t) && (tR > t) && (cond == 0)) {
    servoLeft.writeMicroseconds(1580);
    servoRight.writeMicroseconds(1510);
    //right turn, right sensor sees black and other two see white
  }

  else if ((tL > t) && (tM < t) && (tR < t) && (cond == 0)) {
    servoLeft.writeMicroseconds(1490);
    servoRight.writeMicroseconds(1420);
    //left turn, left sensor sees black
  }
  else if ((tL > t) && (tM > t) && (tR > t) && (cond == 0)) {
    //all three see black
    cond = 1; //changes condition so bot can run through other sections of code
    servoLeft.writeMicroseconds(1500);
    servoRight.writeMicroseconds(1500);
    //bot stops
    delay(500);
    servoLeft.writeMicroseconds(1520);
    servoRight.writeMicroseconds(1480);
    //bot inches forward slightly
    delay(400);
    servoLeft.writeMicroseconds(1500);
    servoRight.writeMicroseconds(1500);
    //bot stops
    delay(500);
    servoLeft.writeMicroseconds(1450);
    servoRight.writeMicroseconds(1450);
    //90 degree turn
    delay(1000);
    servoLeft.writeMicroseconds(1470);
    servoRight.writeMicroseconds(1530);
    //reverse towards target (due to placement of sensor on back of bot)
    delay(1950);
    servoLeft.writeMicroseconds(1500);
    servoRight.writeMicroseconds(1500);
    //stop
    delay(1000);
  }
  else if ((tL < t) && (tM > t) && (tR > t) && (cond == 0)) {
    servoLeft.writeMicroseconds(1580);
    servoRight.writeMicroseconds(1500);
    //another adjustment command to turn when middle and right see black
  }
  else if ((tL > t) && (tM > t) && (tR < t) && (cond == 0)) {
    servoLeft.writeMicroseconds(1500);
    servoRight.writeMicroseconds(1420);
    //another adjustment command to turn when middle and left see black
  }
  float reading = (analogRead(0));
  //Output of Hall Effect Sensor (integer between 0-1024)

  float mag = reading * 5.0;
  // Converts reading value to volts Signal


  mag /= 1024.0;
  //Divides by 1024 giving the sensor output signal in volts

  mag = mag - 2.50;
  //Subtacts the zero field output of the sensor to provide pole sensing

  mag = mag * 5000;
  //Sets units of output to Gauss (5mV/Gauss)

  //Serial.print("mag strength = "); // Display sensor value(troubleshooting)
  Serial.println(mag, 4);


  //Main sensing:
  if (cond == 1) {

    unsigned long currentMillis = millis(); //measures current time
    if (currentMillis - previousMillis >= interval) { //after interval time runs through sending code
      previousMillis = currentMillis; //resets counter
    
      if (abs(mag) > 2200) { //sensing black
        digitalWrite(11, HIGH); //turns on LED to signal black
        outgoing = '6'; //sets up 6 as the outgoing variable
        Serial2.print(outgoing); //sends 6 as a character to other groups
        x2 = 2; //sets our variable to 2(gold）


      }
      else if ((abs(mag) > 180) && (abs(mag) < 2200)) { //sensing gray
        if (ledState == LOW) { //flips pin 11 on and off
          ledState = HIGH;
        }
        else {
          ledState = LOW;
        }
        digitalWrite(11, ledState);
        outgoing = '5'; //sets up 5 as the outgoing variable
        Serial2.print(outgoing); //sends 5 as a character to other groups
        x2 = 1; //sets our variable to 1(silver）
      }
      else { //sensing white
        digitalWrite(11, LOW); //no LED light
        outgoing = '4'; //sets up 4 as the outgoing variable
        Serial2.print(outgoing); //sends 4 as a character to other groups
        x2 = 0;  //sets our variable to 0(bronze)
        

      }
    }
    if (Serial2.available()) {
      char incoming = Serial2.read(); //sets incoming variable as that read by XBee

      //Serial.println(incoming); (troubleshooting)

      //This section converts the incoming character to an integer:
      //Each if statement determines which range the message came from (1-3, a-c,d-f,g-i)
      //whats it finds the correct location, it assigns the x variable to a 0, 1, or 2 based on the message received
      //it flips the c variable to a 1 so that it stops listening for that groups message
      //it plays a tone to let us know it has received a message

      if ((incoming - 48 < 4) && (incoming - 48 > 0) && (c1 == 0)) {
        x1 = incoming - 49;
        c1 = 1;
        tone(4, 220, 200);
        Serial.println(x1);
        Serial.println(c1);
      }
      else if ((incoming - 96 < 4) && (incoming - 96 > 0) && (c3 == 0)) {
        x3 = incoming - 97;
        c3 = 1;
        Serial.println(x3);
        tone(4, 220, 200);
        //Serial.println(c3);
      }
      else if ((incoming - 96 < 7) && (incoming - 96 > 3)  && (c4 == 0)) {
        x4 = incoming - 100;
        c4 = 1;
        Serial.println(x4);
        tone(4, 220, 200);
        //Serial.println(c4);
      }
      else if ((incoming - 96 < 10) && (incoming - 96 > 6)  && (c5 == 0)) {
        x5 = incoming - 103;
        c5 = 1;
        Serial.println(x5);
        tone(4, 220, 200);
        //Serial.println(c5);
      }
    }
  }

  //Once all c variables equal 1, the bot has received a message from each group and can calculate the remainder

  if ((c1 == 1)  && (c2 == 1)  && (c3 == 1)  && (c4 == 1)  && (c5 == 1) && (cond == 1)) {
    cond = 2; //changes to final demonstration condition
    total = (x1 + x2 + x3 + x4 + x5) % 3; //calculates remainder
    outgoing = outgoing; //helps get proper value into this part of code

    // Serial.print("Total: ");
    // Serial.println(total);
  }
  if (cond == 2) {


    digitalWrite(6, LOW); //writes all LEDs to low
    digitalWrite(3, LOW);
    digitalWrite(11, LOW);

    if (total == 0) { //bronze metal, bot dances back and forth and ccontinues sending message

      digitalWrite(6, HIGH); //displays green light
      servoLeft.writeMicroseconds(1550);
      servoRight.writeMicroseconds(1450);
      Serial2.print(outgoing);
      delay(1000);
      servoLeft.writeMicroseconds(1450);
      servoRight.writeMicroseconds(1550);
      delay(1000);
      Serial2.print(outgoing);

    }
    else if (total == 1) {
      //plays light show by flashing green and red LEDs, and continues sending message
      digitalWrite(3, HIGH);
      digitalWrite(6, LOW);
      Serial2.print(outgoing);
      delay(500);
      digitalWrite(6, HIGH);
      digitalWrite(3, LOW);
      delay(500);
      Serial2.print(outgoing);

    }
    else if (total == 2) {
      //turns on both lights, plays song, sends message
      digitalWrite(3, HIGH);
      digitalWrite(6, HIGH);
      beep(b, q);
      beep(cSH, qh);
      Serial2.print(outgoing);
      beep(cSH, qh);
      beep(fSH, q);
      beep(eH, qh);
      Serial2.print(outgoing);
      beep(dH, qh);
      beep(cSH, q);
      beep(b, qh);
      beep(b, qh);
      beep(cSH, q);
      beep(a, ha * 1.5);
      Serial2.print(outgoing);
      beep(b, q);
      beep(cSH, qh);
      beep(cSH, qh);
      beep(fSH, q);
      beep(eH, qh);
      beep(cSH, qh);
      beep(eH, q);
      beep(b, o);
      Serial2.print(outgoing);
      delay(q * 3);
      beep(gSH, q);
      beep(aH, qh);
      beep(gSH, qh);
      beep(fSH, q);
      beep(eH, qh);
      beep(dH, qh);
      beep(cSH, q);
      beep(b, qh);
      Serial2.print(outgoing);
      beep(eH, qh);
      beep(dH, q);
      beep(cSH, ha * 1.5);
      beep(gSH, q);
      Serial2.print(outgoing);
      beep(aH, qh);
      beep(gSH, qh);
      Serial2.print(outgoing);
      beep(fSH, q);
      beep(eH, qh);
      beep(aH, qh);
      beep(bH, qh);
      beep(bH, o + q);
      delay(ei);
      beep(aH, ei);
      beep(aH, ei);
      Serial2.print(outgoing);
      beep(gSH, ei);
      beep(gSH, ei);
      beep(eH, ei);
      beep(fSH, qh);
      beep(fSH, ei);
      beep(gSH, q);
      Serial2.print(outgoing);
      beep(gSH, ei);
      beep(gSH, q);
      beep(aH, ei);
      Serial2.print(outgoing);
      beep(aH, q);
      beep(aH, ei);
      Serial2.print(outgoing);
      beep(gSH, ei);
      beep(gSH, ei);
      beep(eH, ei);
      beep(fSH, q);
      beep(aH, ei);
      beep(bH, q);
      Serial2.print(outgoing);
      beep(aH, ei);
      beep(gSH, ei);
      beep(gSH, q);
      beep(fSH, qh);
      beep(aH, ei);
      Serial2.print(outgoing);
      beep(gSH, ei);
      beep(gSH, ei);
      beep(eH, ei);
      beep(fSH, q);
      beep(aH, q);
      beep(eH, q);
      Serial2.print(outgoing);
      delay(ei);
      beep(aH, ei);
      beep(gSH, ei);
      beep(fSH, ei);
      Serial2.print(outgoing);
      beep(gSH, ei);
      beep(aH, ha + ei);
      beep(aH, q);
      beep(eH, ei);
      Serial2.print(outgoing);
      beep(eH, q);
      beep(cSH, ei);
      beep(eH, ei);
      beep(b, qh);
      Serial2.print(outgoing);
      beep(aH, ei);
      beep(aH, ei);
      beep(gSH, ei);
      beep(gSH, ei);
      beep(eH, ei);
      beep(fSH, qh);
      beep(fSH, ei);
      beep(gSH, q);
      beep(gSH, ei);
      beep(gSH, q);
      beep(aH, ei);
      Serial2.print(outgoing);
      beep(aH, q);
      beep(aH, ei);
      beep(gSH, ei);
      beep(gSH, ei);
      Serial2.print(outgoing);
      beep(eH, ei);
      beep(fSH, q);
      beep(aH, ei);
      beep(bH, q);
      Serial2.print(outgoing);
      beep(aH, ei);
      beep(gSH, ei);
      beep(gSH, q);
      beep(fSH, qh);
      Serial2.print(outgoing);
      beep(aH, ei);
      beep(gSH, ei);
      beep(gSH, ei);
      beep(eH, ei);
      beep(fSH, q);
      beep(aH, q);
      beep(eH, q);
      delay(ei);
      Serial2.print(outgoing);
      beep(aH, ei);
      beep(gSH, ei);
      Serial2.print(outgoing);
      beep(fSH, ei);
      beep(gSH, ei);
      beep(aH, ha + ei);
      beep(aH, q);
      beep(eH, ei);
      beep(eH, q);
      beep(cSH, ei);
      beep(eH, ei);
      beep(b, qh);
      delay(3 * q);
    }
  }
}





//leds
#define green 8
#define blue 9 
#define red 10

//buttons
#define butred 7
#define butgreen 6 
#define butblue 5

// see if it's necessary to keep it here
int interval = 500;


// Creating the lights sequences
// The user should pass as parameters the number max of rounds of the game
int creatingSequence(int rounds){
  int sequence[rounds];
  for(int index = 0; index < rounds ; index++){
    sequence[index] = random(8,11);
  }
  
  return sequence;
}


// turning on the led passed as a parameter
// and returning the led port 
int turnonled(int output, int timeon = interval){
  digitalWrite(output, HIGH); 
  delay(interval); 
  digitalWrite(output, LOW); 
  delay(interval); 

  return output;
}


// return the led port that was pressed
// or return -1 if none of them were pressed
int readingButtons(){
  if (digitalRead(butgreen) == LOW){
    return turnonled(green); 
  }
  if (digitalRead(butred) == LOW){
    return turnonled(red); 
  }
   if (digitalRead(butblue) == LOW){
    return turnonled(blue); 
  }

  return -1;
}


// defining the ports
void pins(){
  // Outputs 
  pinMode(blue, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);

  //Inputs
  pinMode(butblue, INPUT_PULLUP);
  pinMode(butred, INPUT_PULLUP);
  pinMode(butgreen, INPUT_PULLUP);
}


//all the lights flashing together
void initialSequence(int interval){
  digitalWrite(blue, HIGH);
  digitalWrite(red, HIGH);
  digitalWrite(green, HIGH);
  delay(interval); 
  digitalWrite(blue, LOW);
  digitalWrite(red, LOW);
  digitalWrite(green, LOW);
  delay(interval);
  digitalWrite(blue, HIGH);
  digitalWrite(red, HIGH);
  digitalWrite(green, HIGH);
  delay(interval); 
  digitalWrite(blue, LOW);
  digitalWrite(red, LOW);
  digitalWrite(green, LOW);
  delay(interval);
}


//lights flashing sequentially
void sequentialDance(int interval){
 
  digitalWrite(blue, HIGH);
  delay(interval);
  digitalWrite(blue, LOW);
  digitalWrite(green, HIGH);
  delay(interval);
  digitalWrite(green, LOW);
  digitalWrite(red, HIGH);
  delay(interval); 
  digitalWrite(red, LOW);

  digitalWrite(red, HIGH);
  delay(interval); 
  digitalWrite(red, LOW);
  digitalWrite(green, HIGH);
  delay(interval);
  digitalWrite(green, LOW);
  digitalWrite(blue, HIGH);
  delay(interval);
  digitalWrite(blue, LOW);

  digitalWrite(blue, HIGH);
  delay(interval);
  digitalWrite(blue, LOW);
  digitalWrite(green, HIGH);
  delay(interval);
  digitalWrite(green, LOW);
  digitalWrite(red, HIGH);
  delay(interval); 
  digitalWrite(red, LOW);

  digitalWrite(red, HIGH);
  delay(interval); 
  digitalWrite(red, LOW);
  digitalWrite(green, HIGH);
  delay(interval);
  digitalWrite(green, LOW);
  digitalWrite(blue, HIGH);
  delay(interval);
  digitalWrite(blue, LOW);
}


void setup(){
   // initial configs
   Serial.begin(9600);
   pins(); 
   
   // lights dance showing that the game will start
   initialSequence(200); 
   sequentialDance(200);
   initialSequence(200);

   // generating a seed based on the analog port that suffers interference from the air
   // by this, a different seed will always be found
   randomSeed(analogRead(0)); 
   }

void loop(){

}

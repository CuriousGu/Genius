// leds
#define green 8
#define blue 9 
#define red 10

// buttons
#define butred 7
#define butgreen 6 
#define butblue 5


// Game initial Configs that can be changed
// according to your preference
#define amountRounds 4
int interval = 500;
int sequence[amountRounds];


// Values that you shouldn't change
int currentRound = 0;
int answers = 0; 


// status that the game could be according the logic diagram 
// that can be found in the repository as 'logic-diagram'
enum gamestatus {
  ready_for_next,
  user_answering, 
  user_won,
  user_lose
}; 


// Function to organize in which part of the process
// the game is in, according the enum gamestatus
int currentStatus(){
  if (currentRound <= amountRounds){
    if (answers == currentRound){
      return ready_for_next;
    }else{
      return user_answering;
    }
  }else if (currentRound == amountRounds + 1){
    return user_won;
  } else{
    return user_lose;
  }
}


// Creating the lights sequences
// The user should pass as parameters the number max of rounds of the game
void creatingSequence(){
  for(int index = 0; index < amountRounds ; index++){
    sequence[index] = random(8,11);
  }

  Serial.println("Lights Sequence : " );
  for (int index = 0; index < amountRounds; index++){
    if (sequence[index] == 8){
      Serial.println("green");
    }
    if (sequence[index] == 9){
      Serial.println("blue");
    }
    if (sequence[index] == 10){
      Serial.println("red");
    }
  }
}


// turning on the led passed as a parameter
// and returning the led port 
int turnonled(int output, int timeon = interval){
  digitalWrite(output, HIGH); 
  delay(timeon); 
  digitalWrite(output, LOW); 
  delay(timeon); 

  return output;
}


void preparingNewRound(){  
  currentRound++;
  answers = 0;
  
  if (currentRound <= amountRounds){
    for(int index=0; index < currentRound; index++){
      turnonled(sequence[index]);
      delay(500);
    }  
  }
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

void checkingAnswers(){
  int user_answer = readingButtons();

  // Condition to give time to the user press the button
  // Not considering the -1 answer returned while the button
  // wasn't pressed  
  if (user_answer == -1){
    return; 
  }
  
  if (user_answer == sequence[answers]){
    answers++;
  }else{
    Serial.println("Wrong Attempt! You Failed!! ");
    currentRound = amountRounds + 3;
  }
  
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

   // Calling the function that will create the random sequence
   creatingSequence(); 
   }

void loop(){ 
 
  switch(currentStatus()){
    case ready_for_next:
      Serial.println("STATUS --> ready for more"); 
      preparingNewRound();
      break;
      
    case user_answering:
      Serial.println("STATUS --> User trying"); 
      checkingAnswers();
      break;

    case user_won:
      initialSequence(interval);
      digitalWrite(green,HIGH);
      Serial.println("STATUS --> YES!! The user got it");
      for(;;);
      
    case user_lose:
      initialSequence(interval);
      digitalWrite(red, HIGH);
      Serial.println("STATUS --> OH, NO!! The user didn't remeber the right sequence");
      for(;;);
      
  }
}

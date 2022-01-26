// Constants for the game 

//#define boardSide 14      // number of divisions ("squares") the board is gonna have
#define tMin 10           // minimum possible delay between beeps
#define tMax 2000         // maximum possible delay between beeps (corresponding to maximum distance)
#define dMax sqrt(2*pow(boardSide,2))     // maximum distance (when player and treasure are on opposite vertices of the board)

int level = 1;
int boardSide = 10;

//  Coordinates of the Treasure (to be assigned values at void setup)
int xTreasure = random(boardSide);
int yTreasure = random(boardSide);

// ports for components to interact with arduino
int potX = A0;
int potY = A1;
int buzz = 13;
int led1 = 8;
int led2 = 9;
int led3 = 10;
int led4 = 11;

//  calculates the time interval between beeps, according to distance passed
float calcT(float d){
  float t = tMin + (tMax - tMin)*(d/dMax);
  return t;
}

// buzzes when requested from main loop (using proper interval between beeps)
void pleaseBuzz (float dist){
  digitalWrite(buzz, HIGH);
  delay(10);
  digitalWrite(buzz, LOW);
  delay(calcT(dist));
}

// does a mess with buzzing and blinking
void winGame(){
  //  aux. var. for delaying
  int dell = 125;
  
  // little single-toned melody with light effects
  for(int j = 0; j < 3; j ++){
    for (int i = 0; i < 8; i ++){
      if(i != 7){
        digitalWrite(buzz, HIGH);
        digitalWrite(led1, HIGH);
        digitalWrite(led2, LOW);
        digitalWrite(led3, HIGH);
        digitalWrite(led4, LOW);
        delay(dell);
        digitalWrite(buzz, LOW);
        digitalWrite(led1, LOW);
        digitalWrite(led2, HIGH);
        digitalWrite(led3, LOW);
        digitalWrite(led4, HIGH); 
        delay(dell);
      } else {
        delay(2*dell);
      }
    }
  }
  
  // crazy bliking to finish
  for (int blinkCounter = 0; blinkCounter < 50 ; blinkCounter ++) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, LOW);
    delay(dell/4);
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    digitalWrite(led4, HIGH); 
    delay(dell/4);
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(potX, INPUT);
  pinMode(potY, INPUT);
  pinMode(buzz, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
}

void loop() {
//  reads player position from potentiometers, already converts to board square index (0 to 6)
  int xPos = analogRead(potX)*(float (boardSide)/float (1023));
  int yPos = analogRead(potY)*(float (boardSide)/float (1023));  
  
//  calculates distance between player's position and the treasure
  int deltaX = xPos - xTreasure;
  int deltaY = yPos - yTreasure;
  float distance = sqrt(pow(deltaX,2) + pow(deltaY,2));
  
//  feedbacks on Serial monitor
  Serial.print(xPos);
  Serial.print("\t");
  Serial.print(xTreasure);
  Serial.print("\t");
  Serial.print(yPos);
  Serial.print("\t");
  Serial.print(yTreasure);
  Serial.print("\t");  
  Serial.println(distance);

//  buzzes and delays according to distance given
  pleaseBuzz(distance);

// wins the game
  if(distance < 1){
    winGame();
    level ++;
    Serial.print("\nDone! Now, level ");
    Serial.println(level);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    delay(4000);
    // Lets player know it's about to restart
    digitalWrite(buzz, HIGH);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    delay(100);
    digitalWrite(buzz, LOW);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    delay(1000);
    
    boardSide += 4;
      // assgining a random position to the treasure
    xTreasure = random(boardSide);
    yTreasure = random(boardSide);
  
  }
}

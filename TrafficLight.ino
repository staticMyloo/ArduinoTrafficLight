// Myles Hosken ID: 20124720
// ENEL599 2022 S2 Assignment 1 Traffic Light

const int BUTTON_ONE = 12;
const int BUTTON_TWO = 11;
const int RED_LED_1 = 7;
const int ORANGE_LED_1 = 6;
const int GREEN_LED_1 = 5;
const int RED_LED_2 = 4;
const int ORANGE_LED_2 = 3;
const int GREEN_LED_2 = 2;

void stateZero();
void stateOne();
void stateTwo();
void stateThree();
void stateFour();
void stateFive();
void stateSix();
void stateSeven();
void testMode();
void checkForInput();

unsigned const int BLINK_INTERVAL_1 = 500;
unsigned long timeStamp = 0;
int state = 0;
int buttonOneState = 0;
int B1oldValue = 0;
int testState = 0;
int buttonTwoState = 0;
int B2oldValue = 0;
int cycle = 0;
bool testActive = false;
int phaseControl = 0;


/*
 * Intializing buttons/LED's as input's / output
 */
void setup()
{
  pinMode(BUTTON_ONE, INPUT);
  pinMode(BUTTON_TWO, INPUT);
  pinMode(RED_LED_1, OUTPUT);
  pinMode(ORANGE_LED_1, OUTPUT);
  pinMode(GREEN_LED_1, OUTPUT);
  pinMode(RED_LED_2, OUTPUT);
  pinMode(ORANGE_LED_2, OUTPUT);
  pinMode(GREEN_LED_2, OUTPUT);
}

/*
 * program entry point
 * changes state on cycle variable
 * inner loop to cease external input while testActive is true
 */
void loop()
{
  checkForInput();
  
  switch (cycle)
  {
    case 0:
    stateZero();
    break;
    
    case 1:
    stateOne();
    break;
    
    case 2:
    stateTwo();
    break;
    
    case 3:
    stateThree();
    break;
    
    case 4:
    stateFour();
    break;
    
    case 5:
    stateFive();
    break;
    
    case 6:
    stateSix();
    break;
    
    case 7:
    stateSeven();
    break;
    
    default:
    break; 
  }
  
  while(testActive)
  {
    testMode();
  }
  
}

/*
 * void testMode function responsible while testActive boolean is true
 * Uses millis and a current time stamp to flick between traffic lights at 1hz
 * checkForInput function included at the bottom to allow for loop exit
 */

void testMode()
{
  unsigned long currentTime = millis();
  
  if(phaseControl == 0)
  {
    if((currentTime - timeStamp) >= BLINK_INTERVAL_1)
    {
      phaseControl = 1;
      timeStamp = currentTime;
    }
  }
  else
  {
    if((currentTime - timeStamp) >= BLINK_INTERVAL_1)
    {
      phaseControl = 0;
      timeStamp = currentTime;
    }
  }
    
  switch(phaseControl)
  {
    case 0:
      digitalWrite(RED_LED_1, HIGH);
      digitalWrite(ORANGE_LED_1, HIGH);
      digitalWrite(GREEN_LED_1, HIGH);
      digitalWrite(RED_LED_2, LOW);
      digitalWrite(ORANGE_LED_2, LOW);
      digitalWrite(GREEN_LED_2, LOW);
      break;
    case 1:
      digitalWrite(RED_LED_1, LOW);
      digitalWrite(ORANGE_LED_1, LOW);
      digitalWrite(GREEN_LED_1, LOW);
      digitalWrite(RED_LED_2, HIGH);
      digitalWrite(ORANGE_LED_2, HIGH);
      digitalWrite(GREEN_LED_2, HIGH); 
    default:
      break;
  }
  
  checkForInput();
}

/*
 * Helper function to check for button input, uses delay to accomodate for button debouncing
 * *delay can be increased slighty if required*
 * state is for the button input, cycle variable controls "state" of the traffic light
 * cycle is reset when count is above 7, cycle ranges from 0-7, 8 states total 
 * button 2 will turn boolean and enter inner loop within main function, button one remains inactive during this
 */
void checkForInput()
{
  if(!testActive)
  {
    buttonOneState = digitalRead(BUTTON_ONE);
  }
  
  if((buttonOneState == HIGH) && (B1oldValue == LOW))
  {
    state = 1 - state;
    delay(25);
  }
  
  B1oldValue = buttonOneState;
  
  if(state == 1)
  {
    state = 0;
    cycle += 1;
    if(cycle > 7)
    {
      cycle = 0;
    }
  }
  
  if((buttonOneState == LOW) && (B1oldValue == HIGH))
  {
    delay(25);
  }
  
  buttonTwoState = digitalRead(BUTTON_TWO);
  
  if((buttonTwoState == HIGH) && (B2oldValue == LOW))
  {
    testState = 1 - testState;
    delay(25);
  }
  
  B2oldValue = buttonTwoState;
  
  if(testState == 1)
  {
    testActive = true;
    cycle = 0;
  }
  else
  {
    testActive = false;
  }
  
  if((buttonTwoState == LOW) && (B2oldValue == HIGH))
  {
    delay(25);
  }
}

/*
 * The follow void helper functions are to control LED output depending on the state
 * controlled by switch within the main depending on cycle variable
 */

void stateZero()
{
  digitalWrite(RED_LED_1, HIGH);
  digitalWrite(ORANGE_LED_1, LOW);
  digitalWrite(GREEN_LED_1, LOW);
  digitalWrite(RED_LED_2, HIGH);
  digitalWrite(ORANGE_LED_2, LOW);
  digitalWrite(GREEN_LED_2, LOW);
}

void stateOne()
{
  digitalWrite(RED_LED_1, HIGH);
  digitalWrite(ORANGE_LED_1, HIGH);
  digitalWrite(GREEN_LED_1, LOW);
  digitalWrite(RED_LED_2, HIGH);
  digitalWrite(ORANGE_LED_2, LOW);
  digitalWrite(GREEN_LED_2, LOW);
}

void stateTwo()
{
  digitalWrite(RED_LED_1, LOW);
  digitalWrite(ORANGE_LED_1, LOW);
  digitalWrite(GREEN_LED_1, HIGH);
  digitalWrite(RED_LED_2, HIGH);
  digitalWrite(ORANGE_LED_2, LOW);
  digitalWrite(GREEN_LED_2, LOW);
}

void stateThree()
{
  digitalWrite(RED_LED_1, LOW);
  digitalWrite(ORANGE_LED_1, HIGH);
  digitalWrite(GREEN_LED_1, LOW);
  digitalWrite(RED_LED_2, HIGH);
  digitalWrite(ORANGE_LED_2, LOW);
  digitalWrite(GREEN_LED_2, LOW);
}

void stateFour()
{
  digitalWrite(RED_LED_1, HIGH);
  digitalWrite(ORANGE_LED_1, LOW);
  digitalWrite(GREEN_LED_1, LOW);
  digitalWrite(RED_LED_2, HIGH);
  digitalWrite(ORANGE_LED_2, LOW);
  digitalWrite(GREEN_LED_2, LOW);
}

void stateFive()
{
  digitalWrite(RED_LED_1, HIGH);
  digitalWrite(ORANGE_LED_1, LOW);
  digitalWrite(GREEN_LED_1, LOW);
  digitalWrite(RED_LED_2, HIGH);
  digitalWrite(ORANGE_LED_2, HIGH);
  digitalWrite(GREEN_LED_2, LOW);
}

void stateSix()
{
  digitalWrite(RED_LED_1, HIGH);
  digitalWrite(ORANGE_LED_1, LOW);
  digitalWrite(GREEN_LED_1, LOW);
  digitalWrite(RED_LED_2, LOW);
  digitalWrite(ORANGE_LED_2, LOW);
  digitalWrite(GREEN_LED_2, HIGH);
}

void stateSeven()
{
  digitalWrite(RED_LED_1, HIGH);
  digitalWrite(ORANGE_LED_1, LOW);
  digitalWrite(GREEN_LED_1, LOW);
  digitalWrite(RED_LED_2, LOW);
  digitalWrite(ORANGE_LED_2, HIGH);
  digitalWrite(GREEN_LED_2, LOW);
}

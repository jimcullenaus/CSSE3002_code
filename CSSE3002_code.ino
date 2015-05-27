#define LEFT_1 1 // Light Set 1
#define LEFT_2 2 // Light Set 2
#define LEFT_3 3 // Light Set 3
#define LEFT_4 4 // Light Set 4
#define RIGHT_1 5 // Light Set 5
#define RIGHT_2 6 // Light Set 6
#define RIGHT_3 7 // Light Set 7
#define RIGHT_4 8 // Light Set 8

#define MODE_BUTTON A2 // Mode switch button (pin 2 for interrupts)

#define RIGHT_SENSOR A3 // Right leg accerlerometer pin
#define LEFT_SENSOR A4 // Left leg accerlerometer pin
#define FAKE_TIME 500 // Time for the fake running
const int STEP_THRESHOLD = 200;
volatile boolean runningMode = true;
boolean LEFT_ON = false;


void setup() {
  pinMode(LEFT_1, OUTPUT);
  
  pinMode(LEFT_2, OUTPUT);
  pinMode(LEFT_3, OUTPUT);
  pinMode(LEFT_4, OUTPUT);
  pinMode(RIGHT_1, OUTPUT);
  pinMode(RIGHT_2, OUTPUT);
  pinMode(RIGHT_3, OUTPUT);
  pinMode(RIGHT_4, OUTPUT);  
  
  pinMode(MODE_BUTTON, INPUT);
  
  // Interrupt for mode button. Hopefully this sequencer has interrupts (I know of a work around if there isn't)
  attachInterrupt(0, modeSwitch, RISING);
  // Not sure if these analog pins are set up right
  pinMode(RIGHT_SENSOR, INPUT);
  pinMode(LEFT_SENSOR, INPUT);
  
  displayPowerOnTwo();

}

/* Fairly sure this code should never be entered except immediately after the initial setup.
 * All other transitions between running mode and display mode should be done via the interrupt and modeSwitch
 */
void loop() {
  if(runningMode) {
    //displayCycleTwo(); // Use this, comment out below line, to test that the mode switch button works.
    runningCycle();
  } else {
    displayCycle();
  }
}

/* Switch the mode */
void modeSwitch() {
 runningMode = !runningMode;
 if(runningMode) {
  enterRunningMode();
 } else {
  enterDisplayMode();
 } 
}

/* Show this pattern when entering running mode */
void enterRunningMode() {
  leftLeg();
  delay(100);
  rightLeg();
  delay(100);
  off();
  runningCycle();
  //displayCycleTwo(); // Use this, comment out below line, to test that the mode switch button works.
}

/* Show this pattern when entering display mode */
void enterDisplayMode() {
  off();
  on();
  delay(100);
  off();
  displayCycle();
}

/* Wait for either the left leg or the right leg to sensor to trigger, then light up that leg 
    - currently badly written. May loop infinitely, need to figure out a better way. */
void runningCycle() {
  while(true) {
    int right = analogRead(RIGHT_SENSOR);
    int left = analogRead(LEFT_SENSOR);
    
    if(right > STEP_THRESHOLD) {
      rightLeg();
      break;
    } else if (left > STEP_THRESHOLD) {
      leftLeg();
      break;
    }   
  }
}

void testRunningCycle() {
  while(true) {
    int right = analogRead(RIGHT_SENSOR);
    int left = analogRead(LEFT_SENSOR);
    
    if(left >= STEP_THRESHOLD || right >= STEP_THRESHOLD) {
      toggleLight();
      delay(300);
    }
  }
}

void toggleLight() {
  if (LEFT_ON) {
    rightLeg();
  } else {
    leftLeg();
  }
}

void runningFake() {
  while(true) {
    rightLeg();
    delay(FAKE_TIME);
    leftLeg();
    delay(FAKE_TIME);
  }
}

/* Light up the left leg */
void leftLeg() {
 digitalWrite(LEFT_1, HIGH);
 digitalWrite(LEFT_2, HIGH);
 digitalWrite(LEFT_3, HIGH);
 digitalWrite(LEFT_4, HIGH);
 digitalWrite(RIGHT_1, LOW);
 digitalWrite(RIGHT_2, LOW);
 digitalWrite(RIGHT_3, LOW);
 digitalWrite(RIGHT_4, LOW);
}

/* Light up the right leg */
void rightLeg() {
 digitalWrite(LEFT_1, LOW);
 digitalWrite(LEFT_2, LOW);
 digitalWrite(LEFT_3, LOW);
 digitalWrite(LEFT_4, LOW);
 digitalWrite(RIGHT_1, HIGH);
 digitalWrite(RIGHT_2, HIGH);
 digitalWrite(RIGHT_3, HIGH);
 digitalWrite(RIGHT_4, HIGH);
}

/* Turn all lights off */
void off() {
 digitalWrite(LEFT_1, LOW);
 digitalWrite(LEFT_2, LOW);
 digitalWrite(LEFT_3, LOW);
 digitalWrite(LEFT_4, LOW);
 digitalWrite(RIGHT_1, LOW);
 digitalWrite(RIGHT_2, LOW);
 digitalWrite(RIGHT_3, LOW);
 digitalWrite(RIGHT_4, LOW);
}

/* Turn all lights on */
void on() {
 digitalWrite(LEFT_1, HIGH);
 digitalWrite(LEFT_2, HIGH);
 digitalWrite(LEFT_3, HIGH);
 digitalWrite(LEFT_4, HIGH);
 digitalWrite(RIGHT_1, HIGH);
 digitalWrite(RIGHT_2, HIGH);
 digitalWrite(RIGHT_3, HIGH);
 digitalWrite(RIGHT_4, HIGH);
}

/* One 'cycle' of the display mode */
void displayCycle() {
 digitalWrite(LEFT_1, LOW);
 digitalWrite(LEFT_2, HIGH);
 digitalWrite(LEFT_3, LOW);
 digitalWrite(LEFT_4, HIGH);
 digitalWrite(RIGHT_1, HIGH);
 digitalWrite(RIGHT_2, LOW);
 digitalWrite(RIGHT_3, HIGH);
 digitalWrite(RIGHT_4, LOW);
 delay(500);
 digitalWrite(LEFT_1, HIGH);
 digitalWrite(LEFT_2, LOW);
 digitalWrite(LEFT_3, HIGH);
 digitalWrite(LEFT_4, LOW);
 digitalWrite(RIGHT_1, LOW);
 digitalWrite(RIGHT_2, HIGH);
 digitalWrite(RIGHT_3, LOW);
 digitalWrite(RIGHT_4, HIGH);
 delay(500);
}

/* A second display cycle to be used for testing the button temporarily */
void displayCycleTwo() {
  digitalWrite(LEFT_1, HIGH);
  digitalWrite(LEFT_2, LOW);
  digitalWrite(LEFT_3, LOW);
  digitalWrite(LEFT_4, LOW);
  digitalWrite(RIGHT_1, HIGH);
  digitalWrite(RIGHT_2, LOW);
  digitalWrite(RIGHT_3, LOW);
  digitalWrite(RIGHT_4, LOW);
  delay(500);
  digitalWrite(LEFT_1, LOW);
  digitalWrite(LEFT_2, HIGH);
  digitalWrite(LEFT_3, LOW);
  digitalWrite(LEFT_4, LOW);
  digitalWrite(RIGHT_1, LOW);
  digitalWrite(RIGHT_2, HIGH);
  digitalWrite(RIGHT_3, LOW);
  digitalWrite(RIGHT_4, LOW);
  delay(500);
  digitalWrite(LEFT_1, LOW);
  digitalWrite(LEFT_2, LOW);
  digitalWrite(LEFT_3, HIGH);
  digitalWrite(LEFT_4, LOW);
  digitalWrite(RIGHT_1, LOW);
  digitalWrite(RIGHT_2, LOW);
  digitalWrite(RIGHT_3, HIGH);
  digitalWrite(RIGHT_4, LOW);
  delay(500);
  digitalWrite(LEFT_1, LOW);
  digitalWrite(LEFT_2, LOW);
  digitalWrite(LEFT_3, LOW);
  digitalWrite(LEFT_4, HIGH);
  digitalWrite(RIGHT_1, LOW);
  digitalWrite(RIGHT_2, LOW);
  digitalWrite(RIGHT_3, LOW);
  digitalWrite(RIGHT_4, HIGH);
  delay(500);
}

/* Light sequence to display on powering on */
void displayPowerOn() {
  digitalWrite(LEFT_1, HIGH);
  digitalWrite(LEFT_2, HIGH);
  digitalWrite(LEFT_3, HIGH);
  digitalWrite(LEFT_4, HIGH);
  digitalWrite(RIGHT_1, HIGH);
  digitalWrite(RIGHT_2, HIGH);
  digitalWrite(RIGHT_3, HIGH);
  digitalWrite(RIGHT_4, HIGH); 
  delay(100);
  digitalWrite(LEFT_1, LOW);
  digitalWrite(LEFT_2, LOW);
  digitalWrite(LEFT_3, LOW);
  digitalWrite(LEFT_4, LOW);
  digitalWrite(RIGHT_1, LOW);
  digitalWrite(RIGHT_2, LOW);
  digitalWrite(RIGHT_3, LOW);
  digitalWrite(RIGHT_4, LOW); 
  delay(100);
    digitalWrite(LEFT_1, HIGH);
  digitalWrite(LEFT_2, HIGH);
  digitalWrite(LEFT_3, HIGH);
  digitalWrite(LEFT_4, HIGH);
  digitalWrite(RIGHT_1, HIGH);
  digitalWrite(RIGHT_2, HIGH);
  digitalWrite(RIGHT_3, HIGH);
  digitalWrite(RIGHT_4, HIGH); 
  delay(100);
  digitalWrite(LEFT_1, LOW);
  digitalWrite(LEFT_2, LOW);
  digitalWrite(LEFT_3, LOW);
  digitalWrite(LEFT_4, LOW);
  digitalWrite(RIGHT_1, LOW);
  digitalWrite(RIGHT_2, LOW);
  digitalWrite(RIGHT_3, LOW);
  digitalWrite(RIGHT_4, LOW);
}

void displayPowerOnTwo() {
  digitalWrite(LEFT_1, HIGH);
  digitalWrite(LEFT_2, LOW);
  digitalWrite(LEFT_3, LOW);
  digitalWrite(LEFT_4, LOW);
  digitalWrite(RIGHT_1, LOW);
  digitalWrite(RIGHT_2, LOW);
  digitalWrite(RIGHT_3, LOW);
  digitalWrite(RIGHT_4, LOW);
  delay(1500);
  digitalWrite(LEFT_1, LOW);
  digitalWrite(LEFT_2, HIGH);
  digitalWrite(LEFT_3, LOW);
  digitalWrite(LEFT_4, LOW);
  digitalWrite(RIGHT_1, LOW);
  digitalWrite(RIGHT_2, LOW);
  digitalWrite(RIGHT_3, LOW);
  digitalWrite(RIGHT_4, LOW);
  delay(1500);
  digitalWrite(LEFT_1, LOW);
  digitalWrite(LEFT_2, LOW);
  digitalWrite(LEFT_3, HIGH);
  digitalWrite(LEFT_4, LOW);
  digitalWrite(RIGHT_1, LOW);
  digitalWrite(RIGHT_2, LOW);
  digitalWrite(RIGHT_3, LOW);
  digitalWrite(RIGHT_4, LOW);
  delay(1500);
  digitalWrite(LEFT_1, LOW);
  digitalWrite(LEFT_2, LOW);
  digitalWrite(LEFT_3, LOW);
  digitalWrite(LEFT_4, HIGH);
  digitalWrite(RIGHT_1, LOW);
  digitalWrite(RIGHT_2, LOW);
  digitalWrite(RIGHT_3, LOW);
  digitalWrite(RIGHT_4, LOW);
  delay(1500);
  digitalWrite(LEFT_1, LOW);
  digitalWrite(LEFT_2, LOW);
  digitalWrite(LEFT_3, LOW);
  digitalWrite(LEFT_4, LOW);
  digitalWrite(RIGHT_1, HIGH);
  digitalWrite(RIGHT_2, LOW);
  digitalWrite(RIGHT_3, LOW);
  digitalWrite(RIGHT_4, LOW);
  delay(1500);
  digitalWrite(LEFT_1, LOW);
  digitalWrite(LEFT_2, LOW);
  digitalWrite(LEFT_3, LOW);
  digitalWrite(LEFT_4, LOW);
  digitalWrite(RIGHT_1, LOW);
  digitalWrite(RIGHT_2, HIGH);
  digitalWrite(RIGHT_3, LOW);
  digitalWrite(RIGHT_4, LOW);
  delay(1500);
  digitalWrite(LEFT_1, LOW);
  digitalWrite(LEFT_2, LOW);
  digitalWrite(LEFT_3, LOW);
  digitalWrite(LEFT_4, LOW);
  digitalWrite(RIGHT_1, LOW);
  digitalWrite(RIGHT_2, LOW);
  digitalWrite(RIGHT_3, HIGH);
  digitalWrite(RIGHT_4, LOW);
  delay(1500);
  digitalWrite(LEFT_1, LOW);
  digitalWrite(LEFT_2, LOW);
  digitalWrite(LEFT_3, LOW);
  digitalWrite(LEFT_4, LOW);
  digitalWrite(RIGHT_1, LOW);
  digitalWrite(RIGHT_2, LOW);
  digitalWrite(RIGHT_3, LOW);
  digitalWrite(RIGHT_4, HIGH);
  delay(1500);
}



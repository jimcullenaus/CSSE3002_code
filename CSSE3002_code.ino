#define LEFT_1 7 // Light Set 1
#define LEFT_2 8 // Light Set 2
#define LEFT_3 6 // Light Set 3
#define LEFT_4 9 // Light Set 4
#define RIGHT_1 4 // Light Set 5
#define RIGHT_2 3 // Light Set 6
#define RIGHT_3 2 // Light Set 7
#define RIGHT_4 5 // Light Set 8

#define MODE_BUTTON A2 // Mode switch button (pin 2 for interrupts)

#define RIGHT_SENSOR A3 // Right leg accerlerometer pin
#define LEFT_SENSOR A4 // Left leg accerlerometer pin
#define FAKE_TIME 500 // Time for the fake running
const int STEP_THRESHOLD = 1000;
// 0 is off, 1 is running mode, 2 is display mode
volatile int runningMode = 0;
volatile boolean buttonReady = true; // True when button is ready to be clicked
boolean leftOn = false;

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
  
  pinMode(RIGHT_SENSOR, INPUT);
  pinMode(LEFT_SENSOR, INPUT);
  
  displayPowerOn();

}

void loop() {
  if(runningMode == 1) {
    runningCycle();
  } else if (runningMode == 2) {
    displayCycle();
  } else {
    offMode();
  }
}

void offMode() {
  off();
  delay(200);
  while (true) {
    if (checkButton()) {
      return;
    }
  }
}

void runningCycle() {
  modeSetup();
  while(true) {
    int right = analogRead(RIGHT_SENSOR);
    int left = analogRead(LEFT_SENSOR);
    
    if(left >= STEP_THRESHOLD || right >= STEP_THRESHOLD) {
      toggleLight();
      delay(1000);
    }
    if (checkButton()) {
      return;
    }
  }
}

void modeSetup() {
  off();
  delay(100);
  on();
  delay(200);
  off();
}

void displayCycle() {
  modeSetup();
  while (true) {
    digitalWrite(LEFT_1, HIGH);
    digitalWrite(LEFT_2, LOW);
    digitalWrite(LEFT_3, LOW);
    digitalWrite(LEFT_4, LOW);
    digitalWrite(RIGHT_1, HIGH);
    digitalWrite(RIGHT_2, LOW);
    digitalWrite(RIGHT_3, LOW);
    digitalWrite(RIGHT_4, LOW);
    delay(500);
    if (checkButton()) {
      return;
    }
    digitalWrite(LEFT_1, LOW);
    digitalWrite(LEFT_2, HIGH);
    digitalWrite(LEFT_3, LOW);
    digitalWrite(LEFT_4, LOW);
    digitalWrite(RIGHT_1, LOW);
    digitalWrite(RIGHT_2, HIGH);
    digitalWrite(RIGHT_3, LOW);
    digitalWrite(RIGHT_4, LOW);
    delay(500);
    if (checkButton()) {
      return;
    }
    digitalWrite(LEFT_1, LOW);
    digitalWrite(LEFT_2, LOW);
    digitalWrite(LEFT_3, HIGH);
    digitalWrite(LEFT_4, LOW);
    digitalWrite(RIGHT_1, LOW);
    digitalWrite(RIGHT_2, LOW);
    digitalWrite(RIGHT_3, HIGH);
    digitalWrite(RIGHT_4, LOW);
    delay(500);
    if (checkButton()) {
      return;
    }
    digitalWrite(LEFT_1, LOW);
    digitalWrite(LEFT_2, LOW);
    digitalWrite(LEFT_3, LOW);
    digitalWrite(LEFT_4, HIGH);
    digitalWrite(RIGHT_1, LOW);
    digitalWrite(RIGHT_2, LOW);
    digitalWrite(RIGHT_3, LOW);
    digitalWrite(RIGHT_4, HIGH);
    delay(500);
    if (checkButton()) {
      return;
    }
  }
}

void displayPowerOn() {
  off();
  digitalWrite(LEFT_1, HIGH);
  digitalWrite(LEFT_2, LOW);
  digitalWrite(LEFT_3, LOW);
  digitalWrite(LEFT_4, LOW);
  digitalWrite(RIGHT_1, LOW);
  digitalWrite(RIGHT_2, LOW);
  digitalWrite(RIGHT_3, LOW);
  digitalWrite(RIGHT_4, LOW);
  delay(200);
  digitalWrite(LEFT_1, LOW);
  digitalWrite(LEFT_2, HIGH);
  digitalWrite(LEFT_3, LOW);
  digitalWrite(LEFT_4, LOW);
  digitalWrite(RIGHT_1, LOW);
  digitalWrite(RIGHT_2, LOW);
  digitalWrite(RIGHT_3, LOW);
  digitalWrite(RIGHT_4, LOW);
  delay(200);
  digitalWrite(LEFT_1, LOW);
  digitalWrite(LEFT_2, LOW);
  digitalWrite(LEFT_3, HIGH);
  digitalWrite(LEFT_4, LOW);
  digitalWrite(RIGHT_1, LOW);
  digitalWrite(RIGHT_2, LOW);
  digitalWrite(RIGHT_3, LOW);
  digitalWrite(RIGHT_4, LOW);
  delay(200);
  digitalWrite(LEFT_1, LOW);
  digitalWrite(LEFT_2, LOW);
  digitalWrite(LEFT_3, LOW);
  digitalWrite(LEFT_4, HIGH);
  digitalWrite(RIGHT_1, LOW);
  digitalWrite(RIGHT_2, LOW);
  digitalWrite(RIGHT_3, LOW);
  digitalWrite(RIGHT_4, LOW);
  delay(200);
  digitalWrite(LEFT_1, LOW);
  digitalWrite(LEFT_2, LOW);
  digitalWrite(LEFT_3, LOW);
  digitalWrite(LEFT_4, LOW);
  digitalWrite(RIGHT_1, HIGH);
  digitalWrite(RIGHT_2, LOW);
  digitalWrite(RIGHT_3, LOW);
  digitalWrite(RIGHT_4, LOW);
  delay(200);
  digitalWrite(LEFT_1, LOW);
  digitalWrite(LEFT_2, LOW);
  digitalWrite(LEFT_3, LOW);
  digitalWrite(LEFT_4, LOW);
  digitalWrite(RIGHT_1, LOW);
  digitalWrite(RIGHT_2, HIGH);
  digitalWrite(RIGHT_3, LOW);
  digitalWrite(RIGHT_4, LOW);
  delay(200);
  digitalWrite(LEFT_1, LOW);
  digitalWrite(LEFT_2, LOW);
  digitalWrite(LEFT_3, LOW);
  digitalWrite(LEFT_4, LOW);
  digitalWrite(RIGHT_1, LOW);
  digitalWrite(RIGHT_2, LOW);
  digitalWrite(RIGHT_3, HIGH);
  digitalWrite(RIGHT_4, LOW);
  delay(200);
  digitalWrite(LEFT_1, LOW);
  digitalWrite(LEFT_2, LOW);
  digitalWrite(LEFT_3, LOW);
  digitalWrite(LEFT_4, LOW);
  digitalWrite(RIGHT_1, LOW);
  digitalWrite(RIGHT_2, LOW);
  digitalWrite(RIGHT_3, LOW);
  digitalWrite(RIGHT_4, HIGH);
  delay(200);
  on();
  delay(400);
}

/*** Helper procedures go below here ***/

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

void toggleLight() {
  if (leftOn) {
    rightLeg();
    leftOn = false;
  } else {
    leftLeg();
    leftOn = true;
  }
}

boolean checkButton() {
  if ((digitalRead(MODE_BUTTON) == HIGH) && buttonReady) {
    runningMode = (runningMode + 1) % 3;
    buttonReady = !buttonReady;
    return true;
  } else if (!buttonReady) {
    buttonReady = !buttonReady;
  } else {
    return false;
  }
}

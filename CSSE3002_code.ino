#define LEFT_1 7 // Light Set 1
#define LEFT_2 8 // Light Set 2
#define LEFT_3 6 // Light Set 3
#define LEFT_4 9 // Light Set 4
#define RIGHT_1 4 // Light Set 5
#define RIGHT_2 3 // Light Set 6
#define RIGHT_3 2 // Light Set 7
#define RIGHT_4 5 // Light Set 8

#define MODE_BUTTON A2 // Mode switch button (pin 2 for interrupts)

#define RIGHT_SENSOR A3 // Right leg vibration sensor pin
#define LEFT_SENSOR A5 // Left leg vibration sensor pin

#define STEP_THRESHOLD 700

volatile int mode = 0; // 0 off, 1 running, 2 display
volatile boolean buttonReady = true; // True when button is ready to be clicked
boolean leftOn = false; // true when the left leg is being turned on next for running mode

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
  
  powerOn();
}

void loop() {
  if (mode == 1) {
    runningCycle();
  } else if (mode == 2) {
    displayCycle();
  } else {
    offMode();
  }
}

/*void runningCycle() {
  modeChange();
  while (true) {
    right(1,1,1,1);
    left(0,0,0,0);
    delay(500);
    if (checkButton()) {
      return;
    }
    left(1,1,1,1);
    right(0,0,0,0);
    delay(500);
    if (checkButton()) {
      return;
    }
  }
}*/

/*
void runningCycle() {
  modeChange();
  int index = 0;
  boolean tests[10];
  boolean signal = false;
  
  while (true) {
    tests[index] = ((analogRead(RIGHT_SENSOR) >= STEP_THRESHOLD) || (analogRead(LEFT_SENSOR) >= STEP_THRESHOLD));
    index = (index + 1) % 10;
    for (int i = 0; i < 10; ++i) {
      signal &= tests[i];
    }
    if (signal) {
      toggleLight();
      delay(500);
      left(0,0,0,0);
      right(0,0,0,0);
      signal = false;
      for (int i = 0; i < 10; ++i) {
        tests[i] = false;
      }
    }
    if (checkButton()) {
      return;
    }
  }
}
*/

void runningCycle() {
  modeChange();
  int loopsSinceToggle = 200;
  while(true) {
    if (loopsSinceToggle >= 200) {
      if (signal()) {
        toggleLight();
        delay(500);
      } else {
        left(0,0,0,0);
        right(0,0,0,0);
      }
      if (checkButton()) {
        return;
      }
      loopsSinceToggle = 0;
    } else {
      ++loopsSinceToggle;
      //delay(10);
    }
  }
}

/** Check if there is a signal from the vibration sensors.
 *  Read a number of times, and if enough of those times are over the threshold,
 *  return true. Otherwise, return false.
 **/
boolean signal() {
  int count = 0;
  int highest = 0;
  boolean continuous = false;
  
  for (int i = 0; i < 20; ++i) {
    int rightRead = analogRead(RIGHT_SENSOR);
    int leftRead = analogRead(LEFT_SENSOR);
    if (leftRead >= STEP_THRESHOLD || rightRead >= STEP_THRESHOLD) {
      ++count;
      continuous = true;
    } else {
      continuous = false;
      if (count > highest) {
        highest = count;
      }
      count = 0;
    }
  }
  if (highest >= 10) {
    return true;
  } else {
    return false;
  }
}

void displayCycle() {
  modeChange();
  while (true) {
    right(1,0,0,0);
    left(1,0,0,0);
    delay(500);
    if (checkButton()) {
      return;
    }
    right(0,1,0,0);
    left(0,1,0,0);
    delay(500);
    if (checkButton()) {
      return;
    }
    right(0,0,1,0);
    left(0,0,1,0);
    delay(500);
    if (checkButton()) {
      return;
    }
    right(0,0,0,1);
    left(0,0,0,1);
    delay(500);
    if (checkButton()) {
      return;
    }
  }
}

/* standby mode: all off but responsive to the mode button */
void offMode() {
  left(0,0,0,0);
  right(0,0,0,0);
  delay(200);
  while (true) {
    if (checkButton()) {
      return;
    }
  }
} 

/* Light up the left leg */
void left(boolean l1, boolean l2, boolean l3, boolean l4) {
 digitalWrite(LEFT_1, l1 ? HIGH : LOW);
 digitalWrite(LEFT_2, l2 ? HIGH : LOW);
 digitalWrite(LEFT_3, l3 ? HIGH : LOW);
 digitalWrite(LEFT_4, l4 ? HIGH : LOW);
}

/* Light up the right leg */
void right(boolean r1, boolean r2, boolean r3, boolean r4) {
 digitalWrite(RIGHT_1, r1 ? HIGH : LOW);
 digitalWrite(RIGHT_2, r2 ? HIGH : LOW);
 digitalWrite(RIGHT_3, r3 ? HIGH : LOW);
 digitalWrite(RIGHT_4, r4 ? HIGH : LOW);
}

/* true if button pressed (this procedure to avoid contact bounce) */
boolean checkButton() {
  if ((digitalRead(MODE_BUTTON) == HIGH) && buttonReady) {
    mode = (mode + 1) % 3;
    buttonReady = !buttonReady;
    return true;
  } else if ((digitalRead(MODE_BUTTON) == LOW) && !buttonReady) {
    buttonReady = !buttonReady;
  } else {
    return false;
  }
}

/* blink all lights once when mode changed */
void modeChange() {
  left(0,0,0,0);
  right(0,0,0,0);
  delay(400);
  left(1,1,1,1);
  right(1,1,1,1);
  delay(200);
  left(0,0,0,0);
  right(0,0,0,0);
  delay(200);
  left(1,1,1,1);
  right(1,1,1,1);
  delay(200);
  left(0,0,0,0);
  right(0,0,0,0);
  delay(500);
}

/* pattern displayed when device powered on */
void powerOn() {
  
  /* left leg first */
  right(0,0,0,0);
  
  left(1,0,0,0);
  delay(200);
  left(0,1,0,0);
  delay(200);
  left(0,0,1,0);
  delay(200);
  left(0,0,0,1);
  delay(200);
  
  /* then right leg */
  left(0,0,0,0);
  
  right(1,0,0,0);
  delay(200);
  right(0,1,0,0);
  delay(200);
  right(0,0,1,0);
  delay(200);
  right(0,0,0,1);
  delay(200);
  
  /* then all on */
  left(1,1,1,1);
  right(1,1,1,1);
  delay(400);
}

void toggleLight() {
  if (leftOn) {
    right(1,1,1,1);
    left(0,0,0,0);
    leftOn = false;
  } else {
    left(1,1,1,1);
    right(0,0,0,0);
    leftOn = true;
  }
}
  

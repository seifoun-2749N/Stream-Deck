# include <Keyboard.h>

const int ROWS = 6;
const int COLS = 4;
const int rowPins[ROWS] = {2, 3, 4, 5, 6, 7};
const int colPins[COLS] = {8, 9, 10, 16};

bool buttonState[ROWS][COLS] = {false};
bool lastButtonState[ROWS][COLS] = {false};
unsigned long lastDebounceTime[ROWS][COLS] = {0};
const unsigned long debounceDelay = 50;

bool physicalButtonPressed[6] = {false};
bool lastPhysicalButtonState[6] = {false};

void setup() {
  for (int i = 0; i < ROWS; i++) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins, HIGH);
  }

  for (int i = 0; i < COLS; i++) {
    pinMode(colPins[i], INPUT_PULLUP);
  }

  Keyboard.begin();

}

void loop() {
  scanMatrix();
  detectPhysicalButtons();
  handlePhysicalButtonActions();

}

void scanMatrix() {
  for (int row = 0 ; row < ROWS; row++) {
    digitalWrite(rowPins[row], LOW);
    delayMicroseconds(10);
    for (int col = 0; col < COLS; col++) {
      bool reading = !digitalRead(colPins[col]);

      if (reading != lastButtonState[row][col]) {
        lastDebounceTime[row][col] = millis();
      }

      if ((millis() - lastDebounceTime[row][col]) > debounceDelay) {
        if (reading != buttonState[row][col]) {
          buttonState[row][col] = reading;
        }
        lastButtonState[row][col] = reading;
      }

      digitalWrite(rowPins[row], HIGH);
    }
  }

  
}

void detectPhysicalButtons() {
  for (int physBtn = 0; physBtn < 6; physBtn++) {
    int startBtn = physBtn * 4;
    int pressedCount = 0;

    for (int i = 0; i < 4; i++) {
      int btnNum = startBtn + i;
      int row = btnNum / COLS;
      int col = btnNum % COLS;

      if (buttonState[row][col]) {
        pressedCount++;
      }
    }
    physicalButtonPressed[physBtn] = (pressedCount >= 2);
  } 
}

void handlePhysicalButtonActions() {
  for (int i = 0; i < 6; i++) {
    if (physicalButtonPressed[i] && !lastPhysicalButtonState[i]) {
      onPhysicalButtonPress(i);
    }

    lastPhysicalButtonState[i] = physicalButtonPressed[i];
  }
}

void onPhysicalButtonPress(int physicalButton) {
  switch(physicalButton) {
    case 0:
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press('m');
      delay(100);
      Keyboard.releaseAll();
      break;
      
    case 1:
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press('d');
      delay(100);
      Keyboard.releaseAll();
      break;
      
    case 2:
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('c');
      delay(100);
      Keyboard.releaseAll();
      break;
      
    case 3:
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('v');
      delay(100);
      Keyboard.releaseAll();
      break;
      
    case 4:
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_LEFT_SHIFT);
      Keyboard.press(KEY_ESC);
      delay(100);
      Keyboard.releaseAll();
      break;
      
    case 5:
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('s');
      delay(100);
      Keyboard.releaseAll();
      break;
  }
}
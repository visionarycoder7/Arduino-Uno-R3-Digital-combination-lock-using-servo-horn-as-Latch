// 🔑 Digital Combination Lock Code (Tinkercad Version)
// This code requires the Keypad, LiquidCrystal_I2C, and Servo libraries.

#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <string.h> // Required for strcmp() function

// --- 1. COMPONENT PIN DEFINITIONS ---

// Keypad Setup (4x4)
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'} // '*' for Reset, '#' for Enter
};

// Keypad Rows connected to Digital Pins D2-D5
byte rowPins[ROWS] = {2, 3, 4, 5}; 
// Keypad Columns connected to Digital Pins D6-D9
byte colPins[COLS] = {6, 7, 8, 9};

Keypad customKeypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// LCD Setup (I2C Address)
// NOTE: Change 0x27 to 0x3F if your LCD doesn't work!
LiquidCrystal_I2C lcd(0x27, 16, 2); 

// Servo and Indicator Pins
Servo lockServo;
const int servoPin = 10;   // Servo signal wire connected to D10
const int buzzerPin = 11;  // Piezo Buzzer connected to D11
const int ledGreen = 12;   // Green LED (Success)
const int ledRed = 13;     // Red LED (Locked/Failure)

// --- 2. PASSWORD AND LOGIC VARIABLES ---

// Define the Master Code (must end with '#' as the Enter key)
const char masterCode[] = "1975"; 
const byte codeLength = 5; // Must match the length of masterCode (4 digits + 1 sentinel)

char inputCode[codeLength]; // Array to hold the user's input
byte inputIndex = 0;       // Tracks the current position in the inputCode array

const int LOCKED_POSITION = 0;   // Servo position for Locked
const int UNLOCKED_POSITION = 90; // Servo position for Unlocked

// --- 3. SETUP ---
void setup() {
  Serial.begin(9600); 
  
  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.print("SOHAN'S LOCK");
  
  // Setup Servo
  lockServo.attach(servoPin);
  lockServo.write(LOCKED_POSITION); 
  
  // Setup Outputs
  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  
  // Initial state: Locked (Red LED ON)
  digitalWrite(ledGreen, LOW);
  digitalWrite(ledRed, HIGH); 
  
  delay(1500);
  resetSystem(); // Prepare the display for input
}

// --- 4. MAIN LOOP ---
void loop() {
  char key = customKeypad.getKey(); // Check for key press

  if (key != NO_KEY) {
    if (key == '#') {
      checkCode(); // '#' key submits the code
    } 
    else if (key == '*') {
      resetSystem(); // '*' key resets the input
    }
    else {
      typeCode(key); // Any other key is part of the code
    }
  }
}

// --- 5. CUSTOM FUNCTIONS ---

// Handles key input and updates LCD with '*'
void typeCode(char key) {
  // Only allow input up to the required code length
  if (inputIndex < codeLength - 1) { 
    inputCode[inputIndex] = key;
    lcd.setCursor(inputIndex, 1);
    
    // Display '*' for security
    lcd.print('*');
    inputIndex++;
    
    // Debugging print
    Serial.print("Input: ");
    Serial.println(inputCode);
  }
}

// Compares user input with master code
void checkCode() {
  // CRITICAL: Add null terminator to treat the char array as a string
  inputCode[inputIndex] = '\0'; 
  
  lcd.clear();
  lcd.print("Checking Code...");
  delay(500);

  // Compare the input code with the master code using strcmp()
  if (strcmp(inputCode, masterCode) == 0) {
    accessGranted();
  } else {
    accessDenied();
  }
}

// Action for correct code
void accessGranted() {
  lcd.clear();
  lcd.print("ACCESS GRANTED");
  
  // Visual & Audio Feedback
  digitalWrite(ledRed, LOW);
  digitalWrite(ledGreen, HIGH);
  tone(buzzerPin, 1500, 200); // High positive tone
  
  // Unlock door (move servo)
  lockServo.write(UNLOCKED_POSITION);
  
  delay(3000); // Door stays open for 3 seconds
  
  resetSystem(); // Lock and prepare for next input
}

// Action for incorrect code
void accessDenied() {
  lcd.clear();
  lcd.print("ACCESS DENIED");
  
  // Visual & Audio Feedback
  digitalWrite(ledRed, LOW);
  delay(100);
  digitalWrite(ledRed, HIGH); // Flash red LED
  tone(buzzerPin, 400, 500); // Low, long error tone
  
  delay(1500);
  resetSystem();
}

// Resets the system state (locks the door and clears display)
void resetSystem() {
  // Clear the input code array
  memset(inputCode, 0, codeLength);
  inputIndex = 0;
  
  // Relock the servo
  lockServo.write(LOCKED_POSITION);
  
  // Reset LEDs and display
  digitalWrite(ledRed, HIGH);
  digitalWrite(ledGreen, LOW);
  lcd.clear();
  lcd.print("Enter Code:");
  lcd.setCursor(0, 1); // Set cursor to second line for input
}

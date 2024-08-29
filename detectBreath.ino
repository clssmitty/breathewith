const int NUM_READINGS = 450;     // Number of readings to keep for moving average
const int INPUT_PIN = A2;         // Analog pin for breath sensor input
const int TEMP_PIN = A0;          // Analog pin for temperature sensor (unused in this code)

// Array to store sensor readings
int readings[NUM_READINGS];       // Circular buffer for storing sensor readings
int readIndex = 0;                // Current index in the circular buffer
long total = 0;                   // Sum of all readings in the buffer
long average = 0;                 // Moving average of sensor readings

// Variables for breath detection
int currentReading = 0;           // Most recent sensor reading
int lastReading = 0;              // Previous sensor reading
int impulseDifference = 0;        // Difference between current and last reading

// Flags and counters for breath detection
bool goodImpulse = false;         // Indicates a significant increase in sensor value
bool breathingStarted = false;    // Indicates the start of a breath
bool stopBreathing = false;       // Indicates the end of a breath
int aboveAvg = 0;                 // Counter for readings above the moving average
unsigned int breathDuration = 0;  // Duration of the current breath in milliseconds

// Main breath state
enum BreathState { NOT_BREATHING, BREATHING };
BreathState breathState = NOT_BREATHING;

// Thresholds and durations for breath detection
const int BREATH_START_THRESHOLD = 430;
const int BREATH_END_THRESHOLD_SHORT = 430;
const int BREATH_END_THRESHOLD_MEDIUM = 450;
const int BREATH_END_THRESHOLD_LONG = 460;
const int BREATH_DURATION_SHORT = 1000;
const int BREATH_DURATION_MEDIUM = 3000;
const int BREATH_DURATION_LONG = 6000;
const int BREATH_DURATION_MAX = 8000;

/**
 * Setup function: Initializes serial communication and sensor readings
 */
void setup() {
  Serial.begin(9600);
  initializeReadings();
}

/**
 * Initializes all readings in the circular buffer to zero
 */
void initializeReadings() {
  for (int i = 0; i < NUM_READINGS; i++) {
    readings[i] = 0;
  }
}

/**
 * Main loop function: Continuously updates readings and detects breaths
 */
void loop() {
  updateReadings();
  updateBreathState();
  printOutput();
  delay(3);  // Short delay for stability
}

/**
 * Updates the circular buffer with the latest sensor reading
 */
void updateReadings() {
  // Read from the sensor once
  currentReading = analogRead(INPUT_PIN);

  // Update the circular buffer
  total = total - readings[readIndex];
  readings[readIndex] = currentReading;
  total = total + currentReading;

  // Update last reading
  lastReading = readings[(readIndex - 1 + NUM_READINGS) % NUM_READINGS];
  impulseDifference = currentReading - lastReading;

  // Move to the next position in the circular buffer
  readIndex = (readIndex + 1) % NUM_READINGS;
  average = total / NUM_READINGS;
}

/**
 * Updates the breath state based on sensor readings and durations
 */
void updateBreathState() {
  bool aboveAvg = currentReading > average + 6;

  switch (breathState) {
    case NOT_BREATHING:
      if (aboveAvg && currentReading > BREATH_START_THRESHOLD) {
        breathState = BREATHING;
        breathDuration = 0;
      }
      break;
    case BREATHING:
      breathDuration += 3;  // Assuming 3ms per loop iteration
      if (!aboveAvg) {
        checkBreathEnd();
      }
      break;
  }
}

/**
 * Checks if the current breath has ended based on duration and sensor value
 */
void checkBreathEnd() {
  if (breathDuration <= BREATH_DURATION_SHORT && currentReading < BREATH_END_THRESHOLD_SHORT) {
    breathState = NOT_BREATHING;
  } else if (breathDuration <= BREATH_DURATION_MEDIUM && currentReading < BREATH_END_THRESHOLD_MEDIUM) {
    breathState = NOT_BREATHING;
  } else if (breathDuration <= BREATH_DURATION_LONG && currentReading < BREATH_END_THRESHOLD_LONG) {
    breathState = NOT_BREATHING;
  } else if (breathDuration > BREATH_DURATION_MAX) {
    breathState = NOT_BREATHING;
  }
}

/**
 * Outputs the current sensor reading and breath state to serial
 */
void printOutput() {
  Serial.print(analogRead(INPUT_PIN));
  Serial.print(",");
  Serial.println(breathState == BREATHING);
}
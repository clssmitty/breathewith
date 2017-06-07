const int numReadings = 450;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
long total = 0;                  // the running total
long average = 0;                // the average
int currentReading = 0;
int lastReading = 0;
int impulseDifference = 0; 
bool goodImpulse = false; // impulse is when the current reading is greater than the previous reading + 3
int fibLev = 0; // static midway level for gauging end of breath
bool breathingStarted = false;
bool stopBreathing = false;
int aboveAvg = 0;
int breathDuration = 0;

bool breathing = false;

int inputPin = A2;
int tempPin = A0;

void setup() {
  // initialize serial communication with computer:
  Serial.begin(9600);
  // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}

void loop() {
  // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = analogRead(inputPin);
  // add the reading to the total:
  total = total + readings[readIndex];
  
  currentReading = analogRead(inputPin);
  lastReading = readings[readIndex - 1];
  impulseDifference = currentReading - lastReading;

  if (impulseDifference >= 2) {
    goodImpulse = true;
  } else {
    goodImpulse = false;
  }
  
  //Serial.println(currentReading - lastReading);
  
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  average = total / numReadings;

  // current value being greater that average plus 6 is a good start of breath signal
  aboveAvg = currentReading > average+6;

  // if no breath detected check for start of breath
  if (breathing == false){

    // if 6 above moving average and more than 430 (TODO: should update this 430 number to be a long long term moving average + some amount maybe 30)
    if (aboveAvg && currentReading > 430) {
      
      //breathingStarted = true;
      breathing = true;
      breathDuration = 0;
    }
  }

  // if breath already detected check for end of breath
  if (breathing == true){
    // increment breath time
    breathDuration =  breathDuration + 3; // 3ms per loop iteration

    // if we're still 6 above moving average skip checking
    if (aboveAvg == false) {
      // if we're within 6 above the moving average set end criteria by length of breath
      
      
      // set dynamic endpoints based on anecdotal evidence of watching breath cycles
      if (breathDuration <= 1000) {
         //Serial.print("<1000");
         if (currentReading < 430) {
            breathing = false;
          }
        }

        
      if (breathDuration > 1000 && breathDuration <= 3000) {
         //Serial.print("<3000");
         
         if (currentReading < 450) {
            breathing = false;
         }
        
        }
        
      if (breathDuration > 3000 && breathDuration <= 6000) {
         //Serial.print("<6000");
        

         if (currentReading < 460) {
            breathing = false;
         }
         
         }

                  // kill breath if over 8 seconds
      if (breathDuration >8000) {
          breathing = false;
         
      }
              
      }
  }

// print velocity indicator as all values normalized above 25
//if (currentReading - average > 25){
  //  Serial.print(currentReading - average - 25);
    
 // } else {
    //Serial.print("1"); // send baseline velocity as 1 unless there is a velocity component above the 25 threshold
//  }
//Serial.print(",");
  
  Serial.print(analogRead(inputPin));
  Serial.print(",");
  Serial.println(breathing);

  delay(3);        // delay in between reads for stability
  
}

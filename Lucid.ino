#include <Arduino.h>

#include "FrequencyTimer2/FrequencyTimer2.h"  // https://github.com/PaulStoffregen/FrequencyTimer2
#include "stepperMotor/stepperMotor.h"
#include "PollTimer/PollTimer.h"

#include "pin_map.h"
#include "Lucid.h"

void setup() {
  
  Serial.begin(250000);
  while( !Serial ) delay(1); 

  startTimers();
}

void loop() {
  // put your main code here, to run repeatedly:

}

#include <dStepper.h>
#include <PollTimer.h>

#include "pin_map.h"
#include "setup.h"

void setup() {
  
  Serial.begin(250000);
  while( !Serial ) delay(1); 

  startTimers();
}

void loop() {
  // put your main code here, to run repeatedly:

}

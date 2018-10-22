#include <Arduino.h>

#include <FrequencyTimer2.h>  // https://github.com/PaulStoffregen/FrequencyTimer2
#include "src/stepperMotor/stepperMotor.h"
#include "src/PollTimer/PollTimer.h"

#include "pin_map.h"
#include "variables.h"
#include "Lucid.h"

void setup() {

   Serial.begin(250000);
   while( !Serial ) delay(1);

   enableMotors();

   startStepperTickISR();

   startTimers();
}

void loop() {
   
   if( control.check() )
   {
      float static angle = 0.0f;

      angle += .001;
      if( angle > 6.2831853f ) angle -= 6.2831853f;

      cyl_1_position = 10.0 * sinf( angle );

      //CYL_1.setSpeedByPostionMM( cyl_1_position, MOTOR_PULSE_RATE );
      //CYL_1.setSpeed( MOTOR_PULSE_RATE * (cyl_1_position - CYL_1.getPositionMM() ));
      CYL_1.setSpeed( 1.0 );
   }
   else if( buttons.check() )
   {

   }
   else if( display.check() )
   {
      Serial.println( cyl_1_position );
   }
   else if( maintenance.check() )
   {
      //Serial.println( funCounter );
      funCounter = 0;
   }
   
}

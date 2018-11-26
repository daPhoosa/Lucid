#include <Arduino.h>

#include <FrequencyTimer2.h>  // https://github.com/PaulStoffregen/FrequencyTimer2
#include "src/stepperMotor/stepperMotor.h"
#include "src/PollTimer/PollTimer.h"
#include "src/uButton/uButton.h"

#include "pin_map.h"
#include "variables.h"
#include "Lucid.h"


void setup() {

   Serial.begin(250000);
   int i = 0;
   while( !Serial && i++ < 1000 ) delay(1); // wait up to 1s for serial to connect

   setupButtons();

   enableMotors();

   startStepperTickISR();

   startTimers();
}

void loop() {
   
   if( control.check() )
   {

      if( extrudeActive )
      {
         if( millis() - extrudeStartTime > extrudeTime )
         {
            extrudeActive = false;
            disableMotors();
         }
         else
         {
            C[BLUE  ].motor.setSpeed( C[BLUE  ].speed );
            C[RED   ].motor.setSpeed( C[RED   ].speed );
            C[YELLOW].motor.setSpeed( C[YELLOW].speed );
            C[WHITE ].motor.setSpeed( C[WHITE ].speed );
         }
         
      }

      if( !extrudeActive )
      {
         C[BLUE  ].motor.setSpeed( 0 );
         C[RED   ].motor.setSpeed( 0 );
         C[YELLOW].motor.setSpeed( 0 );
         C[WHITE ].motor.setSpeed( 0 );
      }
      
   }
   else if( buttons.check() )
   {
      if( button_green.check() )
      {
         Serial.println("GREEN");
         extrudeActive = !extrudeActive;
         if( extrudeActive ) 
         {
            enableMotors();
            readRecipie();
         }
      }

      if( button_yellow.check() )
      {
         Serial.println("YELLOW");
      }

      if( button_red.check() )
      {
         Serial.println("RED");
      }
   }
   else if( display.check() )
   {
      //Serial.println( cyl_1_position );
   }
   else if( maintenance.check() )
   {
      if( !extrudeActive ) disableMotors();

      
      //Serial.println( funCounter );
      funCounter = 0;
   }
   
}


void readRecipie()
{
   C[BLUE  ].ratio = 1.0;
   C[RED   ].ratio = 1.0;
   C[YELLOW].ratio = 1.0;
   C[WHITE ].ratio = 1.0;

   mixVolume = 1.0;
}

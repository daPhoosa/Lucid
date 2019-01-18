#include <Arduino.h>

#include <FrequencyTimer2.h>  // https://github.com/PaulStoffregen/FrequencyTimer2
#include "src/stepperMotor/stepperMotor.h"
#include "src/PollTimer/PollTimer.h"
#include "src/uButton/uButton.h"

#include "pin_map.h"
#include "variables.h"

#include "communication.h"
#include "display.h"

#include "motors.h"
#include "Lucid.h"
#include "operations.h"
#include "colors.h"


void setup() 
{
   start_serial();

   startDisplay();

   setupButtons();

   setupMotors();

   startStepperTickISR();

   startTimers();
}


void loop() 
{
   
   if( control.check() )
   {
      switch( machine_state )
      {
         case sleep:
            sleep_operations();
            break;

         case dwell:
            dwell_operations();
            break;

         case prePurge:
            pre_purge_operations();
            break;

         case dispense:
            dispense_operations();
            break;

         case postPurge:
            post_purge_operations();
            break;

         case fill:
            fill_operation();
            break;

         case empty:
            empty_operation();
            break;

         default:
            break;
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

         if( machine_state == fill )
         {
            selected_cyl++;
         }
         else
         { 
            selected_cyl = 0;
            machine_state = fill;
            disableMotors();
            Serial.println(machine_state);
         }
         Serial.println("FILL");
      }

      if( button_red.check() )
      {
         Serial.println("RED");

         if( machine_state == empty )
         {
            selected_cyl++;
         }
         else
         { 
            selected_cyl = 0;
            machine_state = empty;
            disableMotors();
            Serial.println("EMPTY");
         }
         Serial.println(selected_cyl);
      }

   }
   else if( display.check() )
   {
      if(touch_screen.touched())
      {
         TS_Point p = touch_screen.getPoint();

         onTouch(p.x, p.y);
      }
   }
   else if( maintenance.check() )
   {
      //if( !extrudeActive ) disableMotors();

      
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

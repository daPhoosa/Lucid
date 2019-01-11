

void sleep_operations()
{

}


void dwell_operations()
{

}


void pre_purge_operations()
{
   static uint32_t startTime;
   static bool active = false;

   if( active )
   {
      if( millis() - startTime > purgeTime ) // operation complete
      {
         active = false;

         machine_state = dispense; // go to next operation
      }
      else
      {
         // operation active
      }
   }
   else  // become active
   {
      startTime = millis();
      active = true;
      enableMotors();

      CYL_1.setSpeed( purgeSpeed );
      CYL_2.setSpeed( purgeSpeed );
      CYL_3.setSpeed( purgeSpeed );
      CYL_4.setSpeed( purgeSpeed );

   }
}


void dispense_operations()
{
   if( millis() - extrudeStartTime > extrudeTime )
   {
      extrudeActive = false;
      disableMotors();
   }
   else
   {
      CYL_1.setSpeed( C[BLUE  ].speed );
      CYL_2.setSpeed( C[RED   ].speed );
      CYL_3.setSpeed( C[YELLOW].speed );
      CYL_4.setSpeed( C[WHITE ].speed );
      //CYL_5.setSpeed( C[ ].speed );
      //CYL_6.setSpeed( C[ ].speed );
      //CYL_7.setSpeed( C[ ].speed );
      //CYL_8.setSpeed( C[ ].speed );
      //CYL_9.setSpeed( C[ ].speed );
   }
}


void post_purge_operations()
{
  static uint32_t startTime;
   static bool active = false;

   if( active )
   {
      if( millis() - startTime > purgeTime ) // operation complete
      {
         active = false;

         machine_state = dwell; // go to next operation
      }
      else
      {
         // operation active
      }
   }
   else  // become active
   {
      startTime = millis();
      active = true;
      enableMotors();

      CYL_1.setSpeed( -purgeSpeed );
      CYL_2.setSpeed( -purgeSpeed );
      CYL_3.setSpeed( -purgeSpeed );
      CYL_4.setSpeed( -purgeSpeed );

   }
}


void fill_operation()
{
   switch( selected_cyl )
   {
      case 0:
         enableMotors();
         break;

      case 1:
         CYL_1.setSpeed( -1.5 );
         break;

      case 2:
         CYL_1.setSpeed( 0 );
         CYL_2.setSpeed( -1.5 );
         break;

      case 3:
         CYL_2.setSpeed( 0 );
         CYL_3.setSpeed( -1.5 );
         break;

      case 4:
         CYL_3.setSpeed( 0 );
         CYL_4.setSpeed( -1.5 );
         break;

      default:
         CYL_4.setSpeed( 0 );
         disableMotors();
         break;
   }
}


void empty_operation()
{
   switch( selected_cyl )
   {
      case 0:
         enableMotors();
         break;

      case 1:
         CYL_1.setSpeed( 0.5 );
         break;

      case 2:
         CYL_1.setSpeed( 0 );
         CYL_2.setSpeed( 0.5 );
         break;

      case 3:
         CYL_2.setSpeed( 0 );
         CYL_3.setSpeed( 0.5 );
         break;

      case 4:
         CYL_3.setSpeed( 0 );
         CYL_4.setSpeed( 0.5 );
         break;

      default:
         CYL_4.setSpeed( 0 );
         disableMotors();
         break;
   }
}

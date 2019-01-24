

void sleep_operations()
{

}


void dwell_operations()
{
   disableMotors();
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
   static uint32_t startTime;
   static bool active = false;

   uint32_t dispenseTime = 4000; // 4 second

   if( active )
   {
      if( millis() - startTime > dispenseTime ) // operation complete
      {
         active = false;

         machine_state = postPurge; // go to next operation
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

      if( vBlue.s || vRed.s || vYellow.s || vWhite.s )
      {
         float invSumSpeed = 1.0f / float(vBlue.s + vRed.s + vYellow.s + vWhite.s);
  
         CYL_1.setSpeed( float(vBlue.s)   * invSumSpeed );
         CYL_2.setSpeed( float(vRed.s)    * invSumSpeed );
         CYL_3.setSpeed( float(vYellow.s) * invSumSpeed );
         CYL_4.setSpeed( float(vWhite.s)  * invSumSpeed );
      }
      else
      {
         CYL_1.setSpeed( 0 );
         CYL_2.setSpeed( 0 );
         CYL_3.setSpeed( 0 );
         CYL_4.setSpeed( 0 );  
      }

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
         CYL_1.setSpeed( -0.2 );
         break;

      case 2:
         CYL_1.setSpeed( 0 );
         CYL_2.setSpeed( -0.2 );
         break;

      case 3:
         CYL_2.setSpeed( 0 );
         CYL_3.setSpeed( -0.2 );
         break;

      case 4:
         CYL_3.setSpeed( 0 );
         CYL_4.setSpeed( -0.2 );
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
         CYL_1.setSpeed( 0.2 );
         break;

      case 2:
         CYL_1.setSpeed( 0 );
         CYL_2.setSpeed( 0.2 );
         break;

      case 3:
         CYL_2.setSpeed( 0 );
         CYL_3.setSpeed( 0.2 );
         break;

      case 4:
         CYL_3.setSpeed( 0 );
         CYL_4.setSpeed( 0.2 );
         break;

      default:
         CYL_4.setSpeed( 0 );
         disableMotors();
         break;
   }
}

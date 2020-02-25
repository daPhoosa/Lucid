

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

   uint32_t dispenseTime = 5000; // miliseconds

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

      /* // RGB
      if( vBlue.value || vRed.value || vYellow.value || vWhite.value )
      {
         float invSum = 1.0f / float(vBlue.value + vRed.value + vYellow.value + vWhite.value );

         CYL_1.setSpeed( float( vBlue.value )   * invSum ); // Normalize
         CYL_2.setSpeed( float( vRed.value )    * invSum );
         CYL_3.setSpeed( float( vYellow.value ) * invSum );
         CYL_4.setSpeed( float( vWhite.value )  * invSum );
      }
      else
      {
         CYL_1.setSpeed( 0.33333f ); // BLACK
         CYL_2.setSpeed( 0.33333f );
         CYL_3.setSpeed( 0.33333f );
         CYL_4.setSpeed( 0 );
      }
      */

      // Lab color conversion
      color_Lab_t a( vLAB_L.value, vLAB_A.value, vLAB_B.value );
      color_XYZ_t b = Lab_to_XYZ( a );
      ColorSolver.get_solution_XYZ( b.X, b.Y, b.Z );
      CYL_1.setSpeed( ColorSolver.get_weight(BLUE) ); // Normalize
      CYL_2.setSpeed( ColorSolver.get_weight(RED) );
      CYL_3.setSpeed( ColorSolver.get_weight(YELLOW) );
      CYL_4.setSpeed( ColorSolver.get_weight(WHITE) );

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
   const float speed = -0.4f;

   switch( selected_cyl )
   {
      case 0:
         enableMotors();
         break;

      case 1:
         CYL_1.setSpeed( speed );
         break;

      case 2:
         CYL_1.setSpeed( 0 );
         CYL_2.setSpeed( speed );
         break;

      case 3:
         CYL_2.setSpeed( 0 );
         CYL_3.setSpeed( speed );
         break;

      case 4:
         CYL_3.setSpeed( 0 );
         CYL_4.setSpeed( speed );
         break;

      default:
         CYL_4.setSpeed( 0 );
         disableMotors();
         break;
   }
}


void empty_operation()
{
   const float speed = 0.4f;

   switch( selected_cyl )
   {
      case 0:
         enableMotors();
         break;

      case 1:
         CYL_1.setSpeed( speed );
         break;

      case 2:
         CYL_1.setSpeed( 0 );
         CYL_2.setSpeed( speed );
         break;

      case 3:
         CYL_2.setSpeed( 0 );
         CYL_3.setSpeed( speed );
         break;

      case 4:
         CYL_3.setSpeed( 0 );
         CYL_4.setSpeed( speed );
         break;

      default:
         CYL_4.setSpeed( 0 );
         disableMotors();
         break;
   }
}




#define COMPUTE_STEP_PER_CC(d,p,s) (100.0f * s / ( 0.25f * PI * d * d * p ))

const float CYL_1_DIAMETER     = 22.0f;
const float CYL_1_PITCH        = 2.0;
const float CYL_1_STEP_PER_REV = 200.0f * 16.0f;
const float CYL_1_STEP_PER_MM  = CYL_1_STEP_PER_REV / CYL_1_PITCH;

const float CYL_2_DIAMETER     = 22.0f;
const float CYL_2_PITCH        = 2.0;
const float CYL_2_STEP_PER_REV = 200.0f * 16.0f;
const float CYL_2_STEP_PER_MM  = CYL_2_STEP_PER_REV / CYL_2_PITCH;

const float CYL_3_DIAMETER     = 22.0f;
const float CYL_3_PITCH        = 2.0;
const float CYL_3_STEP_PER_REV = 200.0f * 16.0f;
const float CYL_3_STEP_PER_MM  = CYL_3_STEP_PER_REV / CYL_3_PITCH;

const float CYL_4_DIAMETER     = 22.0f;
const float CYL_4_PITCH        = 2.0;
const float CYL_4_STEP_PER_REV = 200.0f * 16.0f;
const float CYL_4_STEP_PER_MM  = CYL_4_STEP_PER_REV / CYL_4_PITCH;

const float CYL_5_DIAMETER     = 22.0f;
const float CYL_5_PITCH        = 2.0;
const float CYL_5_STEP_PER_REV = 200.0f * 16.0f;
const float CYL_5_STEP_PER_MM  = CYL_5_STEP_PER_REV / CYL_5_PITCH;

const float CYL_6_DIAMETER     = 22.0f;
const float CYL_6_PITCH        = 2.0;
const float CYL_6_STEP_PER_REV = 200.0f * 16.0f;
const float CYL_6_STEP_PER_MM  = CYL_6_STEP_PER_REV / CYL_6_PITCH;

const float CYL_7_DIAMETER     = 22.0f;
const float CYL_7_PITCH        = 2.0;
const float CYL_7_STEP_PER_REV = 200.0f * 16.0f;
const float CYL_7_STEP_PER_MM  = CYL_7_STEP_PER_REV / CYL_7_PITCH;

const float CYL_8_DIAMETER     = 22.0f;
const float CYL_8_PITCH        = 2.0;
const float CYL_8_STEP_PER_REV = 200.0f * 16.0f;
const float CYL_8_STEP_PER_MM  = CYL_8_STEP_PER_REV / CYL_8_PITCH;

const float CYL_9_DIAMETER     = 22.0f;
const float CYL_9_PITCH        = 2.0;
const float CYL_9_STEP_PER_REV = 200.0f * 16.0f;
const float CYL_9_STEP_PER_MM  = CYL_9_STEP_PER_REV / CYL_9_PITCH;


stepperMotor CYL_1( CYL_1_STEP_PER_MM, 1, MOTOR_PULSE_RATE, CYL_1_STEP_PIN, CYL_1_DIR_PIN );
stepperMotor CYL_2( CYL_2_STEP_PER_MM, 1, MOTOR_PULSE_RATE, CYL_2_STEP_PIN, CYL_2_DIR_PIN );
stepperMotor CYL_3( CYL_3_STEP_PER_MM, 1, MOTOR_PULSE_RATE, CYL_3_STEP_PIN, CYL_3_DIR_PIN );
stepperMotor CYL_4( CYL_4_STEP_PER_MM, 1, MOTOR_PULSE_RATE, CYL_4_STEP_PIN, CYL_4_DIR_PIN );
//stepperMotor CYL_5( CYL_5_STEP_PER_MM, 1, MOTOR_PULSE_RATE, CYL_5_STEP_PIN, CYL_5_DIR_PIN );
//stepperMotor CYL_6( CYL_6_STEP_PER_MM, 1, MOTOR_PULSE_RATE, CYL_6_STEP_PIN, CYL_6_DIR_PIN );
//stepperMotor CYL_7( CYL_7_STEP_PER_MM, 1, MOTOR_PULSE_RATE, CYL_7_STEP_PIN, CYL_7_DIR_PIN );
//stepperMotor CYL_8( CYL_8_STEP_PER_MM, 1, MOTOR_PULSE_RATE, CYL_8_STEP_PIN, CYL_8_DIR_PIN );
//stepperMotor CYL_9( CYL_9_STEP_PER_MM, 1, MOTOR_PULSE_RATE, CYL_9_STEP_PIN, CYL_9_DIR_PIN );


void enableMotors()
{
   if( motorEnableStatus == false ) 
   {
      Serial.println("Enable Motors");

      pinMode( 13, OUTPUT);
      digitalWrite( 13, HIGH );  // LED ON

      motorEnableStatus = true;

      digitalWrite( CYL_1_ENBL_PIN, LOW );
      digitalWrite( CYL_2_ENBL_PIN, LOW );
      digitalWrite( CYL_3_ENBL_PIN, LOW );
      digitalWrite( CYL_4_ENBL_PIN, LOW );
      //digitalWrite( CYL_5_ENBL_PIN, LOW );
      //digitalWrite( CYL_6_ENBL_PIN, LOW );
      //digitalWrite( CYL_7_ENBL_PIN, LOW );
      //digitalWrite( CYL_8_ENBL_PIN, LOW );
      //digitalWrite( CYL_9_ENBL_PIN, LOW );

      CYL_1.setSpeed( 0.0 );
      CYL_2.setSpeed( 0.0 );
      CYL_3.setSpeed( 0.0 );
      CYL_4.setSpeed( 0.0 );
      //CYL_5.setSpeed( 0.0 );
      //CYL_6.setSpeed( 0.0 );
      //CYL_7.setSpeed( 0.0 );
      //CYL_8.setSpeed( 0.0 );
      //CYL_9.setSpeed( 0.0 );
   }
}


void disableMotors()
{
   if( motorEnableStatus == true ) Serial.println("Disable Motors");

   motorEnableStatus = false;
   digitalWrite( 13, LOW ); // LED off

   CYL_1.setSpeed( 0.0 );
   CYL_2.setSpeed( 0.0 );
   CYL_3.setSpeed( 0.0 );
   CYL_4.setSpeed( 0.0 );
   //CYL_5.setSpeed( 0.0 );
   //CYL_6.setSpeed( 0.0 );
   //CYL_7.setSpeed( 0.0 );
   //CYL_8.setSpeed( 0.0 );
   //CYL_9.setSpeed( 0.0 );
   
   digitalWrite( CYL_1_ENBL_PIN, HIGH );
   digitalWrite( CYL_2_ENBL_PIN, HIGH );
   digitalWrite( CYL_3_ENBL_PIN, HIGH );
   digitalWrite( CYL_4_ENBL_PIN, HIGH );
   //digitalWrite( CYL_5_ENBL_PIN, HIGH );
   //digitalWrite( CYL_6_ENBL_PIN, HIGH );
   //digitalWrite( CYL_7_ENBL_PIN, HIGH );
   //digitalWrite( CYL_8_ENBL_PIN, HIGH );
   //digitalWrite( CYL_9_ENBL_PIN, HIGH );
}


void setupMotors()
{
   pinMode( CYL_1_ENBL_PIN, OUTPUT );
   pinMode( CYL_2_ENBL_PIN, OUTPUT );
   pinMode( CYL_3_ENBL_PIN, OUTPUT );
   pinMode( CYL_4_ENBL_PIN, OUTPUT );
   //pinMode( CYL_5_ENBL_PIN, OUTPUT );
   //pinMode( CYL_6_ENBL_PIN, OUTPUT );
   //pinMode( CYL_7_ENBL_PIN, OUTPUT );
   //pinMode( CYL_8_ENBL_PIN, OUTPUT );
   //pinMode( CYL_9_ENBL_PIN, OUTPUT );

   disableMotors();
}

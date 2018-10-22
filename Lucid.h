



const int MOTOR_PULSE_RATE    = 20000;
const int CONTROL_RATE        = 1000;
const int BUTTON_CHECK_RATE   = 100;
const int DISPLAY_UPDATE_RATE = 10;
const int MAINTENANCE_RATE    = 1;


uButton button_green(  GREEN_BUTTON_PIN,  1 );
uButton button_yellow( YELLOW_BUTTON_PIN, 1 );
uButton button_red(    RED_BUTTON_PIN,    1 );

void setupButtons()
{
    pinMode( GREEN_BUTTON_PIN,  INPUT_PULLUP );
    pinMode( YELLOW_BUTTON_PIN, INPUT_PULLUP );
    pinMode( RED_BUTTON_PIN,    INPUT_PULLUP );
}



#define COMPUTE_STEP_PER_CC(d,p,s) (100.0f * s / ( 0.25f * PI * d * d * p ))

const float CYL_1_DIAMETER     = 22.0f;
const float CYL_1_PITCH        = 2.0;
const float CYL_1_STEP_PER_REV = 200.0f * 4.0f;
const float CYL_1_STEP_PER_MM  = CYL_1_STEP_PER_REV / CYL_1_PITCH;

const float CYL_2_DIAMETER     = 22.0f;
const float CYL_2_PITCH        = 2.0;
const float CYL_2_STEP_PER_REV = 200.0f * 4.0f;
const float CYL_2_STEP_PER_MM  = CYL_2_STEP_PER_REV / CYL_2_PITCH;

const float CYL_3_DIAMETER     = 22.0f;
const float CYL_3_PITCH        = 2.0;
const float CYL_3_STEP_PER_REV = 200.0f * 4.0f;
const float CYL_3_STEP_PER_MM  = CYL_3_STEP_PER_REV / CYL_3_PITCH;

const float CYL_4_DIAMETER     = 22.0f;
const float CYL_4_PITCH        = 2.0;
const float CYL_4_STEP_PER_REV = 200.0f * 4.0f;
const float CYL_4_STEP_PER_MM  = CYL_4_STEP_PER_REV / CYL_4_PITCH;

const float CYL_5_DIAMETER     = 22.0f;
const float CYL_5_PITCH        = 2.0;
const float CYL_5_STEP_PER_REV = 200.0f * 4.0f;
const float CYL_5_STEP_PER_MM  = CYL_5_STEP_PER_REV / CYL_5_PITCH;

const float CYL_6_DIAMETER     = 22.0f;
const float CYL_6_PITCH        = 2.0;
const float CYL_6_STEP_PER_REV = 200.0f * 4.0f;
const float CYL_6_STEP_PER_MM  = CYL_6_STEP_PER_REV / CYL_6_PITCH;

const float CYL_7_DIAMETER     = 22.0f;
const float CYL_7_PITCH        = 2.0;
const float CYL_7_STEP_PER_REV = 200.0f * 4.0f;
const float CYL_7_STEP_PER_MM  = CYL_7_STEP_PER_REV / CYL_7_PITCH;

const float CYL_8_DIAMETER     = 22.0f;
const float CYL_8_PITCH        = 2.0;
const float CYL_8_STEP_PER_REV = 200.0f * 4.0f;
const float CYL_8_STEP_PER_MM  = CYL_8_STEP_PER_REV / CYL_8_PITCH;

const float CYL_9_DIAMETER     = 22.0f;
const float CYL_9_PITCH        = 2.0;
const float CYL_9_STEP_PER_REV = 200.0f * 4.0f;
const float CYL_9_STEP_PER_MM  = CYL_9_STEP_PER_REV / CYL_9_PITCH;


PollTimer control( CONTROL_RATE );
PollTimer buttons( BUTTON_CHECK_RATE );
PollTimer display( DISPLAY_UPDATE_RATE );
PollTimer maintenance( MAINTENANCE_RATE );


stepperMotor CYL_1( CYL_1_STEP_PER_MM, 1, MOTOR_PULSE_RATE, CYL_1_STEP_PIN, CYL_1_DIR_PIN );
stepperMotor CYL_2( CYL_2_STEP_PER_MM, 1, MOTOR_PULSE_RATE, CYL_2_STEP_PIN, CYL_2_DIR_PIN );
stepperMotor CYL_3( CYL_3_STEP_PER_MM, 1, MOTOR_PULSE_RATE, CYL_3_STEP_PIN, CYL_3_DIR_PIN );
stepperMotor CYL_4( CYL_4_STEP_PER_MM, 1, MOTOR_PULSE_RATE, CYL_4_STEP_PIN, CYL_4_DIR_PIN );


void enableMotors()
{
   pinMode( CYL_1_ENBL_PIN, OUTPUT );
   pinMode( CYL_2_ENBL_PIN, OUTPUT );
   pinMode( CYL_3_ENBL_PIN, OUTPUT );
   pinMode( CYL_4_ENBL_PIN, OUTPUT );

   digitalWrite( CYL_1_ENBL_PIN, LOW );
   digitalWrite( CYL_2_ENBL_PIN, LOW );
   digitalWrite( CYL_3_ENBL_PIN, LOW );
   digitalWrite( CYL_4_ENBL_PIN, LOW );
}

void startTimers()
{
   control.start();
   buttons.start();
   display.start();
   maintenance.start();
}


void MotorControlISR()
{
   CYL_1.step();
   CYL_2.step();
   CYL_3.step();
   CYL_4.step();
}


void startStepperTickISR()
{
   pinMode(FREQUENCYTIMER2_PIN, OUTPUT);
   FrequencyTimer2::setPeriod( 1000000 / MOTOR_PULSE_RATE );
   FrequencyTimer2::setOnOverflow(MotorControlISR);
}

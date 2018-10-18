const int MOTOR_PULSE_RATE    = 10000;
const int BUTTON_CHECK_RATE   = 100;
const int DISPLAY_UPDATE_RATE = 10;
const int MAINTENANCE_RATE    = 1;

#define COMPUTE_STEP_PER_CC(d,p,s) (100.0f * s / ( 0.25f * PI * d * d * p ))

const float CYL_1_DIAMETER     = 28.0f;
const float CYL_1_PITCH        = 2.0;
const float CYL_1_STEP_PER_REV = 200.0f * 16.0f;
const float CYL_1_STEP_PER_CC  = COMPUTE_STEP_PER_CC( CYL_1_DIAMETER, CYL_1_PITCH, CYL_1_STEP_PER_REV);

const float CYL_2_DIAMETER     = 28.0f;
const float CYL_2_PITCH        = 2.0;
const float CYL_2_STEP_PER_REV = 200.0f * 16.0f;
const float CYL_2_STEP_PER_CC  = COMPUTE_STEP_PER_CC( CYL_2_DIAMETER, CYL_2_PITCH, CYL_2_STEP_PER_REV);

const float CYL_3_DIAMETER     = 28.0f;
const float CYL_3_PITCH        = 2.0;
const float CYL_3_STEP_PER_REV = 200.0f * 16.0f;
const float CYL_3_STEP_PER_CC  = COMPUTE_STEP_PER_CC( CYL_3_DIAMETER, CYL_3_PITCH, CYL_3_STEP_PER_REV);

const float CYL_4_DIAMETER     = 28.0f;
const float CYL_4_PITCH        = 2.0;
const float CYL_4_STEP_PER_REV = 200.0f * 16.0f;
const float CYL_4_STEP_PER_CC  = COMPUTE_STEP_PER_CC( CYL_4_DIAMETER, CYL_4_PITCH, CYL_4_STEP_PER_REV);

const float CYL_5_DIAMETER     = 28.0f;
const float CYL_5_PITCH        = 2.0;
const float CYL_5_STEP_PER_REV = 200.0f * 16.0f;
const float CYL_5_STEP_PER_CC  = COMPUTE_STEP_PER_CC( CYL_5_DIAMETER, CYL_5_PITCH, CYL_5_STEP_PER_REV);

const float CYL_6_DIAMETER     = 28.0f;
const float CYL_6_PITCH        = 2.0;
const float CYL_6_STEP_PER_REV = 200.0f * 16.0f;
const float CYL_6_STEP_PER_CC  = COMPUTE_STEP_PER_CC( CYL_6_DIAMETER, CYL_6_PITCH, CYL_6_STEP_PER_REV);

const float CYL_7_DIAMETER     = 28.0f;
const float CYL_7_PITCH        = 2.0;
const float CYL_7_STEP_PER_REV = 200.0f * 16.0f;
const float CYL_7_STEP_PER_CC  = COMPUTE_STEP_PER_CC( CYL_7_DIAMETER, CYL_7_PITCH, CYL_7_STEP_PER_REV);

const float CYL_8_DIAMETER     = 28.0f;
const float CYL_8_PITCH        = 2.0;
const float CYL_8_STEP_PER_REV = 200.0f * 16.0f;
const float CYL_8_STEP_PER_CC  = COMPUTE_STEP_PER_CC( CYL_8_DIAMETER, CYL_8_PITCH, CYL_8_STEP_PER_REV);

const float CYL_9_DIAMETER     = 28.0f;
const float CYL_9_PITCH        = 2.0;
const float CYL_9_STEP_PER_REV = 200.0f * 16.0f;
const float CYL_9_STEP_PER_CC  = COMPUTE_STEP_PER_CC( CYL_9_DIAMETER, CYL_9_PITCH, CYL_9_STEP_PER_REV);


PollTimer pulseGen( MOTOR_PULSE_RATE );
PollTimer buttons( BUTTON_CHECK_RATE );
PollTimer display( DISPLAY_UPDATE_RATE ):
PollTimer maintenance( MAINTENANCE_RATE );

dStepper motor1( A_MOTOR_STEP_PER_MM, A_MOTOR_DIRECTION, STEPPER_TICK_HZ, A_MOTOR_STEP_PIN, A_MOTOR_DIR_PIN );

void startTimers()
{
   pulseGen.start();
   buttons.start();
   display.start():
   maintenance.start();
}

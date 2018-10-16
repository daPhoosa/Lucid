const int MOTOR_PULSE_RATE    = 10000;
const int BUTTON_CHECK_RATE   = 100;
const int DISPLAY_UPDATE_RATE = 10;
const int MAINTENANCE_RATE    = 1;

struct EXTRUDER
{
   float x = 0.0f;
   float y = 0.0f;
   float z = 0.0f;

   EXTRUDER() : x(0.0f), y(0.0f), z(0.0f) {}
   EXTRUDER( float t_x, float t_y, float t_z ) : x(t_x), y(t_y), z(t_z) {}
};


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

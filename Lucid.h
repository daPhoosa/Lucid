





uButton button_green(  GREEN_BUTTON_PIN,  1 );
uButton button_yellow( YELLOW_BUTTON_PIN, 1 );
uButton button_red(    RED_BUTTON_PIN,    1 );

void setupButtons()
{
   pinMode( GREEN_BUTTON_PIN,  INPUT_PULLUP );
   pinMode( YELLOW_BUTTON_PIN, INPUT_PULLUP );
   pinMode( RED_BUTTON_PIN,    INPUT_PULLUP );
}


PollTimer control( CONTROL_RATE );
PollTimer buttons( BUTTON_CHECK_RATE );
PollTimer display( DISPLAY_UPDATE_RATE );
PollTimer maintenance( MAINTENANCE_RATE );


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

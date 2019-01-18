

const int MOTOR_PULSE_RATE    = 50000;
const int CONTROL_RATE        = 500;
const int BUTTON_CHECK_RATE   = 100;
const int DISPLAY_UPDATE_RATE = 15;
const int MAINTENANCE_RATE    = 1;


const uint32_t purgeTime  = 1000;
const float    purgeSpeed = 1.0f;



uint32_t funCounter = 0;

float volatile cyl_1_position = 0.0f;

bool extrudeActive = false;

const int MAX_COMPONENT_COUNT = 16;

const int BLUE   = 0;
const int RED    = 1;
const int YELLOW = 2;
const int WHITE  = 3;

float mixVolume = 1.0; // CC
uint32_t extrudeTime = 0;
uint32_t extrudeStartTime;

bool motorEnableStatus = false;

bool noTouch = true;



enum machine_state_t
{
   sleep,
   dwell,
   prePurge,
   dispense,
   postPurge,
   fill,
   empty
} machine_state;

struct COMPONENT_DATA_t
{
   float ratio = 0;
   float speed = 0;
   bool fill = false;
   bool empty = false;
} C[MAX_COMPONENT_COUNT];

int selected_cyl = 0;
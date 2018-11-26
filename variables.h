
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





struct COMPONENT_DATA_t
{
   float ratio = 0;
   float speed = 0;

   stepperMotor motor();
   
} C[MAX_COMPONENT_COUNT];
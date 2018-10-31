
uint32_t funCounter = 0;

float volatile cyl_1_position = 0.0f;

bool extrudeActive = false;

const int MAX_COMPONENT_COUNT = 16;

const int BLUE   = 0;
const int RED    = 1;
const int YELLOW = 2;
const int WHITE  = 3;





struct COMPONENT_DATA_t
{
   
} GOOP[MAX_COMPONENT_COUNT];
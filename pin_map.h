// **** PIN DEFINES FOR TEENSY 3.5/3.6 ****
// 5 is intentionally ommitted

#define CYL_1_ENBL_PIN 2
#define CYL_1_STEP_PIN 3
#define CYL_1_DIR_PIN  4

#define CYL_2_ENBL_PIN 6
#define CYL_2_STEP_PIN 7
#define CYL_2_DIR_PIN  8

#define CYL_3_ENBL_PIN 23
#define CYL_3_STEP_PIN 22
#define CYL_3_DIR_PIN  21

#define CYL_4_ENBL_PIN 39
#define CYL_4_STEP_PIN 38
#define CYL_4_DIR_PIN  37

#define CYL_5_ENBL_PIN 36
#define CYL_5_STEP_PIN 35
#define CYL_5_DIR_PIN  34

#define CYL_6_ENBL_PIN 27
#define CYL_6_STEP_PIN 28
#define CYL_6_DIR_PIN  29

//#define X_ENDSTOP_PIN 24
//#define Y_ENDSTOP_PIN 25
//#define Z_ENDSTOP_PIN 26
//#define X_MIN_ENDSTOP_PIN 33
//#define Y_MIN_ENDSTOP_PIN 32
//#define Z_MIN_ENDSTOP_PIN 30

#define GREEN_BUTTON_PIN  24 // borrow these pins from the endstops
#define YELLOW_BUTTON_PIN 26
#define RED_BUTTON_PIN    25
 
//#define GREEN_BUTTON_PIN  17    // 17, A11, A10 (grr... those analog pins don't work with deigitalRead()... )
//#define YELLOW_BUTTON_PIN A11
//#define RED_BUTTON_PIN    A10

#define BED_HEATER_PWM_PIN 9
#define EXTRUDER1_PWM_PIN  20
#define EXTRUDER2_PWM_PIN

#define SPI0_CS   10
#define SPI0_MOSI 11
#define SPI0_MISO 12
#define SPI0_SCK  13

#define BED_THERMISTOR       14
#define EXTRUDER1_THERMISTOR 15
#define EXTRUDER2_THERMISTOR 16




#include <Adafruit_GFX.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_FT6206.h>

//#include <Fonts/FreeMono12pt7b.h>		
//#include <Fonts/FreeMono18pt7b.h>		
//#include <Fonts/FreeMono24pt7b.h>		
//#include <Fonts/FreeMono9pt7b.h>			
//#include <Fonts/FreeMonoBold12pt7b.h>		
//#include <Fonts/FreeMonoBold18pt7b.h>		
//#include <Fonts/FreeMonoBold24pt7b.h>		
//#include <Fonts/FreeMonoBold9pt7b.h>		
//#include <Fonts/FreeMonoBoldOblique12pt7b.h>	
//#include <Fonts/FreeMonoBoldOblique18pt7b.h>	
//#include <Fonts/FreeMonoBoldOblique24pt7b.h>	
//#include <Fonts/FreeMonoBoldOblique9pt7b.h>	
//#include <Fonts/FreeMonoOblique12pt7b.h>		
//#include <Fonts/FreeMonoOblique18pt7b.h>		
//#include <Fonts/FreeMonoOblique24pt7b.h>		
//#include <Fonts/FreeMonoOblique9pt7b.h>		

//#include <Fonts/FreeSans12pt7b.h>		
//#include <Fonts/FreeSans18pt7b.h>		
//#include <Fonts/FreeSans24pt7b.h>		
//#include <Fonts/FreeSans9pt7b.h>			
//#include <Fonts/FreeSansBold12pt7b.h>		
//#include <Fonts/FreeSansBold18pt7b.h>		
//#include <Fonts/FreeSansBold24pt7b.h>		
//#include <Fonts/FreeSansBold9pt7b.h>		
//#include <Fonts/FreeSansBoldOblique12pt7b.h>
#include <Fonts/FreeSansBoldOblique18pt7b.h>
//#include <Fonts/FreeSansBoldOblique24pt7b.h>
//#include <Fonts/FreeSansBoldOblique9pt7b.h>
//#include <Fonts/FreeSansOblique12pt7b.h>
//#include <Fonts/FreeSansOblique18pt7b.h>
//#include <Fonts/FreeSansOblique24pt7b.h>
//#include <Fonts/FreeSansOblique9pt7b.h>

//#include <Fonts/FreeSerif12pt7b.h>
//#include <Fonts/FreeSerif18pt7b.h>
//#include <Fonts/FreeSerif24pt7b.h>
//#include <Fonts/FreeSerif9pt7b.h>
//#include <Fonts/FreeSerifBold12pt7b.h>
//#include <Fonts/FreeSerifBold18pt7b.h>
//#include <Fonts/FreeSerifBold24pt7b.h>
//#include <Fonts/FreeSerifBold9pt7b.h>
//#include <Fonts/FreeSerifBoldItalic12pt7b.h>
//#include <Fonts/FreeSerifBoldItalic18pt7b.h>
//#include <Fonts/FreeSerifBoldItalic24pt7b.h>
//#include <Fonts/FreeSerifBoldItalic9pt7b.h>
#include <Fonts/FreeSerifItalic12pt7b.h>
//#include <Fonts/FreeSerifItalic18pt7b.h>
//#include <Fonts/FreeSerifItalic24pt7b.h>
#include <Fonts/FreeSerifItalic9pt7b.h>

// The FT6206 uses hardware I2C (SCL/SDA)
Adafruit_FT6206 touch_screen = Adafruit_FT6206();

Adafruit_ILI9341 tft = Adafruit_ILI9341(SPI0_CS, TFT_DC);

const int screen_width  = 240;
const int screen_height = 320;

#define RGB8_to_RGB5(R, G, B) (((R>>3)<<11) | ((G>>3)<<6) | (B>>3)) // convert 8bit RGB to 5bit RGB

/*
// Color definitions
#define ILI9341_BLACK       0x0000  ///<   0,   0,   0
#define ILI9341_NAVY        0x000F  ///<   0,   0, 123
#define ILI9341_DARKGREEN   0x03E0  ///<   0, 125,   0
#define ILI9341_DARKCYAN    0x03EF  ///<   0, 125, 123
#define ILI9341_MAROON      0x7800  ///< 123,   0,   0
#define ILI9341_PURPLE      0x780F  ///< 123,   0, 123
#define ILI9341_OLIVE       0x7BE0  ///< 123, 125,   0
#define ILI9341_LIGHTGREY   0xC618  ///< 198, 195, 198
#define ILI9341_DARKGREY    0x7BEF  ///< 123, 125, 123
#define ILI9341_BLUE        0x001F  ///<   0,   0, 255
#define ILI9341_GREEN       0x07E0  ///<   0, 255,   0
#define ILI9341_CYAN        0x07FF  ///<   0, 255, 255
#define ILI9341_RED         0xF800  ///< 255,   0,   0
#define ILI9341_MAGENTA     0xF81F  ///< 255,   0, 255
#define ILI9341_YELLOW      0xFFE0  ///< 255, 255,   0
#define ILI9341_WHITE       0xFFFF  ///< 255, 255, 255
#define ILI9341_ORANGE      0xFD20  ///< 255, 165,   0
#define ILI9341_GREENYELLOW 0xAFE5  ///< 173, 255,  41
#define ILI9341_PINK        0xFC18  ///< 255, 130, 198
*/

const unsigned int BACKGROUND = RGB8_to_RGB5( 64, 64, 64 );

struct v_bar_graph_data_t
{
   int x, y, w, h, value, minimum, maximum, c;
};

//                              x    y   w    h    v   mi ma     color
v_bar_graph_data_t vBlue   = {   8, 80, 50, 150, 128,  0, 255, ILI9341_CYAN };
v_bar_graph_data_t vRed    = {  66, 80, 50, 150, 128,  0, 255, ILI9341_MAGENTA };
v_bar_graph_data_t vYellow = { 124, 80, 50, 150, 128,  0, 255, ILI9341_YELLOW };
v_bar_graph_data_t vWhite  = { 182, 80, 50, 150, 128,  0, 255, ILI9341_WHITE };

v_bar_graph_data_t vLAB_L  = {   8, 80, 50, 150, 100,  0,  100, ILI9341_WHITE };
v_bar_graph_data_t vLAB_A  = {  66, 80, 50, 150,  0, -128, 127, ILI9341_WHITE };
v_bar_graph_data_t vLAB_B  = { 124, 80, 50, 150,  0, -128, 127, ILI9341_WHITE };
v_bar_graph_data_t v_QTY   = { 182, 80, 50, 150,  5,  0,   10,  ILI9341_WHITE };

v_bar_graph_data_t v_RGB   = { 182, 80, 50, 150, 100,  0,  100, ILI9341_WHITE };

void drawSplitBar( v_bar_graph_data_t b )
{
   int i = (( b.value - b.minimum ) * b.h ) / ( b.maximum - b.minimum );
   tft.fillRect( b.x, b.y, b.w, b.h-i, 0 );
   tft.fillRect( b.x, b.y+b.h-i, b.w, i, b.c );
}

void drawBarBorder( v_bar_graph_data_t b )
{
   tft.fillRect( b.x-1, b.y-1, b.w+2, b.h+2, b.c );
   tft.fillRect( b.x-2, b.y-2, b.w+4, b.h+4, b.c );
}

void barShowSplit( v_bar_graph_data_t b )
{
   int x = b.x+12;
   int y = b.y-20;
   tft.fillRect( x, y, b.w, 16, BACKGROUND);
   tft.setFont();
   tft.setTextSize(2);
   tft.setTextColor( ILI9341_WHITE, BACKGROUND);
   tft.setCursor( x, y);
   tft.print(b.value);
}

void updateBar( v_bar_graph_data_t b )
{
   drawSplitBar( b );
   barShowSplit( b );
}

bool touchInBar( int x, int y, v_bar_graph_data_t & b )
{
   if( x > b.x && x < (b.x+b.w) ) // inside width
   {
      if( y > b.y && y < (b.y+b.h) ) // inside height
      {
         if( y < (b.y+b.h/2)) // in top half of bar
         {
            b.value++; 
         }
         else // bottom half of bar
         {
            b.value--;
         }
         b.value = constrain( b.value, b.minimum, b.maximum);
         updateBar( b );
         return true;
      }
   }
   return false;
}


void lucidSplashScreen()
{
   String t = "RPM";
   int x = 15;
   int y = 30;

   //tft.setFont(&FreeSerifBoldItalic24pt7b);
   tft.setFont(&FreeSansBoldOblique18pt7b);

   tft.setCursor( x+3, y+3 ); // shadow
   tft.setTextColor(ILI9341_BLACK);
   tft.println(t);

   tft.setCursor( x, y );     // text
   tft.setTextColor(ILI9341_WHITE);
   tft.println(t);

   x += 85;
   y += -6;

   tft.setFont(&FreeSerifItalic12pt7b);
   tft.setTextColor(ILI9341_BLACK); // shadow
   tft.setCursor( x+2, y+2 );
   tft.println("Mon Spectre");
   tft.setTextColor(ILI9341_WHITE); // text
   tft.setCursor( x, y );
   tft.println("Mon Spectre");

}


void initDrawBar( v_bar_graph_data_t b )
{
   drawBarBorder( b );
   drawSplitBar(  b );
   barShowSplit(  b );
}

void startDisplay()
{
   tft.begin();

   touch_screen.begin(40);

   //tft.fillScreen(ILI9341_BLACK);
   tft.fillScreen(BACKGROUND);

   tft.setRotation(2); 

   lucidSplashScreen();

   // *** RGB BARS
   initDrawBar( vBlue );
   initDrawBar( vRed );
   initDrawBar( vYellow );
   initDrawBar( vWhite );

   // *** LAB BARS
   //initDrawBar( vLAB_L );
   //initDrawBar( vRed );
   //initDrawBar( vYellow );
   //initDrawBar( vWhite );
}

bool RGB_touch_check( int x, int y )
{
   if( touchInBar( x, y, vBlue   ) ) return true;
   if( touchInBar( x, y, vRed    ) ) return true;
   if( touchInBar( x, y, vYellow ) ) return true;
   if( touchInBar( x, y, vWhite  ) ) return true;

   return false;
}

bool LAB_touch_check( int x, int y )
{
   if( touchInBar( x, y, vLAB_L ) ) return true;
   if( touchInBar( x, y, vLAB_A ) ) return true;
   if( touchInBar( x, y, vLAB_B ) ) return true;
   if( touchInBar( x, y, v_QTY  ) ) return true;

   return false;
}

void onTouch( int x, int y, bool longTouch )
{
   //x = screen_width  - x; // translate from touch coordinates to pixel coordinates
   //y = screen_height - y;

   // in the future use longTouch for drag motion

   RGB_touch_check( x, y );

   /*
   if( LAB_touch_check( x, y ) )
   {
      color_Lab_t c_Lab = { vLAB_L.value, vLAB_A.value, vLAB_B.value };
      color_RGB_t c_RGB = Lab_to_RGB( c_Lab );

      // update color preview
      v_RGB.c  = RGB8_to_RGB5( c_RGB.R, c_RGB.G, c_RGB.B );
      drawSplitBar( v_RGB.c )

      // update CMYW colors
      color_CMYW_t c_CMYW = RGB_to_CMYW( c_RGB );
      vBlue.c   = c_CMYW.C;
      vRed.c    = c_CMYW.M;
      vYellow.c = c_CMYW.Y;
      vWhite.c  = c_CMYW.W;

      updateBar( vBlue );
      updateBar( vRed  );
      updateBar( vYellow );
      updateBar( vWhite  );

   }
    */
}
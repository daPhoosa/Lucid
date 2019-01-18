
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
//#include <Fonts/FreeSansBoldOblique18pt7b.h>
//#include <Fonts/FreeSansBoldOblique24pt7b.h>
//#include <Fonts/FreeSansBoldOblique9pt7b.h>
//#include <Fonts/FreeSansOblique12pt7b.h>
//#include <Fonts/FreeSansOblique18pt7b.h>
//#include <Fonts/FreeSansOblique24pt7b.h>
//#include <Fonts/FreeSansOblique9pt7b.h>

//#include <Fonts/FreeSerif12pt7b.h>
//#include <Fonts/FreeSerif18pt7b.h>
#include <Fonts/FreeSerif24pt7b.h>
//#include <Fonts/FreeSerif9pt7b.h>
//#include <Fonts/FreeSerifBold12pt7b.h>
//#include <Fonts/FreeSerifBold18pt7b.h>
//#include <Fonts/FreeSerifBold24pt7b.h>
//#include <Fonts/FreeSerifBold9pt7b.h>
//#include <Fonts/FreeSerifBoldItalic12pt7b.h>
//#include <Fonts/FreeSerifBoldItalic18pt7b.h>
//#include <Fonts/FreeSerifBoldItalic24pt7b.h>
//#include <Fonts/FreeSerifBoldItalic9pt7b.h>
//#include <Fonts/FreeSerifItalic12pt7b.h>
//#include <Fonts/FreeSerifItalic18pt7b.h>
//#include <Fonts/FreeSerifItalic24pt7b.h>
//#include <Fonts/FreeSerifItalic9pt7b.h>

// The FT6206 uses hardware I2C (SCL/SDA)
Adafruit_FT6206 touch_screen = Adafruit_FT6206();

Adafruit_ILI9341 tft = Adafruit_ILI9341(SPI0_CS, TFT_DC);

const int screen_width  = 240;
const int screen_height = 320;

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

const int BACKGROUND = ILI9341_DARKGREY;


struct v_bar_graph_data_t
{
   int x, y, w, h, s, c;
};

v_bar_graph_data_t vBlue   = {   8, 112, 50, 200, 50, ILI9341_BLUE };
v_bar_graph_data_t vRed    = {  66, 112, 50, 200, 50, ILI9341_RED };
v_bar_graph_data_t vYellow = { 124, 112, 50, 200, 50, ILI9341_YELLOW };
v_bar_graph_data_t vWhite  = { 182, 112, 50, 200, 50, ILI9341_WHITE };

void drawSplitBar( v_bar_graph_data_t b )
{
   int i = ( b.s * b.h ) / 100;
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
   tft.print(b.s);
}

bool touchInBar( int x, int y, v_bar_graph_data_t & b )
{
   if( x > b.x && x < (b.x+b.w) ) // inside width
   {
      if( y > b.y && y < (b.y+b.h) ) // inside height
      {
         if( y < (b.y+b.h/2)) // in top half of bar
         {
            b.s++; 
         }
         else // bottom half of bar
         {
            b.s--;
         }
         b.s = constrain( b.s, 0, 100);
         drawSplitBar( b );
         barShowSplit( b );
         return true;
      }
   }
   return false;
}


void lucidSplashScreen()
{
   tft.setTextColor(ILI9341_WHITE);
   //tft.setTextSize(3);
   tft.setFont(&FreeSerif24pt7b);
   tft.println("LUCID");
}


void startDisplay()
{
   tft.begin();

   touch_screen.begin(40);

   //tft.fillScreen(ILI9341_BLACK);
   tft.fillScreen(BACKGROUND);

   tft.setRotation(0); 

   tft.setCursor( 50, 50);

   lucidSplashScreen();

   drawBarBorder( vBlue );
   drawSplitBar(  vBlue );
   barShowSplit(  vBlue );

   drawBarBorder( vRed );
   drawSplitBar(  vRed );
   barShowSplit(  vRed );

   drawBarBorder( vYellow );
   drawSplitBar(  vYellow );
   barShowSplit(  vYellow );
   
   drawBarBorder( vWhite );
   drawSplitBar(  vWhite );
   barShowSplit(  vWhite );
}


void onTouch( int x, int y)
{
   x = screen_width  - x; // translate from touch coordinates to pixel coordinates
   y = screen_height - y;

   if( touchInBar( x, y, vBlue ) )
   {

   }
   else if( touchInBar( x, y, vRed ) )
   {

   }
   else if( touchInBar( x, y, vYellow ) )
   {

   }
   else if( touchInBar( x, y, vWhite ) )
   {

   }
   
}
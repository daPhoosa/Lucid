/*
 *    Color Space Conversion Library, Phillip Schmidt, 2019
 * 
 *    DATA TYPES:
 *       color_RGB_t  (float R, float G, float B)              // RGB arguments should be scaled to 0-1 range
 *       color_XYZ_t  (float X, float Y, float Z)
 *       color_Lab_t  (float L, float a, float b)
 *       color_CMYK_t (float C, float M, float Y, float K)
 *       color_CMYW_t (float C, float M, float Y, float W)
 *
 *       Data initialization:
 *          color_RGB_t color( 0.1, 0.2, 0.3 );
 * 
 *          is the same as:
 * 
 *          color_RGB_t color;
 *          color.R = 0.1;
 *          color.G = 0.2;
 *          color.B = 0.3;
 * 
 *    COLOR SPACE CONVERSION FUNCTIONS:
 *       color_XYZ_t Lab_to_XYZ(   const color_Lab_t c )
 *       color_Lab_t XYZ_to_Lab(   const color_XYZ_t c )   
 *       color_XYZ_t RGB_to_XYZ(   color_RGB_t       c )
 *       color_RGB_t XYZ_to_RGB(   const color_XYZ_t c )
 *       color_RGB_t CMYK_to_RGB(  color_CMYK_t      c )
 *       color_CMYW_t RGB_to_CMYW( color_RGB_t       c )
 */


/*
 * DATA STRUCTURES
 */ 

struct color_RGB_t
{
   float R, G, B;
   
   color_RGB_t() : R(0), G(0), B(0) {}
   color_RGB_t(const float R, const float G, const float B) : R(R), G(G), B(B) {}
};

struct color_XYZ_t
{
   float  X, Y, Z;
   
   color_XYZ_t() : X(0.0f), Y(0.0f), Z(0.0f) {}
   color_XYZ_t(const float X, const float Y, const float Z) : X(X), Y(Y), Z(Z) {}
};

struct color_Lab_t
{
   float L, a, b;
   
   color_Lab_t() : L(0.0f), a(0.0f), b(0.0f) {}
   color_Lab_t(const float L, const float a, const float b) : L(L), a(a), b(b) {}
};

struct color_CMYK_t
{
   float  C, M, Y, K;
   
   color_CMYK_t() : C(0.0f), M(0.0f), Y(0.0f), K(0.0f) {}
   color_CMYK_t(const float C, const float M, const float Y, const float K) : C(C), M(M), Y(Y), K(K) {}
};

struct color_CMYW_t
{
   float  C, M, Y, W;
   
   color_CMYW_t() : C(0.0f), M(0.0f), Y(0.0f), W(0.0f) {}
   color_CMYW_t(const float C, const float M, const float Y, const float W) : C(C), M(M), Y(Y), W(W) {}
};


/*
 * CONSTANTS
 */

const color_XYZ_t D65(95.047, 100.0, 108.883);  // Illuminant D65 white point - https://en.wikipedia.org/wiki/Illuminant_D65
const float CIE_E = 216.0f / 24389.0f;
const float CIE_K = 24389.0f / 27.0f;


/*
 * CONVERSION FUNCTIONS
 */
 
color_XYZ_t Lab_to_XYZ( const color_Lab_t c )
{
   // Reference: http://www.brucelindbloom.com/index.html?Eqn_Lab_to_XYZ.html
  
   float fy = (c.L + 16.0f) / 116.0f;
   float fz = fy - c.b / 200.0f;
   float fx = c.a / 500.0f + fy;

   color_XYZ_t r;

   float fx3 = fx * fx * fx;
   if( fx3 > CIE_E )
   {
      r.X = fx3;
   }
   else
   {
      r.X = ( 116.0f * fx - 16.0f ) / CIE_K;
   }

   if( c.L > CIE_K * CIE_E )
   {
      float a = ( c.L + 16.0f ) / 116.0f;
      r.Y = a * a * a;
   }
   else
   {
      r.Y = c.L / CIE_K;
   }

   float fz3 = fz * fz * fz;
   if( fz3 > CIE_E )
   {
      r.Z = fz3;
   }
   else
   {
      r.Z = ( 116.0f * fz - 16.0f ) / CIE_K;
   }

   r.X *= D65.X; // apply white point compensation
   r.Y *= D65.Y;
   r.Z *= D65.Z;

   return r;
}

color_Lab_t XYZ_to_Lab( const color_XYZ_t c )   
{
   // http://www.brucelindbloom.com/index.html?Eqn_XYZ_to_Lab.html

   color_XYZ_t r( c.X/D65.X, c.Y/D65.Y, c.Z/D65.Z ); // reverse white point compensation

   float fx, fy, fz;

   if( r.X > CIE_E )
   {
      fx = powf( r.X, 1.0f/3.0f ); // cube root of Xr
   }
   else
   {
      fx = (CIE_K * r.Y + 16.0f) / 116.0f;
   }

   if( r.Y > CIE_E )
   {
      fy = powf( r.Y, 1.0f/3.0f );
   }
   else
   {
      fy = (CIE_K * r.Y + 16.0f) / 116.0f;
   }

   if( r.Z > CIE_E )
   {
      fz = powf( r.Z, 1.0f/3.0f );
   }
   else
   {
      fz = ( CIE_K * r.Z + 16.0f ) / 116.0f;
   }

   color_Lab_t a( 116.0f * fy - 16.0f, 500.0f * (fx - fy), 200.0f * (fy - fz) );

   return a;
}

color_XYZ_t RGB_to_XYZ( color_RGB_t c ) // pass RGB scaled to 0-1 range
{
   const float M[3][3] = {{ 0.4124564, 0.3575761, 0.1804375 },  // sRGB http://www.brucelindbloom.com/index.html?Eqn_RGB_XYZ_Matrix.html
                          { 0.2126729, 0.7151522, 0.0721750 },
                          { 0.0193339, 0.1191920, 0.9503041 }};

   if( c.R <= 0.04045 )
   {
      c.R /= 12.92f;
   }
   else
   {
      c.R = powf( (( c.R + 0.055f) / 1.055), 2.4 );
   }

   if( c.G <= 0.04045 )
   {
      c.G /= 12.92f;
   }
   else
   {
      c.G = powf( (( c.G + 0.055f) / 1.055), 2.4 );
   }

   if( c.B <= 0.04045 )
   {
      c.B /= 12.92f;
   }
   else
   {
      c.B = powf( (( c.B + 0.055f) / 1.055), 2.4 );
   }
   
   color_XYZ_t z;

   z.X = (M[0][0] * c.R + M[0][1] * c.G + M[0][2] * c.B) * 100.0f; // = [M] * [rgb]^t
   z.Y = (M[1][0] * c.R + M[1][1] * c.G + M[1][2] * c.B) * 100.0f;
   z.Z = (M[2][0] * c.R + M[2][1] * c.G + M[2][2] * c.B) * 100.0f;

   return z;   
}

color_RGB_t XYZ_to_RGB( const color_XYZ_t c )
{
   const float M_inv[3][3] = {{ 3.2404542, -1.5371385, -0.4985314 },  // sRGB http://www.brucelindbloom.com/index.html?Eqn_RGB_XYZ_Matrix.html
                              {-0.9692660,  1.8760108,  0.0415560 },
                              { 0.0556434, -0.2040259,  1.0572252 }};

   float r = (M_inv[0][0] * c.X + M_inv[0][1] * c.Y + M_inv[0][2] * c.Z) * 0.01f;
   float g = (M_inv[1][0] * c.X + M_inv[1][1] * c.Y + M_inv[1][2] * c.Z) * 0.01f;
   float b = (M_inv[2][0] * c.X + M_inv[2][1] * c.Y + M_inv[2][2] * c.Z) * 0.01f;

   if( r <= 0.0031308 )
   {
      r *= 12.92;
   }
   else
   {
      r = 1.055f * powf( r, 1.0f/2.4f ) - 0.055f;
   }

   if( g <= 0.0031308 )
   {
      g *= 12.92;
   }
   else
   {
      g = 1.055f * powf( g, 1.0f/2.4f ) - 0.055f;
   }

   if( b <= 0.0031308 )
   {
      b *= 12.92;
   }
   else
   {
      b = 1.055f * powf( b, 1.0f/2.4f ) - 0.055f;
   }

   return color_RGB_t( r, g, b );
}

color_RGB_t CMYK_to_RGB( color_CMYK_t c )
{
   color_RGB_t a;

   a.R = ( 1.0f - c.C ) * ( 1.0f - c.K );
   a.G = ( 1.0f - c.M ) * ( 1.0f - c.K );
   a.B = ( 1.0f - c.Y ) * ( 1.0f - c.K );

   return a;
}

color_CMYK_t RGB_to_CMYK( color_RGB_t c )
{
   color_CMYK_t a;

   a.K = 1 - max(max( c.R, c.G ), c.B);

   a.C = ( 1.0f - c.R - a.K ) / ( 1.0f - a.K );
   a.M = ( 1.0f - c.G - a.K ) / ( 1.0f - a.K );
   a.Y = ( 1.0f - c.B - a.K ) / ( 1.0f - a.K );

   return a;
}

color_CMYW_t RGB_to_CMYW( color_RGB_t c )
{
   color_CMYW_t a;

   a.C = ( 1.0f - c.R );
   a.M = ( 1.0f - c.G );
   a.Y = ( 1.0f - c.B );
   a.W = sqrtf( 3.0f - ( a.C*a.C + a.M*a.M + a.Y*a.Y )); // when RGB = 1,1,1 then only white, when RGB = 0,0,0 then no white

   // future: add normalization to prevent white from being greater than 1, for now I don't care...

   return a;
};



/*
 *  DISPLAY functions  
 *   ( Add "#define SerialPort Serial" above #include to enable these functions to output )
 */


void display( color_Lab_t c )
{
   #ifdef SerialPort
   SerialPort.print("L: "); SerialPort.println(c.L);
   SerialPort.print("a: "); SerialPort.println(c.a);
   SerialPort.print("b: "); SerialPort.println(c.b);
   #endif
}

void display( color_XYZ_t c )
{
   #ifdef SerialPort
   SerialPort.print("X: ");SerialPort.println(c.X);
   SerialPort.print("Y: ");SerialPort.println(c.Y);
   SerialPort.print("Z: ");SerialPort.println(c.Z);
   #endif
}

void display( color_RGB_t c )
{
   #ifdef SerialPort
   SerialPort.print("R: ");SerialPort.println(c.R);
   SerialPort.print("G: ");SerialPort.println(c.G);
   SerialPort.print("B: ");SerialPort.println(c.B);
   #endif
}

void display( color_CMYK_t c )
{
   #ifdef SerialPort
   SerialPort.print("C: ");SerialPort.println(c.C);
   SerialPort.print("M: ");SerialPort.println(c.M);
   SerialPort.print("Y: ");SerialPort.println(c.Y);
   SerialPort.print("K: ");SerialPort.println(c.K);
   #endif
}

void display( color_CMYW_t c )
{
   #ifdef SerialPort
   SerialPort.print("C: ");SerialPort.println(c.C);
   SerialPort.print("M: ");SerialPort.println(c.M);
   SerialPort.print("Y: ");SerialPort.println(c.Y);
   SerialPort.print("W: ");SerialPort.println(c.W);
   #endif
}

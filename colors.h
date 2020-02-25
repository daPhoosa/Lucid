
/*
float get_color_value( int angle )
{
    while( angle > 360 ) angle -= 360;
    while( angle < 0   ) angle += 360;

    if( angle > 239 ) return 0.0f;

    float a = float(angle) * ( 3.14159265f / 180.0f ) * 0.75f; // convert to radians and scale to make 180deg expand to 240 deg

    return sinf( a );
}


void get_RYBW_color( int hue, int saturation, int lightness, int & R, int & Y, int & B, int & W )
{
    Y = get_color_value( hue + 120);
    R = get_color_value( hue );
    B = get_color_value( hue - 120);
}
*/

void setupColors()
{
    ColorSolver.add_component(  8.71, 12.73, 26.67, 1.791 ); // cyan
    ColorSolver.add_component( 29.78, 17.75, 16.77, 1.492 ); // magenta
    ColorSolver.add_component( 61.67, 66.93,  7.18, 1.055 ); // yellow
    ColorSolver.add_component( 77.60, 79.55, 60.01, 1.000 ); // white
}




#define max_component_cnt 10

class GradDescentSolver
{
    public:
        void add_component( const float & x, const float & y, const float & z, const float & s );
        void show_components();

        void get_solution_XYZ( float x, float y, float z );
        float get_weight( int i );

        void show_weights();

    private:
        int component_cnt = 0;

        struct components_t
        {
            float  X, Y, Z;
            components_t() : X(0.0f), Y(0.0f), Z(0.0f) {}
            components_t(const float X, const float Y, const float Z ) : X(X), Y(Y), Z(Z) {}
        };
        components_t components[max_component_cnt];

        const components_t max_XYZ = { 95.05, 100.0, 108.9 }; // D65 white point

        components_t current_color;
        float error_now;
        float error_last;

        components_t compute_color( float weights[] )
        {
            // Weighted geomtric mean
            components_t a = { powf(components[0].X, weights[0]), powf(components[0].Y, weights[0]), powf(components[0].Z, weights[0]) };
            for( int i=1; i<component_cnt; i++ )
            {
                a.X *= powf( components[i].X, weights[i] );
                a.Y *= powf( components[i].Y, weights[i] );
                a.Z *= powf( components[i].Z, weights[i] );
            }
            return a;
        }

        components_t sub( const components_t & lhs, const components_t & rhs )
        {
            components_t a = { lhs.X - rhs.X, lhs.Y - rhs.Y, lhs.Z - rhs.Z };
            return a;
        }

        components_t sum( const components_t & lhs, const components_t & rhs )
        {
            components_t a = { lhs.X + rhs.X, lhs.Y + rhs.Y, lhs.Z + rhs.Z };
            return a;
        }

        components_t mul( const components_t & lhs, const float & s )
        {
            components_t a = { lhs.X * s, lhs.Y * s, lhs.Z * s };
            return a;
        }

        components_t get_biased_color( int index, float bias )
        {
            float w[component_cnt];
            for( int i=0; i<component_cnt; i++ ) w[i] = weight[i]; // copy weights
            w[index] += bias;
            norm_weights( w );
            return compute_color( w );
        }

        float dist( const components_t & a, const components_t & b )
        {
            float x = a.X - b.X;
            float y = a.Y - b.Y;
            float z = a.Z - b.Z;
            return sqrtf( x*x + y*y + z*z );
        }

        float weight[max_component_cnt];
        float slope[max_component_cnt];

        void get_pos();
        void display( components_t t );
        void norm_weights( float w[] );

} ColorSolver;


void GradDescentSolver::add_component( const float & x, const float & y, const float & z, const float & scale )
{
    components_t a = { x, y, z };
    a = mul( a, scale ); // scale to account for strength
    components[component_cnt] = a;
    //components[component_cnt] = mul( sub( max_XYZ, a ), scale); // invert, subtractive color mixing
    display( components[component_cnt] );
    if(component_cnt < max_component_cnt - 1) component_cnt++;
}


void GradDescentSolver::show_weights()
{
    for(int i=0; i<component_cnt; i++)
    {
        Serial.print(weight[i], 4);
        Serial.print("\t");
    }
    Serial.println("");
}


void GradDescentSolver::show_components()
{
    for(int i=0; i<component_cnt; i++)
    {
        display(components[i]);
    }
}


void GradDescentSolver::display( components_t t )
{
    Serial.print("X:"); Serial.print(t.X);
    Serial.print("  Y:"); Serial.print(t.Y);
    Serial.print("  Z:"); Serial.println(t.Z);
}


void GradDescentSolver::norm_weights( float w[] )
{
    float total = 0;
    for( int i=0; i<component_cnt; i++ ) total += w[i]; // sum weights
    for( int i=0; i<component_cnt; i++ ) w[i] /= total; // scale weights
}


void GradDescentSolver::get_solution_XYZ( float x, float y, float z )
{
    components_t target = { x, y, z };
    //target = sub( max_XYZ, target); // Invert target color (subtractive color mixing)
    display( target );

    // compute starting weights
    for( int i=0; i<component_cnt; i++ )
    {
        weight[i] = 1.0f / ( dist( components[i], target ) + 0.00001f );
    }
    norm_weights( weight );

    //  Begin solving
    current_color = compute_color( weight );
    //display( current_color );
    error_now = dist( current_color, target );
    //Serial.println( error_now );
    error_last = 99999;
    int iteration_cnt = 0;
    float step;

    //Serial.print("Itteration"); Serial.print("\t"); Serial.print("Error"); Serial.print("\t"); Serial.print("Cyan"); Serial.print("\t"); Serial.print("Magenta"); Serial.print("\t"); Serial.print("Yellow"); Serial.print("\t"); Serial.println("White");

    while( error_now < error_last && error_now > 0.1f )
    {
        //Serial.print(iteration_cnt); Serial.print("\t"); Serial.print(error_now/10, 2); Serial.print("\t"); show_weights();

        iteration_cnt++;
        float max_slope = 0;
        int max_index = 0;
        step = max( error_now * 0.0005f, 0.00005f );

        for( int i=0; i<component_cnt; i++ )
        {
            components_t delta = get_biased_color( i, step ); 
            float error_next = dist( delta, target );
            slope[i] = ( error_next - error_now ) / step;

            if( abs(slope[i]) > abs(max_slope) ) // new slope is steeper
            {
                if( slope[i] < 0 || weight[i] > step ) // insure weights don't go negative
                {
                    max_slope = slope[i];
                    max_index = i;
                }
            }
        }

        if( max_slope > 0 ) // increment most effective color
        {
            weight[max_index] -= step;
        }
        else
        {
            weight[max_index] += step;
        }
        norm_weights( weight );

        current_color = compute_color( weight );
        error_last = error_now;
        error_now = dist( current_color, target ); // recompute error

        //Serial.println( error_now, 4 );
    }

    //Serial.print(iteration_cnt); Serial.print("\t"); Serial.print(error_now/100.,4); Serial.print("\t"); show_weights();

    /* debug output
    display( sub( max_XYZ, current_color ));
    Serial.print("Error: "); Serial.println( error_now, 4 );
    Serial.println(iteration_cnt);
    Serial.println(step, 4);
    */

    // Normalize Weights
    //norm_weights( weight );
    show_weights();
    display( current_color );
}


float GradDescentSolver::get_weight( int i )
{
    return weight[i];
}
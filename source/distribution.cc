#include "distribution.h"

#include <iostream>
#include <time.h>
#include <cstdlib>
#include <random>
#include <cmath> //contains the const M_PI
#include <cassert> // for the assert function
#include<cstdlib>


double distribution::uniforme(double min, double max)
{
double resultat;
assert(min<max);
resultat=min+((double)rand()/(RAND_MAX))*(max-min); //example : resultat =min(-1) + rand(6000)/randmax(10000) * 2 = 0.2
return resultat; 
}
/*
RAND_MAX: This macro expands to an integral constant expression whose value is 
the maximum value returned by the rand function.
This value is library-dependent, but is guaranteed to be at least 32767 
on any standard library implementation.
*/
//Distribution en cosinus
double distribution::cosinus(double xMin, double xMax )
{
assert( xMin < xMax );
double a = 0.5 * ( xMin + xMax );
// location parameter
double b = ( xMax - xMin ) / M_PI;
// scale parameter
return a + b * asin( uniforme( -1., 1. ) );
}

//FONCTIONS GLOBALES
/*
#include "distribution.h"

#include <iostream>
#include <time.h>
#include <cstdlib>
#include <random>
#include <cmath> //contains the const M_PI
#include <cassert> // for the assert function
#include<cstdlib>

using namespace std;

//Distribution uniforme
double uniforme(double min, double max)
{
double resultat;
assert(min<max);
resultat=min+((double)rand()/(RAND_MAX))*(max-min); //example : resultat =min(-1) + rand(6000)/randmax(10000) * 2 = 0.2
return resultat; 
}
*/
/*
RAND_MAX: This macro expands to an integral constant expression whose value is 
the maximum value returned by the rand function.
This value is library-dependent, but is guaranteed to be at least 32767 
on any standard library implementation.
*/
/*
//Distribution en cosinus
double cosinus(double xMin, double xMax )
{
assert( xMin < xMax );
double a = 0.5 * ( xMin + xMax );
// location parameter
double b = ( xMax - xMin ) / M_PI;
// scale parameter
return a + b * asin( uniforme( -1., 1. ) );
}
*/

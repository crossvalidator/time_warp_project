/* rand example: guess the number */
#include "exponentialrandomvariable.h"

float exponentialrandomvariable(float lambda, float min) 
{
	// generates exponential random variable with mean lambda and minimum value min
	// typically min is 0
    // uses uniform random variable to generate this exponential random variable

  float x,u =0;

  /* initialize random seed: */
  //srand ( time(0) );

  /* generate secret number: */
  //u = rand() / RAND_MAX;
  u = rand() %2;
  u = u/2;

  x = log(1-u);
  x = -1* x/(lambda-min) + min;
   
  return(x);
}


  
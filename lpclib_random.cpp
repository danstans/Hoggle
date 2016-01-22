#include <iostream>
#include <stdlib.h>
#include "lpclib.h"
using namespace std;

int RandomInt(int low, int high)
{
#if RAND_MAX == INT_MAX
    return ( rand() % (1+high-low) + low );
#else
    return ( ((rand()*RAND_MAX)+rand()) % (1+high-low) + low );
#endif
}

double RandomDouble(double low, double high)
{
    double val = rand();
    double fraction = val / (RAND_MAX);
    return ( fraction*(high-low) + low );
}

bool RandomChance(double p)
{
    return (RandomDouble(0,1) <= p);
}


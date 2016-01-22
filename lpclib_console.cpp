#if defined(_MSC_VER) || defined(WIN32)  || defined(_WIN32) || defined(__WIN32__) \
|| defined(WIN64)    || defined(_WIN64) || defined(__WIN64__)
#define OS_IS_WINDOWS
#endif

#include <iostream>
#include <sstream>
#ifdef OS_IS_WINDOWS
#include <conio.h>
#endif
#include <stdlib.h>
#include "lpclib.h"
using namespace std;

// Helper functions
template <typename T>
static bool CheckInput (string str, T & val)
{
	stringstream ss;
    ss << str;
    ss >> val;
    if (!ss)
        return false;

    ss.get();
    if (ss)
        return false;

    return true;

}

template <typename T>
static T GetInput(string what, istream & src)
{
    T val;
    string input = GetLine(src);
    while (!CheckInput(input, val))
    {
        cout << "Expected " << what << " - try again: ";
        input = GetLine(src);
    }
    return (val);
}
void Error (string str)
{
    cerr << endl << "** " << str << endl;
    throw (exception());
}

string GetLine(istream & src)
{
    string s;
    char c;
    src.get(c);
    while (c != '\n')
    {
        s += c;
        src.get(c);
    }
    return (s);
}

int GetInt(istream & src)
{
    return (GetInput<int>("integer", src));
}

double GetDouble(istream & src)
{
    return (GetInput<double>("number", src));
}

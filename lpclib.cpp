#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <stdarg.h>
#include <map>
#include "lpclib.h"
#undef main
using namespace std;

#define CODEBLOCKS


#define BANNERSIZE 60
// CinReplacement __lpclib_cin;

int __lpclib_system_messages = 1;

static void PrintBanner(string s)
{
    unsigned long int extracols = BANNERSIZE - s.length() - 2;
    if (__lpclib_system_messages)
    {
        for (int i = 0; i < extracols/2; i++)
            cout << "-";
        cout << " " << s << " ";
        for (int i = 0; i < (extracols - extracols/2); i++)
            cout << "-";
        cout << "\n";
    }
}


static string GetTimeStr()
{
    time_t rawtime;
    string when;
    time ( &rawtime );
    when = string(ctime(&rawtime));
    when = when.substr(0, when.length()-1);
    return (when);
}

void HideSystemMessages()
{
    __lpclib_system_messages = 0;
}

int main()
{
    srand((unsigned int)time(0));
    rand();

    PrintBanner("Program started " + GetTimeStr());

    try {
        __lpclib_user_main();
        cout << "\n";
        __lpclib_system_messages = 1;
        PrintBanner("Program ended normally " + GetTimeStr());
#ifndef CODEBLOCKS
        cout << "[Enter to quit...]";
        GetLine();
#endif
    } catch (exception &e) {
        cout << "\n";
        __lpclib_system_messages = 1;
        PrintBanner("Runtime error ended program " + GetTimeStr());
    }
   	return 0;
}





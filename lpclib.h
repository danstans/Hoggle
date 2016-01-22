#ifndef _LPCLIB_H
#define _LPCLIB_H

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

typedef unsigned char smallint;

template <typename T>
class Vector;

/** @file lpclib.h
 @brief LPCLib Functions
 
 All functions listed here are usable in any program
 you create using the standard LPCLib starter project,
 */ 


/** \name Reporting a Runtime Error */
/* @{ */
/**
 * Issues an error message and stops the programs.
 * @param str the error message to print
 */
void Error (string str);
/* @} */

/** \name Getting User Input */
/* @{ */

/** Gets one line of text input.
 @param src The input source, cin by default
 @return The string typed by the user */
string GetLine(istream & src=cin);

/** Gets one integer from an input source.
 @param src The input source, cin by default
 @return The integer typed by the user */
int GetInt(istream & src=cin);

/** Gets one number (not limited to an integer) from an input source.
 @param src The input source, cin by default
 @return The number typed by the user */
double GetDouble(istream & src=cin);

/* @} */

/** \name Converting Values */
/* @{ */

/** Converts the given int into a string.
 @param num The integer value to be converted
 @return A string matching the integer value given */
string IntToString(int num);

/** Converts the double double into a string.
 @param num The integer value to be converted
 @return A string matching the double value given */
string DoubleToString(double num);

/** Converts the given string into an integer value, if possible.
 @param str The string to be converted
 @return An integer value derived from the string given */
int StringToInt(string str);

/** Converts the given string into an double value, if possible.
 @param str The string to be converted
 @return A double value derived from the string given */
double StringToDouble(string str);

/** Converts the given string into all-lowercase.
 @param str The string to be converted
 @return A string identical to str, but with any letters changed to lowercase */
string ConvertToLowerCase(string str);

/** Converts the given string into all-uppsercase.
 @param str The string to be converted
 @return A string identical to str, but with any letters changed to uppercase */
string ConvertToUpperCase(string str);

/* @} */

/** \name Generating Random Values */
/* @{ */

/** Generates a random int within a range of values.
 @param low The lowest possible value generated
 @param high The highest possible value generated
 @return A random integer within the range specified */
int RandomInt(int low, int high);

/** Generates a random number within a range of values.
 @param low The lowest possible value generated
 @param high The highest possible value generated
 @return A random number within the range specified */
double RandomDouble(double low, double high);

/** Generates true/false value randomly, with a given probability.
 @param p The probability of getting a true value - a number between 0 and 1.0
 @return true or false */
bool RandomChance(double p);

/* @} */

/** \name Graphics Functions */
/* @{ */
/** Define (or redefine) a named color
 @param name The name of the color
 @param red The color's red value, 0 to 255
 @param green The color's green value, 0 to 255
 @param blue The color's blue value, 0 to 255 */
void DefineColor(string name, smallint red, smallint green, smallint blue);

/** Determine if a color with the given name is already defined
 @param name The name of the color 
 @return true if the color is defined, false if it is not */
bool ColorIsDefined(string name);

/** Print a list of the colors that are currently defined */
void ListColors();

/** Opens the main graphics window, using the given dimensions and color
    NOTE: This function must be called before doing any drawing.
 @param width The width of the window
 @param height The height of the window 
 @param color The background color of the window */
void GraphicsWindow(int width, int height, string color);

/** Update the contents of the graphics window. The
  effects of any drawing commands only become visible in the graphics
  window when UpdateDisplay() is called. */
void UpdateDisplay();

/** Retrieve the width of the graphics window.
 @return The width of the graphics window, in pixels */
int GetWidth();

/** Retrieve the height of the graphics window.
 @return The height of the graphics window, in pixels */
int GetHeight();

/** Draw a straight line between two points.
 @param x1,y1 One endpoint of the line
 @param x2,y2 The other endpoint of the line 
 @param color The color of the line (must be a color already defined) */
void DrawLine(int x1, int y1, int x2, int y2, string color);

/** Draw a rectangle.
 @param x,y The upper left corner of the rectangle
 @param width,height The dimensions of the rectangle
 @param color The color of the rectangle (must be a color already defined)
 @param filled Whether or not the rectangle is filled */
void DrawRectangle(int x, int y, int width, int height, string color, bool filled=false);

/** Draw a triangle.
 @param x1, y1 The coordinates of the first point
 @param x2, y2 The coordinates of the second point
 @param x3, y3 The coordinates of the third point
 @param color The color of the triangle (must be a color already defined)
 @param filled Whether or not the triangle is filled */
void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, string color, bool filled=false);

/** Draw a circle.
 @param x,y The coordinates of the center
 @param r The radius
 @param color The color of the circle (must be a color already defined)
 @param filled Whether or not the circle is filled */
void DrawCircle(int x, int y, int r, string color, bool filled=false);

/** Draw an elipse.
 @param x,y The coordinates of the center
 @param rx,ry The lengths of the major and minor axes
 @param color The color of the ellipse (must be a color already defined) 
 @param filled Whether or not the ellipse is filled */
void DrawEllipse(int x, int y, int rx, int ry, string color, bool filled=false);

/** Draw a filled polygon
 
 */
void DrawPolygon(Vector<int> points, string color);

/** Draw the given image in the main graphics window.
 @param imageFileName The filename of the image file. This must be inside a folder named "Images" inside the project folder
 @param x,y The location at which to draw the image. */
void DrawImage(string imageFileName, int x, int y);

/** Draw the given image in the main graphics window, scaled to specified dimensions.
 @param imageFileName The filename of the image file. This must be inside a folder named "Images" inside the project folder
 @param x,y The location at which to draw the image
 @param width, height The scaled (stretched) dimensions to use */
void DrawImage(string imageFileName, int x, int y, int width, int height);

/** Draw a text string on the graphics window.
 @param str The text to draw
 @param x,y The upper-left corner of the area where the text will be placed
 @param color The color of the text (must be a color already defined)
 @param fontsize The font size of the text */
void DrawString(string str, int x, int y, string color, int fontsize=13);

int StringWidth(string str, int fontsize=13);

/** Pause the program until the mouse button is down. */
void WaitForMouseDown();

/** Pause the program until the mouse button is up. */
void WaitForMouseUp();

/** Determine whether the mouse button is currently up or down.
 @return true if the mouse button is down, false if it is up */
bool MouseIsDown();

/** Determine the current position of the mouse pointer.
 @return The mouse pointer's x coordinate */
int MouseX();

/** Determine the current position of the mouse pointer.
 @return The mouse pointer's y coordinate */
int MouseY();

/** Gets a single character of input.
 @return The character typed by the user */
char GetChar();

/** Pause the program for a specified amount of time.
 @param seconds the amount of time to pause, in seconds */
void Pause(double seconds);

/* @} */


/** \name Secondary Image Windows */

/* @{ */

/** Displays the given image in a separate window.
 @param imageFileName The filename of the image file. This must be inside a folder named "Images" inside the project folder */
void DisplayImage(string imageFileName);

/** Displays the given image in a separate window, scaling it to the dimensions given.
 @param imageFileName The filename of the image file. This must be inside a folder named "Images" inside the project folder 
 @param width The window width
 @param height The window height */
void DisplayImage(string imageFileName, int width, int height);

/** Removes any image currently being displayed. */
void RemoveImage();

/* @} */

/** \name Controlling System Messages */
/* @{ */

/** Stops the output of extra messages from the library. */
void HideSystemMessages();

/* @} */

/** \name LPC CS Database Access */
/* @{ */
void ConnectToDB(string username, string password);
void DBInsertRecord(int ID, int authcode, string record);
Vector<string> DBRetrieveAllRecords(int ID, int authcode);
Vector<string> DBRetrieveMyRecords(int ID, int authcode);
/* @} */


// =========================================================================
// Other stuff  - client code using the library doesn't need to see this...
// =========================================================================

#define cin Error("Use of 'cin' with LPCLib is not allowed."); cin
#define main __lpclib_user_main
int __lpclib_user_main();

#endif

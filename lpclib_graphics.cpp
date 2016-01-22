#include <iostream>

#include <map>
#include "CImg.h"
#include "lpclib.h"
#include "vector.h"
using namespace cimg_library;

void PrintBanner(string s);

// Globals
CImgDisplay * imgdisplay = NULL;
CImg<unsigned char> * image = NULL;
CImgDisplay * gdisplay = NULL;
CImg<unsigned char> * gpixels = NULL;

struct _color { smallint components[3]; };
map<string, _color> _colormap;

map<string, CImg<unsigned char> *> _imagemap;

static void CheckInit()
{
    if (!gpixels)
        Error("GraphicsWindow() must be called before any drawing or mouse commands.");
}

static void ColorSetup()
{
    if (!ColorIsDefined("red"))
        DefineColor("red", 255, 0, 0);

    if (!ColorIsDefined("green"))
        DefineColor("green", 0, 255, 0);
    
    if (!ColorIsDefined("blue"))
        DefineColor("blue", 0, 0, 255);
    
    if (!ColorIsDefined("yellow"))
        DefineColor("yellow", 255, 255, 0);
    
    if (!ColorIsDefined("magenta"))
        DefineColor("magenta", 255, 0, 255);
    
    if (!ColorIsDefined("cyan"))
        DefineColor("cyan", 0, 255, 255);
    
    if (!ColorIsDefined("white"))
        DefineColor("white", 255, 255, 255);
    
    if (!ColorIsDefined("black"))
        DefineColor("black", 0, 0, 0);
}

void DefineColor(string name, smallint red, smallint green, smallint blue)
{
    _color c;
    c.components[0] = red;
    c.components[1] = green;
    c.components[2] = blue;
    _colormap[name] = c;
}

bool ColorIsDefined(string name)
{
    return (_colormap.find(name) != _colormap.end());
}

void ListColors()
{
    ColorSetup();
    map<string, _color>::iterator i = _colormap.begin();
    cout << "COLORS DEFINED\n";
    cout << "--------------\n";
    cout << "Red   Green Blue  Color Name\n";
    for ( ; i != _colormap.end(); i++)
    {
        _color c = i->second;
        printf ("%-3i   %-3i   %-3i   %s\n",
                c.components[0], c.components[1], c.components[2],
                 i->first.c_str());
    }
}
static _color GetColor(string name)
{
    if (_colormap.find(name) == _colormap.end())
    {
        Error ("You tried to use a color named '" + name + "', which is not defined.");
        return ( *((_color *) 0)); // to make compiler happy
    }
    else
        return (_colormap[name]);
}

void UpdateDisplay()
{
    gpixels->display(*gdisplay);
}

void GraphicsWindow(int width, int height, string color)
{
    ColorSetup();
    if (gpixels != NULL)
        Error ("GraphicsWindow() was already called");
    gpixels = new CImg<unsigned char>(width, height, 1, 3);
    _color c = GetColor(color);
    gpixels->draw_rectangle(0, 0, width-1, height-1, c.components);
    gdisplay = new CImgDisplay(*gpixels, "Graphics Window"); 
    gpixels->display(*gdisplay);
    if (gdisplay->window_width() != width)
        Error("Requested width " + IntToString(width) + " does not fit the screen.");
    if (gdisplay->height() != height)
        Error("Requested height " + IntToString(height) + " does not fit the screen.");
}

void DisplayImage(string imageFileName, int width, int height)
{
    imageFileName = string("Images/") + imageFileName;

    image = new CImg<unsigned char> (imageFileName.c_str());

    if (!image)
        Error (string("Could not load image '") + imageFileName
                + "'");

    if (width == -1729 && height == -1729)
    {

    }
    else if (width < 0 || height < 0)
        Error("Invalid dimensions given for image");
    else
        image->resize(width, height, -100, -100, 3);

    if (imgdisplay != NULL)
        delete imgdisplay;

    imgdisplay = new CImgDisplay(*image, "Image Window");
}


void DisplayImage(string imageFileName)
{
    DisplayImage(imageFileName, -1729, -1729);
}


void RemoveImage()
{
    if (imgdisplay)
    {
        delete imgdisplay;
        delete image;
        imgdisplay = 0;
        image = 0;
    }
}

void DrawLine(int x1, int y1, int x2, int y2, string color)
{
    gpixels->draw_line(x1, y1, x2, y2, GetColor(color).components);
    //gpixels->display(*gdisplay);
}

void DrawRectangle(int x, int y, int width, int height, string color, bool filled)
{
    CheckInit();
    _color c = GetColor(color);
    if (filled)
        gpixels->draw_rectangle(x, y, x+width, y+height, c.components);
    else
        gpixels->draw_rectangle(x, y, x+width, y+height, c.components, 1, ~0U);
    //gpixels->display(*gdisplay);
}

void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, string color, bool filled)
{
    CheckInit();
    _color c = GetColor(color);
    if (filled)
        gpixels->draw_triangle(x1, y1, x2, y2, x3, y3, c.components);
    else
        gpixels->draw_triangle(x1, y1, x2, y2, x3, y3, c.components, 1, ~0U);
    //gpixels->display(*gdisplay);
}

void DrawCircle(int x, int y, int r, string color, bool filled)
{
    CheckInit();
    _color c = GetColor(color);
    if (filled)
        gpixels->draw_circle(x, y, r, c.components);
    else
        gpixels->draw_circle(x, y, r, c.components, 1, 1);
    //gpixels->display(*gdisplay);
}

void DrawEllipse(int x, int y, int w, int h, string color, bool filled)
{
    CheckInit();
    _color c = GetColor(color);
    if (filled)
        gpixels->draw_ellipse(x, y, w, h, 0, c.components);
    else
        gpixels->draw_ellipse(x, y, w, h, 0, c.components, 1, 1);
}


void DrawImage(string imageFileName, int x, int y, int width, int height)
{
    CImg<unsigned char> * img;
    if (_imagemap.find(imageFileName) == _imagemap.end())
    {
        img = new CImg<unsigned char> ((string("Images/") + imageFileName).c_str());
        if (!img)
            Error (string("Could not load image '") + imageFileName
                   + "'");
        _imagemap[imageFileName] = img;
    }
    else
        img = _imagemap[imageFileName];
    
    if (width == -1729 && height == -1729)
        gpixels->draw_image(x, y, *img);
    else if (width < 0 || height < 0)
        Error("Invalid dimensions given for image");
    else
        gpixels->draw_image(x, y, img->get_resize(width, height));
    
    //gpixels->display(*gdisplay);
}

void DrawImage(string imageFileName, int x, int y)
{
    DrawImage(imageFileName, x, y, -1729, -1729);
}

void DrawString(string str, int x, int y, string color, int fontsize)
{
    gpixels->draw_text (x, y, str.c_str(), GetColor(color).components, NULL, 1, fontsize);
    //gpixels->display(*gdisplay);
}

int StringWidth(string str, int fontsize)
{
    CImg<> empty;
    smallint c[] = {255, 255, 255};
    empty.draw_text(0,0,str.c_str(), c, NULL, 1, fontsize);
    return empty.width();
}

void DrawPolygon(Vector<int> coords, string color)
{
    if (coords.size() % 2 != 0)
        Error("DrawPolygon called with odd number of coords");
    
    CImg<int> points(coords.size()/2, 2, 1, 1, 0);
    for (int k = 0; k < coords.size()/2; k++)
    {
        for (int which = 0; which < 2; which++)
            points(k, which) = coords[k*2+which];
    }
    gpixels->draw_polygon(points, GetColor(color).components);
}


void WaitForMouseDown()
{
    CheckInit();
    while (1)
    {
        gdisplay->wait();
        if (gdisplay->button() > 0)
            break;
    }
}

void WaitForMouseUp()
{
    CheckInit();
    while (1)
    {
        gdisplay->wait();
        if (gdisplay->button() == 0)
            break;
    }
}

int MouseX()
{
    CheckInit();
    return (gdisplay->mouse_x());
}

int MouseY()
{
    CheckInit();
    return (gdisplay->mouse_y());
}

bool MouseIsDown()
{
    return (gdisplay->button() > 0);
}

void Pause(double seconds)
{
    CheckInit();
    UpdateDisplay();
    cimg_library::cimg::sleep(seconds * 1000);
}

int GetWidth()
{
    CheckInit();
    return gpixels->width();
}

int GetHeight()
{
    CheckInit();
    return gpixels->height();
}

char GetChar()
{
    char c;
    while(1)
    { 
        gdisplay->wait();
        //cout << gdisplay->key() << endl;
        c = gdisplay->key();
        if (c > 0 && c < 128)
        {
            //cout << "Returning " << (int) c << endl;
            return (c == 13 ? '\n' : c);
        }
    }
}

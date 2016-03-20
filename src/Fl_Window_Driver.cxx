//
// "$Id$"
//
// A base class for platform specific window handling code
// for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2016 by Bill Spitzak and others.
//
// This library is free software. Distribution and use rights are outlined in
// the file "COPYING" which should have been included with this file.  If this
// file is missing or damaged, see the license at:
//
//     http://www.fltk.org/COPYING.php
//
// Please report all bugs and problems on the following page:
//
//     http://www.fltk.org/str.php
//


#include <config.h>
#include <FL/Fl_Window_Driver.H>
#include <FL/fl_draw.H>


Fl_Window_Driver::Fl_Window_Driver(Fl_Window *win) :
pWindow(win)
{
  shape_data_ = NULL;
}


Fl_Window_Driver::~Fl_Window_Driver()
{
}

int Fl_Window_Driver::minw() {return pWindow->minw;}
int Fl_Window_Driver::minh() {return pWindow->minh;}
int Fl_Window_Driver::maxw() {return pWindow->maxw;}
int Fl_Window_Driver::maxh() {return pWindow->maxh;}
unsigned char Fl_Window_Driver::size_range_set() {return pWindow->size_range_set;}

void Fl_Window_Driver::flush_single() { pWindow->Fl_Window::flush(); }
void Fl_Window_Driver::draw() { pWindow->draw(); }


void Fl_Window_Driver::take_focus()
{
  // nothing to do
}


void Fl_Window_Driver::flush_double()
{
  flush_single();
}


void Fl_Window_Driver::flush_overlay()
{
  flush_single();
}


void Fl_Window_Driver::draw_begin()
{
  // nothing to do
}


void Fl_Window_Driver::draw_end()
{
  // nothing to do
}



void Fl_Window_Driver::destroy_double_buffer() {
  Fl_X *i = Fl_X::i(pWindow);
  fl_delete_offscreen(i->other_xid);
  i->other_xid = 0;
}


/** Assigns a non-rectangular shape to the window.
 This function gives an arbitrary shape (not just a rectangular region) to an Fl_Window.
 An Fl_Image of any dimension can be used as mask; it is rescaled to the window's dimension as needed.
 
 The layout and widgets inside are unaware of the mask shape, and most will act as though the window's
 rectangular bounding box is available
 to them. It is up to you to make sure they adhere to the bounds of their masking shape.
 
 The \p img argument can be an Fl_Bitmap, Fl_Pixmap, Fl_RGB_Image or Fl_Shared_Image:
 \li With Fl_Bitmap or Fl_Pixmap, the shaped window covers the image part where bitmap bits equal one,
 or where the pixmap is not fully transparent.
 \li With an Fl_RGB_Image with an alpha channel (depths 2 or 4), the shaped window covers the image part
 that is not fully transparent.
 \li With an Fl_RGB_Image of depth 1 (gray-scale) or 3 (RGB), the shaped window covers the non-black image part.
 \li With an Fl_Shared_Image, the shape is determined by rules above applied to the underlying image.
 The shared image should not have been scaled through Fl_Shared_Image::scale().
 
 Platform details:
 \li On the unix/linux platform, the SHAPE extension of the X server is required.
 This function does control the shape of Fl_Gl_Window instances.
 \li On the MSWindows platform, this function does nothing with class Fl_Gl_Window.
 \li On the Mac platform, OS version 10.4 or above is required.
 An 8-bit shape-mask is used when \p img is an Fl_RGB_Image:
 with depths 2 or 4, the image alpha channel becomes the shape mask such that areas with alpha = 0
 are out of the shaped window;
 with depths 1 or 3, white and black are in and out of the
 shaped window, respectively, and other colors give intermediate masking scores.
 This function does nothing with class Fl_Gl_Window.
 
 The window borders and caption created by the window system are turned off by default. They
 can be re-enabled by calling Fl_Window::border(1).
 
 A usage example is found at example/shapedwindow.cxx.
 
 \version 1.3.3 (and requires compilation with FL_ABI_VERSION >= 10303)
 */
void Fl_Window::shape(const Fl_Image* img) {pWindowDriver->shape(img);}


/** Set the window's shape with an Fl_Image.
 \see void shape(const Fl_Image* img)
 */
void Fl_Window::shape(const Fl_Image& img) {pWindowDriver->shape(&img);}

/** Returns non NULL when the window has been assigned a non-rectangular shape */
int Fl_Window::is_shaped() {return pWindowDriver->shape_data_ != NULL;}

void Fl_Window_Driver::shape_pixmap_(Fl_Image* pixmap) {
  Fl_RGB_Image* rgba = new Fl_RGB_Image((Fl_Pixmap*)pixmap);
  shape_alpha_(rgba, 3);
  delete rgba;
}

void Fl_Window_Driver::capture_titlebar_and_borders(Fl_Shared_Image*& top, Fl_Shared_Image*& left, Fl_Shared_Image*& bottom, Fl_Shared_Image*& right) {
  top = left = bottom = right = NULL;
}

//
// End of "$Id$".
//

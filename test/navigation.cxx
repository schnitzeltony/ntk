//
// "$Id: navigation.cxx 8090 2010-12-21 02:37:41Z greg.ercolano $"
//
// Navigation test program for the Fast Light Tool Kit (FLTK).
//
// Silly test of navigation keys. This is not a recommended method of
// laying out your panels!
//
// Copyright 1998-2010 by Bill Spitzak and others.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA.
//
// Please report all bugs and problems on the following page:
//
//     http://www.fltk.org/str.php
//

#include <stdio.h>
#include <stdlib.h>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Light_Button.H>

#define WIDTH 600
#define HEIGHT 300
#define GRID 25

void ToggleArrowFocus_CB(Fl_Widget *w, void*) {
  Fl_Light_Button *b = (Fl_Light_Button*)w;
  Fl::option(Fl::OPTION_ARROW_FOCUS, b->value() ? true : false);
}
int main(int argc, char **argv) {
  if (argc > 1) srand(atoi(argv[1]));
  Fl_Window window(WIDTH,HEIGHT+40,argv[0]);
    // Include a toggle button to control arrow focus
    Fl_Light_Button arrowfocus_butt(10,HEIGHT+10,130,20," Arrow Focus");
    arrowfocus_butt.callback(ToggleArrowFocus_CB);
    arrowfocus_butt.value(Fl::option(Fl::OPTION_ARROW_FOCUS) ? 1 : 0);	// use default
    arrowfocus_butt.tooltip("Control horizontal arrow key focus navigation behavior.\n"
                            "e.g. Fl::OPTION_ARROW_FOCUS");
  window.end(); // don't auto-add children
  for (int i = 0; i<10000; i++) {
    // make up a random size of widget:
    int x = rand()%(WIDTH/GRID+1) * GRID;
    int y = rand()%(HEIGHT/GRID+1) * GRID;
    int w = rand()%(WIDTH/GRID+1) * GRID;
    if (w < x) {w = x-w; x-=w;} else {w = w-x;}
    int h = rand()%(HEIGHT/GRID+1) * GRID;
    if (h < y) {h = y-h; y-=h;} else {h = h-y;}
    if (w < GRID || h < GRID || w < h) continue;
    // find where to insert it and see if it intersects something:
    Fl_Widget *j = 0;
    int n; for (n=0; n < window.children(); n++) {
      Fl_Widget *o = window.child(n);
      if (x<o->x()+o->w() && x+w>o->x() &&
	  y<o->y()+o->h() && y+h>o->y()) break;
      if ( !j && ( y<o->y() || (y==o->y() && x<o->x()) ) ) j = o;
    }
    // skip if intersection:
    if (n < window.children()) continue;
    window.insert(*(new Fl_Input(x,y,w,h)),j);
  }
  window.show(argc, argv);
  return Fl::run();
}

//
// End of "$Id: navigation.cxx 8090 2010-12-21 02:37:41Z greg.ercolano $".
//

#ifndef TRAILER_WINDOW
#define TRAILER_WINDOW

#include <iostream>
using namespace std;
#include <gstreamer-1.0/gst/gst.h>
#include <string.h>


class TrailerWindow {
    public:
        TrailerWindow();
        ~TrailerWindow();
        static int run(string url);

};

#endif
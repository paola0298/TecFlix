#ifndef TRAILER_WINDOW
#define TRAILER_WINDOW

#include <iostream>
using namespace std;
#include <gstreamer-1.0/gst/gst.h>


class TrailerWindow {
    public:
        TrailerWindow();
        ~TrailerWindow();
        static void run(string url);

};

#endif
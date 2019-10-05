#ifndef SCROLL_WINDOW
#define SCROLL_WINDOW

#include <gtkmm-3.0/gtkmm/window.h>
#include <gtkmm-3.0/gtkmm/scrolledwindow.h>
#include <gtkmm-3.0/gtkmm/flowbox.h>
#include <gtkmm-3.0/gtkmm/label.h>
#include <gtkmm-3.0/gtkmm/box.h>
#include <gtkmm-3.0/gtkmm/button.h>
#include <gtkmm-3.0/gtkmm/image.h>
#include <gtkmm-3.0/gtkmm/application.h>
#include <iostream>
#include <thread>
#include "../Logic/ReadCSV.cpp"
#include "InfoWindow.cpp"
#include <iostream>
using namespace std;


class ScrollWindow : public Gtk::Window {
    public:
        ScrollWindow();
        virtual ~ScrollWindow();
        static void run();
    
    private:
        Gtk::Box mainContainer;
        Gtk::Box upperContainer;
        Gtk::ScrolledWindow scrollContainer;
        Gtk::FlowBox posterContainer;
        Gtk::Label title;
        Gtk::Label memory;
        Gtk::Label memoryData;
        CSVReader reader;
        vector<Movie> moviesVector;
        vector<string> postersVector;
        vector<string> summaryVector;
        vector<Gtk::Button*> buttonVector;
        vector<string> dataList;

        string actualImagePath;
        string actualSinopsis;
        bool first = true;
        int totalPosters = 0;
        bool isRunning = true;

        void loadData();
        void clearContainer();
        void showPosters();
        void openInfoWindow(int index);
        void showImageThread();
        void addToWindowThread();
        void threadController();
        void controller();
        bool releaseMemory();
        void addImageToContainer(string imagePath, int index);
        Glib::RefPtr<Gdk::Pixbuf> load_image(std::string path, int width, int height);
};

#endif
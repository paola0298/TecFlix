#ifndef PAGINATION_WINDOW
#define PAGINATION_WINDOW

#include <gtkmm-3.0/gtkmm/window.h>
#include <gtkmm-3.0/gtkmm/flowbox.h>
#include <gtkmm-3.0/gtkmm/label.h>
#include <gtkmm-3.0/gtkmm/box.h>
#include <gtkmm-3.0/gtkmm/button.h>
#include <gtkmm-3.0/gtkmm/image.h>
#include <gtkmm-3.0/gtkmm/application.h>
#include "NoPagination.cpp"
#include <iostream>
#include <thread>
#include <future>

// #include <filesystem>
// #include <fstream>
// #define BOOST_NO_CXX11_SCOPED_ENUMS
// #include <boost/filesystem.hpp>
// #undef BOOST_NO_CXX11_SCOPED_ENUMS
using namespace std;

class PaginationWindow : public Gtk::Window {
    public:
        PaginationWindow();
        ~PaginationWindow();
        static void run();

    private:
        int start;
        int end;
        int actualPage;
        int lastPageShow;
        string actualImagePath;
        string actualSinopsis;
        vector<string> dataList;
        Gtk::Box mainContainer;
        Gtk::Box upperContainer;
        Gtk::Box paginationContainer;
        Gtk::FlowBox posterContainer;
        Gtk::Label title;
        Gtk::Label memory;
        Gtk::Label memoryData;
        CSVReader reader;
        // LinkedList<Movie> *listOfMovies;
        vector<Movie> moviesVector;
        vector<string> sinopsisVector;
        vector<string> imagePathVector;
        vector<Gtk::Image*> widgetButton;
        
        
        void downloadData(string html, int index);
        void download(int initial);
        void releaseMemoryBack();
        void test();
        void loadData();
        void loadPages();
        void showPosters(int page=1);
        void openInfoWindow(Movie actualMovie);
        void clearContainer();
        void showDataThread(int initial);
        static Glib::RefPtr<Gdk::Pixbuf> load_image(std::string path, int width, int height);
};

#endif
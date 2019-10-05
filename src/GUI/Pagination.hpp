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

using namespace std;

class PaginationWindow : public Gtk::Window {
    public:
        PaginationWindow();
        ~PaginationWindow();
        static void run();

    private:
        Gtk::Box mainContainer;
        Gtk::Box upperContainer;
        Gtk::Box paginationContainer;
        Gtk::FlowBox posterContainer;
        Gtk::Label title;
        Gtk::Label memory;
        Gtk::Label memoryData;
        CSVReader reader;

        int totalPosters = 1;
        int actualPage = 0;
        int lastPage = 0;
        int lastPageShow = 10;
        string actualImagePath;
        string actualSinopsis;
        vector<string> imagePathVector;
        vector<string> dataList;
        vector<string> sinopsisVector;


        void loadPages();
        void showPosters(int page=1);
        void clearContainer();
        void loadData();
        bool releaseMemory();
        void downloadData(string html, int index);
        void addImageToContainer(string imagePath, int index);
        void openInfoWindow(int initial);
        void downloadImagesThread(int initial);
        void downloadImages(int initial);
        void updatePages();
        static Glib::RefPtr<Gdk::Pixbuf> load_image(std::string path, int width, int height);




        int startt = 1;
        int endd = 17;
        int actualPagee = 1;
        int *start = &startt;
        int *end = &endd;        
        
        // LinkedList<Movie> *listOfMovies;
        vector<Movie> moviesVector;
        
        vector<Gtk::Image*> widgetButton;

        
};

#endif
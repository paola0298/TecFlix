 #ifndef NO_PAGINATION
 #define NO_PAGINATION

 #include <gtkmm-3.0/gtkmm/window.h>
 #include <gtkmm-3.0/gtkmm/scrolledwindow.h>
 #include <gtkmm-3.0/gtkmm/flowbox.h>
 #include <gtkmm-3.0/gtkmm/label.h>
 #include <gtkmm-3.0/gtkmm/box.h>
 #include <gtkmm-3.0/gtkmm/button.h>
 #include <gtkmm-3.0/gtkmm/image.h>
 #include <gtkmm-3.0/gtkmm/application.h>
 #include <iostream>
 #include "../Logic/ReadCSV.cpp"
 #include "../Logic/HTMLManagement.cpp"
 #include "InfoWindow.cpp"
 using namespace std;

class NoPaginationWindow : public Gtk::Window {
    public:
        NoPaginationWindow();
        virtual ~NoPaginationWindow();
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
        vector<Movie> listOfMovies;
        
        void test();
        void loadData();
        void showPosters();
        void openInfoWindow(Movie actualMovie);
        static Glib::RefPtr<Gdk::Pixbuf> load_image(std::string path, int width, int height);
};

 #endif
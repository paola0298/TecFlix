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
 #include "../Logic/ReadCSV.cpp"
 #include "../Logic/Movie.cpp"
 #include "../Structures/LinkedList.cpp"
 #include "../Logic/HTMLManagement.cpp"
 #include "InfoWindow.cpp"
 #include <iostream>
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
        LinkedList<Movie> *listOfMovies;
        
        void loadData();
        void showPosters();
        void openInfoWindow(Movie actualMovie);
        Glib::RefPtr<Gdk::Pixbuf> load_image(std::string path, int width, int height);
};

 #endif
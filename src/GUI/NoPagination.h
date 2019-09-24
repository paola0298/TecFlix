 #ifndef NO_PAGINATION
 #define NO_PAGINATION

 #include <gtkmm-3.0/gtkmm/window.h>
 #include <gtkmm-3.0/gtkmm/scrolledwindow.h>
 #include <gtkmm-3.0/gtkmm/flowbox.h>
 #include <gtkmm-3.0/gtkmm/label.h>
 #include <gtkmm-3.0/gtkmm/box.h>
 #include "../Logic/ReadCSV.cpp"
 #include "../Logic/Movie.cpp"

 #include <iostream>
 using namespace std;

class NoPaginationWindow : public Gtk::Window {
    public:
        NoPaginationWindow();
        virtual ~NoPaginationWindow();

    private:
        Gtk::Box mainContainer;
        Gtk::Box upperContainer;
        Gtk::ScrolledWindow scrollContainer;
        Gtk::FlowBox posterContainer;
        Gtk::Label title;
        Gtk::Label memory;
        Gtk::Label memoryData;
        CSVReader reader;

        void loadData();
};

 #endif
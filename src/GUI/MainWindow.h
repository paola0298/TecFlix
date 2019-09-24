#ifndef MAIN_WINDOW
#define MAIN_WINDOW

#include <gtkmm-3.0/gtkmm/box.h>
#include <gtkmm-3.0/gtkmm/button.h>
#include <gtkmm-3.0/gtkmm/image.h>
#include <gtkmm-3.0/gtkmm/window.h>
#include <gtkmm-3.0/gtkmm/application.h>
#include <iostream>
using namespace std;


class MainWindow : public Gtk::Window {
    public:
        MainWindow();
        virtual ~MainWindow();

    private:

        Gtk::Box mainContainer;
        Gtk::Button pagination;
        Gtk::Button noPagination;
        Gtk::Button scroll;

        Gtk::Image paginationImage;
        Gtk::Image noPaginationImage;
        Gtk::Image scrollImage;

        void openPaginationWindow();
        void openNoPaginationWindow();
        void openScrollWindow();
         Glib::RefPtr<Gdk::Pixbuf> load_image(std::string path, int width, int height);

};

#endif
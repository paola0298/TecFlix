#ifndef TAREA_GUI_H
#define TAREA_GUI_H

#include <gtkmm-3.0/gtkmm/box.h>
#include <gtkmm-3.0/gtkmm/button.h>
#include <gtkmm-3.0/gtkmm/window.h>
#include <gtkmm-3.0/gtkmm/label.h>
#include <gtkmm-3.0/gtkmm/entry.h>
#include <gtkmm-3.0/gtkmm/radiobutton.h>

class TecFlix : public Gtk::Window {
public:
    TecFlix();
    virtual ~TecFlix();

protected:

    // Signal handlers:
    // Our new improved on_button_clicked(). (see below)
    void on_button_clicked(Glib::ustring data);
    Glib::RefPtr<Gdk::Pixbuf> load_image(std::string path, int width, int height);

    // Child widgets:
    Gtk::Box mainContainer;
    Gtk::Box tittleContainer;
    Gtk::Box headerContainer;
    Gtk::Box movieContainer;
    Gtk::Box movieContainer1;
    Gtk::Box movieContainer2;
    Gtk::Box paginationContainer;
 
    Gtk::Label option;
    Gtk::Label tittle;
    Gtk::Label memory;
    Gtk::RadioButton noPaginacionRB, paginacionRB, tradicionalRB, scrollRB;



    Gtk::Button movie1;
    Gtk::Button movie2;
    Gtk::Button movie3;
    Gtk::Button movie4;
    Gtk::Button movie5;
    Gtk::Button movie6;
    Gtk::Button movie7;
    Gtk::Button movie8;
    Gtk::Button movie9;
    Gtk::Button movie10;
    Gtk::Image image1;
    Gtk::Image image2;
    Gtk::Image image3;
    Gtk::Image image4;
    Gtk::Image image5;
    Gtk::Image image6;
    Gtk::Image image7;
    Gtk::Image image8;
    Gtk::Image image9;
    Gtk::Image image10;
    

};

#endif //TAREA_GUI_H

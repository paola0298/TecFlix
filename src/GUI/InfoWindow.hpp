#ifndef INFO_WINDOW
#define INFO_WINDOW

#include <gtkmm-3.0/gtkmm/box.h>
#include <gtkmm-3.0/gtkmm/button.h>
#include <gtkmm-3.0/gtkmm/window.h>
#include <gtkmm-3.0/gtkmm/label.h>
#include <gtkmm-3.0/gtkmm/entry.h>
#include <iostream>
#include "TrailerWindow.cpp"
// #include "../Logic/Movie.cpp"

class InfoWindow: public Gtk::Window {
    public:
        InfoWindow();
        virtual ~InfoWindow();
        void static run(Movie actualMovie);

    private:

        void loadInformation(Movie record);
        void playTrailer();
        Glib::RefPtr<Gdk::Pixbuf> load_image(std::string path, int width, int height);
        

        Gtk::Box mainContainerI; //HBox
        Gtk::Box rightContainer; //VBox
        Gtk::Box leftContainer; //VBox
        Gtk::Box durationContainer; //HBox
        Gtk::Box directorContainer;
        Gtk::Box genresContainer;
        Gtk::Box scoreContainer;
        Gtk::Box actorsContainer;
        Gtk::Box languageContainer;
        Gtk::Box keywordsContainer;

        Gtk::Image moviePoster;
        Gtk::Image playImage;
        Gtk::Button playButton;
        Gtk::Label movieTittle;

        Gtk::Label tittleYear;
        Gtk::Label tittleYearInfo;

        Gtk::Label imdbScore;
        Gtk::Label imdbScoreInfo;

        Gtk::Label duration;
        Gtk::Label durationInfo;

        Gtk::Label sinopsis;
        Gtk::Label sinopsisInfo;
        
        Gtk::Label directorName;
        Gtk::Label directorNameInfo;

        Gtk::Label genres;
        Gtk::Label genresInfo;

        Gtk::Label actorsNames;
        Gtk::Label actorsNamesInfo;

        Gtk::Label language;
        Gtk::Label languageInfo;

        Gtk::Label plotKeywords;
        Gtk::Label plotKeywordsInfo;
};

#endif


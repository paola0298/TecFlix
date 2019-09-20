#ifndef TAREA_GUI_H
#define TAREA_GUI_H

#include <gtkmm-3.0/gtkmm/box.h>
#include <gtkmm-3.0/gtkmm/button.h>
#include <gtkmm-3.0/gtkmm/window.h>
#include <gtkmm-3.0/gtkmm/label.h>
#include <gtkmm-3.0/gtkmm/entry.h>

class InfoWindow : public Gtk::Window {
    public:
        InfoWindow();
        virtual ~InfoWindow();

    protected:

        void playTrailer();
        void loadInformation();

        Gtk::Box mainContainer; //HBox
        Gtk::Box rightContainer; //VBox
        Gtk::Box leftContainer; //VBox

        Gtk::Image moviePoster;
        Gtk::Image playImage;
        Gtk::Button playButton;

        Gtk::Label movieTittle;
        Gtk::Label sinopsis;
        Gtk::Label sinopsisInfo;
        Gtk::Label duration;
        Gtk::Label durationInfo;
        Gtk::Label directorName;
        Gtk::Label directorNameInfo;
        Gtk::Label genres;
        Gtk::Label genresInfo;
        Gtk::Label imdbScore;
        Gtk::Label imdbScoreInfo;
        Gtk::Label tittleYear;
        Gtk::Label tittleYearInfo;
        Gtk::Label autorsNames;
        Gtk::Label autorsNamesInfo;
        Gtk::Label language;
        Gtk::Label languageInfo;
        Gtk::Label plotKeywords;
        Gtk::Label plotKeywordsInfo;

        std::vector<std::string> record;
};

#endif //TAREA_GUI_H

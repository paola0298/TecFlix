#include "InfoWindow.h"
#include <iostream>


InfoWindow::InfoWindow():
mainContainerI(Gtk::ORIENTATION_HORIZONTAL, 0),
rightContainer(Gtk::ORIENTATION_VERTICAL, 0),
leftContainer(Gtk::ORIENTATION_VERTICAL, 0),
durationContainer(Gtk::ORIENTATION_HORIZONTAL, 0),
sinopsis("Sinopsis: "), duration("Duracion: "),
directorName("Director"), genres("Generos: "),
imdbScore("Puntuacion: "), tittleYear("Anio de lanzamiento: "),
actorsNames("Nombres de los actores: "), language("Idioma: "),
plotKeywords("Palabras clave: ") {

    add(mainContainerI);
    mainContainerI.pack_start(leftContainer, false, false, 10);
    mainContainerI.pack_start(rightContainer, false, false, 10);

    leftContainer.pack_start(movieTittle, false, false, 10);
    leftContainer.pack_start(playButton, false, false, 10);
    leftContainer.set_halign(Gtk::ALIGN_CENTER);

    rightContainer.pack_start(tittleYearInfo);

    scoreContainer.pack_start(imdbScore, false, false, 10);
    scoreContainer.pack_start(imdbScoreInfo, false, false, 10);

    durationContainer.pack_start(duration, false, false, 10);
    durationContainer.pack_start(durationInfo, false, false, 10);

    rightContainer.pack_start(scoreContainer, false, false, 10);
    rightContainer.pack_start(durationContainer, false, false, 0);

    rightContainer.pack_start(sinopsis, false, false, 0);
    rightContainer.pack_start(sinopsisInfo, false, false, 0);

    directorContainer.pack_start(directorName, false, false, 10);
    directorContainer.pack_start(directorNameInfo, false, false, 0);

    genresContainer.pack_start(genres, false, false, 10);
    genresContainer.pack_start(genresInfo, false, false, 0);

    actorsContainer.pack_start(actorsNames, false, false, 10);
    actorsContainer.pack_start(actorsNamesInfo, false, false, 0);

    languageContainer.pack_start(language, false, false, 10);
    languageContainer.pack_start(languageInfo, false, false, 0);

    keywordsContainer.pack_start(plotKeywords, false, false, 10);
    keywordsContainer.pack_start(plotKeywordsInfo, false, false, 0);

    rightContainer.pack_start(directorContainer, false, false, 10);
    rightContainer.pack_start(genresContainer, false, false, 10);
    rightContainer.pack_start(actorsContainer, false, false, 10);
    rightContainer.pack_start(languageContainer, false, false, 10);
    rightContainer.pack_start(keywordsContainer, false, false, 10);

    

    show_all_children();
}

InfoWindow::~InfoWindow() { }

void InfoWindow::playTrailer() {
    std::cout << "Playing trailer...\n";
}

int InfoWindow::run(std::vector<std::string> record) {
    auto app = Gtk::Application::create();
    InfoWindow info;
    info.loadInformation(record);
    return app->run(info);
}

void InfoWindow::loadInformation(std::vector<std::string> record) {
    std::cout << "Loading information...\n";
    std::string movieTitle = record[11]; 
    std::string year = record[23];
    std::string score = record[25];
    std::string duration = record[3];
    // std::string sinopis = record;
    std::string director =  record[1];
    std::string genres = record[9];
    std::string actor1 =  record[10];
    std::string actor2 =  record[6];
    std::string actor3 =  record[14];
    std::string language =  record[19];
    std::string keywords =  record[16];
    std::string url = record[17];
    std::string actors = actor1 + ", " + actor2 + ", " + actor3;
    moviePoster = Gtk::Image(
        load_image("/home/paola/Documents/II Semestre 2019/Algoritmos y Estructuras de Datos II/Proyectos programados/TecFlix/res/avengers.jpg", 
        215, 290));
    playButton.set_image(moviePoster);
    

     movieTittle.set_text(movieTitle);
     tittleYearInfo.set_text(year);
     imdbScoreInfo.set_text(score);
     durationInfo.set_text(duration);
     directorNameInfo.set_text(director);
     genresInfo.set_text(genres);
     actorsNamesInfo.set_text(actors);
     languageInfo.set_text(language);
     plotKeywordsInfo.set_text(keywords);
}

Glib::RefPtr<Gdk::Pixbuf> InfoWindow::load_image(std::string path, int width, int height) {
    return Gdk::Pixbuf::create_from_file(path, width, height);
}
#include "InfoWindow.h"
#include <iostream>

InfoWindow::InfoWindow():
mainContainer(Gtk::ORIENTATION_HORIZONTAL, 0),
rightContainer(Gtk::ORIENTATION_VERTICAL, 0),
leftContainer(Gtk::ORIENTATION_VERTICAL, 0),
sinopsis("Sinopsis"), duration("Duracion"),
directorName("Director"), genres("Generos"),
imdbScore("Puntuacion"), tittleYear("Anio de lanzamiento"),
autorsNames("Nombres de los autores"), language("Idioma"),
plotKeywords("Palabras clave") {

    add(mainContainer);
    mainContainer.pack_start(leftContainer, false, false, 10);
    mainContainer.pack_start(rightContainer, false, false, 10);

    leftContainer.pack_start(movieTittle, false, false, 10);
    leftContainer.pack_start(moviePoster, false, false, 10);
    leftContainer.pack_start(playButton, false, false, 10);

    

    loadInformation();
    show_all_children();
}

InfoWindow::~InfoWindow() { }

void InfoWindow::playTrailer() {
    std::cout << "Playing trailer...\n";
}

void InfoWindow::loadInformation() {
    std::cout << "Loading information...\n";

}
#include "InfoWindow.h"

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
    rightContainer.pack_start(sinopsisInfo, true, true, 0);

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

    playButton.signal_clicked().connect(sigc::mem_fun(*this, 
        &InfoWindow::playTrailer));
    
    sinopsisInfo.set_line_wrap();
    show_all_children();
}

InfoWindow::~InfoWindow() { }

void InfoWindow::playTrailer() {
    std::cout << "Playing trailer...\n";
    TrailerWindow::run("https://imdb-video.media-imdb.com/vi1822465049/MV5BY2NlMmJmMmQtMmNjZi00N2VhLWJlZDgtYTZjMjEzYTliNmEwXkExMV5BbXA0XkFpbWRiLWV0cy10cmFuc2NvZGU@.mp4?Expires=1569449713&Signature=uwjxplg-1DB3tkNbYyaVe6cWxixcXGgjK4xFzDNabDZM0gN3~7EYbUKlCMwOedZPBPqIp3uWQwMujaiXUnE0Wz~NgKNeNHC0lwPy4EYdlLTJ5Y~RAsFNIi61lmDsFBd12xTUScou4ZYAOndkh3fSJ6j9XE4wL5-LOascxww6bHiC1ZgdD~kAVFF1ZxL~f782dYvsDC2p8L-CxsHNYrKNjtdreNbU5V9iJLnwMZ7TXL-eXUwTCLoJyryFLUpe7-ArwHec-RMG04dnk9JsjKBe30Pi~H72TY95BEuy65eNlZAiXBMx8NCxD~Ur47~ny~3qUAg1XYhjHt64RvLAvNkB2A__&Key-Pair-Id=APKAIFLZBVQZ24NQH3KA");

}

void InfoWindow::run(Movie actualMovie) {
    auto app = Gtk::Application::create();
    static InfoWindow infoWin;
    infoWin.loadInformation(actualMovie);
    // app->run(infoWin);
    infoWin.show();
}

void InfoWindow::loadInformation(Movie actualMovie) {
    std::cout << "Loading information...\n";
    moviePoster = Gtk::Image(
        load_image(actualMovie.posterDir, 215, 290));
    playButton.set_image(moviePoster);

     movieTittle.set_text(actualMovie.movieTitle);
     tittleYearInfo.set_text(actualMovie.year);
     imdbScoreInfo.set_text(actualMovie.score);
     durationInfo.set_text(actualMovie.duration);
     directorNameInfo.set_text(actualMovie.director);
     genresInfo.set_text(actualMovie.genres);
     actorsNamesInfo.set_text(actualMovie.actors);
     languageInfo.set_text(actualMovie.language);
     plotKeywordsInfo.set_text(actualMovie.keywords);
     sinopsisInfo.set_text(actualMovie.sinopsis);
}

Glib::RefPtr<Gdk::Pixbuf> InfoWindow::load_image(std::string path, int width, int height) {
    return Gdk::Pixbuf::create_from_file(path, width, height);
}
#include "InfoWindow.hpp"

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
    
    sinopsisInfo.set_line_wrap();
    show_all_children();
}

InfoWindow::~InfoWindow() { }

void InfoWindow::playTrailer(string movieTitle) {
    
    HTMLManagement htmlObj;
    string url = htmlObj.getTrailerLink(movieTitle.c_str());
    // std::cout << "url of trailer: " << url << ".\n";
    std::cout << "Playing trailer of " << movieTitle << "\n";
    if (url != "") {
        cout << "Playing trailer...\n";
        url = "http://" + url;
        
        // TrailerWindow::run("es.vid.web.acsta.net//nmedia//s3_ES//35//18//68//50//35//18915989_sd_013.mp4");
        TrailerWindow::run(url);
    }

}

void InfoWindow::run(Movie actualMovie, string path, string summary) {
    auto app = Gtk::Application::create();
    static InfoWindow infoWin;
    infoWin.loadInformation(actualMovie, path, summary);
    // app->run(infoWin);
    infoWin.show();
}

void InfoWindow::loadInformation(Movie actualMovie, string path, string summary) {
    // std::cout << "Loading information...\n";
    string movieTitle = actualMovie.movieTitle;

    moviePoster = Gtk::Image(load_image(path, 215, 290));
    playButton.set_image(moviePoster);
    playButton.signal_clicked().connect(sigc::bind<string>(sigc::mem_fun(*this, &InfoWindow::playTrailer), movieTitle));
         

     movieTittle.set_text(movieTitle);
     tittleYearInfo.set_text(actualMovie.year);
     imdbScoreInfo.set_text(actualMovie.score);
     durationInfo.set_text(actualMovie.duration);
     directorNameInfo.set_text(actualMovie.director);
     genresInfo.set_text(actualMovie.genres);
     actorsNamesInfo.set_text(actualMovie.actors);
     languageInfo.set_text(actualMovie.language);
     plotKeywordsInfo.set_text(actualMovie.keywords);
     sinopsisInfo.set_text(summary);
}

Glib::RefPtr<Gdk::Pixbuf> InfoWindow::load_image(std::string path, int width, int height) {
    return Gdk::Pixbuf::create_from_file(path, width, height);
}

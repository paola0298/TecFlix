#include "NoPagination.hpp"

NoPaginationWindow::NoPaginationWindow() : 
title("Bienvenido a TecFlix"),
mainContainer(Gtk::ORIENTATION_VERTICAL),
upperContainer(Gtk::ORIENTATION_HORIZONTAL),
memory("Uso de memoria: "), 
reader("/home/paola/Documents/II Semestre 2019/Algoritmos y Estructuras de Datos II/Proyectos programados/TecFlix/res/movie_metadata.csv") {
    
    listOfMovies = new LinkedList<Movie>;
    set_title("TecFlix");
    set_border_width(10);
    add(mainContainer);

    mainContainer.pack_start(upperContainer, false, false, 10);
    mainContainer.pack_start(scrollContainer, true, true, 10);

    upperContainer.pack_start(title, false, false, 400);
    upperContainer.pack_start(memory, false, false, 0);
    upperContainer.pack_start(memoryData, false, false, 0);

    // upperContainer.set_size_request(1000, 25);

    scrollContainer.add(posterContainer);
    // scrollContainer.set_size_request(1000, 565);
    scrollContainer.set_policy(Gtk::PolicyType::POLICY_NEVER, Gtk::PolicyType::POLICY_AUTOMATIC);

    // posterContainer.set_max_children_per_line(5);
    loadData();
    showPosters();
    show_all_children();
}

NoPaginationWindow::~NoPaginationWindow() { }

void NoPaginationWindow::loadData() {
    cout << "Loading data from csv file\n";
    
    vector<string> dataList = reader.getData(0, 0, true);
    cout << "Size of datalist: " << dataList.size() << "\n";
    // vector<string> record = reader.getRecord(dataList.size()-1, dataList);

    // for (int i=1; i<dataList.size(); i++) {
    for (int i=1; i<5; i++) {
        cout << "indice " << i << "\n";
        vector<string> record = reader.getRecord(i, dataList);
        string movieTitle = record[11]; 
        string year = record[23];
        string score = record[25];
        string duration = record[3];
        string director =  record[1];
        string genres = record[9];
        string actor1 =  record[10];
        string actor2 =  record[6];
        string actor3 =  record[14];
        string language =  record[19];
        string keywords =  record[16];
        string url = record[17];
        string actors = actor1 + ", " + actor2 + ", " + actor3;

        HTMLManagement html;
        string stringHtml = html.getHTML(url);
        string sinopsis = html.getSummary(stringHtml);
        string imagePath = html.getPosterPath(stringHtml, to_string(i));
        string trailerLink = html.getTrailerLink(stringHtml);

        Movie movie(movieTitle, year, score, duration, sinopsis, director, genres, 
        actors, language, keywords, trailerLink, imagePath);

        listOfMovies->insertEnd(movie);
    }

    cout << "List size: " << listOfMovies->getSize() << "\n";
}

void NoPaginationWindow::showPosters() {
    for (int i=0; i<listOfMovies->getSize(); i++) {
        Movie actualMovie = listOfMovies->getValueAtPos(i); 
        string imagePath = actualMovie.posterDir;
        Gtk::Button *buttonImage = new Gtk::Button();
        Gtk::Image *imageButton = new Gtk::Image(load_image(imagePath, 215, 290));
        buttonImage->set_image(*imageButton);

        posterContainer.add(*buttonImage);
        buttonImage->signal_clicked().connect(sigc::bind<Movie>(sigc::mem_fun(*this,
            &NoPaginationWindow::openInfoWindow), actualMovie));

        // buttonImage->signal_clicked().connect(sigc::mem_fun(*this, 
        //     &NoPaginationWindow::openInfoWindow));
        posterContainer.show_all_children();
    }
}

void NoPaginationWindow::openInfoWindow(Movie actualMovie) {
    cout << "Movie Name: " << actualMovie.movieTitle << "\n";
    InfoWindow::run(actualMovie);
}

void NoPaginationWindow::run() {
    auto app = Gtk::Application::create();
    static NoPaginationWindow noPaginationWin;
    noPaginationWin.set_default_size(1000,600);
    app->run(noPaginationWin);
}

Glib::RefPtr<Gdk::Pixbuf> NoPaginationWindow::load_image(std::string path, int width, int height) {
    return Gdk::Pixbuf::create_from_file(path, width, height);
}
#include "Pagination.hpp"

PaginationWindow::~PaginationWindow() { }

PaginationWindow::PaginationWindow() : 
title("Bienvenido a TecFlix"),
mainContainer(Gtk::ORIENTATION_VERTICAL),
upperContainer(Gtk::ORIENTATION_HORIZONTAL),
paginationContainer(Gtk::ORIENTATION_HORIZONTAL),
memory("Uso de memoria"),
reader("/home/paola/Documents/II Semestre 2019/Algoritmos y Estructuras de Datos II/Proyectos programados/TecFlix/res/movie_metadata.csv") {
    set_title("TecFlix");
    set_border_width(10);
    add(mainContainer);

    //Packing main container widgets
    mainContainer.pack_start(upperContainer, false, false, 10);
    mainContainer.pack_start(posterContainer, true, true, 10);
    mainContainer.pack_end(paginationContainer, false, false, 5);

    //Packing upper container widgets
    upperContainer.pack_start(title, false, false, 400);
    upperContainer.pack_start(memory, false, false, 0);
    upperContainer.pack_start(memoryData, false, false, 0);

    //settings to containers
    upperContainer.set_size_request(1000, 25);
    posterContainer.set_size_request(1000, 565);
    paginationContainer.set_size_request(1000, 10);

    paginationContainer.set_halign(Gtk::ALIGN_CENTER);

    loadPages();
    show_all_children();

}


void PaginationWindow::loadData() {
    cout << "Loading data... \n";
    if (actualPage > 2) {
        bool memoryReleased = releaseMemory();
        if (memoryReleased)
            cout << "Memory released correctly \n";
    }
    int i = 0;
    if (actualPage == 1) {
        dataList = reader.getData(0, 16);
        i = 1;
    } else
        dataList = reader.getData(totalPosters, totalPosters+8);
    
    for (i; i<dataList.size(); i++) {
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

        cout << "Adding " << movieTitle << ", to list of movies...\n";
        Movie movie(movieTitle, year, score, duration, "", director, genres, 
        actors, language, keywords, "", "");
        movie.index = totalPosters;
        movie.url = url;
        moviesVector.push_back(movie);
        totalPosters++;
    }
}

bool PaginationWindow::releaseMemory() {
    cout << "Freeing memory...\n";
    std::cout << "Vector movie size before " << moviesVector.size() << "\n";
    std::cout << "Vector image size before " << imagePathVector.size() << "\n\n";
    for (int i=0; i<9; i++) {
        moviesVector.erase(moviesVector.begin()+i);
        imagePathVector.erase(imagePathVector.begin()+i);
    }

    std::cout << "Vector movie size after " << moviesVector.size() << "\n";
    std::cout << "Vector image size after " << imagePathVector.size() << "\n\n";

    return moviesVector.size() == imagePathVector.size();
}

void PaginationWindow::downloadData(string html, int index){
    cout << "Downloading image and summary... \n";
    HTMLManagement htmlObj;
    actualImagePath = htmlObj.getPosterPath(html, to_string(index));
    actualSinopsis = htmlObj.getSummary(html);
}

void PaginationWindow::loadPages() {
    // TODO verificar si la pagina actual es la ultima pagina mostrada
    cout << "Loading pages... \n";
    for (int i=1; i<lastPageShow+1; i++) {
        Gtk::Button *page = new Gtk::Button(to_string(i));
        page->signal_clicked().connect(sigc::bind<int>(
            sigc::mem_fun(*this, &PaginationWindow::showPosters), i));
        paginationContainer.pack_start(*page, false, false, 5);
    }

    paginationContainer.show_all_children();
}

void PaginationWindow::showPosters(int page) {
    clearContainer();
    //TODO verificar si pagina presionada es menor que la que estaba antes
    cout << "Showing posters on window\n";
    lastPage = actualPage;
    actualPage = page;

    loadData();

    int moviesVectorSize  = moviesVector.size();
    int initial = 0;
    int stopParameter;


    if (page == 1) {
         stopParameter = (moviesVectorSize/2)*page;
         //TODO colocar en hilo para verificar si se pude ir cargando las imagenes
         //una por una
         for (initial; initial<stopParameter; initial++) {
            Movie actualMovie = moviesVector[initial];
            string url = actualMovie.url;
            int index = actualMovie.index;
            HTMLManagement htmlObj;
            string htmlData = htmlObj.getHTML(url);
            cout << "Downloading image for movie " << actualMovie.movieTitle << "\n";
            downloadData(htmlData, index);
            imagePathVector.push_back(actualImagePath);
            addImageToContainer(actualImagePath, initial);

         }
    } else {
        initial = 8;
        stopParameter = initial + 8;
        for (initial; initial < stopParameter; initial++) {
            Movie actualMovie = moviesVector[initial];
            addImageToContainer(imagePathVector[initial], initial);
        }
    }

    downloadImagesThread(initial);

}

void PaginationWindow::clearContainer() {
    cout << "Cleaning container...\n";
    vector<Gtk::Widget*> children = posterContainer.get_children();
    for (int i = 0; i<children.size(); i++) {
        Gtk::Widget *child = children[i];
        delete(child);
    }
}

void PaginationWindow::addImageToContainer(string imagePath, int index) {
    cout << "Adding image " << index << " to container...\n";
    Gtk::Button *buttonImage = new Gtk::Button();
    Gtk::Image *imageButton = new Gtk::Image(load_image(imagePath, 215, 290));
    buttonImage->set_image(*imageButton);

    posterContainer.add(*buttonImage);
    buttonImage->signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this,
        &PaginationWindow::openInfoWindow), index));
    posterContainer.show_all_children();
}

void PaginationWindow::downloadImagesThread(int initial) {
    cout << "Starting thread...\n";
    thread postersThread(&PaginationWindow::downloadImages, this, initial);
    postersThread.detach();
}

void PaginationWindow::downloadImages(int initial) {
    for (initial; initial<moviesVector.size(); initial++) {
        Movie actualMovie = moviesVector[initial]; 
        cout << "Downloading image in thread of movie " << actualMovie.movieTitle << "...\n";
        HTMLManagement htmlM;
        string url = actualMovie.url;
        downloadData(htmlM.getHTML(url), actualMovie.index);
        imagePathVector.push_back(actualImagePath);
    }
}

Glib::RefPtr<Gdk::Pixbuf> PaginationWindow::load_image(std::string path, int width, int height) {
    return Gdk::Pixbuf::create_from_file(path, width, height);
}

void PaginationWindow::openInfoWindow(int initial) {
    cout << "Opening Information Window...\n";
    Movie actualMovie = moviesVector[initial];
    string path = imagePathVector[initial];
    InfoWindow::run(actualMovie, path);
}

void PaginationWindow::run() {
    auto app = Gtk::Application::create();
    static PaginationWindow PaginationWin;
    PaginationWin.set_default_size(1000,600);
    // PaginationWin.show();
    app->run(PaginationWin);
}





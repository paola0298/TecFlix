#include "NoPagination.hpp"

NoPaginationWindow::NoPaginationWindow() : 
title("Bienvenido a TecFlix"),
mainContainer(Gtk::ORIENTATION_VERTICAL),
upperContainer(Gtk::ORIENTATION_HORIZONTAL),
memory("Uso de memoria: "), 
reader("/home/paola/Documents/II Semestre 2019/Algoritmos y Estructuras de Datos II/Proyectos programados/TecFlix/res/movie_metadata.csv") {
    
    
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
    // showImageThread();
    show_all_children();

    
}

NoPaginationWindow::~NoPaginationWindow() { }

void NoPaginationWindow::showImageThread() {
    thread showPostersThread(&NoPaginationWindow::showPosters, this);
    showPostersThread.detach();
}

void NoPaginationWindow::downloadImagesThread() {
    thread downloadThread(&NoPaginationWindow::downloadImages, this);
    downloadThread.detach();
}

void NoPaginationWindow::downloadImages() {
    for (int i = 0; i<listOfMovies.size(); i++) {
        Movie actualMovie = listOfMovies[i]; 
        // cout << "Getting image of " << actualMovie.movieTitle << "\n";

        HTMLManagement htmlM;
        // cout << "Getting url \n";
        string url = actualMovie.url;
        // downloadData(htmlM.getHTML(url), actualMovie.index);
        // cout << "Getting html \n";
        string html = htmlM.getHTML(url);
        // cout << "Downloading image...\n";
        actualImagePath = htmlM.getPosterPath(html, to_string(actualMovie.index));
        // cout << "Image downloaded\n";
        actualSinopsis = htmlM.getSummary(html);
        // cout << "Summary \n";
        // cout << "Adding to vector \n";
        postersVector.push_back(actualImagePath);
        summaryVector.push_back(actualSinopsis);
        // cout << "Image added to vector\n";
    }
}

void NoPaginationWindow::loadData() {
    // cout << "Loading data from csv file\n";
    
    vector<string> dataList = reader.getData(0, 0, true);
    // cout << "Size of datalist: " << dataList.size() << "\n";

    for (int i=1; i<dataList.size(); i++) { //descomentar linea para cargar todo en memoria
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

        // HTMLManagement html;
        // string stringHtml = html.getHTML(url);
        // string sinopsis = html.getSummary(stringHtml);
        // string imagePath = html.getPosterPath(stringHtml, to_string(i));
        // string trailerLink = html.getTrailerLink(stringHtml);
        // cout << "Adding " << movieTitle << ", to list of movies...\n";

        Movie movie(movieTitle, year, score, duration, "", director, genres, 
        actors, language, keywords, "", "");
        movie.index = i;
        movie.url = url;

        listOfMovies.push_back(movie);

        Gtk::Button *buttonImage = new Gtk::Button();
        Gtk::Image *image = new Gtk::Image(load_image( "/home/paola/Documents/II Semestre 2019/Algoritmos y Estructuras de Datos II/Proyectos programados/TecFlix/res/film.jpeg",215, 290));
        buttonImage->set_image(*image);
        buttonImage->signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this,
                &NoPaginationWindow::openInfoWindow), (i-1)));
        posterContainer.add(*buttonImage);

        buttonVector.push_back(buttonImage);

    }

    posterContainer.show_all_children();

    // cout << "List size: " << listOfMovies.size() << "\n";

    showImageThread();
}

void NoPaginationWindow::downloadData(string html, int index) {
    // cout << "Downloading image in thread of movie...\n";
    HTMLManagement htmlObj;
    actualImagePath = htmlObj.getPosterPath(html, to_string(index));
    // cout << "Image downloaded\n";
    actualSinopsis = htmlObj.getSummary(html);
    // cout << "Summary \n";
}

void NoPaginationWindow::showPosters() {
    // downloadImagesThread();

    int moviesSize = listOfMovies.size();
    int buttonsListSize = buttonVector.size();

    // cout << "Size of list of movies " << moviesSize << "\n";
    // cout << "Size of list of Buttons " << buttonsListSize << "\n";

    if (moviesSize == buttonsListSize) {
        for (int i = 0; i<moviesSize; i++) {
            Movie actualMovie = listOfMovies[i]; 
            // cout << "Getting image of " << actualMovie.movieTitle << "\n";

            HTMLManagement htmlM;
            // cout << "Getting url \n";
            string url = actualMovie.url;
            // downloadData(htmlM.getHTML(url), actualMovie.index);
            // cout << "Getting html \n";
            string html = htmlM.getHTML(url);
            // cout << "Downloading image...\n";
            actualImagePath = htmlM.getPosterPath(html, to_string(actualMovie.index));
            // cout << "Image downloaded\n";
            actualSinopsis = htmlM.getSummary(html);
            // cout << "Summary \n";
            // cout << "Adding to vector \n";
            postersVector.push_back(actualImagePath);
            summaryVector.push_back(actualSinopsis);
            // cout << "Image added to vector\n";

            Gtk::Image *imageButton = new Gtk::Image(load_image(actualImagePath, 215, 290));
            // cout << "Getting button from vector\n";
            Gtk::Button *actualButton = buttonVector[i];
            // Gtk::Image *lastImage = (Gtk::Image*) actualButton->get_image();
            // delete(lastImage);
            // cout << "Setting new image to button\n";
            actualButton->set_image(*imageButton);
            // cout << "Image set\n";
        }
    }

    // while (true) {
    //     int postersVectorSize = postersVector.size();
       
    //     if (postersVectorSize == lastSize+1) {
    //         cout << "Posters vector size " << postersVectorSize << "\n";
    //         cout << "Last size " << lastSize << "\n";
    //         int index = postersVectorSize-1;
    //         cout << "Getting path ... \n";
    //         string actualPath = postersVector[index];
    //         cout << "Path " << actualPath << "\n";
    //         cout << "Getting actual movie\n";
    //         Movie actual = listOfMovies[index];
    //         cout << "Actual movie " << actual.movieTitle << "...\n";
    //         // Gtk::Button *buttonImage = new Gtk::Button();
    //         Gtk::Image *imageButton = new Gtk::Image(load_image(actualPath, 215, 290));
    //         buttonImage->set_image(*imageButton);
    //         cout << "Adding button to container\n";
    //         // posterContainer.add(*buttonImage);
    //         // buttonImage->signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this,
    //             // &NoPaginationWindow::openInfoWindow), index));

    //         // cout << "Showing on window..\n";
            
    //         // cout << "Shown..\n";
    //         lastSize++;
            
    //     }

    //     show_all_children();
        
    // }

    // for (int i=0; i<8; i++) {
    //     Movie actualMovie = listOfMovies[i]; 
    //     string url = actualMovie.url;
    //     int index = actualMovie.index;
    //     HTMLManagement htmlObj;
    //     string htmlData = htmlObj.getHTML(url);

    //     downloadData(htmlData, index);
    //     postersVector.push_back(actualImagePath);
    //     summaryVector.push_back(actualSinopsis);

    //     cout << "Actual image path " << actualImagePath << "\n";

    //     addImageToContainer(actualImagePath, i);
    // }

    // downloadImagesThread();
}

void NoPaginationWindow::addImageToContainer(string imagePath, int index) {
    // cout << "Adding image " << index << " to container...\n";
    Gtk::Button *buttonImage = new Gtk::Button();
    // cout << "Creating image for button...\n";
    Gtk::Image *imageButton = new Gtk::Image(load_image(imagePath, 215, 290));
    // cout << "Setting image to button \n";
    buttonImage->set_image(*imageButton);
    // cout << "Adding image to container\n";
    posterContainer.add(*buttonImage);
    // cout << "Setting funcionality to button \n";
    buttonImage->signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this,
        &NoPaginationWindow::openInfoWindow), index));
    // cout << "Showing children on window\n";
    posterContainer.show_all_children();
    // cout << "Children showed...";
}

void NoPaginationWindow::openInfoWindow(int index) {
    Movie actualMovie = listOfMovies[index];
    string path = postersVector[index];
    string summary = summaryVector[index];
    // cout << "Movie Name: " << actualMovie.movieTitle << "\n";
    InfoWindow::run(actualMovie, path, summary);
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

#include "Scroll.hpp"

ScrollWindow::ScrollWindow() :
title("Bienvenido a TecFlix"),
mainContainer(Gtk::ORIENTATION_VERTICAL),
upperContainer(Gtk::ORIENTATION_HORIZONTAL),
memory("Uso de memoria"),
reader("/home/paola/Documents/II Semestre 2019/Algoritmos y Estructuras de Datos II/Proyectos programados/TecFlix/res/movie_metadata.csv") {
    set_title("TecFlix");
    set_border_width(10);
    add(mainContainer);

    mainContainer.pack_start(upperContainer, false, false, 10);
    mainContainer.pack_start(scrollContainer, true, true, 10);

    upperContainer.pack_start(title, false, false, 400);
    upperContainer.pack_start(memory, false, false, 0);
    upperContainer.pack_start(memoryData, false, false, 0);

    scrollContainer.add(posterContainer);
    scrollContainer.set_policy(Gtk::PolicyType::POLICY_NEVER, Gtk::PolicyType::POLICY_AUTOMATIC);

    show_all_children();
    //addToWindowThread();
    threadController();
}

void ScrollWindow::addToWindowThread() {
    thread mythread(&ScrollWindow::showPosters, this);
    mythread.detach();
}

void ScrollWindow::loadData() {
    int i = 0;
    if (first) {
        // first = false;
        i = 1;
        dataList = reader.getData(0, 16);
    } else {
        dataList = reader.getData(totalPosters, totalPosters+8);
    }

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

        // cout << "Adding " << movieTitle << ", to list of movies...\n";
        Movie movie(movieTitle, year, score, duration, "", director, genres, 
        actors, language, keywords, "", "");
        movie.index = totalPosters;
        movie.url = url;
        moviesVector.push_back(movie);
        totalPosters++;

        // Gtk::Button *buttonImage = new Gtk::Button();
        // Gtk::Image *image = new Gtk::Image(load_image( "/home/paola/Documents/II Semestre 2019/Algoritmos y Estructuras de Datos II/Proyectos programados/TecFlix/res/film.jpeg",215, 290));
        // buttonImage->set_image(*image);
        // buttonImage->signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this,
        //         &ScrollWindow::openInfoWindow), (i-1)));
        // posterContainer.add(*buttonImage);
        // buttonVector.push_back(buttonImage);
    }

    posterContainer.show_all_children();
}

void ScrollWindow::clearContainer() {
    vector<Gtk::Widget*> children = posterContainer.get_children();
    cout << "Children size " << children.size() << "\n";
    if (children.size() >= 8) {
        for (int i = 0; i<8; i++) {
            Gtk::Widget *child = children[i];
            delete(child);
        }
    }

}

void ScrollWindow::showPosters() {
    clearContainer();

    loadData();

    int moviesVectorSize  = moviesVector.size();
    // int buttonSize = buttonVector.size();
    int i = 0;

    if (!first) {
        i = 8;
    } else {
        first = false;
    }
        
    for (int i; i<moviesVectorSize; i++) {
        Movie actualMovie = moviesVector[i];
        string url = actualMovie.url;
        int index = actualMovie.index;
        HTMLManagement htmlObj;
        string htmlData = htmlObj.getHTML(url);
        cout << "Downloading image for movie " << actualMovie.movieTitle << "\n";
        actualImagePath = htmlObj.getPosterPath(htmlData, to_string(index));
        actualSinopsis = htmlObj.getSummary(htmlData);
        postersVector.push_back(actualImagePath);
        summaryVector.push_back(actualSinopsis);
        addImageToContainer(actualImagePath, i);
    }


    cout << "Finished thread \n";
    

}

void ScrollWindow::addImageToContainer(string imagePath, int index) {
    // cout << "Adding image " << index << " to container...\n";
    Gtk::Button *buttonImage = new Gtk::Button();
    Gtk::Image *imageButton = new Gtk::Image(load_image(imagePath, 215, 290));
    buttonImage->set_image(*imageButton);

    posterContainer.add(*buttonImage);
    buttonVector.push_back(buttonImage);
    buttonImage->signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this,
        &ScrollWindow::openInfoWindow), index));
    posterContainer.show_all_children();
}

void ScrollWindow::openInfoWindow(int initial) {
    Movie actualMovie = moviesVector[initial];
    string path = postersVector[initial];
    string summary = summaryVector[initial];
    InfoWindow::run(actualMovie, path, summary);
}

bool ScrollWindow::releaseMemory() {
    // cout << "Freeing memory...\n";
    // std::cout << "Vector movie size before " << moviesVector.size() << "\n";
    // std::cout << "Vector image size before " << imagePathVector.size() << "\n\n";
    for (int i=0; i<5; i++) {
        moviesVector.erase(moviesVector.begin()+i);
        postersVector.erase(postersVector.begin()+i);
        summaryVector.erase(summaryVector.begin()+i);
        buttonVector.erase(buttonVector.begin()+1);
    }

    // std::cout << "Vector movie silistOfMoviesze after " << moviesVector.size() << "\n";
    // std::cout << "Vector image size after " << imagePathVector.size() << "\n\n";

    return moviesVector.size() == postersVector.size();
}

void ScrollWindow::run() {
    auto app = Gtk::Application::create();
    static ScrollWindow scrollWin;
    scrollWin.set_default_size(1000,700/2);
    app->run(scrollWin);
}

void ScrollWindow::threadController() {
    thread thread(&ScrollWindow::controller, this);
    thread.detach();
}

void ScrollWindow::controller() {
    showPosters();
    while (isRunning) {
        cout << "Button vector size " << buttonVector.size() << "\n";
        if (buttonVector.size() > 7) {
            cout << "Button visible " << !buttonVector[7]->get_child_visible() << "\n";
            if (!buttonVector[8]->get_child_visible()) {
                cout << "Last button of first page is not visiblr\n";
            }
        }

    }

}

Glib::RefPtr<Gdk::Pixbuf> ScrollWindow::load_image(std::string path, int width, int height) {
    return Gdk::Pixbuf::create_from_file(path, width, height);
}

ScrollWindow::~ScrollWindow() {
    isRunning = false;
 }
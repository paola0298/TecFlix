#include "Pagination.hpp"

PaginationWindow::PaginationWindow() :
title("Bienvenido a TecFlix"),
mainContainer(Gtk::ORIENTATION_VERTICAL),
upperContainer(Gtk::ORIENTATION_HORIZONTAL),
paginationContainer(Gtk::ORIENTATION_HORIZONTAL),
memory("Uso de memoria: "), 
reader("/home/paola/Documents/II Semestre 2019/Algoritmos y Estructuras de Datos II/Proyectos programados/TecFlix/res/movie_metadata.csv") {
    
    // listOfMovies = new LinkedList<Movie>;
    start = 1;
    end = 17;
    actualPage = 1;
    lastPageShow = 10;
    set_title("TecFlix");
    set_border_width(10);
    add(mainContainer);
    mainContainer.pack_start(upperContainer, false, false, 10);
    mainContainer.pack_start(posterContainer, true, true, 10);
    mainContainer.pack_end(paginationContainer, false, false, 5);

    upperContainer.pack_start(title, false, false, 400);
    upperContainer.pack_start(memory, false, false, 0);
    upperContainer.pack_start(memoryData, false, false, 0);

    upperContainer.set_size_request(1000, 25);
    posterContainer.set_size_request(1000, 565);
    paginationContainer.set_size_request(1000, 10);
    paginationContainer.set_halign(Gtk::ALIGN_CENTER);
    // posterContainer.set_max_children_per_line(5);



    // loadData();
    // startThread();
    // showPosters(1);
    loadPages();
    show_all_children();
   
}

PaginationWindow::~PaginationWindow() { }

void PaginationWindow::loadData() {
    cout << "Loading data from csv file\n";
    if (actualPage > 1){
        start = start + 8;
        end = end + 8;
    }

    if (actualPage > 2)
        releaseMemoryBack();

    // std::filesystem::remove_all("/home/paola/Documents/II Semestre 2019/Algoritmos y Estructuras de Datos II/Proyectos programados/TecFlix/res/Cache");
    // boost::filesystem::remove_all("/home/paola/Documents/II Semestre 2019/Algoritmos y Estructuras de Datos II/Proyectos programados/TecFlix/res/Cache");
    if (actualPage == 1) 
        dataList = reader.getData(0, end);
    else 
        dataList = reader.getData(start, end);
    cout << "Size of datalist: " << dataList.size() << "\n";
    int startVar = start;

    for (startVar; startVar<end; startVar++) {
        cout << "indice " << startVar << "\n";
        vector<string> record = reader.getRecord(startVar, dataList);
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
    
        Movie movie(movieTitle, year, score, duration, "", director, genres, 
        actors, language, keywords, "", "");
        movie.index = startVar;
        movie.url = url;
        moviesVector.push_back(movie);
    }

    cout << "Vector size: " << moviesVector.size() << "\n";
}

// void PaginationWindow::downloadData() {
//     int startVar = start;
//     cout << startVar << "\n";
//     cout << end << "\n";
//     int i = 0;
//     int j = widgetButton.size();
//     cout << widgetButton.size() << "\n";
//     cout << j << "\n";
//     for (int ii=0; ii<j; ii++) {
//         cout << widgetButton[ii] << "\n";
//     }
//     for (startVar; startVar<9; startVar++) {
//         cout << "Start Var " << startVar << "\n";
//         vector<string> record = reader.getRecord(startVar, dataList);
//         string url = record[17];
//         HTMLManagement html;
//         string stringHtml = html.getHTML(url);
//         string sinopsis = html.getSummary(stringHtml);
//         string imagePath = html.getPosterPath(stringHtml, to_string(startVar));
//         cout << "Setting new image> " << imagePath << "\n";
//         // Gtk::Image *image = new Gtk::Image(load_image(imagePath, 215, 290));
//         // cout << widgetButton.size() << "\n";
//         widgetButton[i]->property_pixbuf().set_value(load_image(imagePath, 215, 290));
//         cout << widgetButton[i] << "\n";
//         i++;
//         // if (i<j)
//         //     widgetButton[i]->set_image(*image);
//         // i++;

//         // sinopsisVector.push_back(sinopsis);
//         // imagePathVector.push_back(imagePath);
//     }
//     cout << "For finished \n";
// }

void PaginationWindow::downloadData(string html, int index) {
    HTMLManagement htmlObj;
    string imagePath = htmlObj.getPosterPath(html, to_string(index));
    cout << "Image path: " << imagePath << "\n";
    actualImagePath = imagePath;
    string summary = htmlObj.getSummary(html);
    actualSinopsis = summary;

}

void PaginationWindow::loadPages() {
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
    loadData();
    int initial = ((page-1)*8);
    actualPage = page;
    int stopParameter;
    int moviesVectorSize = moviesVector.size();

    cout << "Initial " << initial << "\n";
    cout << "Vector size " << moviesVectorSize << "\n";


    if (page == 1) {
        stopParameter = (moviesVectorSize/2)*page;
        for (initial; initial<stopParameter; initial++) {
            // Movie actualMovie = listOfMovies->getValueAtPos(initial);
            Movie actualMovie = moviesVector[initial]; 
            cout << "Movie " << actualMovie.movieTitle << "\n";
            // string imagePath = actualMovie.posterDir;
            // string imagePath = imagePathVector[initial];
            HTMLManagement htmlM;
            string url = actualMovie.url;
            string htmlData = htmlM.getHTML(url);
            int index =  actualMovie.index;
            downloadData(htmlData, index);

            cout << "Actual image path " << actualImagePath << "\n";
            actualMovie.posterDir = actualImagePath;
            actualMovie.sinopsis = actualSinopsis;
            imagePathVector.push_back(actualImagePath);
            
            Gtk::Button *buttonImage = new Gtk::Button();
            Gtk::Image *imageButton = new Gtk::Image(load_image(actualImagePath, 215, 290));
            buttonImage->set_image(*imageButton);

            widgetButton.push_back(imageButton);

            cout << "Widget Button size " << widgetButton.size() << "\n"; 

            posterContainer.add(*buttonImage);
            buttonImage->signal_clicked().connect(sigc::bind<Movie>(sigc::mem_fun(*this,
                &PaginationWindow::openInfoWindow), actualMovie));
        }
    } else {
        stopParameter = initial + 8;

        cout << "Stop parameter " << stopParameter << "\n";
        cout << "initial " << initial << "\n";
        for (initial; initial < stopParameter; initial++) {
            Movie actualMovie = moviesVector[initial]; 
            cout << "Movie " << actualMovie.movieTitle << "\n";
            cout << "Movie image path " << imagePathVector[initial] << "\n";

            Gtk::Button *buttonImage = new Gtk::Button();
            Gtk::Image *imageButton = new Gtk::Image(load_image(imagePathVector[initial], 215, 290));
            buttonImage->set_image(*imageButton);

            posterContainer.add(*buttonImage);
            buttonImage->signal_clicked().connect(sigc::bind<Movie>(sigc::mem_fun(*this,
                &PaginationWindow::openInfoWindow), actualMovie));
        }
    }
    
    posterContainer.show_all_children();

    // download(initial);
    
    showDataThread(initial);
   

    cout << "Thread finished\n";
}

void PaginationWindow::download(int initial) {
    for (initial; initial<moviesVector.size(); initial++) {
        Movie actualMovie = moviesVector[initial]; 
        cout << "Movie " << actualMovie.movieTitle << "\n";
        // string imagePath = actualMovie.posterDir;
        // string imagePath = imagePathVector[initial];
        HTMLManagement htmlM;
        string url = actualMovie.url;
        downloadData(htmlM.getHTML(url), actualMovie.index);

        cout << "Actual image path " << actualImagePath << "\n";
        actualMovie.posterDir = actualImagePath;
        actualMovie.sinopsis = actualSinopsis;
        imagePathVector.push_back(actualImagePath);

        cout << "Movie " << actualMovie.movieTitle << ", poster dir " << actualMovie.posterDir << "\n"; 
    }
}

void PaginationWindow::clearContainer(){
    vector<Gtk::Widget*> children = posterContainer.get_children();
    for (int i = 0; i<children.size(); i++) {
        Gtk::Widget *child = children[i];
        delete(child);
    }

}

void PaginationWindow::openInfoWindow(Movie actualMovie) {
    cout << "Movie Name: " << actualMovie.movieTitle << "\n";
    InfoWindow::run(actualMovie);
}

void PaginationWindow::run() {
    auto app = Gtk::Application::create();
    static PaginationWindow PaginationWin;
    PaginationWin.set_default_size(1000,600);
    app->run(PaginationWin);
}

void PaginationWindow::test() {
    cout<<"Test\n";
}

void PaginationWindow::releaseMemoryBack() {
    for (int i=0; i<9; i++) {
        moviesVector.erase(moviesVector.begin()+i);
        imagePathVector.erase(imagePathVector.begin()+i);
    }
}

void PaginationWindow::showDataThread(int initial) {
    thread postersThread(&PaginationWindow::download, this, initial);
    postersThread.detach();
    
}



Glib::RefPtr<Gdk::Pixbuf> PaginationWindow::load_image(std::string path, int width, int height) {
    return Gdk::Pixbuf::create_from_file(path, width, height);
}


#include "MainWindow.h"


MainWindow::MainWindow() :
mainContainer(Gtk::ORIENTATION_HORIZONTAL) {

    add(mainContainer);
    set_title("TecFlix");
    set_border_width(10);

    paginationImage = Gtk::Image(load_image(
        "/home/paola/Documents/II Semestre 2019/Algoritmos y Estructuras de Datos II/Proyectos programados/TecFlix/res/paginationImage.png",
        212, 212));

    noPaginationImage = Gtk::Image(load_image(
        "/home/paola/Documents/II Semestre 2019/Algoritmos y Estructuras de Datos II/Proyectos programados/TecFlix/res/noPaginationImage.png",
        212,212));

    scrollImage = Gtk::Image(load_image(
        "/home/paola/Documents/II Semestre 2019/Algoritmos y Estructuras de Datos II/Proyectos programados/TecFlix/res/scrollImage.png",
        212, 212));

    pagination.set_image(paginationImage);
    noPagination.set_image(noPaginationImage);
    scroll.set_image(scrollImage);

    pagination.signal_clicked().connect(sigc::mem_fun(*this,
            &MainWindow::openPaginationWindow));
    noPagination.signal_clicked().connect(sigc::mem_fun(*this,
            &MainWindow::openNoPaginationWindow));
    scroll.signal_clicked().connect(sigc::mem_fun(*this, 
            &MainWindow::openScrollWindow));

    mainContainer.pack_start(pagination, false, false, 10);
    mainContainer.pack_start(scroll, false, false, 10);
    mainContainer.pack_start(noPagination, false, false, 10);
    
    show_all_children();
    
}

MainWindow::~MainWindow() { }

Glib::RefPtr<Gdk::Pixbuf> MainWindow::load_image(std::string path, int width, int height) {
    return Gdk::Pixbuf::create_from_file(path, width, height);
}

void MainWindow::openPaginationWindow() {
    cout<<"Opening Pagination Window...\n";
    
}

void MainWindow::openNoPaginationWindow() {
    cout<<"Opening no Pagination Window...\n";
    close();
    NoPaginationWindow::run();
}

void MainWindow::openScrollWindow() {
    cout<<"Opening Scroll Window...\n";
    
}

void MainWindow::run() {
    auto app = Gtk::Application::create("org.tecflix.main");
    static MainWindow window;
    app->run(window);
}

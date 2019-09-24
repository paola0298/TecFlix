#include "NoPagination.h"

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

    upperContainer.set_size_request(1000, 25);

    scrollContainer.add(posterContainer);
    scrollContainer.set_size_request(1000, 565);
    scrollContainer.set_policy(Gtk::PolicyType::POLICY_NEVER, Gtk::PolicyType::POLICY_AUTOMATIC);

    loadData();
    show_all_children();
}

NoPaginationWindow::~NoPaginationWindow() { }

void NoPaginationWindow::loadData() {
    cout << "Loading data from csv file";
    
    std::vector<std::string> dataList = reader.getData(1, 5043);
    std::vector<std::string> record = reader.getRecord(5042, dataList);

    
    

}
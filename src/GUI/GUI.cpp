#include "GUI.h"
#include <iostream>
#include "../Logic/ReadCSV.cpp"

TecFlix::TecFlix():
option("Seleccione el modo de la aplicacion"),
memory("Uso de memoria"),
noPaginacionRB("No paginación"), paginacionRB("Paginacion"),
tradicionalRB("Paginacion tradicional"), scrollRB("Scroll infinito"),
tittle("Tec Flix"), mainContainer(Gtk::ORIENTATION_VERTICAL, 0),
headerContainer(Gtk::ORIENTATION_HORIZONTAL, 0),
paginationContainer(Gtk::ORIENTATION_HORIZONTAL, 0),
movieContainer(Gtk::ORIENTATION_VERTICAL, 0),
movieContainer1(Gtk::ORIENTATION_HORIZONTAL, 0),
movieContainer2(Gtk::ORIENTATION_HORIZONTAL, 0),
tittleContainer(Gtk::ORIENTATION_HORIZONTAL, 0) {
    // This just sets the title of our new window.
    set_title("TecFlix");

    // sets the border width of the window.
    set_border_width(10);

    // put the box into the main window.
    add(mainContainer);

    //main container
    mainContainer.pack_start(tittleContainer, false, false, 10);
    mainContainer.pack_start(headerContainer, false, false, 10);
    mainContainer.pack_start(movieContainer, false, false, 10);
    mainContainer.pack_start(paginationContainer, false, false, 10);

    //tittle container
    tittleContainer.pack_start(tittle, false, false, 400);
    tittleContainer.pack_start(memory, false, false, 0);
    // gtk_widget_modify_font(tittle, pango_font_description_from_string("Monospace 50"))
    
    //header container
    headerContainer.set_size_request(1000, 25);
    headerContainer.set_halign(Gtk::ALIGN_CENTER);
    paginacionRB.join_group(noPaginacionRB);
    tradicionalRB.join_group(noPaginacionRB);
    scrollRB.join_group(noPaginacionRB);

    //adding to header container
    headerContainer.pack_start(option, false, false, 10);
    headerContainer.pack_start(noPaginacionRB, false, false, 10);
    headerContainer.pack_start(paginacionRB, false, false, 10);
    headerContainer.pack_start(tradicionalRB, false, false, 10);
    headerContainer.pack_start(scrollRB, false, false, 10);

    //movie container
    movieContainer.set_size_request(1000, 565);
    movieContainer.pack_start(movieContainer1, false, false, 0);
    movieContainer.pack_start(movieContainer2, false, false, 0);
    movieContainer1.set_size_request(1000, 215);
    movieContainer2.set_size_request(1000, 215);
    // movie1.set_size_request(215,10);

    image1 = Gtk::Image(
        load_image("/home/paola/Documents/II Semestre 2019/Algoritmos y Estructuras de Datos II/Proyectos programados/TecFlix/res/image.jpg", 
        215, 290));

    image2 = Gtk::Image(
        load_image("/home/paola/Documents/II Semestre 2019/Algoritmos y Estructuras de Datos II/Proyectos programados/TecFlix/res/image.jpg", 
        215, 290));
    image3 = Gtk::Image(
        load_image("/home/paola/Documents/II Semestre 2019/Algoritmos y Estructuras de Datos II/Proyectos programados/TecFlix/res/image.jpg", 
        215, 290));
    image4 = Gtk::Image(
        load_image("/home/paola/Documents/II Semestre 2019/Algoritmos y Estructuras de Datos II/Proyectos programados/TecFlix/res/image.jpg", 
        215, 290));
    image5 = Gtk::Image(
        load_image("/home/paola/Documents/II Semestre 2019/Algoritmos y Estructuras de Datos II/Proyectos programados/TecFlix/res/image.jpg", 
        215, 290));
    image6 = Gtk::Image(
        load_image("/home/paola/Documents/II Semestre 2019/Algoritmos y Estructuras de Datos II/Proyectos programados/TecFlix/res/image.jpg", 
        215, 290));
    image7 = Gtk::Image(
        load_image("/home/paola/Documents/II Semestre 2019/Algoritmos y Estructuras de Datos II/Proyectos programados/TecFlix/res/image.jpg", 
        215, 290));
    image8 = Gtk::Image(
        load_image("/home/paola/Documents/II Semestre 2019/Algoritmos y Estructuras de Datos II/Proyectos programados/TecFlix/res/image.jpg", 
        215, 290));
    image9 = Gtk::Image(
        load_image("/home/paola/Documents/II Semestre 2019/Algoritmos y Estructuras de Datos II/Proyectos programados/TecFlix/res/image.jpg", 
        215, 290));
    image10 = Gtk::Image(
        load_image("/home/paola/Documents/II Semestre 2019/Algoritmos y Estructuras de Datos II/Proyectos programados/TecFlix/res/image.jpg", 
        215, 290));

    movie1.set_image(image1);
    movie2.set_image(image2);
    movie3.set_image(image3);
    movie4.set_image(image4);
    movie5.set_image(image5);
    movie6.set_image(image6);
    movie7.set_image(image7);
    movie8.set_image(image8);
    movie9.set_image(image9);
    movie10.set_image(image10);

    // movieContainer.add(image);
    movieContainer1.add(movie1);
    movieContainer1.add(movie2);
    movieContainer1.add(movie4);
    movieContainer1.add(movie5);
    movieContainer1.add(movie3);
    movieContainer2.add(movie6);
    movieContainer2.add(movie7);
    movieContainer2.add(movie8);
    movieContainer2.add(movie9);
    movieContainer2.add(movie10);
    

    //pagination container
    paginationContainer.set_size_request(1000, 10);

    


    // Now when the button is clicked, we call the "on_button_clicked" function
    // with a pointer to "button 1" as it's argument
    movie1.signal_clicked().connect(sigc::bind<Glib::ustring>(
            sigc::mem_fun(*this, &TecFlix::on_button_clicked), "button 1"));

    show_all_children();

}

TecFlix::~TecFlix() { }

void TecFlix::on_button_clicked(Glib::ustring data) {
    std::cout << "Hello World - " << data << " was pressed" << std::endl;
    // read_record(9);
}

Glib::RefPtr<Gdk::Pixbuf> TecFlix::load_image(std::string path, int width, int height) {
    return Gdk::Pixbuf::create_from_file(path, width, height);
}

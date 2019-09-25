// #include "GUI/GUI.cpp"
// #include <gtkmm-3.0/gtkmm/application.h>
#include "GUI/MainWindow.cpp"

int main (int argc, char *argv[])
{
    gst_init (&argc, &argv);
    // auto app = Gtk::Application::create();

    // MainWindow gui;
    // // gui.set_default_size(1000, 600);
    // //Shows the window and returns when it is closed.
    // app->run(gui);
    MainWindow::run();
    return 0;
}
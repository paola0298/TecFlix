#include "GUI/MainWindow.cpp"

int main (int argc, char *argv[]) {
    gst_init (&argc, &argv);
    MainWindow::run(); 
    return 0;
}
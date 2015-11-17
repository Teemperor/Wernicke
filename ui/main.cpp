
#include "WernickeMainWindow.h"


int oldmain(int argc, char **argv)
{

    QApplication app (argc, argv);

    QMainWindow* window = new QMainWindow();

    window->showMaximized();

    RecordDialog recordDialog;
    recordDialog.run();

    return app.exec();
}

int main(int argc, char **argv)
{

    WernickeMainWindow main(argc, argv);

    return main.start();
}




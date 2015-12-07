#include <QApplication>
#include "commandserver.h"

#define LOCALSERVER_NAME "ibbrowser"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);

    CommandServer cmdServ(LOCALSERVER_NAME);
    cmdServ.startListening();

    return a.exec();
}

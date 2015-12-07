#include <QApplication>
#include <signal.h>
#include "commandserver.h"
#include "mydaemon.h"

#define LOCALSERVER_NAME "ibbrowser"

static int setup_unix_signal_handlers();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);

    MyDaemon myDaemon;
    if (setup_unix_signal_handlers() != 0)
        return 1;

    CommandServer cmdServ(LOCALSERVER_NAME);
    cmdServ.startListening();

    return a.exec();
}

static int setup_unix_signal_handlers()
{
    struct sigaction hup, term;

    hup.sa_handler = MyDaemon::hupSignalHandler;
    sigemptyset(&hup.sa_mask);
    hup.sa_flags = 0;
    hup.sa_flags |= SA_RESTART;

    if (sigaction(SIGHUP, &hup, 0) > 0)
        return 1;

    term.sa_handler = MyDaemon::termSignalHandler;
    sigemptyset(&term.sa_mask);
    term.sa_flags = 0;
    term.sa_flags |= SA_RESTART;

    if (sigaction(SIGTERM, &term, 0) > 0)
        return 2;
    if (sigaction(SIGINT, &term, 0) > 0)
        return 3;

    return 0;
}

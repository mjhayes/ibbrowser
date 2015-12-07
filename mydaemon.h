#ifndef MYDAEMON_H
#define MYDAEMON_H

#include <QObject>
#include <QSocketNotifier>

class MyDaemon : public QObject
{
    Q_OBJECT

public:
    MyDaemon();

    // Unix signal handlers.
    static void hupSignalHandler(int unused);
    static void termSignalHandler(int unused);

public slots:
    // Qt signal handlers.
    void handleSigHup();
    void handleSigTerm();

private:
    static int sighupFd[2];
    static int sigtermFd[2];

    QSocketNotifier *snHup;
    QSocketNotifier *snTerm;
};

#endif // MYDAEMON_H

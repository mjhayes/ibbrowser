#include <QApplication>
#include <QDebug>
#include <unistd.h>
#include <sys/socket.h>
#include "mydaemon.h"

int MyDaemon::sighupFd[2] = { 0 };
int MyDaemon::sigtermFd[2] = { 0 };

MyDaemon::MyDaemon() : QObject()
{
    if (::socketpair(AF_UNIX, SOCK_STREAM, 0, sighupFd))
        qFatal("Couldn't create HUP socketpair");

    if (::socketpair(AF_UNIX, SOCK_STREAM, 0, sigtermFd))
        qFatal("Couldn't create TERM socketpair");

    snHup = new QSocketNotifier(sighupFd[1], QSocketNotifier::Read, this);
    connect(snHup, SIGNAL(activated(int)), this, SLOT(handleSigHup()));
    snTerm = new QSocketNotifier(sigtermFd[1], QSocketNotifier::Read, this);
    connect(snTerm, SIGNAL(activated(int)), this, SLOT(handleSigTerm()));
}

void MyDaemon::hupSignalHandler(int)
{
    char a = 1;
    ::write(sighupFd[0], &a, sizeof(a));
}

void MyDaemon::termSignalHandler(int)
{
    char a = 1;
    ::write(sigtermFd[0], &a, sizeof(a));
}

void MyDaemon::handleSigTerm()
{
    snTerm->setEnabled(false);
    char tmp;
    ::read(sigtermFd[1], &tmp, sizeof(tmp));

    // Cleanly exit from QApplication::exec()
    QApplication::quit();

    snTerm->setEnabled(true);
}

void MyDaemon::handleSigHup()
{
    snHup->setEnabled(false);
    char tmp;
    ::read(sighupFd[1], &tmp, sizeof(tmp));

    // We have nothing to do with this at the moment.

    snHup->setEnabled(true);
}

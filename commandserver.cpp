#include <QWebView>

#include "commandclient.h"
#include "commandserver.h"

CommandServer::CommandServer(QString name)
{
    serverName = name;
}

bool CommandServer::startListening()
{
    if (QLocalServer::removeServer(serverName) == false)
        return false;

    QObject::connect(&server, SIGNAL(newConnection()), this, SLOT(handleServerConnect()));

    if (server.listen(serverName) == false)
        return false;

    qDebug() << "socket path: " << server.fullServerName();

    return true;
}

void CommandServer::handleServerConnect()
{
    qDebug() << "handleServerConnect";
    CommandClient *cc = new CommandClient(server.nextPendingConnection());
    QObject::connect(cc, SIGNAL(commandReceived(QString)), this, SLOT(handleServerCommand(QString)));
}

void CommandServer::handleServerCommand(QString commandStr)
{
    qDebug() << "handleServerCommand: " << commandStr;

    /* Create, load, and show webview */
    QWebView *wv = new QWebView();
    wv->setWindowFlags(wv->windowFlags() | Qt::FramelessWindowHint);
    wv->load(QUrl::fromUserInput(commandStr));
    wv->show();
}

#include "commandclient.h"
#include "commandserver.h"
#include "ittywebview.h"

CommandServer::CommandServer(QString name) : serverName(name)
{
}

CommandServer::~CommandServer()
{
    QLocalServer::removeServer(serverName);
}

bool CommandServer::startListening()
{
    if (QLocalServer::removeServer(serverName) == false)
        return false;

    QObject::connect(&server, SIGNAL(newConnection()), SLOT(handleServerConnect()));

    if (server.listen(serverName) == false)
        return false;

    qDebug() << "socket path: " << server.fullServerName();

    return true;
}

void CommandServer::handleServerConnect()
{
    qDebug() << "handleServerConnect";
    CommandClient *cc = new CommandClient(server.nextPendingConnection());
    QObject::connect(cc, SIGNAL(commandReceived(QString)), SLOT(handleServerCommand(QString)));
}

void CommandServer::handleServerCommand(QString commandStr)
{
    qDebug() << "handleServerCommand: " << commandStr;

    /* Create, load, and show webview */
    IttyWebView *wv = new IttyWebView();
    wv->load(QUrl::fromUserInput(commandStr));
    wv->show();
}

#include "commandclient.h"

CommandClient::CommandClient(QLocalSocket *client)
{
    this->client = client;

    QObject::connect(client, SIGNAL(readyRead()), this, SLOT(handleClientData()));
    QObject::connect(client, SIGNAL(disconnected()), this, SLOT(handleClientDisconnect()));
}

void CommandClient::handleClientData()
{
    qDebug() << "handleClientData";
    if (client->canReadLine() == false)
        return;

    QByteArray lineBytes = client->readLine();
    QString lineStr(lineBytes);

    /* Remove leading and trailing whitespace */
    lineStr = lineStr.trimmed();

    qDebug() << lineStr;

    emit commandReceived(lineStr);
}

void CommandClient::handleClientDisconnect()
{
    qDebug() << "Client disconnected";
    delete this;
}

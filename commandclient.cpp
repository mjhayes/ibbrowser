#include "commandclient.h"

CommandClient::CommandClient(QLocalSocket *client)
{
    client->setParent(this);
    this->client = client;

    QObject::connect(client, SIGNAL(readyRead()), SLOT(handleClientData()));
    QObject::connect(client, SIGNAL(disconnected()), SLOT(deleteLater()));
}

void CommandClient::handleClientData()
{
    qDebug() << "handleClientData";
    if (client->canReadLine() == false)
        return;

    QString lineStr(client->readLine());

    /* Remove leading and trailing whitespace */
    lineStr = lineStr.trimmed();

    qDebug() << lineStr;

    emit commandReceived(lineStr);
}

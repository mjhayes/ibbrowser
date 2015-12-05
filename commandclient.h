#ifndef COMMANDCLIENT_H
#define COMMANDCLIENT_H

#include <QLocalSocket>

class CommandClient : public QObject
{
    Q_OBJECT

public:
    CommandClient(QLocalSocket *client);

private:
    QLocalSocket *client;

signals:
    void commandReceived(QString commandStr);

public slots:
    void handleClientData();
    void handleClientDisconnect();
};

#endif // COMMANDCLIENT_H

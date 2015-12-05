#ifndef COMMANDSERVER_H
#define COMMANDSERVER_H

#include <QLocalServer>

class CommandServer : public QObject
{
    Q_OBJECT

public:
    CommandServer(QString name);
    virtual ~CommandServer() {};
    bool startListening();

private:
    QLocalServer server;
    QString serverName;

public slots:
    void handleServerConnect();
    void handleServerCommand(QString commandStr);
};

#endif // COMMANDSERVER_H

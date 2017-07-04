#ifndef ACQUISITIONSERVER_H
#define ACQUISITIONSERVER_H

#include <QThread>
#include <QSerialPort>
#include <QMutex>
#include <QWaitCondition>

class AcquisitionServer : public QThread
{    
    Q_OBJECT

public:
    AcquisitionServer(QObject *parent = 0);
    ~AcquisitionServer();

    bool startPort(QString portName);
    void stopPort();

signals:
    void dataReceived(unsigned char data);

protected:
    void run() override;

private:
    QMutex mutex;
    QWaitCondition condition;

    QSerialPort portBioAmp;

    unsigned char readByte;
    bool abort;
};

#endif // ACQUISITIONSERVER_H

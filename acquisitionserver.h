#ifndef ACQUISITIONSERVER_H
#define ACQUISITIONSERVER_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>

#include <QSerialPort>

#include <QByteArray>

class AcquisitionServer : public QThread
{    
    Q_OBJECT

public:
    AcquisitionServer(QObject *parent = 0);
    ~AcquisitionServer();

    bool startPort(QString portName);
    void stopPort();
    void write(QByteArray data);

signals:
    void dataReceived(unsigned char data);
    void portOpened();
    void portClosed();

public slots:
    void setBaudRate(long baudRate);

protected:
    void run() override;

private:
    QMutex mutex;
    QWaitCondition condition;

    QSerialPort portBioAmp;

    bool abort;
    long baudRate;
};

#endif // ACQUISITIONSERVER_H

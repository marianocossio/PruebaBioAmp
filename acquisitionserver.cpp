#include "acquisitionserver.h"

AcquisitionServer::AcquisitionServer(QObject *parent) : QThread(parent)
{
    abort = false;

    baudRate = 115200;
}

AcquisitionServer::~AcquisitionServer()
{
    mutex.lock();

    abort = true;
    condition.wakeOne();

    mutex.unlock();

    wait();
}

bool AcquisitionServer::startPort(QString portName)
{
    bool result;

    QMutexLocker locker(&mutex);

    portBioAmp.setPortName(portName);
    portBioAmp.open(QSerialPort::ReadWrite);
    portBioAmp.setBaudRate(baudRate);

    result = portBioAmp.isOpen();

    if (!isRunning())
        start(LowPriority);
    else
        condition.wakeOne();

    if (result)
    {
        abort = false;

        emit portOpened();
    }

    return result;
}

void AcquisitionServer::stopPort()
{
    mutex.lock();

    if (portBioAmp.isOpen())
        portBioAmp.close();

    abort = true;
    condition.wakeOne();

    mutex.unlock();

    wait();

    emit portClosed();
}

void AcquisitionServer::write(QByteArray data)
{
    mutex.lock();

    portBioAmp.write(data);

    mutex.unlock();
}

void AcquisitionServer::setBaudRate(long baudRate)
{
    this->baudRate = baudRate;
}

void AcquisitionServer::run()
{
    forever
    {
        if (abort)
            return;

        bool bytesAvailable;
        char *readBytes = new char;
        int bytesRead;

        mutex.lock();

        bytesAvailable = (portBioAmp.bytesAvailable() > 1);

        mutex.unlock();

        if (bytesAvailable)
        {
            mutex.lock();

            bytesRead = portBioAmp.read(readBytes,1);

            mutex.unlock();

            if (bytesRead != (-1))
                emit dataReceived(*readBytes);
        }

        delete readBytes;
    }
}

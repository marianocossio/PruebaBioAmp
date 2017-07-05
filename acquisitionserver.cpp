#include "acquisitionserver.h"

AcquisitionServer::AcquisitionServer(QObject *parent) : QThread(parent)
{
    abort = false;
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
    portBioAmp.setBaudRate(9600);

    result = portBioAmp.isOpen();

    if (!isRunning())
        start(LowPriority);
    else
        condition.wakeOne();

    // ---------------------------

    if (result)
    {
        abort = false;
        //portBioAmp.write("x1060100X");
        //portBioAmp.write("2345678");

        emit portOpened();
    }

    // ---------------------------

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

void AcquisitionServer::run()
{
    forever
    {
        if (abort)
            return;

        bool bytesAvailable;

        mutex.lock();

        bytesAvailable = (portBioAmp.bytesAvailable() > 0);

        mutex.unlock();

        if (bytesAvailable)
        {
            mutex.lock();

            readByte = (unsigned char) portBioAmp.read(1)[0];

            mutex.unlock();

            emit dataReceived(readByte);
        }

        emit dataReceived(255);
    }
}

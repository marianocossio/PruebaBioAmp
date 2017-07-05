#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QList>

#include "acquisitionserver.h"

namespace Ui {
class Principal;
}

class Principal : public QMainWindow
{
    Q_OBJECT

public:
    explicit Principal(QWidget *parent = 0);
    ~Principal();

private slots:
    void on_startPushButton_clicked();
    void on_stopPushButton_clicked();

    void selectPort(QAction* port);
    void showData(unsigned char data);
    void portClosed();

private:
    Ui::Principal *ui;

    QList<QSerialPortInfo> availablePorts;

    AcquisitionServer acquisitionServer;

    QString portName;
};

#endif // PRINCIPAL_H

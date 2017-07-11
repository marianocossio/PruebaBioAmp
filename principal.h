#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <fstream>

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QList>
#include <QVector>

#include <QResizeEvent>

#include "acquisitionserver.h"
#include "graph.h"

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

    void on_sendPushButton_clicked();

protected:
    void resizeEvent(QResizeEvent *event);

private:
    Ui::Principal *ui;

    QList<QSerialPortInfo> availablePorts;

    AcquisitionServer acquisitionServer;

    QString portName;
    QVector<int> channels;

    int byteNumber;
    bool newWord;

    std::ofstream salida;
};

#endif // PRINCIPAL_H

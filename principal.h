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

    void on_channel1CB_toggled(bool checked);

    void on_channel2CB_toggled(bool checked);

    void on_channel3CB_toggled(bool checked);

    void on_channel4CB_toggled(bool checked);

    void on_channel5CB_toggled(bool checked);

    void on_channel6CB_toggled(bool checked);

    void on_channel7CB_toggled(bool checked);

    void on_channel8CB_toggled(bool checked);

    void on_testPB_clicked();

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

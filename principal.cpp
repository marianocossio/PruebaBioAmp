#include "principal.h"
#include "ui_principal.h"

Principal::Principal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Principal)
{
    ui->setupUi(this);

    availablePorts = QSerialPortInfo::availablePorts();

    for (int i = 0; i < availablePorts.size(); i++)
    {
        ui->menu_Puerto->addAction(availablePorts[i].portName());
        ui->menu_Puerto->actions()[ui->menu_Puerto->actions().size() - 1]->setCheckable(true);
        ui->menu_Puerto->actions()[ui->menu_Puerto->actions().size() - 1]->setChecked(false);
    }

    //ui->readByteLabel->setStyleSheet("QLabel { background-color : black; color : grey; }");

    divisor = 0;

    connect(ui->menu_Puerto, SIGNAL(triggered(QAction*)), this, SLOT(selectPort(QAction*)));
    connect(&acquisitionServer, SIGNAL(dataReceived(char)), this, SLOT(showData(char)));
    connect(&acquisitionServer, SIGNAL(portClosed()), this, SLOT(portClosed()));
}

Principal::~Principal()
{
    delete ui;
}

void Principal::on_startPushButton_clicked()
{
    int counter = 0;
    while (!acquisitionServer.startPort(portName) && (counter < 10))
        counter++;

    if (counter < 10)
        ui->readByteLabel->setText("Puerto Abierto");
}

void Principal::on_stopPushButton_clicked()
{
    acquisitionServer.stopPort();
}

void Principal::selectPort(QAction *port)
{
    for (int i = 0; i < ui->menu_Puerto->actions().size(); i++)
        ui->menu_Puerto->actions()[i]->setChecked(false);

    port->setChecked(true);

    portName = port->text();
}

void Principal::showData(char data)
{
    int lim_sup = 75;
    int lim_inf = 50;

    if (divisor == 0)
    {
        if (((data > lim_inf) && (data < lim_sup)) || ((data > (-lim_sup)) && (data < (-lim_inf))))
        {
            ui->readByteLabel->setText(QString::number((int) data));
            ui->openGLWidget->addData((int) data);

            lastData = (int) data;
        }
        else
        {
            ui->readByteLabel->setText(QString::number(lastData));
            ui->openGLWidget->addData(lastData);
        }
    }

    divisor += 1;
    if (divisor == 10)
        divisor = 0;
}

void Principal::portClosed()
{
    ui->readByteLabel->setText("Puerto Cerrado");
}

void Principal::on_sendPushButton_clicked()
{
    //ui->readByteLabel->setText("");
    acquisitionServer.write(ui->sendLineEdit->text().toUtf8());
}

void Principal::resizeEvent(QResizeEvent *event)
{
    //ui->readByteLabel->move(10, 80);
    //ui->readByteLabel->resize(width() - 20, height() - 120);

    ui->openGLWidget->move(10, 80);
    ui->openGLWidget->resize(width() - 20, height() - 120);
}

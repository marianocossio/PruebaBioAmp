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

    connect(ui->menu_Puerto, SIGNAL(triggered(QAction*)), this, SLOT(selectPort(QAction*)));
    connect(&acquisitionServer, SIGNAL(dataReceived(unsigned char)), this, SLOT(showData(unsigned char)));
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

void Principal::showData(unsigned char data)
{
    ui->readByteLabel->setText(QString::number((int) data));
}

void Principal::portClosed()
{
    ui->readByteLabel->setText("Puerto Cerrado");
}

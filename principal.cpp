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

    ui->readByteLabel->setStyleSheet("QLabel { background-color : black; color : grey; }");

    newWord = false;
    channels.resize(15);

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

    salida.open("bytesleidos.txt");
}

void Principal::on_stopPushButton_clicked()
{
    salida.close();
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
    if (data == 0xA0)
    {
        newWord = true;
        byteNumber = 1;
    }

    else if (newWord)
    {
        ++byteNumber;

        if ((byteNumber > 2) && (byteNumber < 27))
        {
            int index = ((int)(byteNumber / 3));

            switch (byteNumber % 3)
            {
            case 0:
                channels[index] = 0;
                channels[index] |= ((0xFF & data) << 16);
                break;

            case 1:
                channels[index] |= ((0xFF & data) << 8);
                break;

            case 2:
                channels[index] |= (0xFF & data);
                channels[index] &= 0xFFFFFF80;          // xxxxxxxx xxxxxxxx xxxxxxxx x0000000

                if ((channels[index] & 0x00800000) > 0) // xxxxxxxx 1xxxxxxx xxxxxxxx xxxxxxxx
                    channels[index] |= 0xFF000000;      // 11111111 xxxxxxxx xxxxxxxx xxxxxxxx
                else
                    channels[index] &= 0x00FFFFFF;      // 00000000 xxxxxxxx xxxxxxxx xxxxxxxx

                break;
            }
        }

        else if ((byteNumber >= 27) && (byteNumber < 33))
            channels[byteNumber - 18] = (int) data;

        else
        {
            switch (byteNumber)
            {
            case 2:
                channels[0] = (int) data;
                break;

            case 33:
                for (int i = 0; i < channels.size(); i++)
                    salida << channels[i] << " ";

                salida << std::endl;

                ui->openGLWidget->addData(channels.mid(1,8));

                newWord = false;

                break;
            }
        }
    }
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

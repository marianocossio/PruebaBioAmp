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

    ui->channel1CB->setEnabled(false);
    ui->channel2CB->setEnabled(false);
    ui->channel3CB->setEnabled(false);
    ui->channel4CB->setEnabled(false);
    ui->channel5CB->setEnabled(false);
    ui->channel6CB->setEnabled(false);
    ui->channel7CB->setEnabled(false);
    ui->channel8CB->setEnabled(false);

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
    {
        ui->readByteLabel->setText("Puerto Abierto");        

        ui->channel1CB->setChecked(true);
        ui->channel2CB->setChecked(true);
        ui->channel3CB->setChecked(true);
        ui->channel4CB->setChecked(true);
        ui->channel5CB->setChecked(true);
        ui->channel6CB->setChecked(true);
        ui->channel7CB->setChecked(true);
        ui->channel8CB->setChecked(true);

        ui->channel1CB->setEnabled(true);
        ui->channel2CB->setEnabled(true);
        ui->channel3CB->setEnabled(true);
        ui->channel4CB->setEnabled(true);
        ui->channel5CB->setEnabled(true);
        ui->channel6CB->setEnabled(true);
        ui->channel7CB->setEnabled(true);
        ui->channel8CB->setEnabled(true);

        acquisitionServer.write("b");
    }

    salida.open("bytesleidos.txt");
}

void Principal::on_stopPushButton_clicked()
{
    acquisitionServer.write("s");
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
    ui->openGLWidget->move(10, 80);
    ui->openGLWidget->resize(width() - 100, height() - 120);
    ui->channel1CB->move(width() - 80, 10);
    ui->channel2CB->move(width() - 80, 40);
    ui->channel3CB->move(width() - 80, 70);
    ui->channel4CB->move(width() - 80, 100);
    ui->channel5CB->move(width() - 80, 130);
    ui->channel6CB->move(width() - 80, 160);
    ui->channel7CB->move(width() - 80, 190);
    ui->channel8CB->move(width() - 80, 220);

    ui->testPB->move(width() - 80, 300);
}

void Principal::on_channel1CB_toggled(bool checked)
{
    if (checked)
        acquisitionServer.write("!");
    else
        acquisitionServer.write("1");
}

void Principal::on_channel2CB_toggled(bool checked)
{
    if (checked)
        acquisitionServer.write("@");
    else
        acquisitionServer.write("2");
}

void Principal::on_channel3CB_toggled(bool checked)
{
    if (checked)
        acquisitionServer.write("#");
    else
        acquisitionServer.write("3");
}

void Principal::on_channel4CB_toggled(bool checked)
{
    if (checked)
        acquisitionServer.write("$");
    else
        acquisitionServer.write("4");
}

void Principal::on_channel5CB_toggled(bool checked)
{
    if (checked)
        acquisitionServer.write("%");
    else
        acquisitionServer.write("5");
}

void Principal::on_channel6CB_toggled(bool checked)
{
    if (checked)
        acquisitionServer.write("^");
    else
        acquisitionServer.write("6");
}

void Principal::on_channel7CB_toggled(bool checked)
{
    if (checked)
        acquisitionServer.write("&");
    else
        acquisitionServer.write("7");
}

void Principal::on_channel8CB_toggled(bool checked)
{
    if (checked)
        acquisitionServer.write("*");
    else
        acquisitionServer.write("8");
}

void Principal::on_testPB_clicked()
{
    acquisitionServer.write("]");
}

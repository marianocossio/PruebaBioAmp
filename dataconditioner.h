#ifndef DATACONDITIONER_H
#define DATACONDITIONER_H

#include <QObject>

class DataConditioner : public QObject
{
    Q_OBJECT
public:
    explicit DataConditioner(QObject *parent = 0);

signals:

public slots:
};

#endif // DATACONDITIONER_H
#ifndef GRAPH_H
#define GRAPH_H

#include <QOpenGLWidget>
#include <QVector>

class Graph : public QOpenGLWidget
{
    Q_OBJECT

public:
    Graph(QWidget *parent);

    void addData(QVector<int> data);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    QVector< QVector<int> > localSignals;

    void printSignal(int signalIndex);
};

#endif // GRAPH_H

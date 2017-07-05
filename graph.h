#ifndef GRAPH_H
#define GRAPH_H

#include <QOpenGLWidget>
#include <QVector>

class Graph : public QOpenGLWidget
{
    Q_OBJECT

public:
    Graph(QWidget *parent);

    void addData(int data);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    QVector<int> signal;
};

#endif // GRAPH_H

#include "graph.h"

Graph::Graph(QWidget *parent = 0) : QOpenGLWidget(parent)
{

}

void Graph::addData(int data)
{
    if (signal.size() >= width())
        signal.clear();

    signal.push_back(data);

    update();
}

void Graph::initializeGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void Graph::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, w * 1.0f, -100.0f, 100.0f, -1.0f, 1.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Graph::paintGL()
{
    glPushMatrix();

    glBegin(GL_LINES);

    glColor3f(0.0f, 1.0f, 0.0f);

    for (int i = 0; i < signal.size() - 1; i++)
    {
        glVertex3f(i * 1.0f, signal[i] * 1.0f, 0.0f);
        glVertex3f((i + 1) * 1.0f, signal[i + 1] * 1.0f, 0.0f);
    }

    glEnd();
}

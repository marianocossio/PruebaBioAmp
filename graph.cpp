#include "graph.h"

Graph::Graph(QWidget *parent = 0) : QOpenGLWidget(parent)
{
    localSignals.resize(8);
}

void Graph::addData(QVector<int> data)
{
    if (localSignals[0].size() >= width())
        for (int index = 0; index < localSignals.size(); index++)
            localSignals[index].clear();

    for (int index = 0; index < localSignals.size(); index++)
        localSignals[index].push_back(data[index]);

    update();
}

void Graph::initializeGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void Graph::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h / localSignals.size());

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, w * 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Graph::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    for (int index = 0; index < localSignals.size(); index++)
        printSignal(index);

    glFlush();
}

void Graph::printSignal(int signalIndex)
{
    glViewport(0, signalIndex * (height() / localSignals.size()), width(), height() / localSignals.size());

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, width() * 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_DEPTH_BUFFER_BIT);

    glPushMatrix();

    glBegin(GL_LINES);

    glColor3f(0.0f, 1.0f, 0.0f);

    for (int i = 0; i < localSignals[signalIndex].size() - 1; i++)
    {
        glVertex3f(i * 1.0f, localSignals[signalIndex][i] / (90000 * 1.0f), 0.0f);
        glVertex3f((i + 1) * 1.0f, localSignals[signalIndex][i + 1] / (90000 * 1.0f), 0.0f);
    }

    glEnd();

    glPopMatrix();
}

#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QDebug>

class GLWidget : public QOpenGLWidget
{
public:
    GLWidget(QWidget* parent = nullptr,Qt::WindowFlags f =Qt::WindowFlags());
    ~GLWidget();
protected:
    virtual void initializeGL();
    virtual void resizeGL(int w,int h);
    virtual void paintGL();

private:
    GLuint shaderProgram;
    QOpenGLFunctions_3_3_Core* core;
};

#endif // GLWIDGET_H

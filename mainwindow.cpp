#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionopen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("select File"),".");
    qDebug() << fileName;
    ui->openGLWidget->changeObjModel(fileName);
}

void MainWindow::on_checkBox_clicked(bool checked)
{
    //check box of line mode
    if(checked)
        ui->openGLWidget->isLineMode = GL_TRUE;
    else
        ui->openGLWidget->isLineMode = GL_FALSE;
}

void MainWindow::on_checkBox_2_clicked(bool checked)
{
    //check box of lighting
    if(checked)
        ui->openGLWidget->isOpenLighting = GL_TRUE;
    else {
        ui->openGLWidget->isOpenLighting = GL_FALSE;
    }
}

#include "cameraform.h"
#include "ui_cameraform.h"

#include <QCamera>
#include <QCameraInfo>
#include <QCameraViewfinder>
#include <QMediaRecorder>
#include <QMediaMetaData>
#include <QVideoProbe>
#include <QCameraImageCapture>
#include <QDebug>

CameraForm::CameraForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CameraForm)
{
    ui->setupUi(this);

    camera = new QCamera(QCameraInfo::defaultCamera(), this);
    viewfinder = new DCameraView(ui->widget);
    viewfinder->resize(150,150);
    viewfinder->setAspectRatioMode(Qt::KeepAspectRatioByExpanding);

    viewfinder->move(ui->widget->width()/2-viewfinder->width()/2, ui->widget->height()/2-viewfinder->height()/2);

    if(camera){
        viewfinder->setSource(camera);
        camera->start();
    }
}

CameraForm::~CameraForm()
{
    camera->stop();
    delete ui;
}

void CameraForm::on_horizontalSlider_valueChanged(int value)
{
    viewfinder->setScale(1+value/50.0);
}

void CameraForm::on_pushButton_clicked()
{
    ui->label->setPixmap(viewfinder->capture());
}

void CameraForm::on_pushButton_2_clicked()
{
    viewfinder->setMirroredHorizontal(!viewfinder->mirroredHorizontal());
}

void CameraForm::on_pushButton_3_clicked()
{
    viewfinder->setRound(!viewfinder->round());
}

#include "modelwindow.h"
#include <QKeyEvent>
#include <QTimer>

ModelWindow::~ModelWindow(){
}

ModelWindow::ModelWindow()
{
    qDebug() << "constructor called";
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateCaption()));
    timer->start(1000);

}

void ModelWindow::updateCaption(){
    ticks++;
    qDebug() <<  QString::fromStdString("tick" +  std::to_string(ticks));
} 

void ModelWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        //myLabel->setText("You pressed ESC");
	qDebug() << "You pressed ESC";
    }
}
 
void ModelWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        //myLabel->setText("You released ESC");
	qDebug() << "You released ESC";
	ModelWindow::quitApplication();
    }
}

//void ModelWindow::quitApplication()
//{
//
//}

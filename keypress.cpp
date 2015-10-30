#include "keypress.h"
 
#include <QApplication>
#include <QKeyEvent>
 
KeyPress::KeyPress(QWidget *parent) :
    QWidget(parent)
{
    myLabel = new QLabel("LABEL");
    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(myLabel);
    setLayout(mainLayout);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateCaption()));
    timer->start(1000);
 
}

void KeyPress::updateCaption(){
	ticks++;
	QString message = QString::fromStdString("tick" +  std::to_string(ticks));
	myLabel->setText(message);
} 
void KeyPress::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        myLabel->setText("You pressed ESC");
	qDebug() << "You pressed ESC";
    }
}
 
void KeyPress::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        myLabel->setText("You released ESC");
	qDebug() << "You released ESC";
    }
}

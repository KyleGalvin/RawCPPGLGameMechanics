#ifndef KEYPRESS_H
#define KEYPRESS_H
 
#include <QWidget>
#include <QtGui>
#include <QLabel>
#include <QVBoxLayout> 

class KeyPress : public QWidget
{
    Q_OBJECT
public:
    KeyPress(QWidget *parent = 0);

public slots: 
    void updateCaption(); 
 
protected:
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
private:
    int ticks = 0;
    QLabel *myLabel;
    QVBoxLayout *mainLayout;
};
 
#endif // KEYPRESS_H

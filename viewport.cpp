#include "viewport.h"
#include <QKeyEvent>
#include <QTimer>

Viewport::~Viewport() {
}

Viewport::Viewport()
{
  qDebug() << "constructor called";
  QTimer *timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(updateCaption()));
  timer->start(20);


  //convention: XYZ maps to element 012 respectively

  //x-axis
  Right.reset( new std::vector< double > ());
  Right->push_back(1);
  Right->push_back(0);
  Right->push_back(0);

  //camera looks down the z-axis
  Target.reset( new std::vector< double > ());
  Target->push_back(0);
  Target->push_back(0);
  Target->push_back(1);

  //y-axis at the top
  Up.reset( new std::vector< double > ());
  Up->push_back(0);
  Up->push_back(1);
  Up->push_back(0);

  //camera is a point...
  Dimensions.push_back(0);
  Dimensions.push_back(0);
  Dimensions.push_back(0);
  //...at the origin...
  Location.push_back(0);
  Location.push_back(0);
  Location.push_back(0);
  //..with no rotation
  Rotation.push_back(0);
  Rotation.push_back(0);
  Rotation.push_back(0);

  mass = 10.0;
  friction = 0.5;
  zoom = 45.0;
  maxSpeed = 0.01;
  minSpeed = 0.0001;

  xVel = 0.0;
  yVel = 0.0;
  zVel = 0.0;

  xAcc = 0.0;
  yAcc = 0.0;
  zAcc = 0.0;
}

void Viewport::updateCaption() {
  step();
}

void Viewport::keyPressEvent(QKeyEvent *event)
{
  if (event->key() == Qt::Key_Escape)
  {
    qDebug() << "You pressed ESC";
  } else if ( tolower( event->key() ) == 'w') {
    buttonInput[0] = true;
  } else if ( tolower( event->key() ) == 'a') {
    buttonInput[1] = true;
  } else if ( tolower( event->key() ) == 's') {
    buttonInput[3] = true;
  } else if ( tolower( event->key() ) == 'd') {
    buttonInput[4] = true;
  }
}

void Viewport::keyReleaseEvent(QKeyEvent *event)
{
  if (event->key() == Qt::Key_Escape)
  {
    qDebug() << "You released ESC";
    Viewport::quitApplication();
  } else if ( tolower( event->key() ) == 'w') {
    buttonInput[0] = false;
  } else if ( tolower( event->key() ) == 'a') {
    buttonInput[1] = false;
  } else if ( tolower( event->key() ) == 's') {
    buttonInput[3] = false;
  } else if ( tolower( event->key() ) == 'd') {
    buttonInput[4] = false;
  }
}

void Viewport::stepAxis(bool positiveButton, bool negativeButton, float* speedAlongAxis) {
  if (positiveButton == false && negativeButton == false) { //coast to a stop
    if (*speedAlongAxis > 0 &&  *speedAlongAxis < minSpeed) {
      *speedAlongAxis = 0;
    } else if (*speedAlongAxis < 0 && *speedAlongAxis > -minSpeed) {
      *speedAlongAxis = 0;
    } else if (*speedAlongAxis > 0) {
      *speedAlongAxis = *speedAlongAxis - minSpeed;
    } else if (*speedAlongAxis < 0) {
      *speedAlongAxis = *speedAlongAxis + minSpeed;
    }
  } else if ((positiveButton && speedAlongAxis >= 0) || (negativeButton && speedAlongAxis <= 0)) { //accelerate towards full speed
    *speedAlongAxis = *speedAlongAxis + ((int) positiveButton - (int) negativeButton);
  } else { //actively braking / changing direction. stop faster
    *speedAlongAxis = *speedAlongAxis + ((int) positiveButton - (int) negativeButton) * 6;
  }
}


void Viewport::step() {
  //set acceleration
  /*
      index = direction * (positive*1 || negative*2)
      index = {up,left,forward,down,right,backward}
  */
  stepAxis(buttonInput[0], buttonInput[3], &yVel);
  stepAxis(buttonInput[4], buttonInput[1], &xVel);
  stepAxis(buttonInput[2], buttonInput[5], &zVel);

  float rotSpeed = 1;
  if (buttonInput[6]) {
    rotateX(rotSpeed);
  }
  if (buttonInput[9]) {
    rotateX(-rotSpeed);
  }
  if (buttonInput[10]) {
    rotateY(rotSpeed);
  }
  if (buttonInput[7]) {
    rotateY(-rotSpeed);
  }
  if (buttonInput[8]) {
    rotateZ(rotSpeed);
  }
  if (buttonInput[11]) {
    rotateZ(-rotSpeed);
  }



  if (xVel > maxSpeed) { //enforce max speeds
    xVel = maxSpeed;
  } else if (xVel < -maxSpeed) {
    xVel = -maxSpeed;
  }
  if (yVel > maxSpeed) { //enforce max speeds
    yVel = maxSpeed;
  } else if (yVel < -maxSpeed) {
    yVel = -maxSpeed;
  }
  if (zVel > maxSpeed) { //enforce max speeds
    zVel = maxSpeed;
  } else if (zVel < -maxSpeed) {
    zVel = -maxSpeed;
  }

  translateRight(xVel);
  translateUp(yVel);
  translateForward(zVel);
}


void Viewport::pushUp(bool btnDown) {
  buttonInput[0] = btnDown;
}
void Viewport::pushLeft(bool btnDown) {
  buttonInput[1] = btnDown;
}
void Viewport::pushForward(bool btnDown) {
  buttonInput[2] = btnDown;
}
void Viewport::pushDown(bool btnDown) {
  buttonInput[3] = btnDown;
}
void Viewport::pushRight(bool btnDown) {
  buttonInput[4] = btnDown;
}
void Viewport::pushBackward(bool btnDown) {
  buttonInput[5] = btnDown;
}
void Viewport::tiltDown(bool btnDown) {
  buttonInput[6] = btnDown;
}
void Viewport::tiltUp(bool btnDown) {
  buttonInput[9] = btnDown;
}
void Viewport::panLeft(bool btnDown) {
  buttonInput[10] = btnDown;
}
void Viewport::panRight(bool btnDown) {
  buttonInput[7] = btnDown;
}
void Viewport::yawCW(bool btnDown) {
  buttonInput[8] = btnDown;
}
void Viewport::yawCCW(bool btnDown) {
  buttonInput[11] = btnDown;
}



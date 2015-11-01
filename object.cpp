#include "object.h"
#include "math.h"

void Object::calculateAcceleration( std::vector< double >  NetForce) {
  xAcc = (NetForce[0] / mass) - (friction * xVel);
  yAcc = (NetForce[1] / mass) - (friction * yVel);
  zAcc = (NetForce[2] / mass) - (friction * zVel);
}
void Object::Normalize(boost::scoped_ptr< std::vector< double > > *vec) {
  //normalize!
  float len = sqrt(((**vec)[0] * (**vec)[0]) + ((**vec)[1] * (**vec)[1]) + ((**vec)[2] * (**vec)[2]));
  (**vec)[0] /= len;
  (**vec)[1] /= len;
  (**vec)[2] /= len;
}
void Object::accUp(float y) {
  yAcc += y;
}

void Object::accRight(float x) {
  xAcc += x;
}

void Object::accForward(float z) {
  zAcc += z;
}

void Object::velUp(float y) {
  yVel += y;
}
void Object::velRight(float x) {
  xVel += x;
}
void Object::velForward(float z) {
  zVel += z;
}
void Object::rotateX(float amount)
{
  //mod 360 for sane numbers
  int IntAmount = (int) amount;
  int AdjustedIntAmount = IntAmount % 360;
  //save the decimal/fraction
  amount -= IntAmount;
  //add the simplified whole with the fraction
  amount += AdjustedIntAmount;

  std::vector< double >  tempTarget = *Target;
  std::vector< double >  tempUp = *Up;

  amount /= 57.2957795f; // convert degrees to radians

  (*Target)[0] = (cos(amount) * tempTarget[0]) - (sin(amount) * tempUp[0]);
  (*Target)[1] = (cos(amount) * tempTarget[1]) - (sin(amount) * tempUp[1]);
  (*Target)[2] = (cos(amount) * tempTarget[2]) - (sin(amount) * tempUp[2]);

  (*Up)[0] = (cos(amount) * tempUp[0]) + (sin(amount) * tempTarget[0]);
  (*Up)[1] = (cos(amount) * tempUp[1]) + (sin(amount) * tempTarget[1]);
  (*Up)[2] = (cos(amount) * tempUp[2]) + (sin(amount) * tempTarget[2]);

  Normalize(&Target);
  Normalize(&Up);
}

void Object::rotateY(float amount)
{
  //mod 360 for sane numbers
  int IntAmount = (int) amount;
  int AdjustedIntAmount = IntAmount % 360;
  //save the decimal/fraction
  amount -= IntAmount;
  //add the simplified whole with the fraction
  amount += AdjustedIntAmount;

  std::vector< double >  tempTarget = *Target;
  std::vector< double >  tempRight = *Right;

  amount /= 57.2957795f; // convert degrees to radians

  (*Target)[0] = (cos(amount) * tempTarget[0]) + (sin(amount) * tempRight[0]);
  (*Target)[1] = (cos(amount) * tempTarget[1]) + (sin(amount) * tempRight[1]);
  (*Target)[2] = (cos(amount) * tempTarget[2]) + (sin(amount) * tempRight[2]);


  (*Right)[0] = (cos(amount) * tempRight[0]) - (sin(amount) * tempTarget[0]);
  (*Right)[1] = (cos(amount) * tempRight[1]) - (sin(amount) * tempTarget[1]);
  (*Right)[2] = (cos(amount) * tempRight[2]) - (sin(amount) * tempTarget[2]);

  Normalize(&Right);
  Normalize(&Target);
}

void Object::rotateZ(float amount)
{
  //mod 360 for sane numbers
  int IntAmount = (int) amount;
  int AdjustedIntAmount = IntAmount % 360;
  //save the decimal/fraction
  amount -= IntAmount;
  //add the simplified whole with the fraction
  amount += AdjustedIntAmount;

  std::vector< double >  tempRight = *Right;
  std::vector< double >  tempUp = *Up;

  amount /= 57.2957795f; // convert degrees to radians

  (*Up)[0] = (cos(amount) * tempUp[0]) - (sin(amount) * tempRight[0]);
  (*Up)[1] = (cos(amount) * tempUp[1]) - (sin(amount) * tempRight[1]);
  (*Up)[2] = (cos(amount) * tempUp[2]) - (sin(amount) * tempRight[2]);

  (*Right)[0] = (cos(amount) * tempRight[0]) + (sin(amount) * tempUp[0]);
  (*Right)[1] = (cos(amount) * tempRight[1]) + (sin(amount) * tempUp[1]);
  (*Right)[2] = (cos(amount) * tempRight[2]) + (sin(amount) * tempUp[2]);

  Normalize(&Up);
  Normalize(&Right);
}

void Object::translateUp(float amount) {
  Location[0] += (*Up)[0] * amount;
  Location[1] += (*Up)[1] * amount;
  Location[2] += (*Up)[2] * amount;
}
void Object::translateForward(float amount) {
  Location[0] += (*Target)[0] * amount;
  Location[1] += (*Target)[1] * amount;
  Location[2] += (*Target)[2] * amount;
}
void Object::translateRight(float amount) {
  Location[0] += (*Right)[0] * amount;
  Location[1] += (*Right)[1] * amount;
  Location[2] += (*Right)[2] * amount;
}

void Object::translateX(float amount) {
  Location[0] += amount;
}

void Object::translateY(float amount) {
  Location[1] += amount;
}

void Object::translateZ(float amount) {
  Location[2] += amount;
}
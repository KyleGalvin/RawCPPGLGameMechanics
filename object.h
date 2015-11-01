#ifndef OBJECT_H
#define OBJECT_H

#include "boost/scoped_ptr.hpp"
#include <vector>

class Object {
public:

  boost::scoped_ptr< std::vector< double > > Up;
  boost::scoped_ptr< std::vector< double > > Target;
  boost::scoped_ptr< std::vector< double > > Right;

  std::vector< double > Location;
  std::vector< double > Dimensions;
  std::vector< double > Rotation;

  int texture;
  float xVel;
  float yVel;
  float zVel;

  float xAcc;
  float yAcc;
  float zAcc;

  float mass;
  float friction;
  float maxSpeed;

  void calculateAcceleration( std::vector< double >  NetForce);
  void Normalize(boost::scoped_ptr< std::vector< double > > *vec);

  void accUp(float y);
  void accRight(float x);
  void accForward(float z);

  void velUp(float y);
  void velRight(float x);
  void velForward(float z);

  void rotateX(float amount);
  void rotateY(float amount);
  void rotateZ(float amount);

  void translateUp(float amount);
  void translateForward(float amount);
  void translateRight(float amount);

  void translateX(float amount);
  void translateY(float amount);
  void translateZ(float amount);
};
#endif // OBJECT_H
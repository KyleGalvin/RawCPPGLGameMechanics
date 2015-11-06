#ifndef MODELWINDOW_H
#define MODELWINDOW_H

#include <string>
#include <QWidget>
#include <QTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions>
#include <vector>

#include "boost/scoped_ptr.hpp"

#include "object.h"
#include "model.h"
#include "openglwindow.h"
#include "modelloader.h"

struct Force {
  boost::scoped_ptr< std::vector< double > > direction;
  float magnitude;
};

// OpenGL 2.1/OpenGL ES -- Inherit from QOpenGLFunctions to get OpenGL 2.1/OpenGL ES 2.0 functions
class Viewport : public OpenGLWindow, public Object
{
  Q_OBJECT
public:

  //Viewport(QString filepath, ModelLoader::PathType pathType, QString texturePath="", QWidget *parent=0);
  ~Viewport();
  Viewport();

  void step();
  void pushUp(bool btnDown);
  void pushLeft(bool btnDown);
  void pushForward(bool btnDown);
  void pushDown(bool btnDown);
  void pushRight(bool btnDown);
  void pushBackward(bool btnDown);
  void tiltDown(bool btnDown);
  void tiltUp(bool btnDown);
  void panLeft(bool btnDown);
  void panRight(bool btnDown);
  void yawCW(bool btnDown);
  void yawCCW(bool btnDown);

public slots:
  void updateCaption();

signals:
  void quitApplication();

protected:
  void keyPressEvent(QKeyEvent *);
  void keyReleaseEvent(QKeyEvent *);

private:
  virtual void createShaderProgram( QString vShader, QString fShader) = 0;
  virtual void createBuffers() = 0;
  virtual void createAttributes() = 0;
  virtual void setupLightingAndMatrices() = 0;

  void stepAxis(bool, bool, float*);

  boost::scoped_ptr< std::vector< Model > > models;

  boost::scoped_ptr<Force> UpForce;
  boost::scoped_ptr<Force> ForwardForce;
  boost::scoped_ptr<Force> RightForce;

  float zoom;
  float maxSpeed;
  float minSpeed;

  //controller state
  bool buttonInput[12] = {0, //up
                          0,//left
                          0,//forward
                          0,//down
                          0,//right
                          0,//backward

                          0,//rotUp
                          0,//rotLeft
                          0,//rotForward
                          0,//rotDown
                          0,//rotRight
                          0
                         };//rotBackward

  //virtual void draw();
  void drawNode(const Node *node, QMatrix4x4 objectMatrix);
  void setMaterialUniforms(MaterialInfo &mater);



  QOpenGLShaderProgram m_shaderProgram;

  QOpenGLBuffer m_vertexBuffer;
  QOpenGLBuffer m_normalBuffer;
  QOpenGLBuffer m_textureUVBuffer;
  QOpenGLBuffer m_indexBuffer;

  QSharedPointer<Node> m_rootNode;

  QMatrix4x4 m_projection, m_view, m_model, m_model2;

  QString m_filepath;
  ModelLoader::PathType m_pathType;
  QString m_texturePath;

  LightInfo m_lightInfo;
  MaterialInfo m_materialInfo;

  bool m_error;
  int ticks = 0;
};

#endif // MODELWINDOW_H

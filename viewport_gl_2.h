#ifndef MODELWINDOW_GL_2_H
#define MODELWINDOW_GL_2_H

#include <string>
#include <QWidget>
#include <QTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions>
#include "viewport.h"
#include "modelloader.h"

// OpenGL 2.1/OpenGL ES -- Inherit from QOpenGLFunctions to get OpenGL 2.1/OpenGL ES 2.0 functions
class Viewport_GL_2 : public QOpenGLFunctions, public Viewport
{
  using Viewport::Viewport;//forward constructor args
  //Q_OBJECT
public:
  Viewport_GL_2(QString filepath, ModelLoader::PathType pathType, QString texturePath = "");

public slots:
  void quitApplication();

protected:
  void initializeGL();
  void resizeGL(int w, int h);
  void paintGL();
  void cleanupGL();
  //void keyPressEvent(QKeyEvent *);
  //void keyReleaseEvent(QKeyEvent *);

private:
  void createShaderProgram( QString vShader, QString fShader);
  void createBuffers();
  void createAttributes();
  void setupLightingAndMatrices();

  //void draw();
  void drawNode(const Node *node, QMatrix4x4 objectMatrix);
  void setMaterialUniforms(MaterialInfo &mater);

  QOpenGLShaderProgram m_shaderProgram;

  QOpenGLBuffer m_vertexBuffer;
  QOpenGLBuffer m_normalBuffer;
  QOpenGLBuffer m_textureUVBuffer;
  QOpenGLBuffer m_indexBuffer;

  QSharedPointer<Node> m_rootNode;

  QMatrix4x4 m_projection, m_view, m_model;

  QString m_filepath;
  ModelLoader::PathType m_pathType;
  QString m_texturePath;

  LightInfo m_lightInfo;
  MaterialInfo m_materialInfo;

  bool m_error;
  int ticks = 0;
};

#endif // MODELWINDOW_GL_2_H

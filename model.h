#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <vector>
//#include cjson

class Scene : public Scene {
  bool unpacked = false;
public:
  Scene OpenScene(QString filename);
  //OpenScene calls this -- void UnpackScene();
  vector< Model > objects;
};

class Model : public Object {
public:
  QOpenGLBuffer m_vertexBuffer;
  QOpenGLBuffer m_normalBuffer;
  QOpenGLBuffer m_textureUVBuffer;
  QOpenGLBuffer m_indexBuffer;
  QMatrix4x4 m_model;
};

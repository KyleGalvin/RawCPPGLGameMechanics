#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

class Model : public Object {
public:

  QOpenGLBuffer m_vertexBuffer;
  QOpenGLBuffer m_normalBuffer;
  QOpenGLBuffer m_textureUVBuffer;
  QOpenGLBuffer m_indexBuffer;
  QMatrix4x4 m_model;
};

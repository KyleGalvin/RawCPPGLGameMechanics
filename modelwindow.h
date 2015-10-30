#ifndef MODELWINDOW_H
#define MODELWINDOW_H

#include <string>
#include <QWidget>
#include <QTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions>
#include "openglwindow.h"
#include "modelloader.h"

// OpenGL 2.1/OpenGL ES -- Inherit from QOpenGLFunctions to get OpenGL 2.1/OpenGL ES 2.0 functions
class ModelWindow : public OpenGLWindow
{
    Q_OBJECT
public:

    //ModelWindow(QString filepath, ModelLoader::PathType pathType, QString texturePath="", QWidget *parent=0);
    ~ModelWindow();
    ModelWindow();

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

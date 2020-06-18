#ifndef WIZUALIZACJAKOSC_H
#define WIZUALIZACJAKOSC_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QtOpenGL>
#include <QOpenGLBuffer>
#include <QSurfaceFormat>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QMouseEvent>
#include <QColor>
#include <QSlider>
#include <QObject>


QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram);
QT_FORWARD_DECLARE_CLASS(QOpenGLTexture)

class WizualizacjaKosc : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    using QOpenGLWidget::QOpenGLWidget;

    ~WizualizacjaKosc();

    void obroc(int x_a, int y_a, int z_a);
    void setClearColor(const QColor &color);

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

signals:
private:
    void utworz_kosc();
    QColor clearColor;
    QPoint lastPos;

    QSlider* Sender;

    int xRot = 0;
    int yRot = 0;
    int zRot = 0;
    QOpenGLTexture *textury_kosc[6] = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
    QOpenGLShaderProgram *program = nullptr;
    QOpenGLBuffer vbo;

public slots:

    void obrocX(int val);
    void obrocY(int val);
    void obrocZ(int val);

};

#endif // WIZUALIZACJAKOSC_H

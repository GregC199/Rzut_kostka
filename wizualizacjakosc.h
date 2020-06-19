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

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

    void x_okresl_zakres();
    void y_okresl_zakres();
    void z_okresl_zakres();
    void okres_zakresy();
    int x_zakres = 0;
    int y_zakres = 0;
    int z_zakres = 0;

    int mem_sciana = 1;

    bool czy_slider;

    int sciany[4][4][4] = {{{1,1,1,1},{3,5,4,2},{6,6,6,6},{4,2,3,5}},
                           {{5,4,2,3},{5,4,2,3},{5,4,2,3},{5,4,2,3}},
                           {{6,6,6,6},{4,2,3,5},{1,1,1,1},{3,5,4,2}},
                           {{2,3,5,4},{2,3,5,4},{2,3,5,4},{2,3,5,4}}};

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

signals:
    void emituj_zmiane_sciany(int value);

private:

    void normalizuj_kat(int &kat);

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

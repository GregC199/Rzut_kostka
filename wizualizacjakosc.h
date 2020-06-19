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

#define PROGRAM_VERTEX_ATTRIBUTE 0
#define PROGRAM_TEXCOORD_ATTRIBUTE 1

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram);
QT_FORWARD_DECLARE_CLASS(QOpenGLTexture)

/*!
 * \brief Implementacja klasy \link WizualizacjaKosc\endlink będącej reimplementacją klasy QOpenGlWidget
 *
 * Klasa ta tworzy obiekt OpenGL służący do wizualizacji kości.
 *
 */

class WizualizacjaKosc : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    /*!
     * \brief Wykorzystanie konstruktora dla dziedziczonej klasy QOpenGLWidget
     */
    using QOpenGLWidget::QOpenGLWidget;

    /*!
     * \brief Destruktor obiektu klasy
     *
     */
    ~WizualizacjaKosc();

    /*!
     * \brief Obrót wzdłuż trzech osi
     *
     */
    void obroc(int x_a, int y_a, int z_a);

    /*!
     * \brief Zmiana koloru tła widgetu
     *
     */
    void setClearColor(const QColor &color);

    /*!
     * \brief Nadpisanie minimalnego preferowanego rozmiaru
     *
     */
    QSize minimumSizeHint() const override;
    /*!
     * \brief Nadpisanie preferowanego rozmiaru
     *
     */
    QSize sizeHint() const override;

    /*!
     * \brief Określenie położenia kości na osi OX
     *
     */
    void x_okresl_zakres();
    /*!
     * \brief Określenie położenia kości na osi OY
     *
     */
    void y_okresl_zakres();
    /*!
     * \brief Określenie położenia kości na osi OZ
     *
     */
    void z_okresl_zakres();
    /*!
     * \brief Określenie położenia kości we wszystkich trzech osiach
     *
     */
    void okresl_zakresy();
    /*!
     *  \param[in] x_zakres -> zmienna przechowująca położenie w osi OX
     *  \param[in] y_zakres -> zmienna przechowująca położenie w osi OY
     *  \param[in] z_zakres -> zmienna przechowująca położenie w osi OZ
     */
    int x_zakres = 0;
    int y_zakres = 0;
    int z_zakres = 0;

    /*!
     *  \param[in] mem_sciana -> zmienna przechowująca poprzednią wartość ściany
     *  \param[in] czy_slider -> zmienna określająca czy zmiana kąta odbyła się za pomocą slidera
     *  \param[in] sciany -> tablica3D przechowująca wartości górnej ściany dla każdego z możliwych położeń kości
     */
    int mem_sciana = 1;

    bool czy_slider;

    int sciany[4][4][4] = {{{1,1,1,1},{3,5,4,2},{6,6,6,6},{4,2,3,5}},
                           {{5,4,2,3},{5,4,2,3},{5,4,2,3},{5,4,2,3}},
                           {{6,6,6,6},{4,2,3,5},{1,1,1,1},{3,5,4,2}},
                           {{2,3,5,4},{2,3,5,4},{2,3,5,4},{2,3,5,4}}};

protected:
    /*!
     * \brief Inicjalizacja obiektu OpenGL - kości
     *
     */
    void initializeGL() override;

    /*!
     * \brief Odrysowanie kości
     *
     */
    void paintGL() override;

    /*!
     * \brief Zmiana rozmiarów kości
     *
     */
    void resizeGL(int w, int h) override;

signals:
    /*!
     * \brief Emituje zmianę wartości górnej ściany kostki
     *
     */
    void emituj_zmiane_sciany(int value);

private:

    /*!
     * \brief Funkcja odpowiadająca za normalizację kąta
     *
     */
    void normalizuj_kat(int &kat);

    /*!
     * \brief Funkcja odpowiedzialna za utworzenie samej kostki
     *
     */
    void utworz_kosc();


    /*!
     * \param[in] clearColor -> zmienna służaca do nadawania koloru tła Widgetu,
     * \param[in] lastPos -> ostatnia pozycja,
     * \param[in] Sender -> wskaźnik na wysyłającego sygnał
     *
     */


    QColor clearColor;
    QPoint lastPos;

    QSlider* Sender;

    /*!
     *  \param[in] xRot -> kąt kości wzdłuż osi OX
     *  \param[in] yRot -> kąt kości wzdłuż osi OY
     *  \param[in] zRot -> kąt kości wzdłuż osi OZ
     *  \param[in] textury_kosc -> tablica przechowująca tekstury kości
     *  \param[in] program -> OpenGLShaderProgram - obsługujący wyświetlanie kości
     *  \param[in] vbo -> OpenGLBuffer - bufor obsługujący wyświetlanie kości
     */

    int xRot = 0;
    int yRot = 0;
    int zRot = 0;

    QOpenGLTexture *textury_kosc[6] = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
    QOpenGLShaderProgram *program = nullptr;

    QOpenGLBuffer vbo;

public slots:

    /*!
     * \brief Slot obrotu kości o zadany kąt wzdłuż osi OX
     *
     */
    void obrocX(int val);
    /*!
     * \brief Slot obrotu kości o zadany kąt wzdłuż osi OY
     *
     */
    void obrocY(int val);
    /*!
     * \brief Slot obrotu kości o zadany kąt wzdłuż osi OZ
     *
     */
    void obrocZ(int val);

};

#endif // WIZUALIZACJAKOSC_H

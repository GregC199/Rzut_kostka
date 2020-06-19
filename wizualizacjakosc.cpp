#include "wizualizacjakosc.h"
#include <iostream>

/*!
 * \brief Obrót wzdłuż trzech osi
 *
 * Kość jest obracana o znormalizowane kąty:
 * ->\link x_a\endlink wzdłuż osi OX,
 * ->\link y_a\endlink wzdłuż osi OY,
 * ->\link z_a\endlink wzdłuż osi OZ.
 *
 * Następnie określana jest orientacja kości za pomocą \link okresl_zakresy\endlink oraz aktualizwana wizualizacja kości.
 */
void WizualizacjaKosc::obroc(int x_a, int y_a, int z_a)
{
    this->xRot += x_a;
    this->yRot += y_a;
    this->zRot += z_a;
    normalizuj_kat(this->xRot);
    normalizuj_kat(this->yRot);
    normalizuj_kat(this->zRot);

    okresl_zakresy();

    this->paintGL();
    update();
}
/*!
 * \brief Nadpisanie preferowanego rozmiaru
 *
 */
QSize WizualizacjaKosc::sizeHint() const
{
    return QSize(200, 200);
}
/*!
 * \brief Określenie położenia kości we wszystkich trzech osiach
 *
 * Funkcja ta określa położenie kości wzdłuż każdej z trzech osi.
 * Dodatkowo w ramach optymalizacji kodu wykorzystano zmienną
 * \link czy_slider\endlink, aby zapobiec zbędnemu wywoływaniu podczas
 * sterowania kością z płytki.
 *
 * Na sam koniec, jeśli nastąpiła zmiana wartości na górnej ścianie,
 * wysyłany jest sygnał z wartością nowej ściany.
 */
void WizualizacjaKosc::okresl_zakresy(){
    czy_slider = 0;
    x_okresl_zakres();
    y_okresl_zakres();
    z_okresl_zakres();
    czy_slider = 1;
    if(mem_sciana != sciany[x_zakres][y_zakres][z_zakres]){
        emit emituj_zmiane_sciany(sciany[x_zakres][y_zakres][z_zakres]);
        mem_sciana = sciany[x_zakres][y_zakres][z_zakres];
    }
}
/*!
 * \brief Określenie położenia kości na osi OX
 *
 * Funkcja ta określa położenie kości wzdłuż osi OX i zapisuje je do zmiennej
 * \link x_zakres\endlink. Na sam koniec jeśli wywołanie funkcji pochodziło od Slidera
 * to emitujemy sygnał z wartością nowej ściany, jeśli nastąpiła zmiana wartości górnej ściany.
 */
void WizualizacjaKosc::x_okresl_zakres()
{
    for(int i = 0; i < 4;++i){
        if(xRot<(i*90+45) && xRot>((i-1)*90+45)){
            x_zakres = i;
        }
    }
    if(xRot>315 || xRot<45)x_zakres = 0;
    if(mem_sciana != sciany[x_zakres][y_zakres][z_zakres]){
        if(czy_slider == 1){
            emit emituj_zmiane_sciany(sciany[x_zakres][y_zakres][z_zakres]);
            mem_sciana = sciany[x_zakres][y_zakres][z_zakres];

        }
    }
    mem_sciana = sciany[x_zakres][y_zakres][z_zakres];
}
/*!
 * \brief Określenie położenia kości na osi OY
 *
 * Funkcja ta określa położenie kości wzdłuż osi OY i zapisuje je do zmiennej
 * \link y_zakres\endlink. Na sam koniec jeśli wywołanie funkcji pochodziło od Slidera
 * to emitujemy sygnał z wartością nowej ściany, jeśli nastąpiła zmiana wartości górnej ściany.
 */
void WizualizacjaKosc::y_okresl_zakres()
{
    for(int i = 0; i <= 4;++i){
        if(yRot<(i*90+45) && yRot>((i-1)*90+45)){
            y_zakres = i;
        }
    }
    if(yRot>315 || yRot<45)y_zakres = 0;
    if(mem_sciana != sciany[x_zakres][y_zakres][z_zakres]){
        if(czy_slider == 1){
            emit emituj_zmiane_sciany(sciany[x_zakres][y_zakres][z_zakres]);
            mem_sciana = sciany[x_zakres][y_zakres][z_zakres];

        }
    }
}
/*!
 * \brief Określenie położenia kości na osi OZ
 *
 * Funkcja ta określa położenie kości wzdłuż osi OZ i zapisuje je do zmiennej
 * \link z_zakres\endlink. Na sam koniec jeśli wywołanie funkcji pochodziło od Slidera
 * to emitujemy sygnał z wartością nowej ściany, jeśli nastąpiła zmiana wartości górnej ściany.
 */
void WizualizacjaKosc::z_okresl_zakres()
{
    for(int i = 1; i < 4;++i){
        if(zRot<(i*90+45) && zRot>((i-1)*90+45)){
            z_zakres = i;
        }
    }
    if(zRot>315 || zRot<45)z_zakres = 0;
    if(mem_sciana != sciany[x_zakres][y_zakres][z_zakres]){
        if(czy_slider == 1){
            emit emituj_zmiane_sciany(sciany[x_zakres][y_zakres][z_zakres]);
            mem_sciana = sciany[x_zakres][y_zakres][z_zakres];
        }
    }
}
/*!
 * \brief Nadpisanie minimalnego preferowanego rozmiaru
 *
 */
QSize WizualizacjaKosc::minimumSizeHint() const
{
    return QSize(50, 50);
}

/*!
 * \brief Funkcja odpowiadająca za normalizację kąta
 *
 * Funkcja normalizuje kąt zadany na wejściu.
 */
void WizualizacjaKosc::normalizuj_kat(int &kat)
{
    while (kat < 0)
        kat += 360;
    while (kat > 360)
        kat -= 360;
}

/*!
 * \brief Slot obrotu kości o zadany kąt wzdłuż osi OX
 *
 * Funkcja ta normalizuje wpierw wartość kątu zadaną przez sygnał,
 * a następnie przypisuje ją do kątu kości wzdłuż osi OX, określa
 * położenie oraz odrysowywuje kość.
 */
void WizualizacjaKosc::obrocX(int val)
{
    normalizuj_kat(val);
    xRot = val;

    x_okresl_zakres();

    this->paintGL();
    update();
}
/*!
 * \brief Slot obrotu kości o zadany kąt wzdłuż osi OY
 *
 * Funkcja ta normalizuje wpierw wartość kątu zadaną przez sygnał,
 * a następnie przypisuje ją do kątu kości wzdłuż osi OY, określa
 * położenie oraz odrysowywuje kość.
 */
void WizualizacjaKosc::obrocY(int val)
{
    normalizuj_kat(val);
    yRot = val;

    y_okresl_zakres();

    this->paintGL();
    update();
}
/*!
 * \brief Slot obrotu kości o zadany kąt wzdłuż osi OZ
 *
 * Funkcja ta normalizuje wpierw wartość kątu zadaną przez sygnał,
 * a następnie przypisuje ją do kątu kości wzdłuż osi OZ, określa
 * położenie oraz odrysowywuje kość.
 */
void WizualizacjaKosc::obrocZ(int val)
{
    normalizuj_kat(val);
    zRot = val;

    z_okresl_zakres();

    this->paintGL();
    update();
}
/*!
 * \brief Destruktor obiektu klasy
 *
 * Ustawiamy makeCurrent na "brak", następnie usuwamy buffor OpenGL'a,
 * usuwamy każdą z tekstur, aż w końcu usuwamy OpenGLShaderProgram \link program\endlink.
 *
 */
WizualizacjaKosc::~WizualizacjaKosc(){
    makeCurrent();
    vbo.destroy();
    for (int i = 0; i < 6; ++i)
        delete textury_kosc[i];
    delete program;
    doneCurrent();
}

/*!
 * \brief Zmiana koloru tła widgetu
 *
 */
void WizualizacjaKosc::setClearColor(const QColor &color)
{
    clearColor = color;
    this->update();
}
/*!
 * \brief Inicjalizacja obiektu OpenGL - kości
 *
 * Wpierw inicjalizujemy kolor tła Widgetu, następnie inicjalizujemy OpenGLFunctions,
 * i tworzymy naszą kość za pomocą funkcji \link utworz_kosc\endlink i zadajemy kolor tła.
 * Następnie inicjalizujemy GL_DEPTH_TEST w celu uzyskania 3D widgetu.
 * Potem inicjalizujemy vertex oraz fragment shadery i przekazujemy je do naszego
 * QOpenGLShaderProgram \link program\endlink. Następnie wiążemy \link program\endlink
 * z atrybutami lokacji vertex, a następnie texCoord. Potem wszystko łączymy i wiążemy.
 */
void WizualizacjaKosc::initializeGL()
{
    QColor kolor_tla;

    kolor_tla.setRgb(79,136,201);

    initializeOpenGLFunctions();

    setClearColor(kolor_tla);

    utworz_kosc();



    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

        QOpenGLShader *vshader = new QOpenGLShader(QOpenGLShader::Vertex, this);
        const char *vsrc =
            "attribute highp vec4 vertex;\n"
            "attribute mediump vec4 texCoord;\n"
            "varying mediump vec4 texc;\n"
            "uniform mediump mat4 matrix;\n"
            "void main(void)\n"
            "{\n"
            "    gl_Position = matrix * vertex;\n"
            "    texc = texCoord;\n"
            "}\n";
        vshader->compileSourceCode(vsrc);

        QOpenGLShader *fshader = new QOpenGLShader(QOpenGLShader::Fragment, this);
        const char *fsrc =
            "uniform sampler2D texture;\n"
            "varying mediump vec4 texc;\n"
            "void main(void)\n"
            "{\n"
            "    gl_FragColor = texture2D(texture, texc.st);\n"
            "}\n";
        fshader->compileSourceCode(fsrc);

        program = new QOpenGLShaderProgram;
        program->addShader(vshader);
        program->addShader(fshader);
        program->bindAttributeLocation("vertex", PROGRAM_VERTEX_ATTRIBUTE);
        program->bindAttributeLocation("texCoord", PROGRAM_TEXCOORD_ATTRIBUTE);
        program->link();

        program->bind();
        program->setUniformValue("texture", 0);

}
/*!
 * \brief Zmiana rozmiarów kości
 *
 */
void WizualizacjaKosc::resizeGL(int w, int h)
{

    int side = qMin(w, h);
    glViewport((w - side) / 2, (h - side) / 2, side, side);

}


/*!
 * \brief Odrysowanie kości
 *
 * Odrysowywujemy naszą kość. Kość odrysowywana jest według zadanej rotacji w obiekcie w miejscach:
 * ->\link xRot\endlink - kąt wzdłuż osi OX
 * ->\link yRot\endlink - kąt wzdłuż osi OY
 * ->\link zRot\endlink - kąt wzdłuż osi OZ
 *
 * Następnie włączamy \link PROGRAM_VERTEX_ATTRIBUTE\endlink oraz \link PROGRAM_TEXCOORD_ATTRIBUTE\endlink,
 * ustawiamy buffery dla każdego z nich i wiążemy tekstury każdej ze ścian z zadanymi obrazami.
 */
void WizualizacjaKosc::paintGL()
{
    glClearColor(clearColor.redF(), clearColor.greenF(), clearColor.blueF(), clearColor.alphaF());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    QMatrix4x4 m;
    m.ortho(-0.5f, +0.5f, +0.5f, -0.5f, 4.0f, 15.0f);
    m.translate(0.0f, 0.0f, -10.0f);
    m.rotate(xRot, 1.0f, 0.0f, 0.0f);
    m.rotate(yRot, 0.0f, 1.0f, 0.0f);
    m.rotate(zRot, 0.0f, 0.0f, 1.0f);


    program->setUniformValue("matrix", m);
    program->enableAttributeArray(PROGRAM_VERTEX_ATTRIBUTE);
    program->enableAttributeArray(PROGRAM_TEXCOORD_ATTRIBUTE);
    program->setAttributeBuffer(PROGRAM_VERTEX_ATTRIBUTE, GL_FLOAT, 0, 3, 5 * sizeof(GLfloat));
    program->setAttributeBuffer(PROGRAM_TEXCOORD_ATTRIBUTE, GL_FLOAT, 3 * sizeof(GLfloat), 2, 5 * sizeof(GLfloat));

    for (int i = 0; i < 6; ++i) {
        textury_kosc[i]->bind();
        glDrawArrays(GL_TRIANGLE_FAN, i * 4, 4);
    }



}

/*!
 * \brief Funkcja odpowiedzialna za utworzenie samej kostki
 *
 * Tworzymy naszą kość z koordynatów zadanych w macierzy \link coords\endlink.
 * Rozmiary macierzy - 6 -> 6 ścian, 4 -> krawędzie każda ściany, 3 -> ilość wymiarów.
 * Następnie zapisujemy każdy obrazek do tekstury \link textury_kosc \endlink.
 * Potem tworzymy nasze wektory rozpinające tekstury. Na sam koniec ładujemy wszystko
 * do naszego buffora i wiążemy oraz alokujemy.
 */
void WizualizacjaKosc::utworz_kosc()
{
    static const int coords[6][4][3] = {
            { { +1, -1, -1 }, { -1, -1, -1 }, { -1, +1, -1 }, { +1, +1, -1 } },
            { { +1, +1, -1 }, { -1, +1, -1 }, { -1, +1, +1 }, { +1, +1, +1 } },
            { { +1, -1, +1 }, { +1, -1, -1 }, { +1, +1, -1 }, { +1, +1, +1 } },
            { { -1, -1, -1 }, { -1, -1, +1 }, { -1, +1, +1 }, { -1, +1, -1 } },
            { { +1, -1, +1 }, { -1, -1, +1 }, { -1, -1, -1 }, { +1, -1, -1 } },
            { { -1, -1, +1 }, { +1, -1, +1 }, { +1, +1, +1 }, { -1, +1, +1 } }
        };

        for (int j = 0; j < 6; ++j)
            textury_kosc[j] = new QOpenGLTexture(QImage(QString("%1.png").arg(j + 1)).mirrored());

        QVector<GLfloat> vertData;
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 4; ++j) {
                // vertex position
                vertData.append(0.2 * coords[i][j][0]);
                vertData.append(0.2 * coords[i][j][1]);
                vertData.append(0.2 * coords[i][j][2]);
                // texture coordinate
                vertData.append(j == 0 || j == 3);
                vertData.append(j == 0 || j == 1);
            }
        }

        vbo.create();
        vbo.bind();
        vbo.allocate(vertData.constData(), vertData.count() * sizeof(GLfloat));
}


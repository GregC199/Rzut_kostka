#include "wizualizacjakosc.h"
#include <iostream>
void WizualizacjaKosc::obroc(int x_a, int y_a, int z_a)
{
    this->xRot += x_a;
    this->yRot += y_a;
    this->zRot += z_a;
    normalizuj_kat(this->xRot);
    normalizuj_kat(this->yRot);
    normalizuj_kat(this->zRot);

    okres_zakresy();

    this->paintGL();
    update();
}
QSize WizualizacjaKosc::sizeHint() const
{
    return QSize(200, 200);
}
void WizualizacjaKosc::okres_zakresy(){
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
QSize WizualizacjaKosc::minimumSizeHint() const
{
    return QSize(50, 50);
}
void WizualizacjaKosc::normalizuj_kat(int &kat)
{
    while (kat < 0)
        kat += 360;
    while (kat > 360)
        kat -= 360;
}
void WizualizacjaKosc::obrocX(int val)
{
    Sender = qobject_cast<QSlider *>(sender());
    val = Sender->value();
    normalizuj_kat(val);
    xRot = val;

    x_okresl_zakres();

    this->paintGL();
    update();
}
void WizualizacjaKosc::obrocY(int val)
{
    Sender = qobject_cast<QSlider *>(sender());
    val = Sender->value();
    normalizuj_kat(val);
    yRot = val;

    y_okresl_zakres();

    this->paintGL();
    update();
}
void WizualizacjaKosc::obrocZ(int val)
{
    Sender = qobject_cast<QSlider *>(sender());
    val = Sender->value();
    normalizuj_kat(val);
    zRot = val;

    z_okresl_zakres();

    this->paintGL();
    update();
}
WizualizacjaKosc::~WizualizacjaKosc(){
    makeCurrent();
    vbo.destroy();
    for (int i = 0; i < 6; ++i)
        delete textury_kosc[i];
    delete program;
    doneCurrent();
}

void WizualizacjaKosc::setClearColor(const QColor &color)
{
    clearColor = color;
    this->update();
}

void WizualizacjaKosc::initializeGL()
{
    QColor kolor_tla;

    kolor_tla.setRgb(79,136,201);

    initializeOpenGLFunctions();

    utworz_kosc();

    setClearColor(kolor_tla);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    #define PROGRAM_VERTEX_ATTRIBUTE 0
    #define PROGRAM_TEXCOORD_ATTRIBUTE 1

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

void WizualizacjaKosc::resizeGL(int w, int h)
{

    int side = qMin(w, h);
    glViewport((w - side) / 2, (h - side) / 2, side, side);

}



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


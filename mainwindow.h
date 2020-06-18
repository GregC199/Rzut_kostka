#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

#include <QMainWindow>

//Tworzenie wykresow:
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>
#include <QResizeEvent>
#include <QFont>

//polaczenie z plytka
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothSocket>
#include <QBluetoothLocalDevice>
#include <QDebug>
#include <QDateTime>
#include <QList>

//obsluga operacji na plikach
#include <string>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <math.h>

//kosc
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QtOpenGL>
#include <QOpenGLBuffer>
#include <QSurfaceFormat>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QMouseEvent>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class WizualizacjaKosc;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //tworzenie diody
    void tworz_diode();
    //zmiana kolorow diod
    void zapal_zielone();
    void zapal_czerwone();

    //tworzenie wykresow
    void stworz_wykresy();
    //inicjalizacja obslugi bluetooth
    void obsluga_bt();

    //informacje o nawiazanym polaczeniu
    void inicjalizuj_info();
    void informacje_bluetooth();

    //aktualizacja danych na wykresie
    void aktualizuj_wykres(float a_x,float a_y,float a_z,float g_x,float g_y,double g_z,double rkom,double pkom, unsigned long long czas);

    //wczytanie danych z pliku bedacego logiem polaczenia bluetooth
    void wczytanie_danych_z_logu(unsigned long long czas_zmierzony);

    //kolejne operacje tworzenia wykresow
    void utworz_osie();

    void utworz_serie();

    void utworz_wykresy();

    void wizualizuj_wykresy();

    void przypnij_serie_do_osi();

    //kostka
    void rotuj_kostke(double  xa, double  ya, double  za);
    void przemiesc_kostke();

private slots:

    //aktualizacja obrazku
    void aktualizuj_obraz(int val);

    //obsluga dzialania polaczenia z plytka
    void captureDeviceProperties(const QBluetoothDeviceInfo &device);

    void searchingFinished();

    void on_button_wyszukaj_clicked();
    void on_button_polacz_clicked();
    void on_button_rozlacz_clicked();

    void connectionEstablished();
    void connectionInterrupted();

    void socketReadyToRead();




private:

    //kosc
    WizualizacjaKosc *currentGlWidget;

    float x_mem = 0.0;
    float y_mem = 0.0;
    float z_mem = 0.0;
    QTime dt;
    double x_buff = 0.0;
    double y_buff = 0.0;
    double z_buff = 0.0;

    //obsluga dzialania wykresow
    //wyswietlanie wykresow:
    QChartView* view_acc_wykres_x;
    QChartView* view_acc_wykres_y;
    QChartView* view_acc_wykres_z;
    QChartView* view_gyr_wykres_x;
    QChartView* view_gyr_wykres_y;
    QChartView* view_gyr_wykres_z;

    //serie z wykresow
    QLineSeries* series_acc_wykres_x;
    QLineSeries* series_acc_wykres_y;
    QLineSeries* series_acc_wykres_z;

    QLineSeries* series_gyr_wykres_x;
    QLineSeries* series_kom_wykres_x;

    QLineSeries* series_gyr_wykres_y;
    QLineSeries* series_kom_wykres_y;

    QLineSeries* series_gyr_wykres_z;

    //pomiar czasu
    QTime pomiar;

    //osie czasu
    QValueAxis* timeline_acc_x;
    QValueAxis* timeline_acc_y;
    QValueAxis* timeline_acc_z;
    QValueAxis* timeline_gyr_x;
    QValueAxis* timeline_gyr_y;
    QValueAxis* timeline_gyr_z;

    //osie wartosci
    QValueAxis* acc_x_wartosci_y;
    QValueAxis* acc_y_wartosci_y;
    QValueAxis* acc_z_wartosci_y;
    QValueAxis* gyr_x_wartosci_y;
    QValueAxis* gyr_y_wartosci_y;
    QValueAxis* gyr_z_wartosci_y;


    //wykresy
    QChart* line_acc_wykres_x;
    QChart* line_acc_wykres_y;
    QChart* line_acc_wykres_z;
    QChart* line_gyr_wykres_x;
    QChart* line_gyr_wykres_y;
    QChart* line_gyr_wykres_z;

    //zapis do logu w pliku
    std::ofstream zapis;
    std::ifstream czytanie;

    Ui::MainWindow* ui;

    //aktualizacja logu polaczenia
    void addToLogs(QString message);

    //obsluga bt
    QBluetoothDeviceDiscoveryAgent* discoveryAgent;
    QBluetoothSocket* socket;

    //informacje o bluetooth
    QBluetoothLocalDevice* host;
    QString nazwa_local_host;
    QString adres_local_host;
    QString nazwa_polaczanego;
    QString adres_polaczanego;
    QString uuid_polaczonego;
    QString typ_polaczenia;
    QString data_polaczenia;
protected:

};
#endif // MAINWINDOW_H

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


    /*!
     *
     * \brief Tworzenie diód
     */
    void tworz_diode();
    /*!
     *
     * \brief Zmiana kolorow diód na zielony
     */
    void zapal_zielone();
    /*!
     *
     * \brief Zmiana kolorow diód na czerowny
     */
    void zapal_czerwone();

    /*!
     *
     * \brief Obsługa tworzenia wykresów
     */
    void stworz_wykresy();

    /*!
     *
     * \brief Inicjalizacja obsługi bluetooth
     */
    void obsluga_bt();

    /*!
     *
     * \brief Informacje o nawiązanym połączeniu
     */
    void inicjalizuj_info();

    /*!
     *
     * \brief Szczegóły parametrów połączenia
     */
    void informacje_bluetooth();

    /*!
     *
     * \brief Aktualizacja danych na wykresie
     */
    void aktualizuj_wykres(float a_x,float a_y,float a_z,float g_x,float g_y,double g_z,double rkom,double pkom, unsigned long long czas);

    /*!
     *
     * \brief Wczytanie danych z pliku będącego logiem połączenia bluetooth
     */
    void wczytanie_danych_z_logu(unsigned long long czas_zmierzony);

    /*!
     *
     * \brief Utworzenie osi do wykresów
     */
    void utworz_osie();
    /*!
     *
     * \brief Utworzenie serii do wykresów
     */
    void utworz_serie();

    /*!
     *
     * \brief Utworzenie wykresów
     */
    void utworz_wykresy();

    /*!
     *
     * \brief Utworzenie wizualizacji do wykresów
     */
    void wizualizuj_wykresy();

    /*!
     *
     * \brief Przypięcie wartości serii do osi wykresów
     */
    void przypnij_serie_do_osi();

    /*!
     *
     * \brief Obrót kości o kąty xa, ya, za
     */
    void rotuj_kostke(double  xa, double  ya, double  za);
    /*!
     *
     * \brief Niedokończone - służy za przemieszczenie kostki
     */
    void przemiesc_kostke();

    /*!
     *
     * \param Niedokończone - służy za przemieszczenie kostki
     */
    int mem_rzut = 0;

private slots:

    /*!
     *
     * \brief Aktualizuje obraz Wartość rzutu i lcd Rzut poprzedni
     */
    void aktualizuj_obraz(int val);

    /*!
     *
     * \brief Slot odpowiedzialny za przechwycenie informacji na temat wykrywtego urządzenia
     *
     */
    void captureDeviceProperties(const QBluetoothDeviceInfo &device);

    /*!
     * \brief Slot odpowiedzialny za przechwycenie sygnału zakończenia wyszukiwania
     */
    void searchingFinished();

    /*!
     * \brief Slot odpowiedzialny za obsługę wyszukiwania urządzeń
     */
    void on_button_wyszukaj_clicked();
    /*!
     * \brief Slot odpowiedzialny za przechwycenie sygnału inicjacji połączenia
     */
    void on_button_polacz_clicked();
    /*!
     * \brief Slot odpowiedzialny za przechwycenie sygnału wywołania zakończenia połączenia
     */
    void on_button_rozlacz_clicked();
    /*!
     * \brief Slot nawiązania połączenia
     */
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

    void zmien_lcd(int wartosc);

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

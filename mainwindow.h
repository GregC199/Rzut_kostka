#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

//Tworzenie wykresow:
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>
#include <QResizeEvent>

//polaczenie z plytka
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothSocket>
#include <QDebug>
#include <QDateTime>
#include <QList>
#include <string>
#include <iostream>
#include <stdio.h>
#include <fstream>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void stworz_wykresy();
    void obsluga_bt();
    void aktualizuj_wykres(float a_x,float a_y,float a_z,float g_x,float g_y,float g_z,float rkom,float pkom, unsigned long long czas);
    void wczytanie_danych_z_logu(unsigned long long czas_zmierzony);

private slots:

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

    //os czasu
    QTime pomiar;

    QValueAxis* timeline_acc_x;
    QValueAxis* timeline_acc_y;
    QValueAxis* timeline_acc_z;
    QValueAxis* timeline_gyr_x;
    QValueAxis* timeline_gyr_y;
    QValueAxis* timeline_gyr_z;

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
    void addToLogs(QString message);
    QBluetoothDeviceDiscoveryAgent* discoveryAgent;
    QBluetoothSocket* socket;
protected:
    void resizeEvent(QResizeEvent* event);
};
#endif // MAINWINDOW_H

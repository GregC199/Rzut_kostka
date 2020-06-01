#include "mainwindow.h"

void MainWindow::utworz_osie(){
    //tworzenie osi czasu acc x,y,z
    this->timeline_acc_x = new QValueAxis;
    this->timeline_acc_x->setLabelFormat("%.2f");
    this->timeline_acc_x->setRange(0,10);
    this->timeline_acc_x->setTickCount(6);


    this->timeline_acc_y = new QValueAxis;
    this->timeline_acc_y->setLabelFormat("%.2f");
    this->timeline_acc_y->setRange(0,10);
    this->timeline_acc_y->setTickCount(6);


    this->timeline_acc_z = new QValueAxis;
    this->timeline_acc_z->setLabelFormat("%.2f");
    this->timeline_acc_z->setRange(0,10);
    this->timeline_acc_z->setTickCount(6);

    //tworzenie osi czasu gyr x,y,z
    this->timeline_gyr_x = new QValueAxis;
    this->timeline_gyr_x->setLabelFormat("%.2f");
    this->timeline_gyr_x->setRange(0,10);
    this->timeline_gyr_x->setTickCount(6);


    this->timeline_gyr_y = new QValueAxis;
    this->timeline_gyr_y->setLabelFormat("%.2f");
    this->timeline_gyr_y->setRange(0,10);
    this->timeline_gyr_y->setTickCount(6);


    this->timeline_gyr_z = new QValueAxis;
    this->timeline_gyr_z->setLabelFormat("%.2f");
    this->timeline_gyr_z->setRange(0,10);
    this->timeline_gyr_z->setTickCount(6);


    //tworzenie osi wartosci acc x,y,z
    this->acc_x_wartosci_y = new QValueAxis;
    this->acc_x_wartosci_y->setLabelFormat("%.3f");
    this->acc_x_wartosci_y->setRange(-4,4);
    this->acc_x_wartosci_y->setTickCount(9);


    this->acc_y_wartosci_y = new QValueAxis;
    this->acc_y_wartosci_y->setLabelFormat("%.3f");
    this->acc_y_wartosci_y->setRange(-4,4);
    this->acc_y_wartosci_y->setTickCount(9);


    this->acc_z_wartosci_y = new QValueAxis;
    this->acc_z_wartosci_y->setLabelFormat("%.3f");
    this->acc_z_wartosci_y->setRange(-4,4);
    this->acc_z_wartosci_y->setTickCount(9);


    //tworzenie osi wartosci gyr x,y,z
    this->gyr_x_wartosci_y = new QValueAxis;
    this->gyr_x_wartosci_y->setLabelFormat("%.2f");
    this->gyr_x_wartosci_y->setRange(-360,360);
    this->gyr_x_wartosci_y->setTickCount(9);

    this->gyr_y_wartosci_y = new QValueAxis;
    this->gyr_y_wartosci_y->setLabelFormat("%.2f");
    this->gyr_y_wartosci_y->setRange(-360,360);
    this->gyr_y_wartosci_y->setTickCount(9);

    this->gyr_z_wartosci_y = new QValueAxis;
    this->gyr_z_wartosci_y->setLabelFormat("%.2f");
    this->gyr_z_wartosci_y->setRange(-360,360);
    this->gyr_z_wartosci_y->setTickCount(9);
}

void MainWindow::utworz_serie(){
    //tworzenie serii
    //acc x,y,z
    this->series_acc_wykres_x = new QLineSeries();
    this->series_acc_wykres_x->append(0,0);

    this->series_acc_wykres_y = new QLineSeries();
    this->series_acc_wykres_y->append(0,0);

    this->series_acc_wykres_z = new QLineSeries();
    this->series_acc_wykres_z->append(0,0);

    //gyr x, roll, y, pitch, z
    this->series_gyr_wykres_x = new QLineSeries();
    this->series_gyr_wykres_x->append(0,0);

    this->series_kom_wykres_x = new QLineSeries();
    this->series_kom_wykres_x->append(0,0);

    this->series_gyr_wykres_y = new QLineSeries();
    this->series_gyr_wykres_y->append(0,0);


    this->series_kom_wykres_y = new QLineSeries();
    this->series_kom_wykres_y->append(0,0);

    this->series_gyr_wykres_z = new QLineSeries();
    this->series_gyr_wykres_z->append(0,0);
}

void MainWindow::utworz_wykresy(){
    //stworzenie wykresu liniowego z serii - acc_x
    this->line_acc_wykres_x = new QChart();

    //dodanie osi
    this->line_acc_wykres_x->addAxis(acc_x_wartosci_y,Qt::AlignLeft);
    this->line_acc_wykres_x->addAxis(this->timeline_acc_x,Qt::AlignBottom);

    //dodanie serii danych
    this->line_acc_wykres_x->addSeries(this->series_acc_wykres_x);

    //dodanie tytulu wykresu
    this->line_acc_wykres_x->setTitle("Zczytania wzdłuż osi X");

    //wylaczenie legendy
    this->line_acc_wykres_x->legend()->hide();



    //kolejne tworzenia wykresow liniowych dla kolejnych zczytan osi - acc_y
    this->line_acc_wykres_y = new QChart();

    this->line_acc_wykres_y->addAxis(acc_y_wartosci_y,Qt::AlignLeft);
    this->line_acc_wykres_y->addAxis(this->timeline_acc_y,Qt::AlignBottom);

    this->line_acc_wykres_y->addSeries(this->series_acc_wykres_y);

    this->line_acc_wykres_y->setTitle("Zczytania wzdłuż osi Y");

    this->line_acc_wykres_y->legend()->hide();



    //acc_z
    this->line_acc_wykres_z = new QChart();

    this->line_acc_wykres_z->addAxis(acc_z_wartosci_y,Qt::AlignLeft);
    this->line_acc_wykres_z->addAxis(this->timeline_acc_z,Qt::AlignBottom);

    this->line_acc_wykres_z->addSeries(this->series_acc_wykres_z);

    this->line_acc_wykres_z->setTitle("Zczytania wzdłuż osi Z");

    this->line_acc_wykres_z->legend()->hide();



    //gyr_x
    this->line_gyr_wykres_x = new QChart();

    this->line_gyr_wykres_x->addAxis(gyr_x_wartosci_y,Qt::AlignLeft);
    this->line_gyr_wykres_x->addAxis(this->timeline_gyr_x,Qt::AlignBottom);

    this->line_gyr_wykres_x->addSeries(this->series_gyr_wykres_x);
    this->line_gyr_wykres_x->addSeries(this->series_kom_wykres_x);

    this->line_gyr_wykres_x->setTitle("Zczytania wzdłuż osi X");

    this->line_gyr_wykres_x->legend()->hide();




    //gyr_y
    this->line_gyr_wykres_y = new QChart();

    this->line_gyr_wykres_y->addAxis(gyr_y_wartosci_y,Qt::AlignLeft);
    this->line_gyr_wykres_y->addAxis(this->timeline_gyr_y,Qt::AlignBottom);

    this->line_gyr_wykres_y->addSeries(this->series_gyr_wykres_y);
    this->line_gyr_wykres_y->addSeries(this->series_kom_wykres_y);

    this->line_gyr_wykres_y->setTitle("Zczytania wzdłuż osi Y");

    this->line_gyr_wykres_y->legend()->hide();




    //gyr_z
    this->line_gyr_wykres_z = new QChart();

    this->line_gyr_wykres_z->addAxis(gyr_z_wartosci_y,Qt::AlignLeft);
    this->line_gyr_wykres_z->addAxis(this->timeline_gyr_z,Qt::AlignBottom);

    this->line_gyr_wykres_z->addSeries(this->series_gyr_wykres_z);

    this->line_gyr_wykres_z->setTitle("Zczytania wzdłuż osi Z");

    this->line_gyr_wykres_z->legend()->hide();
}

void MainWindow::wizualizuj_wykresy(){

    //wyswietlanie utworzonych wykresow - acc_x
    this->view_acc_wykres_x = new QChartView(this->line_acc_wykres_x);
    this->view_acc_wykres_x->setRenderHint(QPainter::Antialiasing);
    this->view_acc_wykres_x->setParent(ui->acc_wykres_x);

    //acc_y
    this->view_acc_wykres_y = new QChartView(this->line_acc_wykres_y);
    this->view_acc_wykres_y->setRenderHint(QPainter::Antialiasing);
    this->view_acc_wykres_y->setParent(ui->acc_wykres_y);

    //acc_z
    this->view_acc_wykres_z = new QChartView(this->line_acc_wykres_z);
    this->view_acc_wykres_z->setRenderHint(QPainter::Antialiasing);
    this->view_acc_wykres_z->setParent(ui->acc_wykres_z);

    //gyr_x
    this->view_gyr_wykres_x = new QChartView(this->line_gyr_wykres_x);
    this->view_gyr_wykres_x->setRenderHint(QPainter::Antialiasing);
    this->view_gyr_wykres_x->setParent(ui->gyr_wykres_x);

    //gyr_y
    this->view_gyr_wykres_y = new QChartView(this->line_gyr_wykres_y);
    this->view_gyr_wykres_y->setRenderHint(QPainter::Antialiasing);
    this->view_gyr_wykres_y->setParent(ui->gyr_wykres_y);

    //gyr_z
    this->view_gyr_wykres_z = new QChartView(this->line_gyr_wykres_z);
    this->view_gyr_wykres_z->setRenderHint(QPainter::Antialiasing);
    this->view_gyr_wykres_z->setParent(ui->gyr_wykres_z);
}

void MainWindow::przypnij_serie_do_osi(){
    //laczenie osi czasu z seriami danych
    this->series_acc_wykres_x->attachAxis(this->timeline_acc_x);
    this->series_acc_wykres_y->attachAxis(this->timeline_acc_y);
    this->series_acc_wykres_z->attachAxis(this->timeline_acc_z);
    this->series_gyr_wykres_x->attachAxis(this->timeline_gyr_x);
    this->series_kom_wykres_x->attachAxis(this->timeline_gyr_x);
    this->series_gyr_wykres_y->attachAxis(this->timeline_gyr_y);
    this->series_kom_wykres_y->attachAxis(this->timeline_gyr_y);
    this->series_gyr_wykres_z->attachAxis(this->timeline_gyr_z);

    //laczenie osi wartosci z seriami danych
    this->series_acc_wykres_x->attachAxis(acc_x_wartosci_y);
    this->series_acc_wykres_y->attachAxis(acc_y_wartosci_y);
    this->series_acc_wykres_z->attachAxis(acc_z_wartosci_y);
    this->series_gyr_wykres_x->attachAxis(gyr_x_wartosci_y);
    this->series_kom_wykres_x->attachAxis(gyr_x_wartosci_y);
    this->series_gyr_wykres_y->attachAxis(gyr_y_wartosci_y);
    this->series_kom_wykres_y->attachAxis(gyr_y_wartosci_y);
    this->series_gyr_wykres_z->attachAxis(gyr_z_wartosci_y);
}

void MainWindow::stworz_wykresy(){

    this->utworz_serie();

    this->utworz_osie();

    this->utworz_wykresy();

    this->przypnij_serie_do_osi();

    this->wizualizuj_wykresy();

    //dostosowanie startowego rozmiaru wykresow - acc
    ui->acc_wykres_x->setGeometry(12,30,274,211);
    ui->acc_wykres_y->setGeometry(292,30,274,211);
    ui->acc_wykres_z->setGeometry(572,30,274,211);

    //gyr
    ui->gyr_wykres_x->setGeometry(12,30,274,210);
    ui->gyr_wykres_y->setGeometry(292,30,274,210);
    ui->gyr_wykres_z->setGeometry(572,30,274,210);


}

#include "mainwindow.h"
/*!
 *
 * \brief Utworzenie osi do wykresów
 *
 * Funkcja tworzące osie. Ustawia zakresy odpowiednie dla każdej z osi oraz zmienia
 * domyślną czcionę dla osi danych na mniejszą.
 */
void MainWindow::utworz_osie(){

    //zmiana rozmiarow czcionki w celu poprawienia widoczności wartości na osiach
    QFont czcionka_osi;
    czcionka_osi.setPixelSize(9);

    //tworzenie osi czasu acc x,y,z
    this->timeline_acc_x = new QValueAxis;
    this->timeline_acc_x->setLabelFormat("%.2f");
    this->timeline_acc_x->setRange(0,10);
    this->timeline_acc_x->setTickCount(6);
    this->timeline_acc_x->setLabelsFont(czcionka_osi);


    this->timeline_acc_y = new QValueAxis;
    this->timeline_acc_y->setLabelFormat("%.2f");
    this->timeline_acc_y->setRange(0,10);
    this->timeline_acc_y->setTickCount(6);
    this->timeline_acc_y->setLabelsFont(czcionka_osi);


    this->timeline_acc_z = new QValueAxis;
    this->timeline_acc_z->setLabelFormat("%.2f");
    this->timeline_acc_z->setRange(0,10);
    this->timeline_acc_z->setTickCount(6);
    this->timeline_acc_z->setLabelsFont(czcionka_osi);

    //tworzenie osi czasu gyr x,y,z
    this->timeline_gyr_x = new QValueAxis;
    this->timeline_gyr_x->setLabelFormat("%.2f");
    this->timeline_gyr_x->setRange(0,10);
    this->timeline_gyr_x->setTickCount(6);
    this->timeline_gyr_x->setLabelsFont(czcionka_osi);


    this->timeline_gyr_y = new QValueAxis;
    this->timeline_gyr_y->setLabelFormat("%.2f");
    this->timeline_gyr_y->setRange(0,10);
    this->timeline_gyr_y->setTickCount(6);
    this->timeline_gyr_y->setLabelsFont(czcionka_osi);


    this->timeline_gyr_z = new QValueAxis;
    this->timeline_gyr_z->setLabelFormat("%.2f");
    this->timeline_gyr_z->setRange(0,10);
    this->timeline_gyr_z->setTickCount(6);
    this->timeline_gyr_z->setLabelsFont(czcionka_osi);


    //tworzenie osi wartosci acc x,y,z
    this->acc_x_wartosci_y = new QValueAxis;
    this->acc_x_wartosci_y->setLabelFormat("%.3f");
    this->acc_x_wartosci_y->setRange(-4,4);
    this->acc_x_wartosci_y->setTickCount(9);
    this->acc_x_wartosci_y->setLabelsFont(czcionka_osi);


    this->acc_y_wartosci_y = new QValueAxis;
    this->acc_y_wartosci_y->setLabelFormat("%.3f");
    this->acc_y_wartosci_y->setRange(-4,4);
    this->acc_y_wartosci_y->setTickCount(9);
    this->acc_y_wartosci_y->setLabelsFont(czcionka_osi);


    this->acc_z_wartosci_y = new QValueAxis;
    this->acc_z_wartosci_y->setLabelFormat("%.3f");
    this->acc_z_wartosci_y->setRange(-4,4);
    this->acc_z_wartosci_y->setTickCount(9);
    this->acc_z_wartosci_y->setLabelsFont(czcionka_osi);


    //tworzenie osi wartosci gyr x,y,z
    this->gyr_x_wartosci_y = new QValueAxis;
    this->gyr_x_wartosci_y->setLabelFormat("%.2f");
    this->gyr_x_wartosci_y->setRange(-360,360);
    this->gyr_x_wartosci_y->setTickCount(9);
    this->gyr_x_wartosci_y->setLabelsFont(czcionka_osi);

    this->gyr_y_wartosci_y = new QValueAxis;
    this->gyr_y_wartosci_y->setLabelFormat("%.2f");
    this->gyr_y_wartosci_y->setRange(-360,360);
    this->gyr_y_wartosci_y->setTickCount(9);
    this->gyr_y_wartosci_y->setLabelsFont(czcionka_osi);

    this->gyr_z_wartosci_y = new QValueAxis;
    this->gyr_z_wartosci_y->setLabelFormat("%.2f");
    this->gyr_z_wartosci_y->setRange(-360,360);
    this->gyr_z_wartosci_y->setTickCount(9);
    this->gyr_z_wartosci_y->setLabelsFont(czcionka_osi);
}
/*!
 *
 * \brief Utworzenie serii do wykresów
 *
 * Funkcja tworząca serie danych dla każdego typu zczytywanych danych oraz
 * dodająca punkty (0,0) na początek wykresu.
 */
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
/*!
 *
 * \brief Utworzenie wykresów
 *
 * Funkcja tworząca wykresy dla trzech osi akcelerometru i trzech osi żyroskopu.
 * Każdy z wykresów ma nadawany tytuł, dodawane serie danych, osie oraz
 * ukrywane legendy w celu poprawienia widoczności.
 */
void MainWindow::utworz_wykresy(){
    //stworzenie wykresu liniowego z serii - acc_x
    this->line_acc_wykres_x = new QChart();

    //dodanie osi
    this->line_acc_wykres_x->addAxis(acc_x_wartosci_y,Qt::AlignLeft);
    this->line_acc_wykres_x->addAxis(this->timeline_acc_x,Qt::AlignBottom);

    //dodanie serii danych
    this->line_acc_wykres_x->addSeries(this->series_acc_wykres_x);

    //dodanie tytulu wykresu
    this->line_acc_wykres_x->setTitle("Zczytania wzdłuż osi Ox");

    //wylaczenie legendy
    this->line_acc_wykres_x->legend()->hide();



    //kolejne tworzenia wykresow liniowych dla kolejnych zczytan osi - acc_y
    this->line_acc_wykres_y = new QChart();

    this->line_acc_wykres_y->addAxis(acc_y_wartosci_y,Qt::AlignLeft);
    this->line_acc_wykres_y->addAxis(this->timeline_acc_y,Qt::AlignBottom);

    this->line_acc_wykres_y->addSeries(this->series_acc_wykres_y);

    this->line_acc_wykres_y->setTitle("Zczytania wzdłuż osi Oy");

    this->line_acc_wykres_y->legend()->hide();



    //acc_z
    this->line_acc_wykres_z = new QChart();

    this->line_acc_wykres_z->addAxis(acc_z_wartosci_y,Qt::AlignLeft);
    this->line_acc_wykres_z->addAxis(this->timeline_acc_z,Qt::AlignBottom);

    this->line_acc_wykres_z->addSeries(this->series_acc_wykres_z);

    this->line_acc_wykres_z->setTitle("Zczytania wzdłuż osi Oz");

    this->line_acc_wykres_z->legend()->hide();



    //gyr_x
    this->line_gyr_wykres_x = new QChart();

    this->line_gyr_wykres_x->addAxis(gyr_x_wartosci_y,Qt::AlignLeft);
    this->line_gyr_wykres_x->addAxis(this->timeline_gyr_x,Qt::AlignBottom);

    this->line_gyr_wykres_x->addSeries(this->series_gyr_wykres_x);
    this->line_gyr_wykres_x->addSeries(this->series_kom_wykres_x);

    this->line_gyr_wykres_x->setTitle("Zczytania wzdłuż osi Ox");

    this->line_gyr_wykres_x->legend()->hide();




    //gyr_y
    this->line_gyr_wykres_y = new QChart();

    this->line_gyr_wykres_y->addAxis(gyr_y_wartosci_y,Qt::AlignLeft);
    this->line_gyr_wykres_y->addAxis(this->timeline_gyr_y,Qt::AlignBottom);

    this->line_gyr_wykres_y->addSeries(this->series_gyr_wykres_y);
    this->line_gyr_wykres_y->addSeries(this->series_kom_wykres_y);

    this->line_gyr_wykres_y->setTitle("Zczytania wzdłuż osi Oy");

    this->line_gyr_wykres_y->legend()->hide();




    //gyr_z
    this->line_gyr_wykres_z = new QChart();

    this->line_gyr_wykres_z->addAxis(gyr_z_wartosci_y,Qt::AlignLeft);
    this->line_gyr_wykres_z->addAxis(this->timeline_gyr_z,Qt::AlignBottom);

    this->line_gyr_wykres_z->addSeries(this->series_gyr_wykres_z);

    this->line_gyr_wykres_z->setTitle("Zczytania wzdłuż osi Oz");

    this->line_gyr_wykres_z->legend()->hide();
}
/*!
 *
 * \brief Utworzenie wizualizacji do wykresów
 *
 * Na podstawie wcześniej utworzonych wykresów tworzona jeszcze jest ich wizualizacja.
 * W tym celu zadajemy każdemu z wykresów odpowiedniego rodzica z ui.
 */
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
/*!
 *
 * \brief Przypięcie wartości serii do osi wykresów
 *
 * Przypina każdą z serii danych do wpierw osi czasu a potem osi wartości.
 */
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
/*!
 *
 * \brief Obsługa tworzenia wykresów
 *
 * Wywołuje funkcje odpowiedzialne za kolejno:
 * ->tworzenie serii \link utworz_serie \endlink,
 * ->tworzenie osi \link utworz_osie \endlink,
 * ->tworzenie wykresów \link utworz_wykresy \endlink,
 * ->przypięcie serii danych do osi \link przypnij_serie_do_osi \endlink,
 * ->wizualizację wykresów \link wizualizuj_wykresy \endlink.
 *
 * Na sam koniec zadaje początkowe rozmiary wykresom.
 */
void MainWindow::stworz_wykresy(){

    this->utworz_serie();

    this->utworz_osie();

    this->utworz_wykresy();

    this->przypnij_serie_do_osi();

    this->wizualizuj_wykresy();

    //dostosowanie startowego rozmiaru wykresow - acc
    ui->acc_wykres_x->setGeometry(9,9,256,192);
    ui->acc_wykres_y->setGeometry(9,9,256,192);
    ui->acc_wykres_z->setGeometry(9,9,256,192);

    //gyr
    ui->gyr_wykres_x->setGeometry(9,9,256,192);
    ui->gyr_wykres_y->setGeometry(9,9,256,192);
    ui->gyr_wykres_z->setGeometry(9,9,256,192);


}

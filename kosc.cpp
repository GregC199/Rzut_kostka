#include "mainwindow.h"
#include <QPixmap>




/*!

 * \brief Aktualizuje obraz Wartość rzutu i lcd Rzut poprzedni
 *
 * Slot aktualizujący obraz wartość rzutu na podstawie
 * wyemitowanego sygnału poprzez klasę \link WizualizacjaKosc \endlink
 * a dokładnie poprzez \link WizualizacjaKosc::emituj_zmiane_sciany(int value) \endlink
 *
 * Obraz aktualizowany jest za pomocą plików x.png, gdzie:
 * x -> odpowiada liczbie wyrzuconych oczek.
 *
 */
void MainWindow::aktualizuj_obraz(int val){

    QString url;



    switch(val){

        case 1:{
            url = "1.png";
            QPixmap img(url);
            ui->obraz->setPixmap(img);
            break;
        };
        case 2:{
            url = "2.png";
            QPixmap img(url);
            ui->obraz->setPixmap(img);
            break;
        };
        case 3:{
            url = "3.png";
            QPixmap img(url);
            ui->obraz->setPixmap(img);
            break;
        };
        case 4:{
            url = "4.png";
            QPixmap img(url);
            ui->obraz->setPixmap(img);
            break;
        }
        case 5:{
            url = "5.png";
            QPixmap img(url);
            ui->obraz->setPixmap(img);
            break;
        }

        case 6:{
            url = "6.png";
            QPixmap img(url);
            ui->obraz->setPixmap(img);
            break;
        }

        default:{
            url = "1.png";
            QPixmap img(url);
            ui->obraz->setPixmap(img);
            break;
        }

    }
    zmien_lcd(val);
    this->mem_rzut = val;
}

/*!
 *
 * \brief Zmiana wartości poprzedniego rzutu
 *
 * Kompiler nie pozwalał umieścić linijki poniżej wewnątrz slotu.
 * Aktualizuje liczbe wyswietlana przez lcd
 */
void MainWindow::zmien_lcd(int wartosc){
    ui->lcdNumber->display(mem_rzut);
}


/*!
 *
 * \brief Obrót kości o kąty xa, ya, za
 *
 * Funkcja realizująca obrót kości na podstawie zczytań z żyroskopu/filtru komplementarnego.
 * W celu obniżenia częstotliwości szumów i drgań zastosowano buffory dla każdej z osi.
 */
void MainWindow::rotuj_kostke(double xa, double ya, double za){

    //zmienne służące za wysłanie wartości obrotu
    int obrot_x = 0;
    int obrot_y = 0;
    int obrot_z = 0;

    //obliczenie delty czasu pomiędzy kolejnym odświeżeniem danych
    int test = dt.restart();
    std::cout << "dt: "<<test<<std::endl;

    //przekształcenie wartości na sekundy
    double pomiar = (test)/1000.0;

    //dodanie różnicy wartości do bufora
    this->x_buff += (xa - x_mem) * pomiar*180;
    this->y_buff += (ya - y_mem) * pomiar*180;
    this->z_buff += (za - z_mem) * pomiar*180;


    //obsługa buforów - przepełnienie co 2 lub -2
    if(x_buff > 2 || x_buff < -2){
        obrot_x = floor(x_buff);
        x_buff -= obrot_x;
    }
    if(y_buff > 2 || y_buff < -2){
        obrot_y = floor(y_buff);
        y_buff -= obrot_y;
    }
    if(z_buff > 2 || z_buff < -2){
        obrot_z = floor(z_buff);
        z_buff -= obrot_z;
    }

    //sprawdzenie czy nasz widget odpowiedzialny za wizualizację kości dalej istnieje i wykonanie obrotu
    if (currentGlWidget)currentGlWidget->obroc(obrot_x,obrot_y,obrot_z);


    //zapis wartości zczytań z każdej z osi do pamięci
    this->x_mem = xa;
    this->y_mem = ya;
    this->z_mem = za;


}
/*!
 *
 * \brief Niedokończone -> służy za przemieszczenie kostki
 *
 * Prototyp niedokończonej funkcji odpowiedzialnej za przemieszczanie wizualizacji kostki.
 *
 */
void MainWindow::przemiesc_kostke(){

}

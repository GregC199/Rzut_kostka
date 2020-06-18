#include "mainwindow.h"
#include <QPixmap>
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
            url = "none.png";
            QPixmap img(url);
            ui->obraz->setPixmap(img);
            break;
        }

    }
}
void MainWindow::rotuj_kostke(double xa, double ya, double za){

    /*if (currentGlWidget)
        currentGlWidget->obroc(+2 * 16, +2 * 16, -1 * 16);*/
    int obrot_x = 0;
    int obrot_y = 0;
    int obrot_z = 0;

    int test = dt.restart();
    std::cout << "dt: "<<test<<std::endl;

    double pomiar = (test)/1000.0;

    std::cout << "pomiar: "<<pomiar<<std::endl;


    this->x_buff += (xa - x_mem) * pomiar*360;
    this->y_buff += (ya - y_mem) * pomiar*360;
    this->z_buff += (za - z_mem) * pomiar*360;

    std::cout << "buff x: "<<x_buff <<std::endl;

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

    std::cout << "obroty: x:"<<obrot_x<<" y:" <<obrot_y<<" z:"<<obrot_z<< std::endl;

    if (currentGlWidget)currentGlWidget->obroc(obrot_x,obrot_y,obrot_z);


    this->x_mem = xa;
    this->y_mem = ya;
    this->z_mem = za;


}

void MainWindow::przemiesc_kostke(){

}

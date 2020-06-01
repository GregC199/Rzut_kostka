#include "mainwindow.h"


void MainWindow::tworz_diode(){

    //dioda 1 - tab "menu glowne"
    ui->diodaL->setFixedHeight(100);
    ui->diodaP->setFixedWidth(100);

    //dioda 2 - tab "status polaczenia"
    ui->dioda2L->setFixedHeight(100);
    ui->dioda2P->setFixedWidth(100);

    //utworzenie ksztaltu kola
    QRect ksztalt(0,0,95,95);
    QRegion kolo(ksztalt, QRegion::Ellipse);

    //nadanie ksztaltu kola diodom
    ui->diodaL->setMask(kolo);
    ui->diodaP->setMask(kolo);

    ui->dioda2L->setMask(kolo);
    ui->dioda2P->setMask(kolo);

    //zapalenie czerwonej diody
    zapal_czerwone();
}

void MainWindow::zapal_czerwone(){

    //dioda prawa ustawienie koloru
    ui->diodaP->setStyleSheet("QPushButton:flat { color: rgb(255, 0, 0); background-color: rgb(255, 0, 0); border: none;}");
    ui->dioda2P->setStyleSheet("QPushButton:flat { color: rgb(255, 0, 0); background-color: rgb(255, 0, 0); border: none;}");

    //dioda lewa ustawienie koloru
    ui->diodaL->setStyleSheet("QPushButton:flat { color: rgb(189, 189, 189); background-color: rgb(189, 189, 189); border: none;}");
    ui->dioda2L->setStyleSheet("QPushButton:flat { color: rgb(189, 189, 189); background-color: rgb(189, 189, 189); border: none;}");

}

void MainWindow::zapal_zielone(){

    //dioda prawa ustawienie koloru
    ui->diodaP->setStyleSheet("QPushButton:flat { color: rgb(189, 189, 189); background-color: rgb(189, 189, 189); border: none; }");
    ui->dioda2P->setStyleSheet("QPushButton:flat { color: rgb(189, 189, 189); background-color: rgb(189, 189, 189); border: none; }");

    //dioda lewa ustawienie koloru
    ui->diodaL->setStyleSheet("QPushButton:flat { color: rgb(38, 255, 0); background-color: rgb(38, 255, 0);  border: none; }");
    ui->dioda2L->setStyleSheet("QPushButton:flat { color: rgb(38, 255, 0); background-color: rgb(38, 255, 0);  border: none; }");

}

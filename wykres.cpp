#include "wykres.h"

Wykres::Wykres(QWidget *parent) : QWidget(parent)
{

}
void Wykres::resizeEvent(QResizeEvent* event){

    QWidget::resizeEvent(event);
    this->zmiana_rozmiaru = this->findChild<QChartView*>();
    this->zmiana_rozmiaru->resize(this->size());
}

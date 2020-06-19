#include "wykres.h"

Wykres::Wykres(QWidget *parent) : QWidget(parent)
{

}
/*!
 * \brief Reimplementacja resizeEvent QWidgetu
 *
 * W celu utworzenia skalujących się wykresów należało zaimplementować resize
 * dziecka - tudzież QChartView - wewnątrz rodzica.
 */
void Wykres::resizeEvent(QResizeEvent* event){

    QWidget::resizeEvent(event);
    this->zmiana_rozmiaru = this->findChild<QChartView*>();
    this->zmiana_rozmiaru->resize(this->size());
}

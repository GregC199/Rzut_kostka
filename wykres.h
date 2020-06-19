#ifndef WYKRES_H
#define WYKRES_H

#include <QWidget>
#include <QChartView>
#include <QtCharts>

/*!
 * \brief Implementacja klasy \link Wykresy\endlink dziedziczącej klasę QWidget
 *
 */
class Wykres : public QWidget
{
    Q_OBJECT
public:
    explicit Wykres(QWidget *parent = nullptr);
protected:
    /*!
     * \brief Reimplementacja resizeEvent QWidgetu
     *
     */
    void resizeEvent(QResizeEvent* event);

signals:

private:
    /*!
     * \brief Zmienna służąca do przechowywania wskaźnika na dziecko
     */
    QChartView* zmiana_rozmiaru;

public slots:
};

#endif // WYKRES_H

#ifndef WYKRES_H
#define WYKRES_H

#include <QWidget>
#include <QChartView>
#include <QtCharts>

class Wykres : public QWidget
{
    Q_OBJECT
public:
    explicit Wykres(QWidget *parent = nullptr);
protected:
    void resizeEvent(QResizeEvent* event);

signals:

private:
    QChartView* zmiana_rozmiaru;

public slots:
};

#endif // WYKRES_H
